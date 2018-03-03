// Physical component dependency
#include "scriptmanager.h"

// Game lib dependencies
#include <agk.h>
#include <utilities\exceptionhandling.h>
#include <utilities\generalfuncs.h>
#include <utilities\jsonparsehelper.h>
#include <script\scriptglobals.h>
#include <script\animationdata.h>

// Boost lib dependencies
#include <boost/format.hpp>

// Standard lib dependencies
#include <cstring>
#include <fstream>

// AngelScript lib dependencies
#include <angelscript.h>

using namespace std;
using namespace nlohmann;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CScriptManager::CScriptManager()
{
    try
    {
        // Create the script engine
        _pScriptEngine = asCreateScriptEngine( ANGELSCRIPT_VERSION );
        if( !_pScriptEngine )
            throw NExcept::CCriticalException( "Error",
                                               "CScriptManager::CScriptManager()",
                                               "AngelScript engine could not be created." );

        // We don't use call backs for every line execution so set this property to not build with line cues
        _pScriptEngine->SetEngineProperty( asEP_BUILD_WITHOUT_LINE_CUES, true );

        // Set the message callback to print the messages that the engine gives in case of errors
        if( _pScriptEngine->SetMessageCallback( asMETHOD( CScriptManager, MessageCallback ), this, asCALL_THISCALL ) < 0 )
            throw NExcept::CCriticalException( "Error",
                                               "CScriptManager::CScriptManager()",
                                               "AngelScript message callback could not be created." );

        // Create the script module. I think I'll only need one.
        _pScriptModule = _pScriptEngine->GetModule( "module", asGM_CREATE_IF_NOT_EXISTS );
        if( _pScriptModule == nullptr )
            throw NExcept::CCriticalException( "Error",
                                               "CScriptManager::CScriptManager()",
                                               "Could not create the script module." );
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CScriptManager::CScriptManager()",
                                           "Failed to create script manager.", e );
    }
}


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CScriptManager::~CScriptManager()
{
    Clear();

    _pScriptEngine->Release();
    _pScriptEngine = nullptr;
}


/// *************************************************************************
/// <summary> 
/// Free all of the scripts.
/// </summary>
/// *************************************************************************
void CScriptManager::Clear()
{
    // Reset the id for each file list to indicate it hasn't been loaded.
    for( auto & iter : _scriptFileList )
        iter.second.id = 0;

    // Release the context pool
    for( auto iter : _pInactiveContextList )
        iter->Release();

    for( auto iter : _pActiveContextList )
        iter->Release();

    // Discard the module and free its memory.
    _pScriptModule->Discard();
    _pScriptModule = nullptr;

    // Clear the functions from the list.
    _pScriptFunctionList.clear();
    _pInactiveContextList.clear();
    _pActiveContextList.clear();
}


/// *************************************************************************
/// <summary> 
/// Locate the folder and compile the list of script files.
/// </summary>
/// *************************************************************************
void CScriptManager::LoadScriptList( const string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _scriptFileList );
}


/// *************************************************************************
/// <summary> 
/// Locate the folder and compile the list of animation data files.
/// </summary>
/// *************************************************************************
void CScriptManager::LoadAnimationDataFileList( const string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _animationDataFileList );
}


/// *************************************************************************
/// <summary> 
/// Get the sprite data.
/// </summary>
/// <param name="name"> Name of the sprite. </param>
/// *************************************************************************
const CAnimationData * CScriptManager::GetAnimationData( const string & name )
{
    try
    {
        // See if the sprite data is already loaded.
        auto loadedIter = _animationDataList.find( name );
        if( loadedIter != _animationDataList.end() )
            return loadedIter->second;

        auto unloadedIter = _animationDataFileList.find( name );
        if( unloadedIter != _animationDataFileList.end() )
        {
            // Load the sprite data file.
            ifstream ifile( unloadedIter->second );

            // Parse the content into a json object.
            json j;
            ifile >> j;

            auto animationIter = j.find( "animation" );
            if( animationIter != j.end() )
            {
                CAnimationData * pData = new CAnimationData();
                _animationDataList.emplace( unloadedIter->first, pData );

                pData->LoadFromIter( animationIter );

                return pData;
            }
        }

        throw NExcept::CCriticalException( "Error",
                                           "CScriptManager::GetAnimationData()",
                                           "No animation data exists with the name '" + name + "'." );
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CScriptManager::GetAnimationData()",
                                           "Failed to get animation data '" + name + "'.", e );
    }

    return nullptr;
}


/// *************************************************************************
/// <summary> 
/// Load all of the scripts of a specific group
/// </summary>
/// *************************************************************************
void CScriptManager::LoadScript( const string & name )
{
    try
    {
        // Make sure the group we are looking has been defined in the list table file
        auto iter = _scriptFileList.find( name );
        if( iter == _scriptFileList.end() )
            throw NExcept::CCriticalException( "Error",
                                               "CScriptManager::LoadScript()",
                                               "Script '" + name + "' could not be found." );

        // Create the script module. I think I'll only need one.
        if( !_pScriptModule )
        {
            _pScriptModule = _pScriptEngine->GetModule( "module", asGM_CREATE_IF_NOT_EXISTS );
            if( !_pScriptModule )
                throw NExcept::CCriticalException( "Error",
                                                   "CScriptManager::CScriptManager()",
                                                   "Could not create the script module." );
        }

        // Add the script to the module if it hasn't already been added.
        if( iter->second.id == 0 )
        {
            AddScript( iter->second.path );
            iter->second.id = 1;

            // Build all the scripts added to the module.
            BuildScript();
        }
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CScriptManager::LoadScript()",
                                           "Failed to load script '" + name + "'.", e );
    }
}


/// *************************************************************************
/// <summary> 
/// Add the script to the module.
/// </summary>
/// *************************************************************************
void CScriptManager::AddScript( const string & filepath )
{
    int fileId = 0;
    char * pScript = nullptr;

    try
    {
        // Load the script file into a charater array
        //shared_ptr<char> spChar = NGeneralFuncs::FileToBuf( filepath );

        fileId = agk::OpenToRead( filepath.c_str() );
        pScript = agk::ReadString( fileId );

        // Load script into module section - the file path is it's ID
        if( _pScriptModule->AddScriptSection( filepath.c_str(), pScript ) < 0 )
            throw NExcept::CCriticalException( "Error",
                                               "CScriptManager::AddScript()",
                                               "File '" + filepath + "' could not be added." );

        if( pScript )
            agk::DeleteString( pScript );

        if( fileId > 0 )
            agk::CloseFile( fileId );
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CScriptManager::AddScript()",
                                           "Failed to add script file '" + filepath + "'.", e );
    }
}


/// *************************************************************************
/// <summary> 
/// Build all the scripts added to the module.
/// </summary>
/// *************************************************************************
void CScriptManager::BuildScript()
{
    // Build the script
    if( _pScriptModule->Build() < 0 )
        throw NExcept::CCriticalException( "Error",
                                           "CScriptManager::BuildScript()",
                                           "Failed to build the scripts from the module." );
}


/// *************************************************************************
/// <summary> 
/// Get the script context from a managed pool.
///
/// NOTE: The receiver of this pointer is the owner if it's still
///       holding on to it when the game terminates.
/// </summary>
/// *************************************************************************
asIScriptContext * CScriptManager::GetContext()
{
    if( !_pInactiveContextList.empty() )
    {
        asIScriptContext * pContex = _pInactiveContextList.back();
        _pInactiveContextList.pop_back();

        return pContex;
    }

    return _pScriptEngine->CreateContext();
}


/// *************************************************************************
/// <summary> 
/// Add the script context back to the managed pool.
/// </summary>
/// *************************************************************************
void CScriptManager::RecycleContext( asIScriptContext * pContext )
{
    auto iter = find( _pActiveContextList.begin(), _pActiveContextList.end(), pContext );
    RecycleContext( iter );
}

/// <summary> 
/// Add the script context back to the managed pool.
/// </summary>
void CScriptManager::RecycleContext( std::vector<asIScriptContext *>::iterator & iter )
{
    _pInactiveContextList.push_back( (*iter) );

    if( iter != _pActiveContextList.end() )
        _pActiveContextList.erase( iter );
}


/// *************************************************************************
/// <summary> 
/// Get pointer to function name.
/// </summary>
/// *************************************************************************
asIScriptFunction * CScriptManager::GetPtrToFunc( const string & name )
{
    // See if this function pointer has already been saved
    auto mapIter = _pScriptFunctionList.find( name );

    // If it's not found, find the function and add it to the map
    // It's faster to keep the function pointers in a map then to use AngelScript's GetFunction call.
    if( mapIter == _pScriptFunctionList.end() )
    {
        // Try to get the pointer to the function
        asIScriptFunction * pScriptFunc = _pScriptModule->GetFunctionByName( name.c_str() );
        if( pScriptFunc == nullptr )
            throw NExcept::CCriticalException( "Error",
                                               "CScriptManager::GetPtrToFunc()",
                                               "AngelScript function '" + name + "' does not exist." );

        // Insert the function pointer into the map
        mapIter = _pScriptFunctionList.emplace( name, pScriptFunc ).first;
    }

    return mapIter->second;
}


/// *************************************************************************
/// <summary> 
/// Call back to display AngelScript messages.
/// </summary>
/// *************************************************************************
void CScriptManager::MessageCallback( const asSMessageInfo & msg )
{
    string type = "ERROR";
    if( msg.type == asMSGTYPE_WARNING )
        type = "WARN";

    else if( msg.type == asMSGTYPE_INFORMATION )
        type = "INFO";

    string msgStr = boost::str( boost::format( "%s (%d, %d) : %s : %s" ) % msg.section % msg.row % msg.col % type % msg.message );

    NGeneralFuncs::PostDebugMsg( msgStr );
}


/// *************************************************************************
/// <summary> 
/// Get the pointer to the script engine.
/// </summary>
/// *************************************************************************
asIScriptEngine * CScriptManager::GetEnginePtr()
{
    return _pScriptEngine;
}


/// *************************************************************************
/// <summary> 
/// Prepare the script function to run.
/// </summary>
/// <param name="function"> Name of the function to add to a context. </param>
/// <param name="pContextVec"> Vector of context pointers to add to. </param>
/// *************************************************************************
asIScriptContext * CScriptManager::Prepare( const string & function, const vector<CScriptParam> & paramList )
{
    // Get a context from the script manager pool
    asIScriptContext * pContext = GetContext();

    // Get the function pointer
    asIScriptFunction * pScriptFunc = GetPtrToFunc( function );

    // Prepare the function to run
    if( pContext->Prepare( pScriptFunc ) < 0 )
    {
        throw NExcept::CCriticalException( "Error Preparing Script!",
                                           boost::str( boost::format( "There was an error preparing the script (%s).\n\n%s\nLine: %s" )
                                                       % function % __FUNCTION__ % __LINE__ ) );
    }

    // Pass the parameters to the script function
    for( size_t i = 0; i < paramList.size(); ++i )
    {
        int returnVal( 0 );

        if( paramList[i].GetType() == CScriptParam::EPT_BOOL )
        {
            returnVal = pContext->SetArgByte( (asUINT)i, paramList[i].Get<bool>() );
        }
        else if( paramList[i].GetType() == CScriptParam::EPT_INT )
        {
            returnVal = pContext->SetArgDWord( (asUINT)i, paramList[i].Get<int>() );
        }
        else if( paramList[i].GetType() == CScriptParam::EPT_UINT )
        {
            returnVal = pContext->SetArgDWord( (asUINT)i, paramList[i].Get<uint>() );
        }
        else if( paramList[i].GetType() == CScriptParam::EPT_FLOAT )
        {
            returnVal = pContext->SetArgFloat( (asUINT)i, paramList[i].Get<float>() );
        }
        else if( paramList[i].GetType() == CScriptParam::EPT_PTR )
        {
            returnVal = pContext->SetArgObject( (asUINT)i, paramList[i].Get<void *>() );
        }

        if( returnVal < 0 )
        {
            throw NExcept::CCriticalException( "Error Setting Script Param!",
                                               boost::str( boost::format( "There was an error setting the script parameter (%s).\n\n%s\nLine: %s" )
                                                           % function % __FUNCTION__ % __LINE__ ) );
        }
    }

    return pContext;
}

//void CScriptManager::Prepare(
//    const string & function,
//    const vector<CScriptParam> & paramList )
//{
//    Prepare( function, _pActiveContextList, paramList );
//}


/// *************************************************************************
/// <summary> 
/// Prepare the spawn script function to run.
/// </summary>
/// *************************************************************************
void CScriptManager::PrepareSpawn( const string & funcName )
{
    auto pContex = asGetActiveContext();
    if( pContex )
    {
        // Prepare the script function to run
        _pActiveContextList.push_back( Prepare( funcName ) );
    }
}

void CScriptManager::PrepareSpawnObj( const string & funcName, void * pVoid )
{
    auto pContex = asGetActiveContext();
    if( pContex )
    {
        // Prepare the script function to run
        _pActiveContextList.push_back( Prepare( funcName, { pVoid } ) );
    }
}


/// *************************************************************************
/// <summary> 
/// Update the script.
/// </summary>
/// *************************************************************************
void CScriptManager::Update()
{
    if( !_pActiveContextList.empty() )
        Update( _pActiveContextList );
}

void CScriptManager::Update( vector<asIScriptContext *> & pContextVec )
{
    auto iter = pContextVec.begin();
    while( iter != pContextVec.end() )
    {
        // See if this context is still being used
        if( ((*iter)->GetState() == asEXECUTION_SUSPENDED) ||
            ((*iter)->GetState() == asEXECUTION_PREPARED) )
        {
            // Execute the script and check for errors
            // Since the script can be suspended, this also is used to continue execution
            if( (*iter)->Execute() < 0 )
            {
                throw NExcept::CCriticalException( "Error Calling Spawn Script!",
                                                   boost::str( boost::format( "There was an error executing the script.\n\n%s\nLine: %s" )
                                                               % __FUNCTION__ % __LINE__ ) );
            }

            // Return the context to the pool if it has not been suspended
            if( (*iter)->GetState() != asEXECUTION_SUSPENDED )
            {
                RecycleContext( (*iter) );
            }
            else
            {
                ++iter;
            }
        }
    }
}


/// *************************************************************************
/// <summary> 
/// Register the class with AngelScript.
/// </summary>
/// *************************************************************************
void CScriptManager::Register()
{
    using namespace NScriptGlobals;

    Throw( _pScriptEngine->RegisterGlobalFunction( "void Spawn(string &in)", asMETHOD( CScriptManager, PrepareSpawn ), asCALL_THISCALL_ASGLOBAL, &CScriptManager::Instance() ) );
}

// Physical component dependency
#include "animation.h"

// Game lib dependencies
#include <angelscript.h>
#include <common\iobject.h>
#include <script\animationdata.h>
#include <managers\scriptmanager.h>
#include <script\scriptglobals.h>
#include <utilities\exceptionhandling.h>

// Boost lib dependencies
#include <boost\format.hpp>

using namespace NDefs;
using namespace std;


/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CAnimation::CAnimation()
{
}


/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// <param name="pData"> Data to initialize the animation. </param> 
/// <param name="pObject"> Object to apply the animation to. </param> 
/// *************************************************************************
CAnimation::CAnimation( const CAnimationData * pData, iObject * pObject, uint conflictIndex )
{
    Init( pData, pObject, conflictIndex );
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CAnimation::~CAnimation()
{
    Clear();
}


/// *************************************************************************
/// <summary>
/// Initialize the animation.
/// </summary>
/// <param name="pData"> Data to initialize the animation. </param> 
/// <param name="pObject"> Object to apply the animation to. </param> 
/// *************************************************************************
void CAnimation::Init( const CAnimationData * pData, iObject * pObject, uint conflictIndex )
{
    if( !pData || !pObject )
        return;

    Clear();

    _pData = pData;
    _pObject = pObject;
    _conflictIndex = conflictIndex;
}


/// *************************************************************************
/// <summary>
/// Clear the animation.
/// </summary>
/// *************************************************************************
void CAnimation::Clear()
{
    Recycle();

    _pData = nullptr;
    _pObject = nullptr;
    _stopType = EST_NULL;
    _conflictIndex = 0;
    _pContextList.clear();
}


/// *************************************************************************
/// <summary>
/// Play the animation.
/// </summary>
/// *************************************************************************
void CAnimation::Play()
{
    if( !IsInitalized() )
        return;

    // Make sure everything is cleared and recycled before we start a script.
    Recycle();

    for( auto & function : _pData->GetFunctionList() )
        _pContextList.push_back( CScriptManager::Instance().Prepare( function, { this } ) );
}


/// *************************************************************************
/// <summary>
/// Stop the animation.
/// </summary>
/// <param name="stopType"> How to stop the animation. </param> 
/// *************************************************************************
void CAnimation::Stop( EStopType stopType )
{
    if( !IsPlaying() || !IsInitalized() )
        return;

    _stopType = stopType;

    if( _stopType == EST_STOP )
        Recycle();
}


/// *************************************************************************
/// <summary>
/// Stop any animations and recycle all contexts.
/// </summary>
/// *************************************************************************
void CAnimation::Recycle()
{
    if( !_pContextList.empty() )
    {
        for( auto pContext : _pContextList )
        {
            if( pContext->GetState() == asEXECUTION_SUSPENDED )
                pContext->Abort();

            CScriptManager::Instance().RecycleContext( pContext );
        }

        _pContextList.clear();
    }

    _stopType = EST_NULL;
}


/// *************************************************************************
/// <summary>
/// Get the end type.
/// </summary>
/// *************************************************************************
EEndType CAnimation::GetEndType() const
{
    return _pData->GetEndType();
}


/// *************************************************************************
/// <summary>
/// Get the stop type.
/// </summary>
/// *************************************************************************
EStopType CAnimation::GetStopType() const
{
    return _stopType;
}


/// *************************************************************************
/// <summary>
/// Whether or not the animation has been initialized.
/// </summary>
/// *************************************************************************
bool CAnimation::IsInitalized() const
{
    return _pData && _pObject;
}


/// *************************************************************************
/// <summary>
/// Set the object's position.
/// </summary>
/// *************************************************************************
void CAnimation::SetPos( const CVector3 & pos )
{
    _pObject->SetPos( pos );
}


/// *************************************************************************
/// <summary>
/// Increment the object's position.
/// </summary>
/// *************************************************************************
void CAnimation::IncPos( const CVector3 & pos )
{
    _pObject->IncPos( pos );
}


/// *************************************************************************
/// <summary>
/// Get the object's position.
/// </summary>
/// *************************************************************************
const CVector3 & CAnimation::GetPos() const
{
    return _pObject->GetPos();
}


/// *************************************************************************
/// <summary>
/// Set the object's rotation.
/// </summary>
/// *************************************************************************
void CAnimation::SetRot( const CVector3 & rot )
{
    _pObject->SetRot( rot );
}


/// *************************************************************************
/// <summary>
/// Increment the object's rotation.
/// </summary>
/// *************************************************************************
void CAnimation::IncRot( const CVector3 & rot )
{
    _pObject->IncRot( rot );
}


/// *************************************************************************
/// <summary>
/// Get the object's rotation.
/// </summary>
/// *************************************************************************
const CVector3 & CAnimation::GetRot() const
{
    return _pObject->GetRot();
}


/// *************************************************************************
/// <summary>
/// Set the object's size.
/// </summary>
/// *************************************************************************
void CAnimation::SetSize( const CVector3 & size )
{
    _pObject->SetSize( size );
}


/// *************************************************************************
/// <summary>
/// Increment the object's size.
/// </summary>
/// *************************************************************************
void CAnimation::IncSize( const CVector3 & size )
{
    _pObject->IncSize( size );
}


/// *************************************************************************
/// <summary>
/// Get the object's size.
/// </summary>
/// *************************************************************************
const CVector3 & CAnimation::GetSize() const
{
    return _pObject->GetSize();
}


/// *************************************************************************
/// <summary>
/// Set the object's color.
/// </summary>
/// *************************************************************************
void CAnimation::SetColor( const CVector4 & color )
{
    _pObject->SetColor( color );
}


/// *************************************************************************
/// <summary>
/// Increment the object's color.
/// </summary>
/// *************************************************************************
void CAnimation::IncColor( const CVector4 & color )
{
    _pObject->IncColor( color );
}


/// *************************************************************************
/// <summary>
/// Get the object's color.
/// </summary>
/// *************************************************************************
const CVector4 & CAnimation::GetColor() const
{
    return _pObject->GetColor();
}


/// *************************************************************************
/// <summary>
/// Set the object's transparency.
/// </summary>
/// *************************************************************************
void CAnimation::SetColorA( float a )
{
    _pObject->SetColorA( a );
}


/// *************************************************************************
/// <summary>
/// Increment the object's transparency.
/// </summary>
/// *************************************************************************
void CAnimation::IncColorA( float a )
{
    _pObject->IncColor( 0, 0, 0, a );
}


/// *************************************************************************
/// <summary>
/// Get the object's transparency.
/// </summary>
/// *************************************************************************
float CAnimation::GetColorA() const
{
    return _pObject->GetColor().a;
}


/// *************************************************************************
/// <summary>
/// Set the object's visibility.
/// </summary>
/// *************************************************************************
void CAnimation::SetVisible( bool visible )
{
    _pObject->SetVisible( visible );
}


/// *************************************************************************
/// <summary>
/// Get the object's visibility.
/// </summary>
/// *************************************************************************
bool CAnimation::IsVisible() const
{
    return _pObject->IsVisible();
}


/// *************************************************************************
/// <summary>
/// Whether or not the animation is playing.
/// </summary>
/// *************************************************************************
bool CAnimation::IsPlaying() const
{
    return _pContextList.size() > 0;
}


/// *************************************************************************
/// <summary>
/// Get the number of times to loop the animation.
/// </summary>
/// *************************************************************************
int CAnimation::GetLoopCount() const
{
    return _pData->GetLoopCount();
}


/// *************************************************************************
/// <summary>
/// Get the animation data.
/// </summary>
/// *************************************************************************
const CAnimationData * CAnimation::GetData() const
{
    return _pData;
}


/// *************************************************************************
/// <summary>
/// Get the index of whichever conflict list this animation belongs to.
/// </summary>
/// *************************************************************************
uint CAnimation::GetConflictIndex() const
{
    return _conflictIndex;
}


/// *************************************************************************
/// <summary>
/// Spawn another context to run concurrently.
/// </summary>
/// <param name="function"> Script function to start. </param>
/// *************************************************************************
void CAnimation::Spawn( const std::string & function )
{
    _pContextList.push_back( CScriptManager::Instance().Prepare( function, { this } ) );
}


/// *************************************************************************
/// <summary>
/// Update the animation.
/// </summary>
/// *************************************************************************
void CAnimation::Update()
{
    // If the animation is paused, don't do anything.
    if( _stopType == EST_PAUSE )
        return;

    vector<asIScriptContext *> pEraseList;

    // Use an indexed loop here just in case a script spawns another context.
    for( uint i = 0; i < _pContextList.size(); i++ )
    {
        auto pContext = _pContextList[i];

        // See if this context is still being used.
        if( (pContext->GetState() == asEXECUTION_SUSPENDED) ||
            (pContext->GetState() == asEXECUTION_PREPARED) )
        {
            // Execute the script and check for errors.
            // Since the script can be suspended, this also is used to continue execution.
            if( pContext->Execute() < 0 )
            {
                throw NExcept::CCriticalException( "Error Calling Spawn Script!",
                        boost::str( boost::format( "There was an error executing the script.\n\n%s\nLine: %s" )
                                                   % __FUNCTION__ % __LINE__ ) );
            }
    
            // Return the context to the pool if it has not been suspended.
            if( pContext->GetState() != asEXECUTION_SUSPENDED )
                pEraseList.push_back( pContext );
        }
    }

    // 
    for( auto pContext : pEraseList )
        _pContextList.erase( std::find(_pContextList.begin(), _pContextList.end(), pContext) );
}


/// *************************************************************************
/// <summary>
/// Register the class with AngelScript.
/// </summary>
/// *************************************************************************
void CAnimation::Register( asIScriptEngine * pEngine )
{
    using namespace NScriptGlobals;

    // Register CScriptComponent2d reference and methods
    Throw( pEngine->RegisterObjectType( "CAnimation", 0, asOBJ_REF | asOBJ_NOCOUNT ) );

    Throw( pEngine->RegisterObjectMethod( "CAnimation", "int GetEndType()", asMETHOD( CAnimation, GetEndType ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "int GetStopType()", asMETHOD( CAnimation, GetStopType ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "int GetLoopCount()", asMETHOD( CAnimation, GetLoopCount ), asCALL_THISCALL ) );

    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void SetPos(const CVector3 &in)",  asMETHOD( CAnimation, SetPos ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void SetRot(const CVector3 &in)",  asMETHOD( CAnimation, SetRot ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void SetSize(const CVector3 &in)", asMETHOD( CAnimation, SetSize ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void SetColor(const CColor &in)",  asMETHOD( CAnimation, SetColor ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void SetColorA(int a)",            asMETHOD( CAnimation, SetColorA ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void SetVisible(bool visible)",    asMETHOD( CAnimation, SetVisible ), asCALL_THISCALL ) );

    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void IncPos(const CVector3 &in)",  asMETHOD( CAnimation, IncPos ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void IncRot(const CVector3 &in)",  asMETHOD( CAnimation, IncRot ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void IncSize(const CVector3 &in)", asMETHOD( CAnimation, IncSize ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void IncColor(const CColor &in)",  asMETHOD( CAnimation, IncColor ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void IncColorA(int a)",            asMETHOD( CAnimation, IncColorA ), asCALL_THISCALL ) );

    Throw( pEngine->RegisterObjectMethod( "CAnimation", "const CVector3 & GetPos()",  asMETHOD( CAnimation, GetPos ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "const CVector3 & GetRot()",  asMETHOD( CAnimation, GetRot ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "const CVector3 & GetSize()", asMETHOD( CAnimation, GetSize ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "const CColor & GetColor()",  asMETHOD( CAnimation, GetColor ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "int GetColorA()",            asMETHOD( CAnimation, GetColorA ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "bool IsVisible()",           asMETHOD( CAnimation, IsVisible ), asCALL_THISCALL ) );

    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void Spawn(string &in)", asMETHOD( CAnimation, Spawn ), asCALL_THISCALL ) );
}
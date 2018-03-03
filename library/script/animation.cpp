// Physical component dependency
#include "animation.h"

// Game lib dependencies
#include <angelscript.h>
#include <common\iobject.h>
#include <script\animationdata.h>
#include <script\scriptmanager.h>
#include <script\scriptglobals.h>

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
CAnimation::CAnimation( const CAnimationData * pData, iObject * pObject )
{
    Init( pData, pObject );
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
void CAnimation::Init( const CAnimationData * pData, iObject * pObject )
{
    if( !pData || !pObject )
        return;

    Clear();

    _pData = pData;
    _pObject = pObject;
}


/// *************************************************************************
/// <summary>
/// Clear the animation.
/// </summary>
/// *************************************************************************
void CAnimation::Clear()
{
    _pData = nullptr;
    _pObject = nullptr;
    _playing = false;
    _endType = ESE_NULL;
    _pContextList.clear();
}


/// *************************************************************************
/// <summary>
/// Play the animation.
/// </summary>
/// *************************************************************************
void CAnimation::Play( bool restartIfPlaying )
{
    if( !IsInitalized() )
        return;

    // If the animation is currently playing and we don't want to restart it, then we leave.
    if( !restartIfPlaying && _playing )
        return;

    // Make sure everything is cleared and recycled before we start a script.
    Recycle();

    for( auto & iter : _pData->GetFunctionList() )
        _pContextList.emplace( iter, CScriptManager::Instance().Prepare( iter, { this } ) );

    _playing = true;
}


/// *************************************************************************
/// <summary>
/// Stop the animation.
/// </summary>
/// <param name="endType"> 
/// How to end the animation. If not specified, it'll end however it's defined
/// in the animation data. </param> 
/// *************************************************************************
void CAnimation::Stop( int endType )
{
    if( !_playing || !IsInitalized() )
        return;

    if( endType == ESE_DEFAULT || endType == ESE_NULL )
        _endType = _pData->GetEndType();
    else
        _endType = endType;

    if( _endType == ESE_STOP )
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
        for( auto iter : _pContextList )
        {
            if( iter.second->GetState() == asEXECUTION_SUSPENDED )
                iter.second->Abort();

            CScriptManager::Instance().RecycleContext( iter.second );
        }


        _pContextList.clear();
    }

    _endType = ESE_NULL;
    _playing = false;
}


/// *************************************************************************
/// <summary>
/// Get the end type. This also tells us if we need to begin ending the animation.
/// </summary>
/// *************************************************************************
int CAnimation::GetEndType() const
{
    return _endType;
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
/// Finish the animation, making it ready to play again. This should be called
/// at the end of each script, letting everything else know the animation is
/// finished.
/// </summary>
/// *************************************************************************
void CAnimation::Finish( const string & function )
{
    _pContextList.erase( function );

    if( _pContextList.size() == 0 )
    {
        _endType = ESE_DEFAULT;
        _playing = false;
    }
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
void CAnimation::SetColor( const CColor & color )
{
    _pObject->SetColor( color );
}


/// *************************************************************************
/// <summary>
/// Increment the object's color.
/// </summary>
/// *************************************************************************
void CAnimation::IncColor( const CColor & color )
{
    _pObject->IncColor( color );
}


/// *************************************************************************
/// <summary>
/// Get the object's color.
/// </summary>
/// *************************************************************************
const CColor & CAnimation::GetColor() const
{
    return _pObject->GetColor();
}


/// *************************************************************************
/// <summary>
/// Set the object's transparency.
/// </summary>
/// *************************************************************************
void CAnimation::SetColorA( int a )
{
    _pObject->SetColorA( a );
}


/// *************************************************************************
/// <summary>
/// Increment the object's transparency.
/// </summary>
/// *************************************************************************
void CAnimation::IncColorA( int a )
{
    _pObject->IncColor( 0, 0, 0, a );
}


/// *************************************************************************
/// <summary>
/// Get the object's transparency.
/// </summary>
/// *************************************************************************
int CAnimation::GetColorA() const
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
    return _playing;
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
/// Register the class with AngelScript.
/// </summary>
/// *************************************************************************
void CAnimation::Register( asIScriptEngine * pEngine )
{
    using namespace NScriptGlobals;

    // Register CScriptComponent2d reference and methods
    Throw( pEngine->RegisterObjectType( "CAnimation", 0, asOBJ_REF | asOBJ_NOCOUNT ) );

    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void Finish(string &in)", asMETHOD( CAnimation, Finish ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "int GetEndType()", asMETHOD( CAnimation, GetEndType ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "int GetLoopCount()", asMETHOD( CAnimation, GetLoopCount ), asCALL_THISCALL ) );

    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void SetPos(CVector3 &in)",       asMETHOD( CAnimation, SetPos ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void SetRot(CVector3 &in)",       asMETHOD( CAnimation, SetRot ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void SetSize(CVector3 &in)",      asMETHOD( CAnimation, SetSize ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void SetColor(const CColor &in)", asMETHOD( CAnimation, SetColor ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void SetColorA(int a)",           asMETHOD( CAnimation, SetColorA ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void SetVisible(bool visible)",   asMETHOD( CAnimation, SetVisible ), asCALL_THISCALL ) );

    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void IncPos(CVector3 &in)",       asMETHOD( CAnimation, IncPos ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void IncRot(CVector3 &in)",       asMETHOD( CAnimation, IncRot ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void IncSize(CVector3 &in)",      asMETHOD( CAnimation, IncSize ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void IncColor(const CColor &in)", asMETHOD( CAnimation, IncColor ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "void IncColorA(int a)",           asMETHOD( CAnimation, IncColorA ), asCALL_THISCALL ) );

    Throw( pEngine->RegisterObjectMethod( "CAnimation", "const CVector3 & GetPos()",  asMETHOD( CAnimation, GetPos ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "const CVector3 & GetRot()",  asMETHOD( CAnimation, GetRot ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "const CVector3 & GetSize()", asMETHOD( CAnimation, GetSize ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "const CColor & GetColor()",  asMETHOD( CAnimation, GetColor ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "int GetColorA()",            asMETHOD( CAnimation, GetColorA ), asCALL_THISCALL ) );
    Throw( pEngine->RegisterObjectMethod( "CAnimation", "bool IsVisible()",           asMETHOD( CAnimation, IsVisible ), asCALL_THISCALL ) );

    Throw( pEngine->RegisterGlobalFunction( "void Spawn(string &in, CAnimation @)", asMETHOD( CScriptManager, PrepareSpawnObj ), asCALL_THISCALL_ASGLOBAL, &CScriptManager::Instance() ) );
}
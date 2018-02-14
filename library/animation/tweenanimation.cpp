// Physical dependency
#include "tweenanimation.h"

// Game lib dependencies
#include <agk.h>
#include <common\iobject.h>
#include <common\vector3.h>
#include <animation\tween.h>
#include <utilities\exceptionhandling.h>
#include <utilities\deletefuncs.h>
#include <managers\animationmanager.h>

// Standard lib dependencies
#include <fstream>

using namespace NDefs;
using namespace std;
using namespace nlohmann;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CTweenChain::CTweenChain()
{
}

/// <summary> 
/// Initialize the tween animation.
/// </summary>
/// <param name="pObject"> The object this animation is for. </param>
/// <param name="iter"> JSON iterator into where. </param>
CTweenChain::CTweenChain( iObject * pObject, json::const_iterator iter )
{
    Init( pObject, iter );
}


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CTweenChain::~CTweenChain()
{
    Clear();
}


/// *************************************************************************
/// <summary> 
/// Clear the tween data.
/// </summary>
/// *************************************************************************
void CTweenChain::Clear()
{
    _pObject = nullptr;

    if ( _chainId )
        agk::DeleteTweenChain( _chainId );

    NDelFunc::DeleteVectorPointers( _tweenList );
}


/// *************************************************************************
/// <summary> 
/// Initialize the tween animation.
/// </summary>
/// <param name="pObject"> The object this animation is for. </param>
/// <param name="iter"> JSON iterator to a tween animation. </param>
/// *************************************************************************
void CTweenChain::Init( iObject * pObject, json::const_iterator iter )
{
    Clear();

    _pObject = pObject;

    auto tweenChainIter = iter->find( "tween" );
    if( tweenChainIter != iter->end() )
    {
        auto tweenIter = tweenChainIter->begin();
        while( tweenIter != tweenChainIter->end() )
        {
            CTween * pTween = new CTween( pObject, tweenIter );
            _tweenList.push_back( pTween );
        }
    }
}


/// *************************************************************************
/// <summary> 
/// Play the animation.
/// </summary>
/// <param name="time"> The time to start the animation at. </param>
/// *************************************************************************
void CTweenChain::Play( float time )
{
    if( !_pObject )
        return;

    Seek( time );
    agk::PlayTweenChain( _chainId );
}


/// *************************************************************************
/// <summary> 
/// Pause the animation.
/// </summary>
/// *************************************************************************
void CTweenChain::Pause()
{
    if( !_pObject )
        return;

    agk::PauseTweenChain( _chainId );
}


/// *************************************************************************
/// <summary> 
/// Resume the animation from where ever it currently is in the animation.
/// </summary>
/// *************************************************************************
void CTweenChain::Resume()
{
    if( !_pObject )
        return;

    agk::PlayTweenChain( _chainId );
}


/// *************************************************************************
/// <summary> 
/// Set to a specific time in the animation.
/// </summary>
/// *************************************************************************
void CTweenChain::Seek( float time )
{
    if( !_pObject )
        return;

    agk::SetTweenChainTime( _chainId, time );
}


/// *************************************************************************
/// <summary> 
/// Whether the animation is playing or not.
/// </summary>
/// *************************************************************************
bool CTweenChain::IsPlaying() const
{
    if( !_pObject )
        return false;

    return agk::GetTweenChainPlaying( _chainId );
}


/// *************************************************************************
/// <summary> 
/// Get the total time it takes to complete the animation.
/// </summary>
/// *************************************************************************
float CTweenChain::GetEndTime() const
{
    return agk::GetTweenChainEndTime( _chainId );
}
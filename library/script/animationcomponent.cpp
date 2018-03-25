// Phyiscal component dependencies
#include "animationcomponent.h"

// Game lib dependencies
#include <script\animation.h>
#include <script\animationdata.h>
#include <managers\scriptmanager.h>
#include <utilities\deletefuncs.h>
#include <utilities\generalfuncs.h>

using namespace std;
using namespace NDefs;

/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CAnimationComponent::CAnimationComponent()
{
}


/// <summary>
/// Constructor
/// </summary>
/// <param name="pObject"> Object that this component belongs to. </param>
/// <param name="animationList"> List of animation names to create. </param>
CAnimationComponent::CAnimationComponent( iObject * pObject, const vector<vector<string>> & animationList )
{
    Init( pObject, animationList );
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CAnimationComponent::~CAnimationComponent()
{
    Clear();
}


/// *************************************************************************
/// <summary>
/// Initialize the animation component.
/// </summary>
/// <param name="pObject"> Object that this component belongs to. </param>
/// <param name="animationList"> List of animation names to create. </param>
/// *************************************************************************
void CAnimationComponent::Init( iObject * pObject, const vector<vector<string>> & animationList )
{
    Clear();

    //for( auto & animation : animationList )
    for( auto & conflictList : animationList )
    {
        for( uint i = 0; i < conflictList.size(); i++ )
        {
            const CAnimationData * pData = CScriptManager::Instance().GetAnimationData( conflictList[i] );
            _pAnimationList.emplace( pData->GetName(), new CAnimation( pData, pObject, i ) );
        }
    }
}


/// *************************************************************************
/// <summary>
/// Clear the animation component.
/// </summary>
/// *************************************************************************
void CAnimationComponent::Clear()
{
    NDelFunc::DeleteMapPointers( _pAnimationList );
    _pAnimationQueue.clear();
    _pPlayingList.clear();
}


/// *************************************************************************
/// <summary>
/// Play an animation.
/// </summary>
/// <param name="name"> Name of the animation to play. </param>
/// <param name="stopType"> How to end any conflicting animation. </param>
/// *************************************************************************
void CAnimationComponent::Play( const string & name, EStopType stopType )
{
    // If no animation was found, leave.
    auto animIter = _pAnimationList.find( name );
    if( animIter == _pAnimationList.end() )
        return;

    // If this animation is already queued up, don't queue it again.
    auto iter = _pAnimationQueue.find( name );
    if( iter != _pAnimationQueue.end() )
        return;

    // Get any conflicting animation playing.
    CAnimation * pConflict = GetConflictingAnimation( animIter->second );

    // If the end animation is null, it means we ignore this play call altogether if
    // a conflicting animation is playing. 
    if( stopType == EST_NULL && pConflict )
        return;

    // The pause stop type is only acknowledged if the current conflicting animation is
    // the one we're trying to play.
    if( stopType == EST_PAUSE && animIter->second == pConflict )
        // If the animation is playing but currently paused, unpause it.
        if( pConflict->GetStopType() == EST_PAUSE )
            pConflict->Stop( EST_NULL );
        else
            pConflict->Stop( EST_PAUSE );
    else
    {
        // Stop the conflicting animation according to the stop type.
        if( pConflict )
            pConflict->Stop( stopType );

        // Add this animation to the queue.
        _pAnimationQueue.emplace( name, animIter->second );
    }
}


/// *************************************************************************
/// <summary>
/// Stop all animations.
/// </summary>
/// <param name="stopType"> How to end the animations. </param>
/// *************************************************************************
void CAnimationComponent::Stop( NDefs::EStopType stopType )
{
    for( auto animIter : _pPlayingList )
        animIter.second->Stop( stopType );
}

/// <summary>
/// Stop an animation.
/// </summary>
/// <param name="name"> Name of the animation to stop. </param>
/// <param name="stopType"> How to end the animation. </param>
void CAnimationComponent::Stop( const std::string & name, NDefs::EStopType stopType )
{
    auto iter = _pPlayingList.find( name );
    if( iter != _pPlayingList.end() )
        iter->second->Stop( stopType );
}


/// *************************************************************************
/// <summary>
/// Whether or not an animation is playing.
/// </summary>
/// <param name="includePaused"> If paused animations should be consider "playing". </param>
/// *************************************************************************
bool CAnimationComponent::IsPlaying( bool includePaused )
{
    if( includePaused )
        return _pPlayingList.size() > 0;

    for( auto animIter : _pPlayingList )
        if( animIter.second->GetStopType() != EST_PAUSE )
            return true;

    return false;
}

/// <summary>
/// Whether or not an animation is playing.
/// </summary>
/// <param name="name"> Name of the animation to stop. </param>
/// <param name="includePaused"> If paused animations should be consider "playing". </param>
bool CAnimationComponent::IsPlaying( const std::string & name, bool includePaused )
{
    auto iter = _pPlayingList.find( name );
    if( iter != _pPlayingList.end() )
    {
        if( includePaused && iter->second->GetStopType() != EST_PAUSE )
            return false;

        return true;
    }

    return false;
}


/// *************************************************************************
/// <summary>
/// Update the animation component.
/// </summary>
/// *************************************************************************
void CAnimationComponent::Update()
{
    // Loop through each animation in the queue. If there are no more conflicting animations playing,
    // play that animation.
    auto queueIter = _pAnimationQueue.begin();
    while( queueIter != _pAnimationQueue.end() )
    {
        // If there's no conflicting animation playing, play this animation.
        if( !GetConflictingAnimation( queueIter->second ) )
        {
            queueIter->second->Play();
            _pPlayingList.emplace( queueIter->first, queueIter->second );
            queueIter = _pAnimationQueue.erase( queueIter );
        }
        else
            ++queueIter;
    }

    // Update the playing animations.
    for( auto animIter : _pPlayingList )
        animIter.second->Update();

    // Remove animations from the playing list if they've finished playing.
    auto playingIter = _pPlayingList.begin();
    while( playingIter != _pPlayingList.end() )
    {
        if( playingIter->second->IsPlaying() )
            ++playingIter;
        else
            playingIter = _pPlayingList.erase( playingIter );
    }
}


/// *************************************************************************
/// <summary>
/// Get any animation currently playing that conflicts with the passed in animation.
/// </summary>
/// <param name="pAnimation"> Animation to compare against. </param>
/// <param name="pConflictList"> List to fill with conflicting animations. </param>
/// *************************************************************************
CAnimation * CAnimationComponent::GetConflictingAnimation( const string & name )
{
    auto iter = _pAnimationList.find( name );
    if( iter != _pAnimationList.end() )
        return GetConflictingAnimation( iter->second );

    return nullptr;
}


/// *************************************************************************
/// <summary>
/// Get any animation currently playing that conflicts with the passed in animation.
/// </summary>
/// <param name="name"> Name of the animation to compare against. </param>
/// <param name="pConflictList"> List to fill with conflicting animations. </param>
/// *************************************************************************
CAnimation * CAnimationComponent::GetConflictingAnimation( const CAnimation * pAnimation )
{
    for( auto playingIter : _pPlayingList )
        if( pAnimation->GetConflictIndex() == playingIter.second->GetConflictIndex() )
            return playingIter.second;

    return nullptr;
}
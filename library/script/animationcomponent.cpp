// Phyiscal component dependencies
#include "animationcomponent.h"

// Game lib dependencies
#include <script\animation.h>
#include <script\animationdata.h>
#include <script\scriptmanager.h>
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
    CAnimation * pAnimation = NGeneralFuncs::GetMapValue( name, _pAnimationList );

    // If no animation was found, leave.
    if( !pAnimation )
        return;

    // If this animation is already queued up, don't queue it again.
    auto iter = _pAnimationQueue.find( name );
    if( iter != _pAnimationQueue.end() )
        return;

    // Get any conflicting animation playing.
    CAnimation * pConflict = GetConflictingAnimation( pAnimation );

    // If the end animation is null, it means we ignore this play call altogether if
    // a conflicting animation is playing. 
    if( stopType == EST_NULL && pConflict )
        return;

    // The pause stop type is only acknowledged if the current conflicting animation is
    // the one we're trying to play.
    if( stopType == EST_PAUSE && pAnimation == pConflict )
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
        _pAnimationQueue.emplace( name, pAnimation );
    }
}


/// *************************************************************************
/// <summary>
/// Stop an animation.
/// </summary>
/// <param name="name"> Name of the animation to stop. </param>
/// <param name="stopType"> How to end the animation. </param>
/// *************************************************************************
void CAnimationComponent::Stop( const std::string & name, NDefs::EStopType stopType )
{
    CAnimation * pAnimation = NGeneralFuncs::GetMapValue( name, _pPlayingList );

    // If the animation isn't playing, ignore the stop.
    if( !pAnimation )
        return;

    pAnimation->Stop( stopType );
}


/// *************************************************************************
/// <summary>
/// Whether or not an animation is playing.
/// </summary>
/// <param name="name"> Name of the animation to stop. </param>
/// <param name="includePaused"> If paused animations should be consider "playing". </param>
/// *************************************************************************
bool CAnimationComponent::IsPlaying( const std::string & name, bool includePaused )
{
    // If no name was passed, check if any animations are playing.
    if( name == "" )
    {
        if( includePaused )
            return _pPlayingList.size() > 0;

        for( auto animIter : _pPlayingList )
            if( animIter.second->GetEndType() != EST_PAUSE )
                return true;
    }
    
    CAnimation * pAnimation = NGeneralFuncs::GetMapValue( name, _pPlayingList );
    if( pAnimation )
    {
        if( includePaused && pAnimation->GetEndType() != EST_PAUSE )
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
    CAnimation * pAnimation = NGeneralFuncs::GetMapValue( name, _pAnimationList );

    if( !pAnimation )
        return nullptr;

    return GetConflictingAnimation( pAnimation );
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
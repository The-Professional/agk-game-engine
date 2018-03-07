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
CAnimationComponent::CAnimationComponent( iObject * pObject, const vector<string> & animationList )
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
void CAnimationComponent::Init( iObject * pObject, const vector<string> & animationList )
{
    Clear();

    for( auto & animation : animationList )
    {
        const CAnimationData * pData = CScriptManager::Instance().GetAnimationData( animation );
        _pAnimationList.emplace( pData->GetName(), new CAnimation( pData, pObject ) );
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
/// <param name="stopType"> How to end any conflicting animations. </param>
/// *************************************************************************
void CAnimationComponent::Play( const string & name, EStopType stopType )
{
    CAnimation * pAnimation = NGeneralFuncs::GetMapValue( name, _pAnimationList );
    
    // Get a list of all conflicting animations that are playing.
    vector<CAnimation *> pConflictList;
    GetConflictingAnimations( pAnimation, pConflictList );

    // If the end animation is null, it means we ignore this play call altogether. 
    if( stopType == EET_NULL && pConflictList.size() > 0 )
        return;

    // If this animation is already queued up, don't queue it again.
    if( std::find( _pAnimationQueue.begin(), _pAnimationQueue.end(), pAnimation ) != _pAnimationQueue.end() )
        return;

    // Begin the stop animation.
    for( auto animation : pConflictList )
         animation->Stop( stopType );

    // Add this animation to the queue.
    _pAnimationQueue.push_back( pAnimation );
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
        // Get a list of all conflicting animations that are playing.
        vector<CAnimation *> pConflictList;
        GetConflictingAnimations( (*queueIter), pConflictList );

        if( pConflictList.size() == 0 )
        {
            (*queueIter)->Play();
            _pPlayingList.push_back( (*queueIter) );
            queueIter = _pAnimationQueue.erase( queueIter );
        }
        else
            ++queueIter;
    }

    // Update the playing animations.
    for( auto pAnimation : _pPlayingList )
        pAnimation->Update();

    // Remove animations from the playing list if they've finished playing.
    auto playingIter = _pPlayingList.begin();
    while( playingIter != _pPlayingList.end() )
    {
        if( (*playingIter)->IsPlaying() )
            ++playingIter;
        else
            playingIter = _pPlayingList.erase( playingIter );
    }
}


/// *************************************************************************
/// <summary>
/// Get any animations currently playing that conflict with the passed in animation.
/// </summary>
/// <param name="pAnimation"> Animation to compare against. </param>
/// <param name="pConflictList"> List to fill with conflicting animations. </param>
/// *************************************************************************
void CAnimationComponent::GetConflictingAnimations( const string & name, vector<CAnimation *> & pConflictList )
{
    CAnimation * pAnimation = NGeneralFuncs::GetMapValue( name, _pAnimationList );
    GetConflictingAnimations( pAnimation, pConflictList );
}


/// *************************************************************************
/// <summary>
/// Get any animations currently playing that conflict with the passed in animation.
/// </summary>
/// <param name="name"> Name of the animation to compare against. </param>
/// <param name="pConflictList"> List to fill with conflicting animations. </param>
/// *************************************************************************
void CAnimationComponent::GetConflictingAnimations( const CAnimation * pAnimation, vector<CAnimation *> & pConflictList )
{
    // Get a list of all conflicting animations that are playing.
    for( auto & pPlaying : _pPlayingList )
    {
        if( pPlaying->IsPlaying() &&
            pAnimation->GetData()->GetObjectFields().ContainsOne( pPlaying->GetData()->GetObjectFields() ) )
            pConflictList.push_back( pPlaying );
    }
}
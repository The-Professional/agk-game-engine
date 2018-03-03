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
}


/// *************************************************************************
/// <summary>
/// Play an animation.
/// </summary>
/// <param name="endType"> How to end any conflicting animations. </param>
/// *************************************************************************
void CAnimationComponent::Play( const string & name, int endType )
{
    CAnimation * pAnimation = NGeneralFuncs::GetMapValue( name, _pAnimationList );
    
    // Get a list of all conflicting animations that are playing.
    vector<CAnimation *> pConflictList;
    GetConflictingAnimations( pAnimation, pConflictList );

    // If the end animation is null, it means we ignore this play call altogether. 
    if( endType == ESE_NULL && pConflictList.size() > 0 )
        return;

    // Begin the stop animation.
    for( auto animation : pConflictList )
         animation->Stop( endType );

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
    auto iter = _pAnimationQueue.begin();
    while( iter != _pAnimationQueue.end() )
    {
        // Get a list of all conflicting animations that are playing.
        vector<CAnimation *> pConflictList;
        GetConflictingAnimations( (*iter), pConflictList );

        if( pConflictList.size() == 0 )
        {
            (*iter)->Play();
            _pAnimationQueue.erase( iter );
        }
        else
            ++iter;
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
    for( auto & animation : _pAnimationList )
    {
        if( animation.second->IsPlaying() &&
            pAnimation->GetData()->GetObjectFields().ContainsOne( animation.second->GetData()->GetObjectFields() ) )
            pConflictList.push_back( animation.second );
    }
}
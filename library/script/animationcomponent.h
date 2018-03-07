#ifndef __animation_component_h__
#define __animation_component_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\bitmask.h>
#include <utilities\jsonparsehelper.h>

// Standard lib dependencies
#include <string>
#include <map>
#include <vector>

// Forward declarations
class CAnimation;

/// *************************************************************************
/// <summary>
/// Class containing logic to play an objects animations.
/// </summary>
/// *************************************************************************
class CAnimationComponent
{
public:

    CAnimationComponent();
    CAnimationComponent( iObject * pObject, const std::vector<std::string> & animationList );
    ~CAnimationComponent();

    // Initialize the animation component.
    void Init( iObject * pObject, const std::vector<std::string> & animationList );

    // Clear the animation component.
    void Clear();

    // Play an animation.
    void Play( const std::string & name, NDefs::EStopType stopType = NDefs::EST_NULL );

    // Update the animation component.
    void Update();

    // Get any animations currently playing that conflict with the passed in animation.
    void GetConflictingAnimations( const std::string & name, std::vector<CAnimation *> & pConflictList );

private:

    // Get any animations currently playing that conflict with the passed in animation.
    void GetConflictingAnimations( const CAnimation * pAnimation, std::vector<CAnimation *> & pConflictList );

private:

    // List of animations.
    std::map<const std::string, CAnimation *> _pAnimationList;

    // The animations waiting to be played.
    std::vector<CAnimation *> _pAnimationQueue;

    // List of animations currently playing.
    std::vector<CAnimation *> _pPlayingList;

};

#endif  // __animation_component_h__


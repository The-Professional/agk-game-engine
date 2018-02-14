#ifndef __tween_animation_h__
#define __tween_animation_h__

// Game lib dependencies
#include <common\defs.h>
#include <utilities\jsonparsehelper.h>

// Standard lib dependencies
#include <string>
#include <vector>

// Forward declarations
class iObject;
class CTween;

/// *************************************************************************
/// <summary> 
/// Class to animate an object through a series of tweens.
/// </summary>
/// *************************************************************************
class CTweenChain
{
public:
    CTweenChain();
    CTweenChain( iObject * pObject, nlohmann::json::const_iterator iter );
    virtual ~CTweenChain();

    // Initialize the animation.
    virtual void Init( iObject * pObject, nlohmann::json::const_iterator iter );

    // Clear the tween data.
    virtual void Clear();

    // Play the animation from the start.
    virtual void Play( float time = 0 );

    // Pause the animation.
    virtual void Pause();

    // Resume the animation from where ever it currently is in the animation.
    virtual void Resume();

    // 
    virtual void End( bool skip);

    // Set to a specific time in the animation.
    virtual void Seek( float time );

    // Whether the animation is playing or not.
    virtual bool IsPlaying() const;

    // Get the total time it takes to complete the animation.
    virtual float GetEndTime() const;

private:



private:

    // The object that the animation is applied to. This pointer does not belong to this class.
    iObject * _pObject = nullptr;

    // AGK id of the tween chain object.
    uint _chainId = 0;

    // AGK tween ids.
    std::vector<CTween *> _tweenList;
};

#endif  // __tween_animation_h__

#ifndef __control_h__
#define __control_h__

// Game lib dependencies
#include <common\defs.h>

// Standard lib dependencies
#include <vector>
#include <map>

// Forward declarations
class iObject;
class CTweenChain;

/// *************************************************************************
/// <summary> 
/// Class to hold base control behavior.
/// </summary>
/// *************************************************************************
class CControl
{
public:

    CControl();
    virtual ~CControl();

    // Update the control.
    virtual void Update();

private:

    // The type of control.
    NDefs::EControlType type;

    // List of sprites associated with the control.
    std::vector<iObject *> _pSpriteList;

    // The current state of the control.
    NDefs::EControlState _state = NDefs::ECS_DISABLED;

    // Map of the animations and their corresponding control state;
    std::map<NDefs::EControlState, CTweenChain *> _animationList;
};

#endif  // __control_h__
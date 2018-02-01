#ifndef __control_h__
#define __control_h__

// Game lib dependencies
#include <common\defs.h>

// Standard lib dependencies
//#include <string>
#include <vector>

// Forward declarations
class CSprite2D;

/// *************************************************************************
/// <summary> 
/// Class to hold base control behavior.
/// </summary>
/// *************************************************************************
class CControl
{
public:
    CControl();
    ~CControl();

private:

    // The type of control.
    NDefs::EControlType type;

    // The state of the control.
    NDefs::EControlState state;

    // Sprite to control each other sprite.
    CSprite2D * pHeadSprite;

    // List of sprites associated with the control.
    std::vector<CSprite2D *> _pSpriteList;
};

#endif  // __control_h__
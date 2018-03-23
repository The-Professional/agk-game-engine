#ifndef __control_h__
#define __control_h__

// Physical component dependency
#include <2d\sprite2d.h>

// Game lib dependencies
#include <common\defs.h>
#include <common\bitmask.h>

// Standard lib dependencies
#include <vector>
#include <map>


/// *************************************************************************
/// <summary> 
/// Class to hold base control behavior.
/// </summary>
/// *************************************************************************
class CControl : public CSprite2D
{
public:

    // Delete the object that belongs to the AGK id.
    virtual void DeleteObject();

    // Get the control type.
    NDefs::EControlType GetControlType() const;

    // Access functions for the control's state.
    virtual void SetState( NDefs::EControlState state );
    NDefs::EControlState GetState() const;

    // Play an animation.
    virtual void Play( const std::string & name, NDefs::EStopType stopType = NDefs::EST_NULL );

    // Stop an animation.
    virtual void Stop( NDefs::EStopType = NDefs::EST_STOP );
    virtual void Stop( const std::string & name, NDefs::EStopType stopType = NDefs::EST_STOP );

    // Whether or not an animation is playing.
    virtual bool IsPlaying( bool includePaused = false );
    virtual bool IsPlaying( const std::string & name, bool includePaused = false );

private:

    void ApplyColor();

private:

    CControl();
    virtual ~CControl();

    // The type of control.
    NDefs::EControlType _controlType;

    // List of sprites associated with the control.
    std::vector<iObject *> _pSpriteList;

    // The current state of the control.
    NDefs::EControlState _state = NDefs::ECS_DISABLED;

    // The window alignment of the control.
    CBitmask<uint> _alignment = NDefs::EA_CENTER;
};

#endif  // __control_h__
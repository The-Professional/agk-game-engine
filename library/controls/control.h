#ifndef __control_h__
#define __control_h__

// Physical component dependency
#include <common\iobject.h>

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
class CControl : public iObject
{
public:

    // Delete the dummy sprite that belongs to the AGK id.
    virtual void DeleteObject();

    // Update AGK with the current color and transformation data.
    virtual void ApplyPosition( const CVector3 & position );
    virtual void ApplyRotation( const CVector3 & rotation );
    virtual void ApplySize( const CVector3 & size );
    virtual void ApplyColor( const CColor & color );

    // Get the current transformation data set in AGK.
    virtual CVector3 GetWorldPos() const;
    virtual CVector3 GetWorldRot() const;
    virtual CVector3 GetWorldSize() const;

    // Get the control type.
    NDefs::EControlType GetControlType() const;

    // Access functions for the control's state.
    virtual void SetState( NDefs::EControlState state );
    NDefs::EControlState GetState() const;

    // Reset the control's position using its previous position.
    virtual void Reposition();

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
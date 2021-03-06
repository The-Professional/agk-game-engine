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

// Forward declarations
class CControlData;

/// *************************************************************************
/// <summary> 
/// Class to hold base control behavior.
/// </summary>
/// *************************************************************************
class iControl : public iObject
{
public:

    // Destructor.
    virtual ~iControl();

    // Get the name of the control.
    virtual const std::string & GetName() const;

    // Clears all of the control's data that belong to it.
    virtual void Clear();

    // Delete the object that belongs to the AGK id.
    virtual void DeleteObject();

    // Access functions for whether the sprite is marked for deletion.
    virtual void MarkForDeletion();
    virtual bool IsMarkedForDeletion() const;

    // Get the data used to create the control.
    const CControlData * GetData() const;

    // Get the current transformation data set in AGK.
    virtual CVector3<float> GetWorldPos() const;
    virtual CVector3<float> GetWorldRot() const;
    virtual CVector3<float> GetWorldSize() const;

    // Update the size or scale, depending on which has been changed.
    virtual void UpdateSize();
    virtual void UpdateScale();

    // Get the control's visibility.
    virtual bool IsVisible() const;

    // Access functions for the control's alignment.
    virtual void SetAlignment( const CBitmask<uint> & alignment );
    virtual CBitmask<uint> GetAlignment() const;

    // Reset the control's position using its previous position.
    virtual void Reposition();

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

protected:

    // Abstract Constructor.
    iControl();

    // Apply changes to AGK.
    virtual void ApplyPosition();
    virtual void ApplyRotation();
    virtual void ApplyScale();
    virtual void ApplyColor();
    virtual void ApplyVisibility();

protected:

    // Control data this control is based off of. The control does not own this.
    const CControlData * _pData = nullptr;

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
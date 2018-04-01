#ifndef __menu_h__
#define __menu_h__

// Physical component dependency
#include <common\iobject.h>

// Game lib dependencies
#include <common\defs.h>
#include <common\bitmask.h>

// Standard lib dependencies
#include <vector>
#include <map>

// Forward declarations
class CMenuData;
class iControl;

/// *************************************************************************
/// <summary> 
/// Class to hold base control behavior.
/// </summary>
/// *************************************************************************
class CMenu : public iObject
{
public:
    CMenu( const std::string & name );
    virtual ~CMenu();

    // Get the name of the menu.
    virtual const std::string & GetName() const;

    // Initialize the menu using the menu's name.
    virtual void Init( const std::string & name );

    // Clears all of the menu's data that belong to it.
    virtual void Clear();

    // Delete the object that belongs to the AGK id.
    virtual void DeleteObject();

    // Access functions for whether the sprite is marked for deletion.
    virtual void MarkForDeletion();
    virtual bool IsMarkedForDeletion() const;

    // Get the data used to create the menu.
    const CMenuData * GetData() const;

    // Get the current transformation data set in AGK.
    virtual CVector3<float> GetWorldPos() const;
    virtual CVector3<float> GetWorldRot() const;
    virtual CVector3<float> GetWorldSize() const;

    // Update the size or scale, depending on which has been changed.
    virtual void UpdateSize();
    virtual void UpdateScale();

    // Get the menu's visibility.
    virtual bool IsVisible() const;

    // Access functions for the menu's alignment.
    virtual void SetAlignment( const CBitmask<uint> & alignment );
    virtual CBitmask<uint> GetAlignment() const;

    // Reset the menu's position using its previous position.
    virtual void Reposition();

    // Access functions for the menu's state.
    virtual void SetEnabled( bool enabled );
    virtual bool IsEnabled() const;

    // Play an animation.
    virtual void Play( const std::string & name, NDefs::EStopType stopType = NDefs::EST_NULL );

    // Stop an animation.
    virtual void Stop( NDefs::EStopType = NDefs::EST_STOP );
    virtual void Stop( const std::string & name, NDefs::EStopType stopType = NDefs::EST_STOP );

    // Whether or not an animation is playing.
    virtual bool IsPlaying( bool includePaused = false );
    virtual bool IsPlaying( const std::string & name, bool includePaused = false );

protected:

    // Apply changes to AGK.
    virtual void ApplyPosition();
    virtual void ApplyRotation();
    virtual void ApplyScale();
    virtual void ApplyColor();
    virtual void ApplyVisibility();

protected:

    // Menu data this menu is based off of. The menu does not own this.
    const CMenuData * _pData = nullptr;

    // List of sprites associated with the menu.
    std::vector<iObject *> _pSpriteList;

    // List of controls associated with the menu.
    std::vector<iControl *> _pControlList;

    // The current state of the menu.
    bool _enabled = true;

    // The window alignment of the menu.
    CBitmask<uint> _alignment = NDefs::EA_CENTER;
};

#endif  // __menu_h__
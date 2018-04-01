#ifndef __sprite_2d_h__
#define __sprite_2d_h__

// Physical dependency
#include <common\iobject.h>

// Game lib dependencies
#include <common\defs.h>
#include <common\vector2.h>
#include <common\vector3.h>
#include <common\bitmask.h>

// Standard lib dependencies
#include <string>

// Forward Declarations
class CSpriteData2D;
class CColor;


/// *************************************************************************
/// <summary>
/// Class to hold 2D sprite information. 
/// </summary>
/// *************************************************************************
class CSprite2D : public iObject
{
public:

    CSprite2D( const std::string & name );
    ~CSprite2D();

    // Get the name of the sprite.
    virtual const std::string & GetName() const;

    // Initialize the sprite using its sprite data.
    virtual void Init( const std::string & name );

    // Delete the object that belongs to the AGK id.
    virtual void DeleteObject();

    // Access functions for whether the sprite is marked for deletion.
    virtual void MarkForDeletion();
    virtual bool IsMarkedForDeletion() const;

    // Get the data used to create the sprite.
    const CSpriteData2D * GetData() const;

    // Get the current transformation data set in AGK.
    virtual CVector3<float> GetWorldPos() const;
    virtual CVector3<float> GetWorldRot() const;
    virtual CVector3<float> GetWorldSize() const;

    // Update the size or scale, depending on which has been changed.
    virtual void UpdateSize();
    virtual void UpdateScale();

    // Get the sprite's visibility.
    virtual bool IsVisible() const;

    // Access functions for the sprite's alignment.
    virtual void SetAlignment( const CBitmask<uint> & alignment );
    virtual CBitmask<uint> GetAlignment() const;

    // Reset the sprite's position using its previous position.
    virtual void Reposition();

protected:

    // Clears all of the sprite's data that belong to it.
    virtual void Clear();

    // Apply changes to AGK.
    virtual void ApplyPosition();
    virtual void ApplyRotation();
    virtual void ApplyScale();
    virtual void ApplyColor();
    virtual void ApplyVisibility();

protected:

    // Sprite data this sprite is based off of. The sprite does not own this.
    const CSpriteData2D * _pData = nullptr;

    // The window alignment of the sprite.
    CBitmask<uint> _alignment = NDefs::EA_CENTER;
};


#endif  // __sprite_2d_h__

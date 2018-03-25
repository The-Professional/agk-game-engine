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

    CSprite2D();
    CSprite2D( CSpriteData2D * pData );
    ~CSprite2D();

    // Get the name of the sprite.
    virtual const std::string & GetName() const;

    // Initialize the sprite using its sprite data.
    virtual void Init( CSpriteData2D * pData );

    // Clears all of the sprite's data that belong to it.
    virtual void Clear();

    // Delete the object that belongs to the AGK id.
    virtual void DeleteObject();

    // Get the data used to create the sprite.
    const CSpriteData2D * GetData() const;

    // Get the current transformation data set in AGK.
    virtual CVector3 GetWorldPos() const;
    virtual CVector3 GetWorldRot() const;
    virtual CVector3 GetWorldSize() const;

    // Update the size or scale, depending on which has been changed.
    virtual void UpdateSize();
    virtual void UpdateScale();

    // Access functions for the sprite's visibility.
    virtual void SetVisible( bool visible );
    virtual bool IsVisible() const;

    // Access functions for the sprite's alignment.
    virtual void SetAlignment( const CBitmask<uint> & alignment );
    virtual CBitmask<uint> GetAlignment() const;

    // Reset the sprite's position using its previous position.
    virtual void Reposition();

protected:

    // Apply the current transformations and color to AGK.
    virtual void ApplyPosition();
    virtual void ApplyRotation();
    virtual void ApplyScale();
    virtual void ApplyColor();

protected:

    // Sprite data this sprite is based off of. The sprite does not own this.
    const CSpriteData2D * _pData = nullptr;

    // The window alignment of the sprite.
    CBitmask<uint> _alignment = NDefs::EA_CENTER;
};


#endif  // __sprite_2d_h__

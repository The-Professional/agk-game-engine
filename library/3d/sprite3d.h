#ifndef __sprite_3d_h__
#define __sprite_3d_h__

// Physical dependency
#include <common\iobject.h>

// Game lib dependencies
#include <common\defs.h>

// Standard lib dependencies
#include <string>

// Forward Declarations
class CSpriteData3D;
class CCollectionObject;

/// *************************************************************************
/// <summary>
/// Class to hold 3D sprite information. 
/// </summary>
/// *************************************************************************
class CSprite3D : public iObject
{
public:

    CSprite3D();
    CSprite3D( CSpriteData3D * pData );
    ~CSprite3D();

    // Initialize the sprite using its sprite data.
    void Init( CSpriteData3D * pData );

    // Delete the object that belongs to the AGK id.
    virtual void DeleteObject();

    // Get the data used to create the sprite.
    const CSpriteData3D * GetData() const;

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

protected:

    // Apply the current transformations and color to AGK.
    virtual void ApplyPosition();
    virtual void ApplyRotation();
    virtual void ApplyScale();
    virtual void ApplyColor();

protected:

    // Sprite data this sprite is based off of. The sprite does not own this.
    const CSpriteData3D * _pData = nullptr;
};


#endif  // __sprite_3d_h__
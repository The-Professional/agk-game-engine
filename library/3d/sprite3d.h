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

/// *************************************************************************
/// <summary>
/// Class to hold 3D sprite information. 
/// </summary>
/// *************************************************************************
class CSprite3D : public iObject
{
public:

    CSprite3D();
    CSprite3D( const CSpriteData3D * objectData );

    ~CSprite3D();

    // Initialize the sprite using its sprite data.
    void Init();

    // Delete the object that belongs to the AGK id.
    virtual void DeleteObject();

    // Access functions for the data used to create the sprite.
    void SetData( CSpriteData3D * pData );
    const CSpriteData3D * GetData() const;

    // Update AGK with the current color and transformation data.
    virtual void UpdatePosAGK();
    virtual void UpdateRotAGK();
    virtual void UpdateSizeAGK();
    virtual void UpdateColorAGK();

    // Access functions for the sprite's visibility.
    virtual void SetVisible( bool visible );
    virtual bool IsVisible() const;

private:

    // Sprite data this sprite is based off of. The sprite does not own this.
    const CSpriteData3D * _pData = nullptr;
};


#endif  // __sprite_3d_h__
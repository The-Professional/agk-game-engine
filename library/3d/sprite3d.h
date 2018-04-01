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

    CSprite3D( const std::string & name );
    ~CSprite3D();

    // Get the name of the sprite.
    virtual const std::string & GetName() const;

    // Initialize the sprite using its sprite data.
    void Init( const std::string & name );

    // Delete the object that belongs to the AGK id.
    virtual void DeleteObject();

    // Access functions for whether the sprite is marked for deletion.
    virtual void MarkForDeletion();
    virtual bool IsMarkedForDeletion() const;

    // Get the data used to create the sprite.
    const CSpriteData3D * GetData() const;

    // Get the current transformation data set in AGK.
    virtual CVector3<float> GetWorldPos() const;
    virtual CVector3<float> GetWorldRot() const;
    virtual CVector3<float> GetWorldSize() const;

    // Update the size or scale, depending on which has been changed.
    virtual void UpdateSize();
    virtual void UpdateScale();

    // Get the sprite's visibility.
    virtual bool IsVisible() const;

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
    const CSpriteData3D * _pData = nullptr;
};


#endif  // __sprite_3d_h__
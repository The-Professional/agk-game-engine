#ifndef __sprite_3d_h__
#define __sprite_3d_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\vector3.h>

// Standard lib dependencies
#include <string>

// Forward Declarations
class CSpriteData3D;

/// *************************************************************************
/// <summary>
/// Class to hold 3D sprite information. 
/// </summary>
/// *************************************************************************
class CSprite3D
{
public:

    CSprite3D();
    CSprite3D( const CSpriteData3D * objectData );

    ~CSprite3D();

    // Initialize
    void Init( const CSpriteData3D * objectData );
    void Clear();

    // Get the name of the sprite.
    const std::string & GetName() const;

    // Access functions for the sprite's position.
    void SetPos( float x, float y, float z );
    void SetPos( const CVector3 & pos );
    CVector3 GetPos() const;
    float GetPosX() const;
    float GetPosY() const;
    float GetPosZ() const;

    // Access functions for the sprite's rotation.
    void SetRot( float x, float y, float z );
    void SetRot( const CVector3 & rot );
    void IncRot( float x, float y, float z );
    void IncRotX( float value );
    void IncRotY( float value );
    void IncRotZ( float value );
    CVector3 GetRot() const;
    float GetRotX() const;
    float GetRotY() const;
    float GetRotZ() const;

    // Access functions for the sprite's scale.
    void SetScale( float uniform );
    void SetScale( float x, float y, float z );
    void SetScale( const CVector3 & scale );
    const CVector3 & GetScale() const;
    float GetScaleX() const;
    float GetScaleY() const;
    float GetScaleZ() const;

private:

    // Sprite data this sprite is based off of. The sprite does not own this.
    const CSpriteData3D * _pData;

    // ID of the sprite.
    uint _id = 0;

    // Scale of the sprite (AGK has no functions to retrieve scale).
    CVector3 _scale;
};


#endif  // __sprite_3d_h__
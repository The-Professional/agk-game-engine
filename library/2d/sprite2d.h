#ifndef __sprite_2d_h__
#define __sprite_2d_h__

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

template <typename type>
class CSize;

/// *************************************************************************
/// <summary>
/// Class to hold 2D sprite information. 
/// </summary>
/// *************************************************************************
class CSprite2D
{
public:

    CSprite2D();
    CSprite2D( const CSpriteData2D * objectData );

    ~CSprite2D();

    // Initialize
    void Init( const CSpriteData2D * objectData );
    void Clear();

    // Get the id of the sprite.
    uint GetID() const;

    // Get the name of the sprite.
    const std::string & GetName() const;

    // Access functions for the sprite's position.
    void SetPos( float x, float y );
    void SetPos( float x, float y, float z );
    void SetPos( const CVector2 & pos );
    void SetPos( const CVector3 & pos );
    void SetPosX( float x );
    void SetPosY( float y );
    void SetPosZ( float z );
    CVector2 GetPos() const;
    float GetPosX() const;
    float GetPosY() const;
    float GetPosZ() const;

    // Access functions for the sprite's rotation.
    void SetRot( float angle);
    void IncRot( float angle );
    float GetRot() const;

    // Access functions for the sprite's scale.
    void SetScale( float uniform );
    void SetScale( float x, float y );
    void SetScale( const CVector2 & scale );
    const CVector2 & GetScale() const;
    float GetScaleX() const;
    float GetScaleY() const;

    // Access functions for the sprite's size.
    void SetSize( const CSize<float> & size );
    CSize<float> GetSize() const;

    // Access functions for the sprite's color.
    void SetColor( const CColor & color );
    CColor GetColor() const;

    // Access functions for the sprite's visibility.
    void SetVisible( bool visible );
    bool IsVisible() const;

    // Reset the sprite's position using its previous position.
    void Reposition();

private:

    // Sprite data this sprite is based off of. The sprite does not own this.
    const CSpriteData2D * _pData = nullptr;

    // ID of the sprite.
    uint _id = 0;

    // Scale of the sprite (AGK has no functions to retrieve scale).
    CVector2 _scale;

    // The previous set position of the sprite. This is used to retain alignment.
    CVector2 _vPos;

    // The window alignment of the sprite.
    CBitmask<uint> _alignment = NDefs::EA_CENTER;
};


#endif  // __sprite_2d_h__

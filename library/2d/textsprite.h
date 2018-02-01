#ifndef __text_sprite_h__
#define __text_sprite_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\vector2.h>

// Standard lib dependencies
#include <string>

// Forward Declarations
class CTextSpriteData;

/// *************************************************************************
/// <summary>
/// Class to hold text sprite information. 
/// </summary>
/// *************************************************************************
class CTextSprite
{
public:

    CTextSprite();
    CTextSprite( const CTextSpriteData * pData );

    ~CTextSprite();

    // Initialize
    void Init( const CTextSpriteData * pData );
    void Clear();

    // Get the id of the sprite.
    uint GetID() const;

    // Get the name of the sprite.
    const std::string & GetName() const;

    // Access functions for the sprite's position.
    void SetPos( float x, float y );
    void SetPos( float x, float y, int depth );
    void SetPos( const CVector2 & pos );
    void SetPos( const CVector2 & pos, int depth );
    void SetDepth( int depth );
    CVector2 GetPos() const;
    float GetPosX() const;
    float GetPosY() const;
    int GetDepth() const;

    // Access functions for the sprite's rotation.
    void SetRot( float angle );
    void IncRot( float angle );
    float GetRot() const;

    // Access functions for the sprite's scale.
    void SetScale( float uniform );
    void SetScale( float x, float y );
    void SetScale( const CVector2 & scale );
    const CVector2 & GetScale() const;
    float GetScaleX() const;
    float GetScaleY() const;

    // Access functions for the sprite's visibility.
    void SetVisible( bool visible );
    bool IsVisible() const;

private:

    // Sprite data this sprite is based off of. The sprite does not own this.
    const CTextSpriteData * _pData = nullptr;

    // ID of the sprite.
    uint _id = 0;

    // Scale of the sprite (AGK has no functions to retrieve scale).
    CVector2 _scale;
};


#endif  // __text_sprite_h__

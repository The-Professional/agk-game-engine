#ifndef __text_sprite_h__
#define __text_sprite_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\vector2.h>
#include <common\vector3.h>
#include <common\color.h>
#include <common\bitmask.h>

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
    void SetPos( float x, float y, float z );
    void SetPos( const CVector2 & pos );
    void SetPos( const CVector3 & pos );
    void SetPosX( float x );
    void SetPosY( float y );
    void SetPosZ( float z );
    CVector3 GetPos() const;
    float GetPosX() const;
    float GetPosY() const;
    float GetPosZ() const;

    // Access functions for the sprite's rotation.
    void SetRot( float angle );
    void IncRot( float angle );
    float GetRot() const;

    // Access functions for the sprite's scale.
    void SetScale( float uniform );
    float GetScale() const;

    // Access functions for the sprite's visibility.
    void SetVisible( bool visible );
    bool IsVisible() const;

    // Access functions for the text sprite's font.
    void SetFont( uint fontId );
    uint GetFont() const;

    // Access functions for the text sprite's text.
    void SetText( const std::string & text );
    std::string GetText() const;

    // Access functions for the text sprite's text spacing.
    void SetTextSpacing( float textSpacing );
    float GetTextSpacing() const;

    // Access functions for the text sprite's line spacing.
    void SetLineSpacing( float lineSpacing );
    float GetLineSpacing() const;

    // Access functions for the text sprite's max width before text begins to wrap.
    void SetMaxWidth( float maxWidth );
    float GetMaxWidth() const;

    // Access functions for the text sprite's color.
    void SetColor( const CColor & color );
    CColor GetColor() const;

    // Access functions for the text sprite's text alignment.
    void SetTextAlignment( NDefs::ETextAlignment alignment );
    NDefs::ETextAlignment GetTextAlignment() const;

    // Access functions for the text sprite's alignment.
    void SetAlignment( const CBitmask<uint> & alignment );
    const CBitmask<uint> & GetAlignment() const;

    // Reset the sprite's position using its previous position.
    void Reposition();

private:

    // Sprite data this sprite is based off of. The sprite does not own this.
    const CTextSpriteData * _pData = nullptr;

    // ID of the text sprite.
    uint _id = 0;

    // ID of the font used.
    uint _fontId = 0;

    // The previous set position of the sprite. This is used to retain alignment.
    CVector2 _prevPos;
    
    // Text sprite's max width before text begins to wrap.
    float _maxWidth = 0;

    // The alignment of the text.
    NDefs::ETextAlignment _textAlignment;

    // The alignment of the sprite.
    CBitmask<uint> _alignment;

    // Text displayed by the sprite.
    std::string _text;
};


#endif  // __text_sprite_h__

#ifndef __text_sprite_h__
#define __text_sprite_h__

// Physical dependency
#include <common\iobject.h>

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
class CTextSprite : public iObject
{
public:

    CTextSprite();
    CTextSprite( const CTextSpriteData * pData, const std::string & text );
    ~CTextSprite();

    // Initialize the sprite using its sprite data.
    void Init( const CTextSpriteData * pData, const std::string & text );

    // Clears all of the text sprite's data that belong to it.
    virtual void Clear();

    // Delete the object that belongs to the AGK id.
    virtual void DeleteObject();

    // Get the data used to create the sprite.
    const CTextSpriteData * GetData() const;

    // Get the current transformation data set in AGK.
    virtual CVector3 GetWorldPos() const;
    virtual CVector3 GetWorldRot() const;
    virtual CVector3 GetWorldSize() const;

    // Access functions for the sprite's visibility.
    virtual void SetVisible( bool visible );
    virtual bool IsVisible() const;

    // Access functions for the text sprite's font.
    virtual void SetFont( uint fontId );
    virtual uint GetFont() const;

    // Access functions for the text sprite's text.
    virtual void SetText( const std::string & text );
    virtual std::string GetText() const;

    // Access functions for the text sprite's size.
    virtual void SetTextSize( float size );
    virtual float GetTextSize() const;

    // Access functions for the text sprite's text spacing.
    virtual void SetTextSpacing( float textSpacing );
    virtual float GetTextSpacing() const;

    // Access functions for the text sprite's line spacing.
    virtual void SetLineSpacing( float lineSpacing );
    virtual float GetLineSpacing() const;

    // Access functions for the text sprite's max width before text begins to wrap.
    virtual void SetMaxWidth( float maxWidth );
    virtual float GetMaxWidth() const;

    // Access functions for the text sprite's text alignment.
    virtual void SetTextAlignment( NDefs::ETextAlignment alignment );
    virtual NDefs::ETextAlignment GetTextAlignment() const;

    // Access functions for the text sprite's alignment.
    virtual void SetAlignment( const CBitmask<uint> & alignment );
    virtual CBitmask<uint> GetAlignment() const;

    // Reset the sprite's position using its previous position.
    virtual void Reposition();

protected:

    // Apply the current transformations and color to AGK.
    virtual void ApplyPosition();
    virtual void ApplyRotation();
    virtual void ApplySize();
    virtual void ApplyScale();
    virtual void ApplyColor();

protected:

    // Sprite data this sprite is based off of. The sprite does not own this.
    const CTextSpriteData * _pData = nullptr;

    // ID of the font used.
    uint _fontId = 0;
    
    // Text sprite's max width before text begins to wrap.
    float _maxWidth = 0;

    // The alignment of the text.
    NDefs::ETextAlignment _textAlignment;

    // The alignment of the sprite.
    CBitmask<uint> _alignment = NDefs::EA_CENTER;

    // Text displayed by the sprite.
    std::string _text;
};


#endif  // __text_sprite_h__

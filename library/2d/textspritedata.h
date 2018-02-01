#ifndef __text_sprite_data_h__
#define __text_sprite_data_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\bitmask.h>
#include <utilities\jsonparsehelper.h>

// Standard lib dependencies
#include <string>

/// *************************************************************************
/// <summary>
/// Class containing the default creation data for a text sprite.
/// </summary>
/// *************************************************************************
class CTextSpriteData
{
public:

    // Constructor/Destructor
    CTextSpriteData();
    CTextSpriteData( const CTextSpriteData & obj );
    ~CTextSpriteData();

    // Load the sprite data from the passed in iterator.
    void LoadFromIter( const std::string & name, nlohmann::json::const_iterator iter );

    // Access functions for the text sprite data.
    const std::string & GetName() const;
    const std::string & GetFont() const;
    const std::string & GetText() const;
    float GetFontSize() const;
    float GetTextSpacing() const;
    float GetLineSpacing() const;
    float GetMaxWidth() const;
    const CBitmask<uint> & GetTextAlignment() const;
    const CBitmask<uint> & GetAlignment() const;

private:

    // The name of the text sprite.
    std::string _name;

    // The font to be used.
    std::string _font;

    // The text to be displayed.
    std::string _text;

    // The size of the font.
    float _fontSize = 4;

    // The space between characters.
    float _textSpacing = 0;

    // The space between lines.
    float _lineSpacing = 0;

    // The max distance until the text wraps around.
    float _maxWidth = 100;

    // The alignment of the text. (i.e. left, right, center)
    CBitmask<uint> _textAlignment = NDefs::EA_LEFT;

    // The alignment of the sprite.
    CBitmask<uint> _alignment = NDefs::EA_TOP | NDefs::EA_LEFT;
};

#endif  // __text_sprite_data_h__

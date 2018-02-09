// Physical component dependency
#include "textspritedata.h"

// Game lib dependencies
#include <utilities\deletefuncs.h>

/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CTextSpriteData::CTextSpriteData()
{
}


/// *************************************************************************
/// <summary>
/// Copy constructor
/// </summary>
/// *************************************************************************
CTextSpriteData::CTextSpriteData( const CTextSpriteData & obj )
{
    *this = obj;
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CTextSpriteData::~CTextSpriteData()
{
}


/// *************************************************************************
/// <summary>
/// Load the sprite data from the passed in iterator.
/// </summary>
/// <param name="iter"> JSON node to parse. </param>
/// *************************************************************************
void CTextSpriteData::LoadFromIter( const std::string & name, nlohmann::json::const_iterator iter )
{
    _name = name;

    NParseHelper::GetString( iter, "font", _font );
    NParseHelper::GetFloat( iter, "size", _size );
    NParseHelper::GetFloat( iter, "textSpacing", _textSpacing );
    NParseHelper::GetFloat( iter, "lineSpacing", _lineSpacing );
    NParseHelper::GetFloat( iter, "maxWidth", _maxWidth );
    NParseHelper::GetColor( iter, _color );
    NParseHelper::GetTextAlignment( iter, _textAlignment );
    NParseHelper::GetAlignment( iter, "alignment", _alignment );
}


/// *************************************************************************
/// <summary> 
/// Get the name of the text sprite.
/// </summary>
/// *************************************************************************
const std::string & CTextSpriteData::GetName() const
{
    return _name;
}


/// *************************************************************************
/// <summary> 
/// Get the font to be used.
/// </summary>
/// *************************************************************************
const std::string & CTextSpriteData::GetFont() const
{
    return _font;
}


/// *************************************************************************
/// <summary> 
/// Get the size of the font.
/// </summary>
/// *************************************************************************
float CTextSpriteData::GetSize() const
{
    return _size;
}


/// *************************************************************************
/// <summary> 
/// Get the space between characters.
/// </summary>
/// *************************************************************************
float CTextSpriteData::GetTextSpacing() const
{
    return _textSpacing;
}


/// *************************************************************************
/// <summary> 
/// Get the space between lines.
/// </summary>
/// *************************************************************************
float CTextSpriteData::GetLineSpacing() const
{
    return _lineSpacing;
}


/// *************************************************************************
/// <summary> 
/// Get the max distance until the text wraps around.
/// </summary>
/// *************************************************************************
float CTextSpriteData::GetMaxWidth() const
{
    return _maxWidth;
}


/// *************************************************************************
/// <summary> 
/// Get the color of the text.
/// </summary>
/// *************************************************************************
const CColor & CTextSpriteData::GetColor() const
{
    return _color;
}


/// *************************************************************************
/// <summary> 
/// Get the alignment of the text.
/// </summary>
/// *************************************************************************
NDefs::ETextAlignment CTextSpriteData::GetTextAlignment() const
{
    return _textAlignment;
}


/// *************************************************************************
/// <summary> 
/// Get the alignment of the sprite.
/// </summary>
/// *************************************************************************
const CBitmask<uint> & CTextSpriteData::GetAlignment() const
{
    return _alignment;
}
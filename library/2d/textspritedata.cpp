// Physical component dependency
#include "textspritedata.h"

// Game lib dependencies
#include <utilities\deletefuncs.h>

using namespace std;
using namespace nlohmann;

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
void CTextSpriteData::LoadFromIter( const string & name, json::const_iterator iter )
{
    _name = name;

    NParseHelper::GetValue( iter, "font", _font );
    NParseHelper::GetValue( iter, "size", _size );
    NParseHelper::GetValue( iter, "textSpacing", _textSpacing );
    NParseHelper::GetValue( iter, "lineSpacing", _lineSpacing );
    NParseHelper::GetValue( iter, "maxWidth", _maxWidth );
    NParseHelper::GetColor( iter, _color );
    NParseHelper::GetTextAlignment( iter, _textAlignment );
    NParseHelper::GetAlignment( iter, "alignment", _alignment );
    NParseHelper::GetValueList( iter, "animations", _animationList );
}


/// *************************************************************************
/// <summary> 
/// Get the name of the text sprite.
/// </summary>
/// *************************************************************************
const string & CTextSpriteData::GetName() const
{
    return _name;
}


/// *************************************************************************
/// <summary> 
/// Get the font to be used.
/// </summary>
/// *************************************************************************
const string & CTextSpriteData::GetFont() const
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
const CVector4<float> & CTextSpriteData::GetColor() const
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


/// *************************************************************************
/// <summary> 
/// Get the list of animations this sprite can perform.
/// </summary>
/// *************************************************************************
const vector<string> & CTextSpriteData::GetAnimationList() const
{
    return _animationList;
}
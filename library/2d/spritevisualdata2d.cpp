// Physical component dependency
#include "spritevisualdata2d.h"

// Game lib dependencies
#include <common\color.h>
#include <common\size.h>
#include <utilities\jsonparsehelper.h>


/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CSpriteVisualData2D::CSpriteVisualData2D()
{
}


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CSpriteVisualData2D::~CSpriteVisualData2D()
{
    // NOTE: Nothing should ever be deleted here
}


/// *************************************************************************
/// <summary>
/// Load the visual sprite data from the passed in iterator.
/// </summary>
/// <param name="iter"> JSON node to parse. </param>
/// *************************************************************************
void CSpriteVisualData2D::LoadFromIter( nlohmann::json::const_iterator iter )
{
    NParseHelper::GetColor( iter, _color );
    NParseHelper::GetString( iter, "textureMap", _textureMap );
    _sizeSet = NParseHelper::GetWH( iter, "size", _size );
}


/// *************************************************************************
/// <summary> 
/// Get the sprite's default color.
/// </summary>
/// *************************************************************************
const CColor & CSpriteVisualData2D::GetColor() const
{
    return _color;
}


/// *************************************************************************
/// <summary> 
/// Get the name of the sprite's texture.
/// </summary>
/// *************************************************************************
const std::string & CSpriteVisualData2D::GetTextureMap() const
{
    return _textureMap;
}


/// *************************************************************************
/// <summary> 
/// Set the sprite's size. This is considered the default size, so we'll want
/// to know this. If it's not set in the sprite's data, we'll need to set this
/// after we create the first sprite and know its size.
/// </summary>
/// *************************************************************************
void CSpriteVisualData2D::SetSize( const CVector2 & size )
{
    if( size.IsFilled() )
    {
        _size = size;
        _sizeSet = true;
    }
}


/// *************************************************************************
/// <summary> 
/// Get the sprite's size.
/// </summary>
/// *************************************************************************
const CVector2 & CSpriteVisualData2D::GetSize() const
{
    return _size;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the size was set in the data file.
/// </summary>
/// *************************************************************************
bool CSpriteVisualData2D::IsSizeSet() const
{
    return _sizeSet;
}
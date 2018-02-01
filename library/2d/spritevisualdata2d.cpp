// Physical component dependency
#include "spritevisualdata2d.h"

// Game lib dependencies
#include <common\color.h>
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
    NParseHelper::GetWH( iter, "size", _size );
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
/// Get the sprite's size.
/// </summary>
/// *************************************************************************
const CSize & CSpriteVisualData2D::GetSize() const
{
    return _size;
}
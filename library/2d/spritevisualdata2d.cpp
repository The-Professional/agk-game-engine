// Physical component dependency
#include "spritevisualdata2d.h"


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
    NParseHelper::GetValue( iter, "textureMap", _textureMap );
    _sizeSet = NParseHelper::GetWH( iter, "size", _size );

    // If the size hasn't been set, whatever the size of this will be the same as its file.
    // This means we don't have to resize anything after creating a sprite.
    if( !_sizeSet )
        _sizeSameAsFile = true;
}


/// *************************************************************************
/// <summary> 
/// Get the sprite's default color.
/// </summary>
/// *************************************************************************
const CVector4<float> & CSpriteVisualData2D::GetColor() const
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
void CSpriteVisualData2D::SetSize( const CVector2<float> & size )
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
const CVector2<float> & CSpriteVisualData2D::GetSize() const
{
    return _size;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the size was set.
/// </summary>
/// *************************************************************************
bool CSpriteVisualData2D::IsSizeSet() const
{
    return _sizeSet;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the size is the same as the file.
/// </summary>
/// *************************************************************************
bool CSpriteVisualData2D::IsSizeSameAsFile() const
{
    return _sizeSameAsFile;
}
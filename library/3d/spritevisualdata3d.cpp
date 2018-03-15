// Physical component dependency
#include "spritevisualdata3d.h"

// Game lib dependencies
#include <common\defs.h>
#include <common\color.h>
#include <utilities\jsonparsehelper.h>

using namespace std;
using namespace NDefs;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CSpriteVisualData3D::CSpriteVisualData3D()
{
}


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CSpriteVisualData3D::~CSpriteVisualData3D()
{
    // NOTE: Nothing should ever be deleted here
}


/// *************************************************************************
/// <summary>
/// Load the visual sprite data from the passed in iterator.
/// </summary>
/// <param name="iter"> JSON node to parse. </param>
/// *************************************************************************
void CSpriteVisualData3D::LoadFromIter( nlohmann::json::const_iterator iter )
{
    NParseHelper::GetString( iter, "mesh", _mesh );
    NParseHelper::GetColor( iter, _color );
    _sizeSet = NParseHelper::GetWHD( iter, "size", _size );
    NParseHelper::GetString( iter, "textureMap", _textureMap );
    NParseHelper::GetString( iter, "normalMap", _normalMap );
    NParseHelper::GetString( iter, "specularMap", _specularMap );
    NParseHelper::GetDimensions( iter, _width, _height, _depth, _radius, _rows, _columns );
    NParseHelper::GetBool( iter, "castShadow", _castShadow );
    NParseHelper::GetBool( iter, "receiveShadow", _receiveShadow );
    NParseHelper::GetMeshType( iter, _type );

    if( !_sizeSet )
        SetSize( { _width, _height, _depth } );
}


/// *************************************************************************
/// <summary> 
/// Get the sprite's object type.
/// </summary>
/// *************************************************************************
EMeshType CSpriteVisualData3D::GetType() const
{
    return _type;
}


/// *************************************************************************
/// <summary> 
/// Get the sprite's mesh name.
/// </summary>
/// *************************************************************************
const string & CSpriteVisualData3D::GetMesh() const
{
    return _mesh;
}


/// *************************************************************************
/// <summary> 
/// Get the name of the shader used to render this sprite.
/// </summary>
/// *************************************************************************
const string & CSpriteVisualData3D::GetShader() const
{
    return _shader;
}


/// *************************************************************************
/// <summary> 
/// Get the sprite's default color.
/// </summary>
/// *************************************************************************
const CColor & CSpriteVisualData3D::GetColor() const
{
    return _color;
}


/// *************************************************************************
/// <summary> 
/// Get the name of the sprite's texture.
/// </summary>
/// *************************************************************************
const string & CSpriteVisualData3D::GetTextureMap() const
{
    return _textureMap;
}


/// *************************************************************************
/// <summary> 
/// Get the id of the normal map used by the sprite.
/// </summary>
/// *************************************************************************
const string & CSpriteVisualData3D::GetNormalMap() const
{
    return _normalMap;
}


/// *************************************************************************
/// <summary> 
/// Get the id of the specular map used by the sprite.
/// </summary>
/// *************************************************************************
const string & CSpriteVisualData3D::GetSpecularMap() const
{
    return _specularMap;
}


/// *************************************************************************
/// <summary> 
/// Get the width of the sprite.
/// </summary>
/// *************************************************************************
float CSpriteVisualData3D::GetWidth() const
{
    return _width;
}


/// *************************************************************************
/// <summary> 
/// Get the height of the sprite.
/// </summary>
/// *************************************************************************
float CSpriteVisualData3D::GetHeight() const
{
    return _height;
}


/// *************************************************************************
/// <summary> 
/// Get the length of the sprite.
/// </summary>
/// *************************************************************************
float CSpriteVisualData3D::GetDepth() const
{
    return _depth;
}


/// *************************************************************************
/// <summary> 
/// Get the radius of the sprite.
/// </summary>
/// *************************************************************************
float CSpriteVisualData3D::GetRadius() const
{
    return _radius;
}


/// *************************************************************************
/// <summary> 
/// Get the diameter of the sprite.
/// </summary>
/// *************************************************************************
float CSpriteVisualData3D::GetDiameter() const
{
    return _radius * 2.f;
}


/// *************************************************************************
/// <summary> 
/// Get the number of rows used to make a sphere.
/// </summary>
/// *************************************************************************
int CSpriteVisualData3D::GetRows() const
{
    return _rows;
}


/// *************************************************************************
/// <summary> 
/// Get the number of columns used to make a cone, cylinder, or sphere.
/// </summary>
/// *************************************************************************
int CSpriteVisualData3D::GetColumns() const
{
    return _columns;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the sprite casts shadows.
/// </summary>
/// *************************************************************************
bool CSpriteVisualData3D::WillCastShadow() const
{
    return _castShadow;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the sprite will receive shadows cast upon it.
/// </summary>
/// *************************************************************************
bool CSpriteVisualData3D::WillReceiveShadow() const
{
    return _receiveShadow;
}


/// *************************************************************************
/// <summary> 
/// Set the sprite's size. This is considered the default size, so we'll want
/// to know this. If it's not set in the sprite's data, we'll need to set this
/// after we create the first sprite and know its size.
/// </summary>
/// *************************************************************************
void CSpriteVisualData3D::SetSize( const CVector3 & size )
{
    if( !size.IsEmptyX() + !size.IsEmptyY() + !size.IsEmptyZ() > 1 )
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
const CVector3 & CSpriteVisualData3D::GetSize() const
{
    return _size;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the size was set in the data file.
/// </summary>
/// *************************************************************************
bool CSpriteVisualData3D::IsSizeSet() const
{
    return _sizeSet;
}
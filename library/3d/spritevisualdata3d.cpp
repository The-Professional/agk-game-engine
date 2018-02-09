// Physical component dependency
#include "spritevisualdata3d.h"

// Game lib dependencies
#include <common\defs.h>
#include <common\color.h>
#include <utilities\jsonparsehelper.h>


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
    //NParseHelper::GetShader( iter, _shader );
    NParseHelper::GetColor( iter, _color );
    NParseHelper::GetString( iter, "textureMap", _textureMap );
    NParseHelper::GetString( iter, "normalMap", _normalMap );
    NParseHelper::GetString( iter, "specularMap", _specularMap );
    NParseHelper::GetDimensions( iter, _width, _height, _depth, _radius, _rows, _columns );
    NParseHelper::GetBool( iter, "castShadow", _castShadow );
    NParseHelper::GetBool( iter, "receiveShadow", _receiveShadow );

    // Set the object type.
    if( _mesh == "box" )
        _type = NDefs::EMT_BOX;
    else if( _mesh == "cone" )
        _type = NDefs::EMT_CONE;
    else if( _mesh == "cylinder" )
        _type = NDefs::EMT_CYLINDER;
    else if( _mesh == "capsule" )
        _type = NDefs::EMT_CAPSULE;
    else if( _mesh == "plane" )
        _type = NDefs::EMT_PLANE;
    else if( _mesh == "sphere" )
        _type = NDefs::EMT_SPHERE;
    else if( !_mesh.empty() )
        _type = NDefs::EMT_MESH;
}


/// *************************************************************************
/// <summary> 
/// Get the sprite's object type.
/// </summary>
/// *************************************************************************
NDefs::EMeshType CSpriteVisualData3D::GetType() const
{
    return _type;
}


/// *************************************************************************
/// <summary> 
/// Get the sprite's mesh name.
/// </summary>
/// *************************************************************************
const std::string & CSpriteVisualData3D::GetMesh() const
{
    return _mesh;
}


/// *************************************************************************
/// <summary> 
/// Get the name of the shader used to render this sprite.
/// </summary>
/// *************************************************************************
const std::string & CSpriteVisualData3D::GetShader() const
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
const std::string & CSpriteVisualData3D::GetTextureMap() const
{
    return _textureMap;
}


/// *************************************************************************
/// <summary> 
/// Get the id of the normal map used by the sprite.
/// </summary>
/// *************************************************************************
const std::string & CSpriteVisualData3D::GetNormalMap() const
{
    return _normalMap;
}


/// *************************************************************************
/// <summary> 
/// Get the id of the specular map used by the sprite.
/// </summary>
/// *************************************************************************
const std::string & CSpriteVisualData3D::GetSpecularMap() const
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
#ifndef __sprite_visual_data_3d_h__
#define __sprite_visual_data_3d_h__

// Game lib dependencies
#include <utilities\jsonparsehelper.h>
#include <common\defs.h>
#include <common\color.h>
#include <common\vector3.h>

// Standard lib dependencies
#include <string>


/// *************************************************************************
/// <summary> 
/// Class containing the default creation data for a 3D sprite's visual
/// properties.
/// </summary>
/// *************************************************************************
class CSpriteVisualData3D
{
public:

    // Constructor/Destructor
    CSpriteVisualData3D();
    ~CSpriteVisualData3D();

    // Load the visual sprite data from the passed in iterator.
    void LoadFromIter( nlohmann::json::const_iterator iter );

    // Get the sprite's object type.
    NDefs::EMeshType GetType() const;

    // Get the sprite's mesh name.
    const std::string & GetMesh() const;

    // Get the name of the shader used to render this sprite.
    const std::string & GetShader() const;

    // Get the sprite's default color.
    const CColor & GetColor() const;

    // Get the sprite's image names.
    const std::string & GetTextureMap() const;
    const std::string & GetNormalMap() const;
    const std::string & GetSpecularMap() const;

    // Get the sprite's dimensions.
    float GetWidth() const;
    float GetHeight() const;
    float GetDepth() const;
    float GetRadius() const;
    float GetDiameter() const;
    int GetRows() const;
    int GetColumns() const;

    // Whether or not the sprite casts shadows.
    bool WillCastShadow() const;

    // Whether or not the sprite will receive shadows cast upon it.
    bool WillReceiveShadow() const;

    // Access functions for the sprite's size.
    void SetSize( const CVector3 & size );
    const CVector3 & GetSize() const;

    // Whether or not the size was set in the data file.
    bool IsSizeSet() const;

private:

    // Type of object.
    NDefs::EMeshType _type = NDefs::EMT_MESH;

    // Mesh name.
    std::string _mesh;

    // Shader to render the sprite with.
    std::string _shader;

    // Initial color of the sprite.
    CColor _color;

    // Images to map onto the sprite.
    std::string _textureMap, _normalMap, _specularMap;

    // Dimensions used to create the sprite.
    float _width = 0, _height = 0, _depth = 0, _radius = 0;
    int _rows = 0, _columns = 0;

    // If the sprite casts a shadow.
    bool _castShadow = false;
    
    // If the sprite receives shadows cast upon it.
    bool _receiveShadow = false;

    // Whether or not the size was set in the data file.
    bool _sizeSet = false;

    // Size of the sprite.
    CVector3 _size;
};

#endif  // __sprite_visual_data_3d_h__

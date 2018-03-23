#ifndef __sprite_visual_data_2d_h__
#define __sprite_visual_data_2d_h__

// Game lib dependencies
#include <utilities\jsonparsehelper.h>
#include <common\vector2.h>
#include <common\vector4.h>

// Standard lib dependencies
#include <string>

/// *************************************************************************
/// <summary> 
/// Class containing the default creation data for a 2D sprite's visual
/// properties.
/// </summary>
/// *************************************************************************
class CSpriteVisualData2D
{
public:

    CSpriteVisualData2D();
    ~CSpriteVisualData2D();

    // Load the visual sprite data from the passed in iterator.
    void LoadFromIter( nlohmann::json::const_iterator iter );

    // Access functions for the visual sprite data.
    const CVector4 & GetColor() const;
    const std::string & GetTextureMap() const;

    // Access functions for the visual sprite's size.
    void SetSize( const CVector2 & size );
    const CVector2 & GetSize() const;

    // Whether or not the size has been set.
    bool IsSizeSet() const;

    // Whether or not the size is the same as the file.
    bool IsSizeSameAsFile() const;

private:

    // Initial color of the sprite.
    CVector4 _color = 1;

    // Image to map onto the sprite.
    std::string _textureMap;

    // Whether or not the size has been set.
    bool _sizeSet = false;

    // Whether or not the size is the same as the file.
    bool _sizeSameAsFile = false;

    // Size of the sprite.
    CVector2 _size;
};

#endif  // __sprite_visual_data_2d_h__

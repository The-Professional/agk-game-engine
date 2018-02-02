#ifndef __sprite_visual_data_2d_h__
#define __sprite_visual_data_2d_h__

// Game lib dependencies
#include <utilities\jsonparsehelper.h>
#include <common\color.h>
#include <common\size.h>

// Standard lib dependencies
#include <string>

// Forward declarations
template <typename type>
class CSize;

/// *************************************************************************
/// <summary> 
/// Class containing the default creation data for a 2D sprite's visual
/// properties.
/// </summary>
/// *************************************************************************
class CSpriteVisualData2D
{
public:

    // Constructor/Destructor
    CSpriteVisualData2D();
    ~CSpriteVisualData2D();

    // Load the visual sprite data from the passed in iterator.
    void LoadFromIter( nlohmann::json::const_iterator iter );

    // Get the sprite's default color.
    const CColor & GetColor() const;

    // Get the sprite's image names.
    const std::string & GetTextureMap() const;

    // Get the sprite's size.
    const CSize<float> & GetSize() const;

private:

    // Initial color of the sprite.
    CColor _color;

    // Image to map onto the sprite.
    std::string _textureMap;

    // Size of the sprite.
    CSize<float> _size;
};

#endif  // __sprite_visual_data_2d_h__

#ifndef __sprite_visual_data_2d_h__
#define __sprite_visual_data_2d_h__

// Game lib dependencies
#include <utilities\jsonparsehelper.h>
#include <common\color.h>
#include <common\vector2.h>

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
    const CColor & GetColor() const;
    const std::string & GetTextureMap() const;

    // Access functions for the visual sprite's size.
    void SetSize( const CVector2 & size );
    const CVector2 & GetSize() const;

    // Whether or not the size was set in the data file.
    bool IsSizeSet() const;

private:

    // Initial color of the sprite.
    CColor _color;

    // Image to map onto the sprite.
    std::string _textureMap;

    // Whether or not the size was set in the data file.
    bool _sizeSet = false;

    // Size of the sprite.
    CVector2 _size;
};

#endif  // __sprite_visual_data_2d_h__

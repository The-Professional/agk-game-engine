#ifndef __sprite_data_2d_h__
#define __sprite_data_2d_h__

// Game lib dependencies
#include <common\bitmask.h>
#include <2d\spritevisualdata2d.h>
#include <utilities\jsonparsehelper.h>

// Standard lib dependencies
#include <string>
#include <vector>

// Forward declarations
class CSpriteVisualData2D;

/// *************************************************************************
/// <summary>
/// Class containing the default creation data for a 2D sprite.
/// </summary>
/// *************************************************************************
class CSpriteData2D
{
public:

    // Constructor/Destructor
    CSpriteData2D();
    CSpriteData2D( const CSpriteData2D & obj );
    ~CSpriteData2D();

    // Load the sprite data from the passed in iterator.
    void LoadFromIter( const std::string & name, nlohmann::json::const_iterator iter );

    // Access functions for the sprite data.
    const CSpriteVisualData2D * GetVisualData() const;
    const std::string & GetName() const;
    const CBitmask<uint> & GetAlignment() const;
    const std::vector<std::string> & GetAnimationList() const;

private:

    // Visual data of the object
    CSpriteVisualData2D * _pVisualData = nullptr;

    // The name of the object data
    std::string _name;

    // The window alignment of the sprite.
    CBitmask<uint> _alignment = NDefs::EA_CENTER;

    // The list of animations this sprite can perform.
    std::vector<std::string> _animationList;
};

#endif  // __sprite_data_2d_h__

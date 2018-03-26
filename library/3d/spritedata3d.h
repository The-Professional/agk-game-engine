#ifndef __sprite_data_3d_h__
#define __sprite_data_3d_h__

// Game lib dependencies
#include <3d\spritevisualdata3d.h>
#include <utilities\jsonparsehelper.h>

// Standard lib dependencies
#include <string>
#include <vector>

/// *************************************************************************
/// <summary>
/// Class containing the default creation data for a 3D sprite.
/// </summary>
/// *************************************************************************
class CSpriteData3D
{
public:

    CSpriteData3D();
    ~CSpriteData3D();

    // Load the sprite data from the passed in iterator.
    void LoadFromIter( const std::string & name, nlohmann::json::const_iterator iter );

    // Access functions for the sprite data.
    CSpriteVisualData3D * GetVisualData() const;
    CSpriteVisualData3D * GetVisualData();
    const std::string & GetName() const;
    const std::vector<std::string> & GetAnimationList() const;

    // Access functions for the default size of the sprite.
    const CVector3<float> & GetSize() const;

private:

    // Visual data of the object
    CSpriteVisualData3D * _pVisualData = nullptr;

    // The name of the object data
    std::string _name;

    // The list of animations this sprite can perform.
    std::vector<std::string> _animationList;
};

#endif  // __sprite_data_3d_h__

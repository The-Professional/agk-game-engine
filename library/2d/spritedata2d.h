#ifndef __sprite_data_2d_h__
#define __sprite_data_2d_h__

// Game lib dependencies
#include <2d\spritevisualdata2d.h>
#include <utilities\jsonparsehelper.h>

// Standard lib dependencies
#include <string>

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

    // Access functions for the visual data.
    const CSpriteVisualData2D * GetVisualData() const;

    // Access functions for the physics data.
    //const CSpritePhysicsData2D & GetPhysicsData() const;

    // Access functions for the data name.
    const std::string & GetName() const;

private:

    // Visual data of the object
    CSpriteVisualData2D * _pVisualData = nullptr;

    // Physics data of the object
    //CSpritePhysicsData2D _physicsData;

    // The name of the object data
    std::string _name;
};

#endif  // __sprite_data_2d_h__

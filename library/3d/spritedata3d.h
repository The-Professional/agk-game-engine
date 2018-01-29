#ifndef __sprite_data_3d_h__
#define __sprite_data_3d_h__

// Game lib dependencies
#include <3d\spritevisualdata3d.h>
#include <utilities\jsonparsehelper.h>

// Standard lib dependencies
#include <string>

/// *************************************************************************
/// <summary>
/// Class containing the default creation data for a 3D sprite.
/// </summary>
/// *************************************************************************
class CSpriteData3D
{
public:

    // Constructor/Destructor
    CSpriteData3D();
    CSpriteData3D( const CSpriteData3D & obj );
    ~CSpriteData3D();

    // Load the sprite data from the passed in iterator.
    void LoadFromIter( const std::string & name, nlohmann::json::const_iterator iter );

    // Access functions for the visual data.
    const CSpriteVisualData3D & GetVisualData() const;

    // Access functions for the physics data.
    //const CSpritePhysicsData3D & GetPhysicsData() const;

    // Access functions for the data name.
    const std::string & GetName() const;

private:

    // Visual data of the object
    CSpriteVisualData3D _visualData;

    // Physics data of the object
    //CSpritePhysicsData3D _physicsData;

    // The name of the object data
    std::string _name;
};

#endif  // __sprite_data_3d_h__


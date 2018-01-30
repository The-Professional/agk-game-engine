#ifndef __resource_file_h__
#define __resource_file_h__

// Game lib dependencies
#include <common\defs.h>

// Standard lib dependencies
#include <string>

// The id of an unloaded image and an unloaded sub image. Auto generated image
// ids will never be either of these values.
const uint UNLOADED_IMAGE_ID = 0;
const uint UNLOADED_SUBIMAGE_ID = 1;

/// *************************************************************************
/// <summary> 
/// Class to hold file path and the id that will belong to what's loaded.
/// </summary>
/// *************************************************************************
class CResourceFile
{
public:
    // The id of the loaded data. If this id is zero, it means the data isn't loaded.
    uint id = UNLOADED_IMAGE_ID;

    // The file path to the data.
    std::string path;

    /// *************************************************************************
    /// <summary> 
    /// Constructor
    /// </summary>
    /// *************************************************************************
    CResourceFile()
    {}

    /// <summary> 
    /// Constructor
    /// </summary>
    CResourceFile( const std::string & p ) : path(p)
    {}

    /// <summary> 
    /// Constructor
    /// </summary>
    CResourceFile( uint _id, const std::string & p ) : id(_id), path(p)
    {}
};


#endif  // __resource_file_h__
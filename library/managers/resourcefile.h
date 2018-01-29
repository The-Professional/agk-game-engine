#ifndef __resource_file_h__
#define __resource_file_h__

// Game lib dependencies
#include <common\defs.h>

// Standard lib dependencies
#include <string>


/// *************************************************************************
/// <summary> 
/// Class to hold file path and the id that will belong to what's loaded.
/// </summary>
/// *************************************************************************
class CResourceFile
{
public:
    // The id of the loaded data. If this id is zero, it means the data isn't loaded.
    uint id = 0;

    // The file path to the data.
    std::string path;

    /// *************************************************************************
    /// <summary> 
    /// Constructor
    /// </summary>
    /// *************************************************************************
    CResourceFile( const std::string & p ) : path(p)
    {}
};


#endif  // __resource_file_h__
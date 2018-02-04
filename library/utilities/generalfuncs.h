#ifndef __general_funcs_h__
#define __general_funcs_h__

// Game lib dependencies
#include <common\bitmask.h>
#include <common\vector2.h>

// Standard lib dependencies
#include <map>
#include <string>

// Forward declarations
class CResourceFile;

namespace NGeneralFuncs
{
    // Increment throught the folder and populate the map with file names and paths.
    void AddFilesToMap( const std::string & folderPath, std::map<std::string, std::string> & obj );
    void AddFilesToMap( const std::string & folderPath, std::map<std::string, CResourceFile> & obj );
    void AddFilesToImageList( const std::string & folderPath, std::map<std::string, CResourceFile> & obj );


}

#endif  // __general_funcs_h__
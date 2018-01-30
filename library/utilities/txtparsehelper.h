#ifndef __txt_parse_helper_h__
#define __txt_parse_helper_h__

// Game lib dependencies
#include <common\defs.h>
#include <utilities\json.hpp>

// Standard lib dependencies
#include <string>

// Forward declarations
class CResourceFile;

namespace NParseHelper
{
    // Load the file and add its subimages to the image list.
    void LoadSubImageFile( const std::string & folderPath, const std::string & file, std::map<std::string, CResourceFile> & imageList );
}

#endif  // __txt_parse_helper_h__
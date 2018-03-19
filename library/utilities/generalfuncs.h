#ifndef __general_funcs_h__
#define __general_funcs_h__

// Game lib dependencies
#include <common\bitmask.h>
#include <common\vector2.h>
#include <utilities\exceptionhandling.h>

// Standard lib dependencies
#include <map>
#include <string>

// Boost lib dependencies
#include <boost\format.hpp>

// Forward declarations
class CResourceFile;

namespace NGeneralFuncs
{
    // Increment throught the folder and populate the map with file names and paths.
    void AddFilesToMap( const std::string & folderPath, std::map<const std::string, const std::string> & obj );
    void AddFilesToMap( const std::string & folderPath, std::map<const std::string, CResourceFile> & obj );
    void AddFilesToImageList( const std::string & folderPath, std::map<const std::string, CResourceFile> & obj );

    // Output string info
    void PostDebugMsg( const std::string & msg );

    /// *************************************************************************
    /// <summary>
    /// Helper function to get the value of a map and error when it doesn't exist.
    /// </summary>
    /// <param name="k"> The key to the value. </param>
    /// <param name="obj"> The map object to search. </param>
    /// *************************************************************************
    template <class key, class value>
    inline value & GetMapValue( const key & k, std::map<const key, value> & obj )
    {
        auto iter = obj.find( k );
        if ( iter == obj.end() )
            throw NExcept::CCriticalException( "General Function Error!",
                    boost::str( boost::format( "There was an error getting a map value.\n\n%s\nLine: %s" )
                                               % __FUNCTION__ % __LINE__ ) );

        return iter->second;
    }

    /// <summary>
    /// Helper function to get the value of a map and error when it doesn't exist.
    /// </summary>
    /// <param name="k"> The key to the value. </param>
    /// <param name="obj"> The map object to search. </param>
    template <class key, class value *>
    inline value * GetMapValue( const key & k, std::map<const key, value *> & obj )
    {
        auto iter = obj.find( k );
        if( iter == obj.end() )
            return nullptr;

        return iter->second;
    }
}

#endif  // __general_funcs_h__
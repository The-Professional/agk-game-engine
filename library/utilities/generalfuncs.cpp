// Physical component dependency
#include "generalfuncs.h"

// Game lib dependencies
#include <agk.h>
#include <managers\resourcefile.h>
#include <utilities\exceptionhandling.h>

using namespace std;

namespace NGeneralFuncs
{
    /// *************************************************************************
    /// <summary>
    /// Increment throught the folder and populate the map with file names and 
    /// paths.
    /// </summary>
    /// <param name="path"> Path to the folder. </param>
    /// <param name="obj"> Map to populate. </param>
    /// *************************************************************************
    void AddFilesToMap( const string & folder, map<string, string> & obj )
    {
        try
        {
            obj.clear();

            // Set the folder we want to read from.
            // If we pass in a folder path without the ending '/', getting it here will add it.
            agk::SetFolder( folder.c_str() );
            string path = agk::GetFolder();
            string file = agk::GetFirstFile();
            string name;

            // Loop through the folder and grab all of the file paths and names.
            while( !file.empty() )
            {
                size_t pos = file.find( '.' );

                // If a dot was found, parse out the name.
                if( pos < file.size() )
                {
                    name = file.substr( 0, pos );
                    obj.insert( pair<string, string>( name, path + file ) );
                }

                // Move onto the next file. If there is no file, GetNextFile() will return an empty string.
                file = agk::GetNextFile();
            }

            // Set the folder back to its original location. Not sure if this is actually necessary.
            agk::SetFolder( "" );
        }
        catch( NExcept::CCriticalException e )
        {
            throw e;
        }
        catch( exception e )
        {
            throw NExcept::CCriticalException( "Error",
                                               "NGeneralFuncs::AddFilesToMap()",
                                               "Failed to find files in '" + folder + "'.", e );
        }
    }

    /// <summary>
    /// Increment throught the folder and populate the map with file names and 
    /// paths.
    /// </summary>
    /// <param name="path"> Path to the folder. </param>
    /// <param name="obj"> Map to populate. </param>
    void AddFilesToMap( const string & folder, map<string, CResourceFile> & obj )
    {
        try
        {
            obj.clear();

            // Set the folder we want to read from.
            // If we pass in a folder path without the ending '/', getting it here will add it.
            agk::SetFolder( folder.c_str() );
            string path = agk::GetFolder();
            string file = agk::GetFirstFile();
            string name;

            // Loop through the folder and grab all of the file paths and names.
            while( !file.empty() )
            {
                size_t pos = file.find( '.' );

                // If a dot was found, parse out the name.
                if( pos < file.size() )
                {
                    name = file.substr( 0, pos );
                    obj.insert( pair<string, CResourceFile>( name, CResourceFile( path + file ) ) );
                }

                // Move onto the next file. If there is no file, GetNextFile() will return an empty string.
                file = agk::GetNextFile();
            }

            // Set the folder back to its original location. Not sure if this is actually necessary.
            agk::SetFolder( "" );
        }
        catch( NExcept::CCriticalException e )
        {
            throw e;
        }
        catch( exception e )
        {
            throw NExcept::CCriticalException( "Error",
                                               "NGeneralFuncs::AddFilesToMap()",
                                               "Failed to find files in '" + folder + "'.", e );
        }
    }
}
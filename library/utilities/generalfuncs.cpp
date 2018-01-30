// Physical component dependency
#include "generalfuncs.h"

// Game lib dependencies
#include <agk.h>
#include <managers\resourcefile.h>
#include <utilities\exceptionhandling.h>
#include <utilities\txtparsehelper.h>

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
    void AddFilesToMap( const string & folderPath, map<string, string> & obj )
    {
        try
        {
            obj.clear();

            // Set the folder we want to read from.
            // If we pass in a folder path without the ending '/', getting it here will add it.
            agk::SetFolder( folderPath.c_str() );
            string folder = agk::GetFolder();
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
                    obj.insert( pair<string, string>( name, folder + file ) );
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
                                               "Failed to find files in '" + folderPath + "'.", e );
        }
    }

    /// <summary>
    /// Increment throught the folder and populate the map with file names and 
    /// paths.
    /// </summary>
    /// <param name="path"> Path to the folder. </param>
    /// <param name="obj"> Map to populate. </param>
    void AddFilesToMap( const string & folderPath, map<string, CResourceFile> & obj )
    {
        try
        {
            obj.clear();

            // Set the folder we want to read from.
            // If we pass in a folder path without the ending '/', getting it here will add it.
            agk::SetFolder( folderPath.c_str() );
            string folder = agk::GetFolder();
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
                    obj.insert( pair<string, CResourceFile>( name, CResourceFile( folder + file ) ) );
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
                                               "Failed to find files in '" + folderPath + "'.", e );
        }
    }


    /// *************************************************************************
    /// <summary>
    /// Increment throught the folder and populate the map with image file names 
    /// and paths.
    /// </summary>
    /// <param name="path"> Path to the folder. </param>
    /// <param name="obj"> Map to populate. </param>
    /// *************************************************************************
    void AddFilesToImageList( const string & folderPath, map<string, CResourceFile> & obj )
    {
        try
        {
            obj.clear();

            // Set the folder we want to read from.
            // If we pass in a folder path without the ending '/', getting it here will add it.
            agk::SetFolder( folderPath.c_str() );
            string folder = agk::GetFolder();
            string file = agk::GetFirstFile();
            string name, ext;

            // Loop through the folder and grab all of the file paths and names.
            while( !file.empty() )
            {
                size_t pos = file.find( '.' );

                // If a dot was found, parse out the name.
                if( pos < file.size() )
                {
                    ext = file.substr( pos + 1 );

                    // If a text file was found, it has subimage info. So we need to parse that.
                    if( ext == "txt" )
                        NParseHelper::LoadSubImageFile( folder, file, obj );
                    else
                    {
                        name = file.substr( 0, pos );

                        if( obj.find(name) != obj.end() )
                            throw NExcept::CCriticalException( "Error",
                                                               "NGeneralFuncs::AddFilesToImageList()",
                                                               "A file using the name '" + name + "' already exists." );

                        obj.insert( pair<string, CResourceFile>( name, CResourceFile( folder + file ) ) );
                    }
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
                                               "NGeneralFuncs::AddFilesToImageList()",
                                               "Failed to find files in '" + folderPath + "'.", e );
        }
    }
}
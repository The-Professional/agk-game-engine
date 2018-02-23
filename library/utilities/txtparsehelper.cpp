// Physical component dependency
#include "txtparsehelper.h"

// Game lib dependencies
#include <managers\resourcefile.h>
#include <utilities\exceptionhandling.h>

// Standard lib depencencies
#include <fstream>

using namespace std;

namespace NParseHelper
{
    /// *************************************************************************
    /// <summary> 
    /// Load the file and add its subimages to the image list.
    /// </summary>
    /// <param name="path"> Path to the text file of subimages. </param>
    /// <param name="imageList"> List of images to add to. </param>
    /// *************************************************************************
    void LoadSubImageFile( const string & folderPath, const string & file, map<const string, CResourceFile> & imageList )
    {
        try
        {
            string line;
            ifstream openFile( folderPath + file );
            if( openFile.is_open() )
            {
                // Sub image files are required be named like 'cube subimages.txt', where
                // the name before the space is the image they're based off of.
                size_t spacePos = file.find_first_of( ' ' );
                string parentName = file.substr( 0, spacePos );

                while( getline( openFile, line ) )
                {
                    size_t pos = line.find_first_of( ':' );
                    string name = line.substr( 0, pos );

                    if( imageList.find( name ) != imageList.end() )
                        throw NExcept::CCriticalException( "Error",
                                                           "NParseHelper::LoadSubImageFile()",
                                                           "A file using the name '" + name + "' already exists." );

                    CResourceFile resource( UNLOADED_SUBIMAGE_ID, parentName );
                    imageList.emplace( name, resource );
                }
            }
        }
        catch( exception e )
        {
            throw NExcept::CCriticalException( "Error",
                                               "NParseHelper::LoadSubImageFile()",
                                               "Failed load file '" + folderPath + file + "'.", e );
        }
    }
}
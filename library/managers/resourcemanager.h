#ifndef __resource_manager_h__
#define __resource_manager_h__

// Game lib dependencies
#include <common\defs.h>
#include <managers\resourcefile.h>

// Standard lib dependencies
#include <string>
#include <map>

/// *************************************************************************
/// <summary> 
/// Class to load and hold 3d mesh id's.
/// </summary>
/// *************************************************************************
class CResourceManager
{
public:
    // Get the instance of the singleton class
    static CResourceManager & Instance()
    {
        static CResourceManager resourceManager;
        return resourceManager;
    }

    // Read the file and compile the list of resource files.
    void LoadMeshList( const std::string & path );
    void LoadAnimatedMeshList( const std::string & path );
    void LoadImageList( const std::string & path );
    void LoadFontList( const std::string & path );

    // Load the resource if not loaded and return its id.
    uint LoadMesh( const std::string & name );
    uint LoadAnimatedMesh( const std::string & name );
    uint LoadImage( const std::string & name );
    uint LoadFont( const std::string & name );

    // Free the resources of the passed in type.
    void Clear( NDefs::EResourceType type = NDefs::ERT_NULL );

private:

    // Constructor
    CResourceManager();

    // Destructor
    virtual ~CResourceManager();

    // Map containing the list of meshes.
    std::map<std::string, CResourceFile> _meshList;

    // Map containing the list of animated meshes.
    std::map<std::string, CResourceFile> _animatedMeshList;

    // Map containing the list of images.
    std::map<std::string, CResourceFile> _imageList;

    // Map containing the list of fonts.
    std::map<std::string, CResourceFile> _fontList;
};

#endif  // __resource_manager_h__

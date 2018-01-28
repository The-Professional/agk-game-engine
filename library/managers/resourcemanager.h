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
    void LoadList( NDefs::EResourceType type, const std::string & path );

    // Get the mesh id.
    uint LoadMesh( const std::string & name );

    // Get the animated mesh id.
    uint LoadAnimatedMesh( const std::string & name );

    // Get the image id.
    uint LoadImage( const std::string & name );

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

};

#endif  // __resource_manager_h__

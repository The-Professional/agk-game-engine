// Physical component dependency
#include "resourcemanager.h"

// Game lib dependencies
#include <agk.h>
#include <utilities\generalfuncs.h>
#include <utilities\exceptionhandling.h>

// Standard lib dependencies
#include <fstream>

using namespace std;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CResourceManager::CResourceManager()
{
} 


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CResourceManager::~CResourceManager()
{
    Clear();
}


/// *************************************************************************
/// <summary> 
/// Locate the folder and compile the list of mesh files.
/// </summary>
/// *************************************************************************
void CResourceManager::LoadMeshList( const std::string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _meshList );
}


/// *************************************************************************
/// <summary> 
/// Locate the folder and compile the list of animated mesh files.
/// </summary>
/// *************************************************************************
void CResourceManager::LoadAnimatedMeshList( const std::string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _animatedMeshList );
}


/// *************************************************************************
/// <summary> 
/// Locate the folder and compile the list of image files.
/// </summary>
/// *************************************************************************
void CResourceManager::LoadImageList( const std::string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _imageList );
}


/// *************************************************************************
/// <summary> 
/// Get the mesh id.
/// </summary>
/// <param name="name"> Name of the mesh. </param>
/// <returns> Loaded mesh id. </returns>
/// *************************************************************************
uint CResourceManager::LoadMesh( const std::string & name )
{
    // Make sure the mesh we are looking for exists.
    auto iter = _meshList.find( name );
    if( iter != _meshList.end() )
    {
        // If the mesh hasn't been loaded yet, load it.
        if( iter->second.id == 0 )
            iter->second.id = agk::LoadObject( iter->second.path.c_str() );

        return iter->second.id;
    }

    return 0;
}


/// *************************************************************************
/// <summary> 
/// Get the animated mesh id.
/// </summary>
/// <param name="name"> Name of the animated mesh. </param>
/// <returns> Loaded animated mesh id. </returns>
/// *************************************************************************
uint CResourceManager::LoadAnimatedMesh( const std::string & name )
{
    // Make sure the mesh we are looking for exists.
    auto iter = _animatedMeshList.find( name );
    if( iter != _animatedMeshList.end() )
    {
        // If the animated mesh hasn't been loaded yet, load it.
        if( iter->second.id == 0 )
            iter->second.id = agk::LoadObjectWithChildren( iter->second.path.c_str() );

        return iter->second.id;
    }

    return 0;
}


/// *************************************************************************
/// <summary> 
/// Get the image id.
/// </summary>
/// <param name="name"> Name of the image. </param>
/// <returns> Loaded image id. </returns>
/// *************************************************************************
uint CResourceManager::LoadImage( const std::string & name )
{
    // Make sure the mesh we are looking for exists.
    auto iter = _imageList.find( name );
    if( iter != _imageList.end() )
    {
        // If the image hasn't been loaded yet, load it.
        if( iter->second.id == 0 )
            iter->second.id = agk::LoadImage( iter->second.path.c_str() );

        return iter->second.id;
    }

    return 0;
}


/// *************************************************************************
/// <summary> 
/// Free the resources of the passed in type.
/// </summary>
/// <param name="name"> Type of resource to free. </param>
/// *************************************************************************
void CResourceManager::Clear( NDefs::EResourceType type )
{
    // Free up any loaded meshes.
    if( type == NDefs::ERT_MESH || type == NDefs::ERT_NULL )
        for( auto & kv : _meshList )
            if( kv.second.id > 0 )
            {
                agk::DeleteObject( kv.second.id );
                kv.second.id = 0;
            }

    // Free up any loaded animated meshes.
    if( type == NDefs::ERT_ANIMATED_MESH || type == NDefs::ERT_NULL )
        for( auto & kv : _animatedMeshList )
            if( kv.second.id > 0 )
            {
                agk::DeleteObjectWithChildren( kv.second.id );
                kv.second.id = 0;
            }

    // Free up any loaded images.
    if( type == NDefs::ERT_IMAGE || type == NDefs::ERT_NULL )
        for( auto & kv : _imageList )
            if( kv.second.id > 0 )
            {
                agk::DeleteImage( kv.second.id );
                kv.second.id = 0;
            }
}
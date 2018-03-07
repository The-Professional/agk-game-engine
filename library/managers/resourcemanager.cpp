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
    NGeneralFuncs::AddFilesToImageList( path, _imageList );

    // Add an extra resource for a solid image.
    CResourceFile solidImage;
    solidImage.id = agk::CreateImageColor( 255, 255, 255, 255 );
    _imageList.emplace( "", solidImage );
}


/// *************************************************************************
/// <summary> 
/// Locate the folder and compile the list of font files.
/// </summary>
/// *************************************************************************
void CResourceManager::LoadFontList( const std::string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _fontList );
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
    auto & resource = NGeneralFuncs::GetMapValue( name, _meshList );

    // If the mesh hasn't been loaded yet, load it.
    if( resource.id == 0 )
        resource.id = agk::LoadObject( resource.path.c_str() );

    return resource.id;
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
    auto & resource = NGeneralFuncs::GetMapValue( name, _animatedMeshList );

    // If the animated mesh hasn't been loaded yet, load it.
    if( resource.id == 0 )
        resource.id = agk::LoadObjectWithChildren( resource.path.c_str() );

    return resource.id;
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
    auto & resource = NGeneralFuncs::GetMapValue( name, _imageList );

    // If the image hasn't been loaded yet, load it.
    if( resource.id == UNLOADED_ID )
        resource.id = agk::LoadImage( resource.path.c_str() );
    else if( resource.id == UNLOADED_SUBIMAGE_ID )
    {
        uint parentId = LoadImage( resource.path );
        resource.id = agk::LoadSubImage( parentId, name.c_str() );
    }

    return resource.id;
}


/// *************************************************************************
/// <summary> 
/// Get the font id.
/// </summary>
/// <param name="name"> Name of the font. </param>
/// <returns> Loaded font id. </returns>
/// *************************************************************************
uint CResourceManager::LoadFont( const std::string & name )
{
    auto & resource = NGeneralFuncs::GetMapValue( name, _fontList );

    // If the animated mesh hasn't been loaded yet, load it.
    if( resource.id == 0 )
        resource.id = agk::LoadFont( resource.path.c_str() );

    return resource.id;
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
            if( kv.second.id != UNLOADED_ID && kv.second.id != UNLOADED_SUBIMAGE_ID )
            {
                agk::DeleteImage( kv.second.id );
                kv.second.id = 0;
            }

    // Free up any loaded images.
    if( type == NDefs::ERT_FONT || type == NDefs::ERT_NULL )
        for( auto & kv : _fontList )
            if( kv.second.id > 0 )
            {
                agk::DeleteFont( kv.second.id );
                kv.second.id = 0;
            }
}
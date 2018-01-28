// Physical component dependency
#include "spritemanager.h"

// Game lib dependencies
#include <utilities\json.hpp>
#include <utilities\jsonparsehelper.h>
#include <utilities\exceptionhandling.h>
#include <utilities\deletefuncs.h>
#include <common\vector3.h>
#include <3d\spritedata3d.h>
#include <3d\sprite3d.h>

// Standard lib dependencies
#include <fstream>

using namespace std;
using namespace nlohmann;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CSpriteManager::CSpriteManager()
{
}


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CSpriteManager::~CSpriteManager()
{
    Clear();
}


/// *************************************************************************
/// <summary> 
/// Read the file and compile the list of sprite data files.
/// </summary>
/// *************************************************************************
void CSpriteManager::LoadDataFileList3D( const std::string & path )
{
    try
    {
        _spriteDataFileList3d.clear();

        // Load the sprite data list file.
        ifstream ifile( path );

        // Parse the content into a json object.
        json j;
        ifile >> j;

        auto listIter = j.find( "spriteDataList3d" );
        if( listIter != j.end() )
        {
            auto iter = listIter->begin();
            while( iter != listIter->end() )
            {
                string key = iter.key();
                string value = iter->get<string>();
                _spriteDataFileList3d.insert( pair<string, string>( key, value ) );
                ++iter;
            }
        }
    }
    catch( NExcept::CCriticalException e )
    {
        throw e;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::LoadDataFileList3D()",
                                           "Failed to load file '" + path + "'.", e );
    }
}


/// *************************************************************************
/// <summary> 
/// Read the file and compile the list of sprite data files.
/// </summary>
/// *************************************************************************
void CSpriteManager::LoadCollectionFileList3D( const std::string & path )
{
    try
    {
        _spriteCollectionFileList3d.clear();

        // Load the sprite data list file.
        ifstream ifile( path );

        // Parse the content into a json object.
        json j;
        ifile >> j;

        auto listIter = j.find( "spriteCollectionList3d" );
        if( listIter != j.end() )
        {
            auto iter = listIter->begin();
            while( iter != listIter->end() )
            {
                string key = iter.key();
                string value = iter->get<string>();
                _spriteCollectionFileList3d.insert( pair<string, string>( key, value ) );
                ++iter;
            }
        }
    }
    catch( NExcept::CCriticalException e )
    {
        throw e;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::LoadCollectionFileList3D()",
                                           "Failed to load file '" + path + "'.", e );
    }
}


/// *************************************************************************
/// <summary> 
/// Get the sprite data.
/// </summary>
/// <param name="name"> Name of the sprite. </param>
/// *************************************************************************
const CSpriteData3D * CSpriteManager::GetSpriteData3D( const std::string & name )
{
    try
    {
        // See if the sprite data is already loaded.
        auto loadedIter = _spriteDataList3d.find( name );
        if( loadedIter != _spriteDataList3d.end() )
            return loadedIter->second;

        auto unloadedIter = _spriteDataFileList3d.find( name );
        if( unloadedIter != _spriteDataFileList3d.end() )
        {
            // Load the sprite data file.
            ifstream ifile( unloadedIter->second );

            // Parse the content into a json object.
            json j;
            ifile >> j;

            auto spriteIter = j.find( "spriteData3d" );
            if( spriteIter != j.end() )
            {
                CSpriteData3D * pData = new CSpriteData3D();
                _spriteDataList3d.insert( pair<string, CSpriteData3D *>( unloadedIter->first, pData ) );
                
                pData->LoadFromIter( unloadedIter->first, spriteIter );

                return pData;
            }
        }

        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::LoadSpriteData3D()",
                                           "No sprite data exists with tha name '" + name + "'." );
    }
    catch( NExcept::CCriticalException e )
    {
        throw e;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::LoadSpriteData3D()",
                                           "Failed to get sprite '" + name + "'.", e );
    }

    return nullptr;
}


/// *************************************************************************
/// <summary> 
/// Create the sprite.
/// </summary>
/// <param name="name"> Name of the sprite. </param>
/// *************************************************************************
CSprite3D * CSpriteManager::CreateSprite3D( const std::string & name )
{
    try
    {
        // Create the sprite object and add it to the sprite list.
        CSprite3D * pSprite = new CSprite3D();
        _spriteList3d[name].push_back( pSprite );

        // Initialize the sprite with sprite data.
        pSprite->Init( GetSpriteData3D( name ) );

        return pSprite;
    }
    catch( NExcept::CCriticalException e )
    {
        throw e;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::CreateSprite3D()",
                                           "Failed to create sprite '" + name + "'.", e );
    }

    return nullptr;
}


/// *************************************************************************
/// <summary> 
/// Create the collection of sprites.
/// </summary>
/// <param name="name"> Name of the sprite collection. </param>
/// *************************************************************************
void CSpriteManager::CreateSpriteCollection3D( const std::string & collectionName )
{
    try
    {
        auto mapIter = _spriteCollectionFileList3d.find( collectionName );
        if( mapIter != _spriteCollectionFileList3d.end() )
        {
            // Load the sprite data file.
            ifstream ifile( mapIter->second );

            // Parse the content into a json object.
            json j;
            ifile >> j;

            auto collectionIter = j.find( "spriteCollection3d" );
            if( collectionIter != j.end() )
            {
                auto iter = collectionIter->begin();
                while( iter != collectionIter->end() )
                {
                    CSprite3D * pSprite = new CSprite3D();
                    _spriteList3d[mapIter->first].push_back( pSprite );

                    string name;
                    NParseHelper::GetName( iter, name );

                    // Initialize the sprite with sprite data.
                    pSprite->Init( GetSpriteData3D( name ) );

                    CVector3 pos;
                    if( NParseHelper::GetPosition( iter, pos ) )
                        pSprite->SetPos( pos );

                    CVector3 rot;
                    if( NParseHelper::GetRotation( iter, rot ) )
                        pSprite->SetRot( rot );

                    CVector3 scale;
                    if( NParseHelper::GetScale( iter, scale ) )
                        pSprite->SetScale( scale );

                    ++iter;
                }
            }
        }
    }
    catch( NExcept::CCriticalException e )
    {
        throw e;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::CreateSpriteCollection3D()",
                                           "Failed to create sprite collection '" + collectionName + "'.", e );
    }
}


/// *************************************************************************
/// <summary> 
/// Free the loaded sprite data and all sprites of the same name.
/// </summary>
/// <param name="name"> Name of the sprite to free. 
///                     Empty string frees everything. </param>
/// *************************************************************************
void CSpriteManager::Clear( const string & name )
{
    try
    {
        if( name.empty() )
        {
            NDelFunc::DeleteMapVectorPointers( _spriteList3d );
            NDelFunc::DeleteMapPointers( _spriteDataList3d );
        }
        else
        {
            NDelFunc::DeleteMapVectorPointers( name, _spriteList3d );
            NDelFunc::DeleteMapPointer( name, _spriteDataList3d );
        }
    }
    catch( NExcept::CCriticalException e )
    {
        throw e;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::Clear()",
                                           name.empty() ? "Failed to clear all sprites and sprite data." :
                                                          "Failed to clear sprite '" + name + "'.", e );
    }
}

/// <summary> 
/// Free the passed in sprite.
/// </summary>
/// <param name="pSprite"> Sprite to free. </param>
void CSpriteManager::Clear( CSprite3D * pSprite )
{
    try
    {
        auto iter = _spriteList3d.find( pSprite->GetName() );
        if( iter != _spriteList3d.end() )
            NDelFunc::DeleteVectorPointer( pSprite, iter->second );
    }
    catch( NExcept::CCriticalException e )
    {
        throw e;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::Clear()",
                                           pSprite ? "Failed to clear sprite '" + pSprite->GetName() + "'." :
                                                     "Failed to clear the sprite.", e );
    }
}
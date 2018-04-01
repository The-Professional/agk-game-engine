// Physical component dependency
#include "spritemanager.h"

// Game lib dependencies
#include <agk.h>
#include <utilities\jsonparsehelper.h>
#include <utilities\exceptionhandling.h>
#include <utilities\deletefuncs.h>
#include <utilities\generalfuncs.h>
#include <common\defs.h>
#include <common\vector3.h>
#include <common\iobject.h>
#include <common\collectionobject.h>
#include <3d\spritedata3d.h>
#include <3d\sprite3d.h>
#include <2d\spritedata2d.h>
#include <2d\sprite2d.h>
#include <2d\textspritedata.h>
#include <2d\textsprite.h>

// Standard lib dependencies
#include <fstream>

using namespace std;
using namespace nlohmann;
using namespace NDefs;

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
    NGeneralFuncs::AddFilesToMap( path, _spriteDataFileList3d );
}


/// *************************************************************************
/// <summary> 
/// Read the file and compile the list of sprite data files.
/// </summary>
/// *************************************************************************
void CSpriteManager::LoadDataFileList2D( const std::string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _spriteDataFileList2d );
}


/// *************************************************************************
/// <summary> 
/// Read the file and compile the list of sprite data files.
/// </summary>
/// *************************************************************************
void CSpriteManager::LoadTextDataFileList( const std::string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _textSpriteDataFileList );
}


/// *************************************************************************
/// <summary> 
/// Read the path and compile the list of collection files in that folder.
/// </summary>
/// *************************************************************************
void CSpriteManager::LoadCollectionFileList( const string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _collectionFileList );
}


/// *************************************************************************
/// <summary> 
/// Get the sprite data.
/// </summary>
/// <param name="name"> Name of the sprite. </param>
/// *************************************************************************
CSpriteData3D * CSpriteManager::GetSpriteData3D( const std::string & name )
{
    try
    {
        // See if the sprite data is already loaded.
        auto loadedIter = _spriteDataList3d.find( name );
        if( loadedIter != _spriteDataList3d.end() )
            return loadedIter->second;

        // If not, load the sprite data.
        const string & filepath = NGeneralFuncs::GetMapValue( name, _spriteDataFileList3d );

        // Load the sprite data file.
        ifstream ifile( filepath );

        // Parse the content into a json object.
        json j;
        ifile >> j;

        auto spriteIter = j.find( "spriteData3d" );
        if( spriteIter != j.end() )
        {
            CSpriteData3D * pData = new CSpriteData3D();
            _spriteDataList3d.emplace( name, pData );
                
            pData->LoadFromIter( name, spriteIter );

            return pData;
        }
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::LoadSpriteData3D()",
                                           "Failed to get sprite data '" + name + "'.", e );
    }

    return nullptr;
}


/// *************************************************************************
/// <summary> 
/// Get the sprite data.
/// </summary>
/// <param name="name"> Name of the sprite. </param>
/// *************************************************************************
CSpriteData2D * CSpriteManager::GetSpriteData2D( const std::string & name )
{
    try
    {
        // See if the sprite data is already loaded.
        auto loadedIter = _spriteDataList2d.find( name );
        if( loadedIter != _spriteDataList2d.end() )
            return loadedIter->second;

        // If not, load the sprite data.
        const string & filepath = NGeneralFuncs::GetMapValue( name, _spriteDataFileList2d );

        // Load the sprite data file.
        ifstream ifile( filepath );

        // Parse the content into a json object.
        json j;
        ifile >> j;

        auto spriteIter = j.find( "spriteData2d" );
        if( spriteIter != j.end() )
        {
            CSpriteData2D * pData = new CSpriteData2D();
            _spriteDataList2d.emplace( name, pData );

            pData->LoadFromIter( name, spriteIter );

            return pData;
        }
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::LoadSpriteData2D()",
                                           "Failed to get sprite data '" + name + "'.", e );
    }

    return nullptr;
}


/// *************************************************************************
/// <summary> 
/// Get the text sprite data.
/// </summary>
/// <param name="name"> Name of the text sprite. </param>
/// *************************************************************************
CTextSpriteData * CSpriteManager::GetTextSpriteData( const std::string & name )
{
    try
    {
        // See if the sprite data is already loaded.
        auto loadedIter = _textSpriteDataList.find( name );
        if( loadedIter != _textSpriteDataList.end() )
            return loadedIter->second;

        // If not, load the sprite data.
        const string & filepath = NGeneralFuncs::GetMapValue( name, _textSpriteDataFileList );

        // Load the sprite data file.
        ifstream ifile( filepath );

        // Parse the content into a json object.
        json j;
        ifile >> j;

        auto spriteIter = j.find( "textSpriteData" );
        if( spriteIter != j.end() )
        {
            CTextSpriteData * pData = new CTextSpriteData();
            _textSpriteDataList.emplace( name, pData );

            pData->LoadFromIter( name, spriteIter );

            return pData;
        }
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::GetTextSpriteData()",
                                           "Failed to get sprite data '" + name + "'.", e );
    }

    return nullptr;
}


/// *************************************************************************
/// <summary> 
/// Create the 3d sprite.
/// </summary>
/// <param name="name"> Name of the sprite. </param>
/// <param name="key"> Key value to locate the sprite. 
/// If not defined, the key will be the sprite's name. </param>
/// *************************************************************************
CSprite3D * CSpriteManager::CreateSprite3D( const string & name, const string & key )
{
    try
    {
        // Create the sprite object and add it to the sprite list.
        CSprite3D * pSprite = new CSprite3D( name );

        if( key.empty() )
            _objectList[name].push_back( pSprite );
        else
            _objectList[key].push_back( pSprite );

        return pSprite;
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
/// Create the 2d sprite.
/// </summary>
/// <param name="name"> Name of the sprite. </param>
/// <param name="key"> Key value to locate the sprite. 
/// If not defined, the key will be the sprite's name. </param>
/// *************************************************************************
CSprite2D * CSpriteManager::CreateSprite2D( const std::string & name, const string & key )
{
    try
    {
        // Create the sprite object and add it to the sprite list.
        CSprite2D * pSprite = new CSprite2D( name );

        if( key.empty() )
            _objectList[name].push_back( pSprite );
        else
            _objectList[key].push_back( pSprite );

        return pSprite;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::CreateSprite2D()",
                                           "Failed to create sprite '" + name + "'.", e );
    }

    return nullptr;
}


/// *************************************************************************
/// <summary> 
/// Create the text sprite.
/// </summary>
/// <param name="name"> Name of the sprite. </param>
/// <param name="text"> The text to display. </param>
/// <param name="key"> Key value to locate the sprite. 
/// If not defined, the key will be the sprite's name. </param>
/// *************************************************************************
CTextSprite * CSpriteManager::CreateTextSprite( const string & name, const string & text, const string & key )
{
    try
    {
        // Create the sprite object and add it to the sprite list.
        CTextSprite * pSprite = new CTextSprite( name, text );

        if( key.empty() )
            _objectList[name].push_back( pSprite );
        else
            _objectList[key].push_back( pSprite );

        return pSprite;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::CreateTextSprite()",
                                           "Failed to create sprite '" + name + "'.", e );
    }

    return nullptr;
}


/// *************************************************************************
/// <summary> 
/// Load the collection.
/// </summary>
/// <param name="name"> Name of the collection. </param>
/// <param name="key"> Key value to locate the sprite. 
/// If not defined, the key will be the sprite's name. </param>
/// <returns> List of loaded objects. </param>
/// *************************************************************************
vector<iObject *> CSpriteManager::CreateCollection( const string & name, const string & key )
{
    vector<iObject *> pObjectList;
    try
    {
        auto mapIter = _collectionFileList.find( name );
        if( mapIter != _collectionFileList.end() )
        {
            // Load the sprite data file.
            ifstream ifile( mapIter->second );

            // Parse the content into a json object.
            json j;
            ifile >> j;

            auto collectionIter = j.find( "collection" );
            if( collectionIter != j.end() )
            {
                string mapKey = key.empty() ? name : key;

                auto objectIter = collectionIter->begin();
                while( objectIter != collectionIter->end() )
                {
                    CCollectionObject collectionObject;
                    NParseHelper::GetCollectionObject( objectIter, collectionObject );
                    iObject * pObject = nullptr;

                    switch( collectionObject.type )
                    {
                    case EOT_SPRITE_3D:
                        pObject = CreateSprite3D( collectionObject.name, mapKey );
                        pObjectList.push_back( pObject );
                        pObject->Set( collectionObject );
                        break;

                    case EOT_SPRITE_2D:
                        pObject = CreateSprite2D( collectionObject.name, mapKey );
                        pObjectList.push_back( pObject );
                        pObject->Set( collectionObject );
                        break;

                    case EOT_TEXT_SPRITE:
                        pObject = CreateTextSprite( collectionObject.name, collectionObject.text, mapKey );
                        pObjectList.push_back( pObject );
                        pObject->Set( collectionObject );
                        break;

                    default:
                        throw NExcept::CCriticalException( "Error",
                                                           "CCollectionManager::LoadCollection()",
                                                           "Invalid type for object in collection '" + name + "'." );
                        break;
                    }

                    ++objectIter;
                }
            }
        }
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CCollectionManager::LoadCollection()",
                                           "Failed to create collection list '" + name + "'.", e );
    }

    return pObjectList;
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
            NDelFunc::DeleteMapVectorPointers( _objectList );
            NDelFunc::DeleteMapPointers( _spriteDataList3d );
            NDelFunc::DeleteMapPointers( _spriteDataList2d );
            NDelFunc::DeleteMapPointers( _textSpriteDataList );
        }
        else
        {
            NDelFunc::DeleteMapVectorPointers( name, _objectList );
            NDelFunc::DeleteMapPointer( name, _spriteDataList3d );
            NDelFunc::DeleteMapPointer( name, _spriteDataList2d );
            NDelFunc::DeleteMapPointer( name, _textSpriteDataList );
        }
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::Clear()",
                                           name.empty() ? "Failed to clear all sprites and sprite data." :
                                                          "Failed to clear sprite '" + name + "'.", e );
    }
}


/// *************************************************************************
/// <summary> 
/// Reposition all sprites.
/// </summary>
/// *************************************************************************
void CSpriteManager::RepositionAllSprites()
{
    for( auto mapIter = _objectList.begin(); mapIter != _objectList.end(); ++mapIter )
        for( auto pSprite : mapIter->second )
            pSprite->Reposition();
}


/// *************************************************************************
/// <summary> 
/// Update all sprites in the manager.
/// </summary>
/// *************************************************************************
void CSpriteManager::Update()
{
    // If an object's parent has been marked for deletion, it should be marked too.
    for( auto mapIter = _objectList.begin(); mapIter != _objectList.end(); ++mapIter )
        for( auto pSprite : mapIter->second )
            pSprite->UpdateForDeletion();

    // Go through each object and either delete or update them.
    auto mapIter = _objectList.begin();
    while( mapIter != _objectList.end() )
    {
        auto objectIter = mapIter->second.begin();
        while( objectIter != mapIter->second.end() )
        {
            // If the object is marked for deletion, delete it.
            if( (*objectIter)->IsMarkedForDeletion() )
            {
                NDelFunc::Delete( (*objectIter) );
                objectIter = mapIter->second.erase( objectIter );
            }
            // Otherwise update it.
            else
            {
                (*objectIter)->Update();
                ++objectIter;
            }
        }

        // If a deletion happened and a vector is now empty, delete the vector.
        if( mapIter->second.empty() )
            mapIter = _objectList.erase( mapIter );
        else
            ++mapIter;
    }
}


/// *************************************************************************
/// <summary> 
/// Transform all the sprites in the manager.
/// </summary>
/// *************************************************************************
void CSpriteManager::Transform()
{
    // Transform each of the sprites.
    for( auto mapIter = _objectList.begin(); mapIter != _objectList.end(); ++mapIter )
        for( auto pSprite : mapIter->second )
            pSprite->Transform();

    // Clear the modified bitmask for each of the sprites.
    for( auto mapIter = _objectList.begin(); mapIter != _objectList.end(); ++mapIter )
        for( auto pSprite : mapIter->second )
            pSprite->ClearModified();
}
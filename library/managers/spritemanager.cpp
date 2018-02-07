// Physical component dependency
#include "spritemanager.h"

// Game lib dependencies
#include <agk.h>
#include <utilities\jsonparsehelper.h>
#include <utilities\exceptionhandling.h>
#include <utilities\deletefuncs.h>
#include <utilities\generalfuncs.h>
#include <common\vector3.h>
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
/// Read the file and compile the list of sprite data files.
/// </summary>
/// *************************************************************************
void CSpriteManager::LoadCollectionFileList3D( const std::string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _spriteCollectionFileList3d );
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
/// Get the sprite data.
/// </summary>
/// <param name="name"> Name of the sprite. </param>
/// *************************************************************************
const CSpriteData2D * CSpriteManager::GetSpriteData2D( const std::string & name )
{
    try
    {
        // See if the sprite data is already loaded.
        auto loadedIter = _spriteDataList2d.find( name );
        if( loadedIter != _spriteDataList2d.end() )
            return loadedIter->second;

        auto unloadedIter = _spriteDataFileList2d.find( name );
        if( unloadedIter != _spriteDataFileList2d.end() )
        {
            // Load the sprite data file.
            ifstream ifile( unloadedIter->second );

            // Parse the content into a json object.
            json j;
            ifile >> j;

            auto spriteIter = j.find( "spriteData2d" );
            if( spriteIter != j.end() )
            {
                CSpriteData2D * pData = new CSpriteData2D();
                _spriteDataList2d.insert( pair<string, CSpriteData2D *>( unloadedIter->first, pData ) );

                pData->LoadFromIter( unloadedIter->first, spriteIter );

                return pData;
            }
        }

        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::LoadSpriteData2D()",
                                           "No sprite data exists with tha name '" + name + "'." );
    }
    catch( NExcept::CCriticalException e )
    {
        throw e;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::LoadSpriteData2D()",
                                           "Failed to get sprite '" + name + "'.", e );
    }

    return nullptr;
}


/// *************************************************************************
/// <summary> 
/// Get the text sprite data.
/// </summary>
/// <param name="name"> Name of the text sprite. </param>
/// *************************************************************************
const CTextSpriteData * CSpriteManager::GetTextSpriteData( const std::string & name )
{
    try
    {
        // See if the sprite data is already loaded.
        auto loadedIter = _textSpriteDataList.find( name );
        if( loadedIter != _textSpriteDataList.end() )
            return loadedIter->second;

        auto unloadedIter = _textSpriteDataFileList.find( name );
        if( unloadedIter != _textSpriteDataFileList.end() )
        {
            // Load the sprite data file.
            ifstream ifile( unloadedIter->second );

            // Parse the content into a json object.
            json j;
            ifile >> j;

            auto spriteIter = j.find( "textSpriteData" );
            if( spriteIter != j.end() )
            {
                CTextSpriteData * pData = new CTextSpriteData();
                _textSpriteDataList.insert( pair<string, CTextSpriteData *>( unloadedIter->first, pData ) );

                pData->LoadFromIter( unloadedIter->first, spriteIter );

                return pData;
            }
        }

        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::GetTextSpriteData()",
                                           "No sprite data exists with tha name '" + name + "'." );
    }
    catch( NExcept::CCriticalException e )
    {
        throw e;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSpriteManager::GetTextSpriteData()",
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
        // Get the data used to create the sprite.
        auto pData = GetSpriteData3D( name );

        // Create the sprite object and add it to the sprite list.
        CSprite3D * pSprite = new CSprite3D( pData );
        _spriteList3d[name].push_back( pSprite );

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
/// Create the sprite.
/// </summary>
/// <param name="name"> Name of the sprite. </param>
/// *************************************************************************
CSprite2D * CSpriteManager::CreateSprite2D( const std::string & name )
{
    try
    {
        // Get the data used to create the sprite.
        auto pData = GetSpriteData2D( name );

        // Create the sprite object and add it to the sprite list.
        CSprite2D * pSprite = new CSprite2D( pData );
        _spriteList2d[name].push_back( pSprite );

        return pSprite;
    }
    catch( NExcept::CCriticalException e )
    {
        throw e;
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
/// <param name="name"> Name of the text sprite. </param>
/// *************************************************************************
CTextSprite * CSpriteManager::CreateTextSprite( const std::string & name )
{
    try
    {
        // Get the data used to create the sprite.
        auto pData = GetTextSpriteData( name );

        // Create the sprite object and add it to the sprite list.
        CTextSprite * pSprite = new CTextSprite( pData );
        _textSpriteList[name].push_back( pSprite );

        return pSprite;
    }
    catch( NExcept::CCriticalException e )
    {
        throw e;
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
                    string name;
                    NParseHelper::GetString( iter, "name", name );

                    // Get the data used to create the sprite.
                    auto pData = GetSpriteData3D( name );

                    // Create the sprite object and add it to the sprite list.
                    CSprite3D * pSprite = new CSprite3D( pData );
                    _spriteList3d[name].push_back( pSprite );

                    CVector3 pos;
                    if( NParseHelper::GetXYZ( iter, "position", pos ) )
                        pSprite->SetPos( pos );

                    CVector3 rot;
                    if( NParseHelper::GetXYZ( iter, "rotation", rot ) )
                        pSprite->SetRot( rot );

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
            NDelFunc::DeleteMapVectorPointers( _spriteList2d );
            NDelFunc::DeleteMapVectorPointers( _textSpriteList );
            NDelFunc::DeleteMapPointers( _spriteDataList3d );
            NDelFunc::DeleteMapPointers( _spriteDataList2d );
            NDelFunc::DeleteMapPointers( _textSpriteDataList );
        }
        else
        {
            NDelFunc::DeleteMapVectorPointers( name, _spriteList3d );
            NDelFunc::DeleteMapVectorPointers( name, _spriteList2d );
            NDelFunc::DeleteMapVectorPointers( name, _textSpriteList );
            NDelFunc::DeleteMapPointer( name, _spriteDataList3d );
            NDelFunc::DeleteMapPointer( name, _spriteDataList2d );
            NDelFunc::DeleteMapPointer( name, _textSpriteDataList );
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
        auto iter = _spriteList3d.find( pSprite->GetData()->GetName() );
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
                                           pSprite ? "Failed to clear sprite '" + pSprite->GetData()->GetName() + "'." :
                                                     "Failed to clear the sprite.", e );
    }
}


/// *************************************************************************
/// <summary> 
/// Reposition all 2d sprites.
/// </summary>
/// *************************************************************************
void CSpriteManager::RepositionAllSprites2D()
{
    auto mapSpriteIter = _spriteList2d.begin();
    while( mapSpriteIter != _spriteList2d.end() )
    {
        auto vecIter = mapSpriteIter->second.begin();
        while( vecIter != mapSpriteIter->second.end() )
        {
            (*vecIter)->Reposition();
            ++vecIter;
        }

        ++mapSpriteIter;
    }

    auto mapTextIter = _textSpriteList.begin();
    while( mapTextIter != _textSpriteList.end() )
    {
        auto vecIter = mapTextIter->second.begin();
        while( vecIter != mapTextIter->second.end() )
        {
            (*vecIter)->Reposition();
            ++vecIter;
        }

        ++mapTextIter;
    }
}
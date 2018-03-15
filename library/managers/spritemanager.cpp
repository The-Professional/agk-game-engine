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
/// <param name="collection"> The collection the sprite belongs to. </param>
/// *************************************************************************
CSprite3D * CSpriteManager::CreateSprite3D( const string & name, const string & collection )
{
    try
    {
        // Get the data used to create the sprite.
        auto pData = GetSpriteData3D( name );

        // Create the sprite object and add it to the sprite list.
        CSprite3D * pSprite = new CSprite3D( pData );

        // If the data does not have a default size, set it to whatever the created sprite's size is.
        if( !pData->GetVisualData()->IsSizeSet() )
            pData->SetSize( pSprite->GetSize() );

        if( collection.empty() )
            _spriteList3d[name].push_back( pSprite );
        else
            _spriteList3d[collection].push_back( pSprite );

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
/// <param name="collection"> The collection the sprite belongs to. </param>
/// *************************************************************************
CSprite2D * CSpriteManager::CreateSprite2D( const std::string & name, const string & collection )
{
    try
    {
        // Get the data used to create the sprite.
        auto pData = GetSpriteData2D( name );

        // Create the sprite object and add it to the sprite list.
        CSprite2D * pSprite = new CSprite2D( pData );

        // If the data does not have a default size, set it to whatever the created sprite's size is.
        if( !pData->GetVisualData()->IsSizeSet() )
            pData->SetSize( pSprite->GetSize() );

        if( collection.empty() )
            _spriteList2d[name].push_back( pSprite );
        else
            _spriteList2d[collection].push_back( pSprite );

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
/// <param name="collection"> The collection the sprite belongs to. </param>
/// *************************************************************************
CTextSprite * CSpriteManager::CreateTextSprite( const string & name, const string & text, const string & collection )
{
    try
    {
        // Get the data used to create the sprite.
        auto pData = GetTextSpriteData( name );

        // Create the sprite object and add it to the sprite list.
        CTextSprite * pSprite = new CTextSprite( pData, text );

        if( collection.empty() )
            _textSpriteList[name].push_back( pSprite );
        else
            _textSpriteList[collection].push_back( pSprite );

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
    for( auto mapIter : _spriteList2d )
        for( auto pSprite : mapIter.second )
            pSprite->Reposition();

    for( auto mapIter : _textSpriteList )
        for( auto pSprite : mapIter.second )
            pSprite->Reposition();
}


/// *************************************************************************
/// <summary> 
/// Update all sprites in the manager.
/// </summary>
/// *************************************************************************
void CSpriteManager::Update()
{
    for( auto mapIter : _spriteList3d )
        for( auto pSprite : mapIter.second )
            pSprite->Update();

    for( auto mapIter : _spriteList2d )
        for( auto pSprite : mapIter.second )
            pSprite->Update();

    for( auto mapIter : _textSpriteList )
        for( auto pSprite : mapIter.second )
            pSprite->Update();
}


/// *************************************************************************
/// <summary> 
/// Transform all the sprites in the manager.
/// </summary>
/// *************************************************************************
void CSpriteManager::Transform()
{
    // Transform each of the sprites.
    //for( auto mapIter : _spriteList3d )
    for( auto mapIter = _spriteList3d.begin(); mapIter != _spriteList3d.end(); ++mapIter )
        for( auto pSprite : mapIter->second )
            pSprite->Transform();

    //for( auto mapIter : _spriteList2d )
    for( auto mapIter = _spriteList2d.begin(); mapIter != _spriteList2d.end(); ++mapIter )
        for( auto pSprite : mapIter->second )
            pSprite->Transform();

    //for( auto mapIter : _textSpriteList )
    for( auto mapIter = _textSpriteList.begin(); mapIter != _textSpriteList.end(); ++mapIter )
        for( auto pSprite : mapIter->second )
            pSprite->Transform();

    // Clear the modified bitmask for each of the sprites.
    //for( auto mapIter : _spriteList3d )
    for( auto mapIter = _spriteList3d.begin(); mapIter != _spriteList3d.end(); ++mapIter )
        for( auto pSprite : mapIter->second )
            pSprite->ClearModified();

    //for( auto mapIter : _spriteList2d )
    for( auto mapIter = _spriteList2d.begin(); mapIter != _spriteList2d.end(); ++mapIter )
        for( auto pSprite : mapIter->second )
            pSprite->ClearModified();

    //for( auto mapIter : _textSpriteList )
    for( auto mapIter = _textSpriteList.begin(); mapIter != _textSpriteList.end(); ++mapIter )
        for( auto pSprite : mapIter->second )
            pSprite->ClearModified();
}
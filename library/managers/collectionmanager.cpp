// Physical component dependency
#include "collectionmanager.h"

// Game lib dependencies
#include <agk.h>
#include <utilities\exceptionhandling.h>
#include <utilities\generalfuncs.h>
#include <managers\spritemanager.h>
#include <common\vector3.h>
#include <3d\sprite3d.h>
#include <2d\sprite2d.h>
#include <2d\textsprite.h>
#include <common\iobject.h>
#include <common\collectionobject.h>

// Standard lib dependencies
#include <fstream>

using namespace std;
using namespace nlohmann;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CCollectionManager::CCollectionManager()
{
}


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CCollectionManager::~CCollectionManager()
{
}


/// *************************************************************************
/// <summary> 
/// Read the path and compile the list of collection files in that folder.
/// </summary>
/// *************************************************************************
void CCollectionManager::LoadCollectionFileList( const string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _collectionFileList );
}


/// *************************************************************************
/// <summary> 
/// Load the collection.
/// </summary>
/// <param name="name"> Name of the collection. </param>
/// <returns> List of loaded objects. </param>
/// *************************************************************************
vector<iObject *> CCollectionManager::LoadCollection( const string & name )
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
                LoadSpriteCollection3D( collectionIter, name, pObjectList );
                LoadSpriteCollection2D( collectionIter, name, pObjectList );
                LoadTextSpriteCollection( collectionIter, name, pObjectList );
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
/// Load all 3d sprites in the collection.
/// </summary>
/// *************************************************************************
void CCollectionManager::LoadSpriteCollection3D( json::const_iterator iter, const string & collectionName, std::vector<iObject *> & pObjectList )
{
    auto collectionIter = iter->find( "sprite3d" );
    if( collectionIter != iter->end() )
    {
        auto objectIter = collectionIter->begin();
        while( objectIter != collectionIter->end() )
        {
            CCollectionObject collectionObject;
            NParseHelper::GetCollectionObject( objectIter, collectionObject );

            // Get the data used to create the sprite.
            iObject * pSprite = CSpriteManager::Instance().CreateSprite3D( collectionObject.name, collectionName );
            pObjectList.push_back( pSprite );
            pSprite->Set( collectionObject );

            ++objectIter;
        }
    }
}


/// *************************************************************************
/// <summary> 
/// Load all 2d sprites in the collection.
/// </summary>
/// *************************************************************************
void CCollectionManager::LoadSpriteCollection2D( json::const_iterator iter, const string & collectionName, std::vector<iObject *> & pObjectList )
{
    auto collectionIter = iter->find( "sprite2d" );
    if( collectionIter != iter->end() )
    {
        auto objectIter = collectionIter->begin();
        while( objectIter != collectionIter->end() )
        {
            CCollectionObject collectionObject;
            NParseHelper::GetCollectionObject( objectIter, collectionObject );

            // Get the data used to create the sprite.
            iObject * pSprite = CSpriteManager::Instance().CreateSprite2D( collectionObject.name, collectionName );
            pObjectList.push_back( pSprite );
            pSprite->Set( collectionObject );

            ++objectIter;
        }
    }
}


/// *************************************************************************
/// <summary> 
/// Load all text sprites in the collection.
/// </summary>
/// *************************************************************************
void CCollectionManager::LoadTextSpriteCollection( json::const_iterator iter, const string & collectionName, std::vector<iObject *> & pObjectList )
{
    auto collectionIter = iter->find( "textSprite" );
    if( collectionIter != iter->end() )
    {
        auto objectIter = collectionIter->begin();
        while( objectIter != collectionIter->end() )
        {
            CCollectionObject collectionObject;
            NParseHelper::GetCollectionObject( objectIter, collectionObject );

            // Get the data used to create the sprite.
            iObject * pSprite = CSpriteManager::Instance().CreateTextSprite( collectionObject.name, collectionObject.text, collectionName );
            pObjectList.push_back( pSprite );
            pSprite->Set( collectionObject );

            ++objectIter;
        }
    }
}
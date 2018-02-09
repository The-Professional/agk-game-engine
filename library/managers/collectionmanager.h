#ifndef __collection_manager_h__
#define __collection_manager_h__

// Game lib dependencies
#include <common\defs.h>
#include <utilities\jsonparsehelper.h>

// Standard lib dependencies
#include <string>
#include <map>

// Forward declarations
class CSprite3D;


/// *************************************************************************
/// <summary> 
/// Class to load collections.
/// </summary>
/// *************************************************************************
class CCollectionManager
{
public:
    // Get the instance of the singleton class
    static CCollectionManager & Instance()
    {
        static CCollectionManager collectionManager;
        return collectionManager;
    }

    // Read the path and compile the list of collection files in that folder.
    void LoadCollectionFileList( const std::string & path );

    // Load the collection.
    void LoadCollection( const std::string & name );

private:

    // Constructor
    CCollectionManager();

    // Destructor
    virtual ~CCollectionManager();

    // Load all 3d sprites in the collection.
    void LoadSpriteCollection3D( nlohmann::json::const_iterator iter, const std::string & collectionName );

    // Load all 2d sprites in the collection.
    void LoadSpriteCollection2D( nlohmann::json::const_iterator iter, const std::string & collectionName );

    // Load all text sprites in the collection.
    void LoadTextSpriteCollection( nlohmann::json::const_iterator iter, const std::string & collectionName );

private:

    // Map containing the list of collection files.
    std::map<std::string, std::string> _collectionFileList;
};

#endif  // __collection_manager_h__

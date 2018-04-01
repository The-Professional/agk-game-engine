#ifndef __sprite_manager_h__
#define __sprite_manager_h__

// Game lib dependencies
#include <common\defs.h>

// Standard lib dependencies
#include <string>
#include <map>
#include <vector>

// Forward declarations
class CSpriteData3D;
class CSpriteData2D;
class CTextSpriteData;
class CSprite3D;
class CSprite2D;
class CTextSprite;
class iObject;

/// *************************************************************************
/// <summary> 
/// Class to load and hold objects.
/// </summary>
/// *************************************************************************
class CSpriteManager
{
public:
    // Get the instance of the singleton class
    static CSpriteManager & Instance()
    {
        static CSpriteManager spriteManager;
        return spriteManager;
    }

    // Read the file and compile the list of sprite data files.
    void LoadDataFileList3D( const std::string & path );
    void LoadDataFileList2D( const std::string & path );
    void LoadTextDataFileList( const std::string & path );

    // Read the path and compile the list of collection files in that folder.
    void LoadCollectionFileList( const std::string & path );

    // Free the loaded sprite data.
    void Clear( const std::string & name = "" );

    // Load the sprite data.
    CSpriteData3D * GetSpriteData3D( const std::string & name );
    CSpriteData2D * GetSpriteData2D( const std::string & name );
    CTextSpriteData * GetTextSpriteData( const std::string & name );

    // Create the sprite.
    CSprite3D * CreateSprite3D( const std::string & name, const std::string & key = "" );
    CSprite2D * CreateSprite2D( const std::string & name, const std::string & key = "" );
    CTextSprite * CreateTextSprite( const std::string & name, const std::string & text, const std::string & key = "" );

    // Create the collection of objects.
    std::vector<iObject *> CreateCollection( const std::string & name, const std::string & key = "" );

    // Reposition all sprites.
    void RepositionAllSprites();

    // Update all sprites in the manager.
    void Update();

    // Transform all the sprites in the manager.
    void Transform();

private:

    CSpriteManager();
    virtual ~CSpriteManager();

private:

    // Map containing the list of sprite data files.
    std::map<const std::string, const std::string> _spriteDataFileList3d;
    std::map<const std::string, const std::string> _spriteDataFileList2d;
    std::map<const std::string, const std::string> _textSpriteDataFileList;

    // Map containing the list of collection files.
    std::map<const std::string, const std::string> _collectionFileList;

    // Map containing the list of loaded sprite data.
    std::map<const std::string, CSpriteData3D *> _spriteDataList3d;
    std::map<const std::string, CSpriteData2D *> _spriteDataList2d;
    std::map<const std::string, CTextSpriteData *> _textSpriteDataList;

    // Map containing the list of loaded objects.
    std::map<const std::string, std::vector<iObject *>> _objectList;
};

#endif  // __sprite_manager_h__

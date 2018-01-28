#ifndef __sprite_data_manager_h__
#define __sprite_data_manager_h__

// Game lib dependencies
#include <common\defs.h>
#include <managers\resourcefile.h>

// Standard lib dependencies
#include <string>
#include <map>
#include <vector>

// Forward declarations
class CSpriteData3D;
class CSprite3D;

/// *************************************************************************
/// <summary> 
/// Class to load and hold 3d mesh id's.
/// </summary>
/// *************************************************************************
class CSpriteManager
{
public:
    // Get the instance of the singleton class
    static CSpriteManager & Instance()
    {
        static CSpriteManager spriteDataManager;
        return spriteDataManager;
    }

    // Read the file and compile the list of sprite data files.
    void LoadDataFileList3D( const std::string & path );

    // Read in the file and compile the list of sprite collection files.
    void LoadCollectionFileList3D( const std::string & path );

    // Free the loaded sprite data.
    void Clear( const std::string & name = "" );
    void Clear( CSprite3D * pSprite );

    // Load the sprite data.
    const CSpriteData3D * GetSpriteData3D( const std::string & name );

    // Create the sprite.
    CSprite3D * CreateSprite3D( const std::string & name );

    // Create the collection of sprites.
    void CreateSpriteCollection3D( const std::string & name );

private:

    // Constructor
    CSpriteManager();

    // Destructor
    virtual ~CSpriteManager();

private:

    // Map containing the list of sprite data files.
    std::map<std::string, std::string> _spriteDataFileList3d;

    // Map containing the list of sprite collection files.
    std::map<std::string, std::string> _spriteCollectionFileList3d;

    // Map containing the list of loaded sprite data.
    std::map<std::string, CSpriteData3D *> _spriteDataList3d;

    // Map containing the list of loaded sprites.
    std::map<std::string, std::vector<CSprite3D *>> _spriteList3d;

};

#endif  // __sprite_data_manager_h__

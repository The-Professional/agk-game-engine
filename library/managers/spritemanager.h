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
class CSpriteData2D;
class CTextSpriteData;
class CSprite3D;
class CSprite2D;
class CTextSprite;

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
    void LoadDataFileList2D( const std::string & path );
    void LoadTextDataFileList( const std::string & path );

    // Read in the file and compile the list of sprite collection files.
    void LoadCollectionFileList3D( const std::string & path );

    // Free the loaded sprite data.
    void Clear( const std::string & name = "" );
    void Clear( CSprite3D * pSprite );

    // Load the sprite data.
    const CSpriteData3D * GetSpriteData3D( const std::string & name );
    const CSpriteData2D * GetSpriteData2D( const std::string & name );
    const CTextSpriteData * GetTextSpriteData( const std::string & name );

    // Create the sprite.
    CSprite3D * CreateSprite3D( const std::string & name );
    CSprite2D * CreateSprite2D( const std::string & name );
    CTextSprite * CreateTextSprite( const std::string & name );

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
    std::map<std::string, std::string> _spriteDataFileList2d;
    std::map<std::string, std::string> _textSpriteDataFileList;

    // Map containing the list of sprite collection files.
    std::map<std::string, std::string> _spriteCollectionFileList3d;

    // Map containing the list of loaded sprite data.
    std::map<std::string, CSpriteData3D *> _spriteDataList3d;
    std::map<std::string, CSpriteData2D *> _spriteDataList2d;
    std::map<std::string, CTextSpriteData *> _textSpriteDataList;

    // Map containing the list of loaded sprites.
    std::map<std::string, std::vector<CSprite3D *>> _spriteList3d;
    std::map<std::string, std::vector<CSprite2D *>> _spriteList2d;
    std::map<std::string, std::vector<CTextSprite *>> _textSpriteList;
};

#endif  // __sprite_data_manager_h__

#ifndef __stage_manager_3d_h__
#define __stage_manager_3d_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\vector3.h>
#include <common\color.h>

// Standard lib dependencies
#include <string>
#include <vector>
#include <map>

// Forward declarations
class CSprite3D;

/// *************************************************************************
/// <summary> 
/// Singleton class to load stage objects.
/// </summary>
/// *************************************************************************
class CStageManager3D
{
public:
    // Get the instance of the singleton class
    static CStageManager3D & Instance()
    {
        static CStageManager3D stage3d;
        return stage3d;
    }

    // Load the stage.
    void LoadStage( const std::string & name );

private:

    // Constructor/Destructor
    CStageManager3D();
    virtual ~CStageManager3D();

    // Name of the loaded stage.
    std::string _name;

    // List of sprites populating the stage.
    std::vector<CSprite3D> _spriteList;

    // Map containing the list of stages and their files.
    std::map<std::string, std::string> _stageFileList;

    // List of lights populating the stage.
    //std::vector<CLight> lightList;
};

#endif  // __stage_manager_3d_h__

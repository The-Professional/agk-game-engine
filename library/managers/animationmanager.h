#ifndef __animation_manager_h__
#define __animation_manager_h__

// Game lib dependencies
#include <common\defs.h>

// Standard lib dependencies
#include <string>
#include <map>

// Forward declarations
class CTweenChain;

/// *************************************************************************
/// <summary> 
/// Class to load and hold tween animations.
/// </summary>
/// *************************************************************************
class CAnimationManager
{
public:
    // Get the instance of the singleton class
    static CAnimationManager & Instance()
    {
        static CAnimationManager animationManager;
        return animationManager;
    }

    // Free the animation resources.
    void Clear();

    // Get the interpolation id from AGK.
    int GetInterpolation( const std::string & interpolation ) const;

    // Get the transform type from the passed in string.
    uint GetTransformType( const std::string & type ) const;

    // Load the list of animations from the passed in folder.
    void LoadAnimationList( const std::string & path );

private:

    CAnimationManager();
    virtual ~CAnimationManager();

    std::map<std::string, std::string> _animationFileList;

    // Map containing the list of meshes.
    std::map<std::string, CTweenChain *> _animationList;

    // List of interpolation methods.
    std::map<std::string, int> _interpolationList;

    // List of transformation types and their string counterpart.
    std::map<std::string, uint> _transformTypeList;
};

#endif  // __animation_manager_h__

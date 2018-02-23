#ifndef __script_h__
#define __script_h__

// Game lib dependencies
#include <common\defs.h>

// Standard lib dependencies
#include <string>
#include <vector>

// Forward declarations
class iObject;
class CAnimationData;
class asIScriptContext;

/// *************************************************************************
/// <summary> 
/// Class to hold animation information.
/// </summary>
/// *************************************************************************
class CScript
{
public:

    CScript();
    CScript( CAnimationData * pData, iObject * pObject );
    ~CScript();

    // Initialize the animation.
    void Init( CAnimationData * pData, iObject * pObject );

    // Clear the animation.
    void Clear();

private:

    // Default data of the animation.
    CAnimationData * _pData = nullptr;

    // The object to animate. This is not owned by the animation.
    iObject * _pObject = nullptr;

    // A list of each function that needs to play when this animation is played.
    std::vector<std::string> _functionList;

    // The context used to animate the object. These are not owned by the animation.
    std::vector<asIScriptContext *> _pContextList;
};


#endif  // __script_h__
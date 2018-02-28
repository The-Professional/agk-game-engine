#ifndef __script_manager_h__
#define __script_manager_h__

// Game lib dependencies
//#include <utilities\smartpointers.h>
#include <script\scriptparam.h>
#include <managers\resourcefile.h>

// Standard lib dependencies
#include <string>
#include <vector>
#include <map>

// Forward declaration(s)
class CAnimationData;
class asIScriptEngine;
class asIScriptContext;
class asIScriptModule;
class asIScriptContext;
class asIScriptFunction;
struct asSMessageInfo;

/// *************************************************************************
/// <summary> 
/// Class to manage AngelScript.
/// </summary>
/// *************************************************************************
class CScriptManager
{
public:

    // Get the instance of the singleton class.
    static CScriptManager & Instance()
    {
        static CScriptManager scriptManager;
        return scriptManager;
    }

    // Get the pointer to the script engine.
    asIScriptEngine * GetEnginePtr();

    // Locate the folder and compile the list of script files.
    void LoadScriptList( const std::string & path );

    // Locate the folder and compile the list of animation data files.
    void LoadAnimationDataFileList( const std::string & path );

    // Load the animation data.
    const CAnimationData * GetAnimationData( const std::string & name );

    // Load a script.
    void LoadScript( const std::string & name );

    // Free all of the scripts of a specific data group.
    void Clear();

    // Get the script engine contex from a managed pool.
    asIScriptContext * GetContext();

    // Update the active scripts.
    void Update();
    void Update( std::vector<asIScriptContext *> & pContextVec );

    // Add the script context back to the managed pool.
    void RecycleContext( asIScriptContext * pContext );

    // Get pointer to function.
    asIScriptFunction * GetPtrToFunc( const std::string & name );

    // Prepare the script function to run.
    asIScriptContext * Prepare(
        const std::string & function,
        const std::vector<CScriptParam> & paramList = std::vector<CScriptParam>() );

    /*asIScriptContext * Prepare(
        const std::string & function,
        const std::vector<CScriptParam> & paramList );*/

    // Register object with AngelScript.
    void Register();

    // Prepare the spawn script function to run.
    void PrepareSpawn( const std::string & funcName );
    void PrepareSpawnObj( const std::string & funcName, void * pVoid );

private:

    // Constructor
    CScriptManager();

    // Destructor
    virtual ~CScriptManager();

    // Add the script to the module.
    void AddScript( const std::string & filePath );

    // Build all the scripts added to the module.
    void BuildScript();

    // Call back to display AngelScript messages.
    void MessageCallback( const asSMessageInfo & msg );

    // Add the script context back to the managed pool.
    void RecycleContext( std::vector<asIScriptContext *>::iterator & iter );

private:

    // Smart com pointer to AngelScript engine.
    asIScriptEngine * _pScriptEngine = nullptr;

    // Map containing a list of AngelScript files.
    std::map<const std::string, CResourceFile> _scriptFileList;

    // Map containing a list of animation data files.
    std::map<const std::string, const std::string> _animationDataFileList;

    // Map containing a list of the animation data pointers.
    std::map<const std::string, CAnimationData *> _animationDataList;

    // Map containing a list of AngelScript function pointers.
    std::map<const std::string, asIScriptFunction *> _pScriptFunctionList;

    // Holds the pool of script contexts.
    std::vector<asIScriptContext *> _pInactiveContextList;

    // Holds active contexts that are executing scripts.
    std::vector<asIScriptContext *> _pActiveContextList;

    // AngelScript module.
    asIScriptModule * _pScriptModule = nullptr;
};

#endif  // __script_manager_h__



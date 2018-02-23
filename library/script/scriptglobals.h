#ifndef __script_globals_h__
#define __script_globals_h__

// Forward declaration(s)
class asIScriptEngine;

/// *************************************************************************
/// <summary> 
/// AngelScript global function registration.
/// </summary>
/// *************************************************************************
namespace NScriptGlobals
{
    void Throw( int value );

    // Register Script CColor Object
    void Register( asIScriptEngine * pEngine );
}

#endif  // __script_globals_h__



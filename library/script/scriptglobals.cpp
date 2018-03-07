// Physical component dependency
#include <script/scriptglobals.h>

// Game lib dependencies
#include <agk.h>
#include <utilities/generalfuncs.h>
#include <utilities/exceptionhandling.h>

// Boost lib dependencies
#include <boost\format.hpp>

// AngelScript lib dependencies
#include <angelscript.h>

namespace NScriptGlobals
{
    /// *************************************************************************
    /// <summary> 
    /// Throw an exception for values less then 0.
    /// </summary>
    /// *************************************************************************
    void Throw( int value )
    {
        if( value < 0 )
            throw NExcept::CCriticalException( "Error Registering AngelScript Function!",
                                               boost::str( boost::format( "Function could not be created.\n\n%s\nLine: %s" )
                                                           % __FUNCTION__ % __LINE__ ) );
    }


    /// *************************************************************************
    /// <summary> 
    /// Suspend the script to the game loop.
    /// </summary>
    /// *************************************************************************
    void Suspend()
    {
        asIScriptContext *ctx = asGetActiveContext();

        // Suspend the context so the game loop can resumed
        if( ctx )
            ctx->Suspend();
    }


    /// *************************************************************************
    /// <summary> 
    /// Register the global functions.
    /// </summary>
    /// <param name="pEngine"> Scripting engine to register the functions to. </param>
    /// *************************************************************************
    void Register( asIScriptEngine * pEngine )
    {
        Throw( pEngine->RegisterGlobalFunction( "float GetElapsedTime()", asFUNCTION( agk::GetFrameTime ), asCALL_CDECL ) );
        Throw( pEngine->RegisterGlobalFunction( "void Print(string &in)", asFUNCTION( NGeneralFuncs::PostDebugMsg ), asCALL_CDECL ) );
        Throw( pEngine->RegisterGlobalFunction( "void Suspend()", asFUNCTION( Suspend ), asCALL_CDECL ) );
    }

}


/************************************************************************
*    FILE NAME:       scriptvector3.h
*
*    DESCRIPTION:     CPoint script object registration
************************************************************************/

#ifndef __script_vector_3_h__
#define __script_vector_3_h__

// Forward declaration(s)
class asIScriptEngine;

/// *************************************************************************
/// <summary>
/// CVector3 script object registration functions.
/// </summary>
/// *************************************************************************
namespace NScriptPoint
{
    // Register CVector3 as a script object.
    void Register( asIScriptEngine * pEngine );
}

#endif  // __script_vector_3_h__



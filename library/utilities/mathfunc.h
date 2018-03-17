#ifndef __math_func_h__
#define __math_func_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\vector3.h>
#include <common\bitmask.h>

/// <summary>
/// Namespace to some general math functions. 
/// </summary>
namespace NMathFunc
{
    // Get whether the two values are approximately equal.
    bool Approximate( float v1, float v2, float error = 0.0001f );

    // Get the new position correctly aligned with the window.
    void AlignPosition( const CBitmask<uint> & alignment, CVector3 & vPos );
    void AlignPositionX( const CBitmask<uint> & alignment, float & x );
    void AlignPositionY( const CBitmask<uint> & alignment, float & y );

    // Perform a modulus operation on floats.
    float Modulus( float v1, float v2 );
}

#endif  // __math_func_h__


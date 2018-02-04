#ifndef __math_func_h__
#define __math_func_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\vector2.h>
#include <common\bitmask.h>

/// <summary>
/// Namespace to some general math functions. 
/// </summary>
namespace NMathFunc
{
    // Get whether the two values are approximately equal.
    bool Approximate( float v1, float v2, float error = 0.0001f );

    // Get the new position correctly aligned with the window.
    CVector2 GetAlignedPos( const CBitmask<uint> & alignment, const CVector2 & vPos );
    float GetAlignedPosX( const CBitmask<uint> & alignment, float x );
    float GetAlignedPosY( const CBitmask<uint> & alignment, float y );
}

#endif  // __math_func_h__


#ifndef __math_func_h__
#define __math_func_h__

// Game lib dependencies
#include <common\vector3.h>
#include <common\size.h>
#include <common\defs.h>
#include <common\bitmask.h>

/// <summary>
/// Namespace to some general math functions. 
/// </summary>
namespace NMathFunc
{
    //// Get the dynamic position
    //CVector3 GetPos( CSize defaultHalfSize )
    //{
    //    CVector3 pos;
    //    
    //    // Strip out any fractional component for correct rendering
    //    //defaultHalfSize.Round();

    //    if( m_parameters.IsSet( CDynamicOffset::EDO_LEFT ) )
    //        pos.x = -(defaultHalfSize.w - point.x);

    //    else if( m_parameters.IsSet( CDynamicOffset::EDO_RIGHT ) )
    //        pos.x = defaultHalfSize.w - point.x;

    //    else if( m_parameters.IsSet( CDynamicOffset::EDO_HORZ_CENTER ) )
    //        pos.x = point.x;

    //    if( m_parameters.IsSet( CDynamicOffset::EDO_TOP ) )
    //        pos.y = defaultHalfSize.h - point.y;
    //        
    //    else if( m_parameters.IsSet( CDynamicOffset::EDO_BOTTOM ) )
    //        pos.y = -(defaultHalfSize.h - point.y);

    //    else if( m_parameters.IsSet( EDO_VERT_CENTER ) )
    //        pos.y = point.y;

    //    return pos;
    //}

}

#endif  // __math_func_h__


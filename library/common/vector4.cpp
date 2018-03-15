// Physical component dependency
#include "vector4.h"

// Game lib dependencies
#include <common\vector2.h>

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CVector4::CVector4( float value )
{
    x = y = z = w = value;
}

// Constructor
CVector4::CVector4( float _x, float _y, float _z, float _w )
{
    x = _x; y = _y; z = _z; w = _w;
}


/// *************************************************************************
/// <summary> 
/// 4D vector assignment.
/// </summary>
/// *************************************************************************
void CVector4::operator = ( float value )
{
    x = y = z = w = value;
}

void CVector4::operator = ( const CVector2 & value )
{
    x = value.x;
    y = value.y;
}


/// *************************************************************************
/// <summary> 
/// 4D vector addition.
/// </summary>
/// *************************************************************************
CVector4 CVector4::operator + ( const CVector4 & vec ) const
{
    return CVector4( x + vec.x, y + vec.y, z + vec.z, w + vec.w );
}


/// *************************************************************************
/// <summary> 
/// 4D vector addition.
/// </summary>
/// *************************************************************************
void CVector4::operator += ( const CVector4 & vec )
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    w += vec.w;
}


/// *************************************************************************
/// <summary> 
/// 4D vector subtraction.
/// </summary>
/// *************************************************************************
CVector4 CVector4::operator - ( const CVector4 & vec ) const
{
    return CVector4( x - vec.x, y - vec.y, z - vec.z, w - vec.w );
}


/// *************************************************************************
/// <summary> 
/// 4D vector subtraction.
/// </summary>
/// *************************************************************************
void CVector4::operator -= ( const CVector4 & vec )
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    w -= vec.w;
}
// Physical component dependency
#include "vector3.h"

// Game lib dependencies
#include <common\vector2.h>

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CVector3::CVector3( float value )
{
    x = y = z = value;
}

// Constructor
CVector3::CVector3( float _x, float _y, float _z )
{
    x = _x; y = _y; z = _z;
}


/// *************************************************************************
/// <summary> 
/// 3D vector assignment.
/// </summary>
/// *************************************************************************
void CVector3::operator = ( float value )
{
    x = y = z = value;
}

// 3D vector assignment.
void CVector3::operator = ( const CVector2 & vec )
{
    x = vec.x;
    y = vec.y;
}


/// *************************************************************************
/// <summary> 
/// 3D vector addition.
/// </summary>
/// *************************************************************************
CVector3 CVector3::operator + ( const CVector3 & vec ) const
{
    return CVector3( x + vec.x, y + vec.y, z + vec.z );
}

// 3D vector addition.
CVector3 CVector3::operator + ( const CVector2 & vec ) const
{
    return CVector3( x + vec.x, y + vec.y );
}


/// *************************************************************************
/// <summary> 
/// 3D vector addition.
/// </summary>
/// *************************************************************************
void CVector3::operator += ( const CVector3 & vec )
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
}

// 3D vector addition.
void CVector3::operator += ( const CVector2 & vec )
{
    x += vec.x;
    y += vec.y;
}


/// *************************************************************************
/// <summary> 
/// 3D vector subtraction.
/// </summary>
/// *************************************************************************
CVector3 CVector3::operator - ( const CVector3 & vec ) const
{
    return CVector3( x - vec.x, y - vec.y, z - vec.z );
}

// 3D vector subtraction.
CVector3 CVector3::operator - ( const CVector2 & vec ) const
{
    return CVector3( x - vec.x, y - vec.y );
}


/// *************************************************************************
/// <summary> 
/// 3D vector subtraction.
/// </summary>
/// *************************************************************************
void CVector3::operator -= ( const CVector3 & vec )
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
}

// 3D vector subtraction.
void CVector3::operator -= ( const CVector2 & vec )
{
    x -= vec.x;
    y -= vec.y;
}
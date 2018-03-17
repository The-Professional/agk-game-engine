// Physical component dependency
#include "vector3.h"

// Game lib dependencies
#include <common\vector2.h>
#include <utilities\mathfunc.h>

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

// Constructor
CVector3::CVector3( const CVector2 & value )
{
    x = value.x; y = value.y;
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

// 3D vector addition.
CVector3 CVector3::operator + ( float value ) const
{
    return CVector3( x + value, y + value, z + value );
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

// 3D vector addition.
void CVector3::operator += ( float value )
{
    x += value;
    y += value;
    z += value;
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

// 3D vector subtraction.
CVector3 CVector3::operator - ( float value ) const
{
    return CVector3( x - value, y - value, z - value );
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

// 3D vector subtraction.
void CVector3::operator -= ( float value )
{
    x -= value;
    y -= value;
    z -= value;
}


/// *************************************************************************
/// <summary> 
/// 3D vector multiplation.
/// </summary>
/// *************************************************************************
CVector3 CVector3::operator * ( const CVector3 & vec ) const
{
    return CVector3( x * vec.x, y * vec.y, z * vec.z );
}

// 3D vector multiplation.
CVector3 CVector3::operator * ( const CVector2 & vec ) const
{
    return CVector3( x * vec.x, y * vec.y );
}

// 3D vector multiplation.
CVector3 CVector3::operator * ( float value ) const
{
    return CVector3( x * value, y * value, z * value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector multiplation.
/// </summary>
/// *************************************************************************
void CVector3::operator *= ( const CVector3 & vec )
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
}

// 3D vector multiplation.
void CVector3::operator *= ( const CVector2 & vec )
{
    x *= vec.x;
    y *= vec.y;
}

// 3D vector multiplation.
void CVector3::operator *= ( float value )
{
    x *= value;
    y *= value;
    z *= value;
}


/// *************************************************************************
/// <summary> 
/// 3D vector division.
/// </summary>
/// *************************************************************************
CVector3 CVector3::operator / ( const CVector3 & vec ) const
{
    return CVector3( vec.IsEmptyX() ? IsEmptyX() ? 1.f : 0 : x / vec.x,
                     vec.IsEmptyY() ? IsEmptyY() ? 1.f : 0 : y / vec.y,
                     vec.IsEmptyZ() ? IsEmptyZ() ? 1.f : 0 : z / vec.z );
}

// 3D vector division.
CVector3 CVector3::operator / ( const CVector2 & vec ) const
{
    return CVector3( vec.IsEmptyX() ? IsEmptyX() ? 1.f : 0 : x / vec.x,
                     vec.IsEmptyY() ? IsEmptyY() ? 1.f : 0 : y / vec.y );
}

// 3D vector division.
CVector3 CVector3::operator / ( float value ) const
{
    if( *(int*)&value == 0 )
        return CVector3( IsEmptyX() ? 1.f : 0,
                         IsEmptyY() ? 1.f : 0,
                         IsEmptyZ() ? 1.f : 0 );

    return CVector3( x / value, y / value, z / value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector division.
/// </summary>
/// *************************************************************************
void CVector3::operator /= ( const CVector3 & vec )
{
    x = vec.IsEmptyX() ? IsEmptyX() ? 1.f : 0 : x / vec.x;
    y = vec.IsEmptyY() ? IsEmptyY() ? 1.f : 0 : y / vec.y;
    z = vec.IsEmptyZ() ? IsEmptyZ() ? 1.f : 0 : z / vec.z;
}

// 3D vector division.
void CVector3::operator /= ( const CVector2 & vec )
{
    x = vec.IsEmptyX() ? IsEmptyX() ? 1.f : 0 : x / vec.x;
    y = vec.IsEmptyY() ? IsEmptyY() ? 1.f : 0 : y / vec.y;
}

// 3D vector division.
void CVector3::operator /= ( float value )
{
    if( *(int*)&value == 0 )
    {
        x = IsEmptyX() ? 1.f : 0;
        y = IsEmptyY() ? 1.f : 0;
        z = IsEmptyZ() ? 1.f : 0;
    }
    else
    {
        x /= value;
        y /= value;
        z /= value;
    }
}


/// *************************************************************************
/// <summary> 
/// 3D vector modulus.
/// </summary>
/// *************************************************************************
void CVector3::operator %= ( float value )
{
    x = NMathFunc::Modulus( x, value );
    y = NMathFunc::Modulus( y, value );
    z = NMathFunc::Modulus( z, value );
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector is empty.
/// </summary>
/// *************************************************************************
bool CVector3::IsEmpty() const
{
    if( IsEmptyX() && IsEmptyY() && IsEmptyZ() )
        return true;

    return false;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's x component is empty.
/// </summary>
/// *************************************************************************
bool CVector3::IsEmptyX() const
{
    return *(int*)&x == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's y component is empty.
/// </summary>
/// *************************************************************************
bool CVector3::IsEmptyY() const
{
    return *(int*)&y == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's z component is empty.
/// </summary>
/// *************************************************************************
bool CVector3::IsEmptyZ() const
{
    return *(int*)&z == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not each dimension has a value.
/// </summary>
/// *************************************************************************
bool CVector3::IsFilled() const
{
    if( !IsEmptyX() && !IsEmptyY() && !IsEmptyZ() )
        return true;

    return false;
}
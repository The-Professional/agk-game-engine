// Physical component dependency
#include "vector4.h"

// Game lib dependencies
#include <common\vector2.h>
#include <common\vector3.h>
#include <utilities\mathfunc.h>

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

// Constructor
CVector4::CVector4( const CVector3 & value )
{
    x = value.x; y = value.y; z = value.z; w = 0;
}

// Constructor
CVector4::CVector4( const CVector2 & value )
{
    x = value.x; y = value.y; z = w = 0;
}


/// *************************************************************************
/// <summary> 
/// 4D vector assignment.
/// </summary>
/// *************************************************************************
void CVector4::operator = ( const CVector3 & value )
{
    x = value.x;
    y = value.y;
    z = value.z;
}

// 4D vector assignment.
void CVector4::operator = ( const CVector2 & value )
{
    x = value.x;
    y = value.y;
}

// 4D vector assignment.
void CVector4::operator = ( float value )
{
    x = y = z = w = value;
}


/// *************************************************************************
/// <summary> 
/// 4D vector addition.
/// </summary>
/// *************************************************************************
CVector4 CVector4::operator + ( const CVector4 & value ) const
{
    return CVector4( x + value.x, 
                     y + value.y, 
                     z + value.z, 
                     w + value.w );
}

// 4D vector addition.
CVector4 CVector4::operator + ( const CVector3 & value ) const
{
    return CVector4( x + value.x, 
                     y + value.y, 
                     z + value.z, 
                     w );
}

// 4D vector addition.
CVector4 CVector4::operator + ( const CVector2 & value ) const
{
    return CVector4( x + value.x, 
                     y + value.y,
                     z,
                     w );
}

// 4D vector addition.
CVector4 CVector4::operator + ( float value ) const
{
    return CVector4( x + value,
                     y + value,
                     z + value,
                     w + value );
}


/// *************************************************************************
/// <summary> 
/// 4D vector addition.
/// </summary>
/// *************************************************************************
void CVector4::operator += ( const CVector4 & value )
{
    x += value.x;
    y += value.y;
    z += value.z;
    w += value.w;
}

// 4D vector addition.
void CVector4::operator += ( const CVector3 & value )
{
    x += value.x;
    y += value.y;
    z += value.z;
}

// 4D vector addition.
void CVector4::operator += ( const CVector2 & value )
{
    x += value.x;
    y += value.y;
}

// 4D vector addition.
void CVector4::operator += ( float value )
{
    x += value;
    y += value;
    z += value;
    w += value;
}


/// *************************************************************************
/// <summary> 
/// 4D vector subtraction.
/// </summary>
/// *************************************************************************
CVector4 CVector4::operator - ( const CVector4 & value ) const
{
    return CVector4( x - value.x,
                     y - value.y,
                     z - value.z,
                     w - value.w );
}

// 4D vector subtraction.
CVector4 CVector4::operator - ( const CVector3 & value ) const
{
    return CVector4( x - value.x,
                     y - value.y,
                     z - value.z,
                     w );
}

// 4D vector subtraction.
CVector4 CVector4::operator - ( const CVector2 & value ) const
{
    return CVector4( x - value.x,
                     y - value.y,
                     z,
                     w );
}

// 4D vector subtraction.
CVector4 CVector4::operator - ( float value ) const
{
    return CVector4( x - value,
                     y - value,
                     z - value,
                     w - value );
}


/// *************************************************************************
/// <summary> 
/// 4D vector subtraction.
/// </summary>
/// *************************************************************************
void CVector4::operator -= ( const CVector4 & value )
{
    x -= value.x;
    y -= value.y;
    z -= value.z;
    w -= value.w;
}

// 4D vector subtraction.
void CVector4::operator -= ( const CVector3 & value )
{
    x -= value.x;
    y -= value.y;
    z -= value.z;
}

// 4D vector subtraction.
void CVector4::operator -= ( const CVector2 & value )
{
    x -= value.x;
    y -= value.y;
}

// 4D vector subtraction.
void CVector4::operator -= ( float value )
{
    x -= value;
    y -= value;
    z -= value;
    w -= value;
}


/// *************************************************************************
/// <summary> 
/// 4D vector multiplication.
/// </summary>
/// *************************************************************************
CVector4 CVector4::operator * ( const CVector4 & value ) const
{
    return CVector4( x * value.x,
                     y * value.y,
                     z * value.z,
                     w * value.w );
}

// 4D vector multiplication.
CVector4 CVector4::operator * ( const CVector3 & value ) const
{
    return CVector4( x * value.x,
                     y * value.y,
                     z * value.z,
                     w );
}

// 4D vector multiplication.
CVector4 CVector4::operator * ( const CVector2 & value ) const
{
    return CVector4( x * value.x,
                     y * value.y,
                     z,
                     w );
}

// 4D vector multiplication.
CVector4 CVector4::operator * ( float value ) const
{
    return CVector4( x * value,
                     y * value,
                     z * value,
                     w * value );
}


/// *************************************************************************
/// <summary> 
/// 4D vector multiplication.
/// </summary>
/// *************************************************************************
void CVector4::operator *= ( const CVector4 & value )
{
    x *= value.x;
    y *= value.y;
    z *= value.z;
    w *= value.w;
}

// 4D vector multiplication.
void CVector4::operator *= ( const CVector3 & value )
{
    x *= value.x;
    y *= value.y;
    z *= value.z;
}

// 4D vector multiplication.
void CVector4::operator *= ( const CVector2 & value )
{
    x *= value.x;
    y *= value.y;
}

// 4D vector multiplication.
void CVector4::operator *= ( float value )
{
    x *= value;
    y *= value;
    z *= value;
    w *= value;
}


/// *************************************************************************
/// <summary> 
/// 4D vector division.
/// </summary>
/// *************************************************************************
CVector4 CVector4::operator / ( const CVector4 & value ) const
{
    return CVector4( value.IsEmptyX() ? IsEmptyX() ? 1.f : 0 : x / value.x,
                     value.IsEmptyY() ? IsEmptyY() ? 1.f : 0 : y / value.y,
                     value.IsEmptyZ() ? IsEmptyZ() ? 1.f : 0 : z / value.z,
                     value.IsEmptyW() ? IsEmptyW() ? 1.f : 0 : w / value.w );
}

// 4D vector division.
CVector4 CVector4::operator / ( const CVector3 & value ) const
{
    return CVector4( value.IsEmptyX() ? IsEmptyX() ? 1.f : 0 : x / value.x,
                     value.IsEmptyY() ? IsEmptyY() ? 1.f : 0 : y / value.y,
                     value.IsEmptyZ() ? IsEmptyZ() ? 1.f : 0 : z / value.z,
                     w );
}

// 4D vector division.
CVector4 CVector4::operator / ( const CVector2 & value ) const
{
    return CVector4( value.IsEmptyX() ? IsEmptyX() ? 1.f : 0 : x / value.x,
                     value.IsEmptyY() ? IsEmptyY() ? 1.f : 0 : y / value.y,
                     z,
                     w );
}

// 4D vector division.
CVector4 CVector4::operator / ( float value ) const
{
    if( *(int*)&value == 0 )
        return CVector4( IsEmptyX() ? 1.f : 0,
                         IsEmptyY() ? 1.f : 0,
                         IsEmptyZ() ? 1.f : 0,
                         IsEmptyW() ? 1.f : 0 );

    return CVector4( x / value,
                     y / value,
                     z / value,
                     w / value );
}


/// *************************************************************************
/// <summary> 
/// 4D vector division.
/// </summary>
/// *************************************************************************
void CVector4::operator /= ( const CVector4 & value )
{
    x = value.IsEmptyX() ? IsEmptyX() ? 1.f : 0 : x / value.x;
    y = value.IsEmptyY() ? IsEmptyY() ? 1.f : 0 : y / value.y;
    z = value.IsEmptyZ() ? IsEmptyZ() ? 1.f : 0 : z / value.z;
    w = value.IsEmptyW() ? IsEmptyW() ? 1.f : 0 : w / value.w;
}

// 4D vector division.
void CVector4::operator /= ( const CVector3 & value )
{
    x = value.IsEmptyX() ? IsEmptyX() ? 1.f : 0 : x / value.x;
    y = value.IsEmptyY() ? IsEmptyY() ? 1.f : 0 : y / value.y;
    z = value.IsEmptyZ() ? IsEmptyZ() ? 1.f : 0 : z / value.z;
}

// 4D vector division.
void CVector4::operator /= ( const CVector2 & value )
{
    x = value.IsEmptyX() ? IsEmptyX() ? 1.f : 0 : x / value.x;
    y = value.IsEmptyY() ? IsEmptyY() ? 1.f : 0 : y / value.y;
}

// 4D vector division.
void CVector4::operator /= ( float value )
{
    if( *(int*)&value == 0 )
    {
        x = IsEmptyX() ? 1.f : 0;
        y = IsEmptyY() ? 1.f : 0;
        z = IsEmptyZ() ? 1.f : 0;
        w = IsEmptyW() ? 1.f : 0;
    }
    else
    {
        x /= value;
        y /= value;
        z /= value;
        w /= value;
    }
}


/// *************************************************************************
/// <summary> 
/// 3D vector modulus.
/// </summary>
/// *************************************************************************
void CVector4::operator %= ( float value )
{
    x = NMathFunc::Modulus( x, value );
    y = NMathFunc::Modulus( y, value );
    z = NMathFunc::Modulus( z, value );
    w = NMathFunc::Modulus( w, value );
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector is empty.
/// </summary>
/// *************************************************************************
bool CVector4::IsEmpty() const
{
    if( IsEmptyX() && IsEmptyY() && IsEmptyZ() && IsEmptyW() )
        return true;

    return false;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's x component is empty.
/// </summary>
/// *************************************************************************
bool CVector4::IsEmptyX() const
{
    return *(int*)&x == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's y component is empty.
/// </summary>
/// *************************************************************************
bool CVector4::IsEmptyY() const
{
    return *(int*)&y == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's z component is empty.
/// </summary>
/// *************************************************************************
bool CVector4::IsEmptyZ() const
{
    return *(int*)&z == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's w component is empty.
/// </summary>
/// *************************************************************************
bool CVector4::IsEmptyW() const
{
    return *(int*)&w == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not each dimension has a value.
/// </summary>
/// *************************************************************************
bool CVector4::IsFilled() const
{
    if( !IsEmptyX() && !IsEmptyY() && !IsEmptyZ() && !IsEmptyW() )
        return true;

    return false;
}
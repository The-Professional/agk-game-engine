// Physical component dependency
#include "vector2.h"

// Game lib dependencies
#include <common\vector3.h>

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CVector2::CVector2( float value )
{
    x = y = value;
}

/// <summary> 
/// Constructor
/// </summary>
CVector2::CVector2( float _x, float _y )
{
    x = _x; y = _y;
}

/// <summary> 
/// Constructor
/// </summary>
CVector2::CVector2( const CVector3 & value )
{
    *this = value;
}


/// *************************************************************************
/// <summary> 
/// 2D vector assignment.
/// </summary>
/// *************************************************************************
void CVector2::operator = ( float value )
{
    x = value;
    y = value;
}

// 2D vector assignment.
void CVector2::operator = ( const CVector3 & value )
{
    x = value.x;
    y = value.y;
}


/// *************************************************************************
/// <summary> 
/// 3D vector addition.
/// </summary>
/// *************************************************************************
CVector2 CVector2::operator + ( const CVector3 & value ) const
{
    return CVector2( x + value.x, y + value.y );
}

// 3D vector addition.
CVector2 CVector2::operator + ( const CVector2 & value ) const
{
    return CVector2( x + value.x, y + value.y );
}

// 3D vector addition.
CVector2 CVector2::operator + ( float value ) const
{
    return CVector2( x + value, y + value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector addition.
/// </summary>
/// *************************************************************************
void CVector2::operator += ( const CVector3 & value )
{
    x += value.x;
    y += value.y;
}

// 3D vector addition.
void CVector2::operator += ( const CVector2 & value )
{
    x += value.x;
    y += value.y;
}

// 3D vector addition.
void CVector2::operator += ( float value )
{
    x += value;
    y += value;
}


/// *************************************************************************
/// <summary> 
/// 3D vector subtraction.
/// </summary>
/// *************************************************************************
CVector2 CVector2::operator - ( const CVector3 & value ) const
{
    return CVector2( x - value.x, y - value.y );
}

// 3D vector subtraction.
CVector2 CVector2::operator - ( const CVector2 & value ) const
{
    return CVector2( x - value.x, y - value.y );
}

// 3D vector subtraction.
CVector2 CVector2::operator - ( float value ) const
{
    return CVector2( x - value, y - value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector subtraction.
/// </summary>
/// *************************************************************************
void CVector2::operator -= ( const CVector3 & value )
{
    x -= value.x;
    y -= value.y;
}

// 3D vector subtraction.
void CVector2::operator -= ( const CVector2 & value )
{
    x -= value.x;
    y -= value.y;
}

// 3D vector subtraction.
void CVector2::operator -= ( float value )
{
    x -= value;
    y -= value;
}


/// *************************************************************************
/// <summary> 
/// 3D vector multiplation.
/// </summary>
/// *************************************************************************
CVector2 CVector2::operator * ( const CVector3 & value ) const
{
    return CVector2( x * value.x, y * value.y );
}

// 3D vector multiplation.
CVector2 CVector2::operator * ( const CVector2 & value ) const
{
    return CVector2( x * value.x, y * value.y );
}

// 3D vector multiplation.
CVector2 CVector2::operator * ( float value ) const
{
    return CVector2( x * value, y * value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector multiplation.
/// </summary>
/// *************************************************************************
void CVector2::operator *= ( const CVector3 & value )
{
    x *= value.x;
    y *= value.y;
}

// 3D vector multiplation.
void CVector2::operator *= ( const CVector2 & value )
{
    x *= value.x;
    y *= value.y;
}

// 3D vector multiplation.
void CVector2::operator *= ( float value )
{
    x *= value;
    y *= value;
}


/// *************************************************************************
/// <summary> 
/// 3D vector division.
/// </summary>
/// *************************************************************************
CVector2 CVector2::operator / ( const CVector3 & value ) const
{
    return CVector3( value.IsEmptyX() ? 0 : x / value.x,
                     value.IsEmptyY() ? 0 : y / value.y );
}

// 3D vector division.
CVector2 CVector2::operator / ( const CVector2 & value ) const
{
    return CVector3( value.IsEmptyX() ? 0 : x / value.x,
                     value.IsEmptyY() ? 0 : y / value.y );
}

// 3D vector division.
CVector2 CVector2::operator / ( float value ) const
{
    if( *(int*)&value == 0 )
        return CVector2();

    return CVector2( x / value, y / value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector division.
/// </summary>
/// *************************************************************************
void CVector2::operator /= ( const CVector3 & value )
{
    x = value.IsEmptyX() ? 0 : x / value.x;
    y = value.IsEmptyY() ? 0 : y / value.y;
}

// 3D vector division.
void CVector2::operator /= ( const CVector2 & value )
{
    x = value.IsEmptyX() ? 0 : x / value.x;
    y = value.IsEmptyY() ? 0 : y / value.y;
}

// 3D vector division.
void CVector2::operator /= ( float value )
{
    if( *(int*)&value == 0 )
        x = y = 0;
    else
    {
        x /= value;
        y /= value;
    }
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector is empty.
/// </summary>
/// *************************************************************************
bool CVector2::IsEmpty() const
{
    if( IsEmptyX() && IsEmptyY() )
        return true;

    return false;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's x component is empty.
/// </summary>
/// *************************************************************************
bool CVector2::IsEmptyX() const
{
    return *(int*)&x == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's y component is empty.
/// </summary>
/// *************************************************************************
bool CVector2::IsEmptyY() const
{
    return *(int*)&y == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not each dimension has a value.
/// </summary>
/// *************************************************************************
bool CVector2::IsFilled() const
{
    if( !IsEmptyX() && !IsEmptyY() )
        return true;

    return false;
}
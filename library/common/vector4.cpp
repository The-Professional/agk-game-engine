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
template <class T>
CVector4<T>::CVector4( T value )
{
    x = y = z = w = value;
}

// Constructor
template <class T>
CVector4<T>::CVector4( T _x, T _y, T _z, T _w )
{
    x = _x; y = _y; z = _z; w = _w;
}

// Constructor
template <class T>
CVector4<T>::CVector4( const CVector3<T> & value )
{
    x = value.x; y = value.y; z = value.z; w = 0;
}

// Constructor
template <class T>
CVector4<T>::CVector4( const CVector2<T> & value )
{
    x = value.x; y = value.y; z = w = 0;
}


/// *************************************************************************
/// <summary> 
/// 4D vector assignment.
/// </summary>
/// *************************************************************************
template <class T>
void CVector4<T>::operator = ( const CVector3<T> & value )
{
    x = value.x;
    y = value.y;
    z = value.z;
}

// 4D vector assignment.
template <class T>
void CVector4<T>::operator = ( const CVector2<T> & value )
{
    x = value.x;
    y = value.y;
}

// 4D vector assignment.
template <class T>
void CVector4<T>::operator = ( T value )
{
    x = y = z = w = value;
}


/// *************************************************************************
/// <summary> 
/// 4D vector addition.
/// </summary>
/// *************************************************************************
template <class T>
CVector4<T> CVector4<T>::operator + ( const CVector4<T> & value ) const
{
    return CVector4<T>( x + value.x,
                        y + value.y, 
                        z + value.z, 
                        w + value.w );
}

// 4D vector addition.
template <class T>
CVector4<T> CVector4<T>::operator + ( const CVector3<T> & value ) const
{
    return CVector4<T>( x + value.x,
                        y + value.y, 
                        z + value.z, 
                        w );
}

// 4D vector addition.
template <class T>
CVector4<T> CVector4<T>::operator + ( const CVector2<T> & value ) const
{
    return CVector4<T>( x + value.x,
                        y + value.y,
                        z,
                        w );
}

// 4D vector addition.
template <class T>
CVector4<T> CVector4<T>::operator + ( T value ) const
{
    return CVector4<T>( x + value,
                        y + value,
                        z + value,
                        w + value );
}


/// *************************************************************************
/// <summary> 
/// 4D vector addition.
/// </summary>
/// *************************************************************************
template <class T>
void CVector4<T>::operator += ( const CVector4<T> & value )
{
    x += value.x;
    y += value.y;
    z += value.z;
    w += value.w;
}

// 4D vector addition.
template <class T>
void CVector4<T>::operator += ( const CVector3<T> & value )
{
    x += value.x;
    y += value.y;
    z += value.z;
}

// 4D vector addition.
template <class T>
void CVector4<T>::operator += ( const CVector2<T> & value )
{
    x += value.x;
    y += value.y;
}

// 4D vector addition.
template <class T>
void CVector4<T>::operator += ( T value )
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
template <class T>
CVector4<T> CVector4<T>::operator - ( const CVector4<T> & value ) const
{
    return CVector4<T>( x - value.x,
                        y - value.y,
                        z - value.z,
                        w - value.w );
}

// 4D vector subtraction.
template <class T>
CVector4<T> CVector4<T>::operator - ( const CVector3<T> & value ) const
{
    return CVector4<T>( x - value.x,
                        y - value.y,
                        z - value.z,
                        w );
}

// 4D vector subtraction.
template <class T>
CVector4<T> CVector4<T>::operator - ( const CVector2<T> & value ) const
{
    return CVector4<T>( x - value.x,
                        y - value.y,
                        z,
                        w );
}

// 4D vector subtraction.
template <class T>
CVector4<T> CVector4<T>::operator - ( T value ) const
{
    return CVector4<T>( x - value,
                        y - value,
                        z - value,
                        w - value );
}


/// *************************************************************************
/// <summary> 
/// 4D vector subtraction.
/// </summary>
/// *************************************************************************
template <class T>
void CVector4<T>::operator -= ( const CVector4<T> & value )
{
    x -= value.x;
    y -= value.y;
    z -= value.z;
    w -= value.w;
}

// 4D vector subtraction.
template <class T>
void CVector4<T>::operator -= ( const CVector3<T> & value )
{
    x -= value.x;
    y -= value.y;
    z -= value.z;
}

// 4D vector subtraction.
template <class T>
void CVector4<T>::operator -= ( const CVector2<T> & value )
{
    x -= value.x;
    y -= value.y;
}

// 4D vector subtraction.
template <class T>
void CVector4<T>::operator -= ( T value )
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
template <class T>
CVector4<T> CVector4<T>::operator * ( const CVector4<T> & value ) const
{
    return CVector4<T>( x * value.x,
                        y * value.y,
                        z * value.z,
                        w * value.w );
}

// 4D vector multiplication.
template <class T>
CVector4<T> CVector4<T>::operator * ( const CVector3<T> & value ) const
{
    return CVector4<T>( x * value.x,
                        y * value.y,
                        z * value.z,
                        w );
}

// 4D vector multiplication.
template <class T>
CVector4<T> CVector4<T>::operator * ( const CVector2<T> & value ) const
{
    return CVector4<T>( x * value.x,
                        y * value.y,
                        z,
                        w );
}

// 4D vector multiplication.
template <class T>
CVector4<T> CVector4<T>::operator * ( T value ) const
{
    return CVector4<T>( x * value,
                        y * value,
                        z * value,
                        w * value );
}


/// *************************************************************************
/// <summary> 
/// 4D vector multiplication.
/// </summary>
/// *************************************************************************
template <class T>
void CVector4<T>::operator *= ( const CVector4<T> & value )
{
    x *= value.x;
    y *= value.y;
    z *= value.z;
    w *= value.w;
}

// 4D vector multiplication.
template <class T>
void CVector4<T>::operator *= ( const CVector3<T> & value )
{
    x *= value.x;
    y *= value.y;
    z *= value.z;
}

// 4D vector multiplication.
template <class T>
void CVector4<T>::operator *= ( const CVector2<T> & value )
{
    x *= value.x;
    y *= value.y;
}

// 4D vector multiplication.
template <class T>
void CVector4<T>::operator *= ( T value )
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
template <class T>
CVector4<T> CVector4<T>::operator / ( const CVector4<T> & value ) const
{
    return CVector4<T>( value.IsEmptyX() ? IsEmptyX() ? (T)1 : 0 : x / value.x,
                        value.IsEmptyY() ? IsEmptyY() ? (T)1 : 0 : y / value.y,
                        value.IsEmptyZ() ? IsEmptyZ() ? (T)1 : 0 : z / value.z,
                        value.IsEmptyW() ? IsEmptyW() ? (T)1 : 0 : w / value.w );
}

// 4D vector division.
template <class T>
CVector4<T> CVector4<T>::operator / ( const CVector3<T> & value ) const
{
    return CVector4<T>( value.IsEmptyX() ? IsEmptyX() ? (T)1 : 0 : x / value.x,
                        value.IsEmptyY() ? IsEmptyY() ? (T)1 : 0 : y / value.y,
                        value.IsEmptyZ() ? IsEmptyZ() ? (T)1 : 0 : z / value.z,
                        w );
}

// 4D vector division.
template <class T>
CVector4<T> CVector4<T>::operator / ( const CVector2<T> & value ) const
{
    return CVector4<T>( value.IsEmptyX() ? IsEmptyX() ? (T)1 : 0 : x / value.x,
                        value.IsEmptyY() ? IsEmptyY() ? (T)1 : 0 : y / value.y,
                        z,
                        w );
}

// 4D vector division.
template <class T>
CVector4<T> CVector4<T>::operator / ( T value ) const
{
    if( *(int*)&value == 0 )
        return CVector4<T>( IsEmptyX() ? (T)1 : 0,
                            IsEmptyY() ? (T)1 : 0,
                            IsEmptyZ() ? (T)1 : 0,
                            IsEmptyW() ? (T)1 : 0 );

    return CVector4<T>( x / value,
                        y / value,
                        z / value,
                        w / value );
}


/// *************************************************************************
/// <summary> 
/// 4D vector division.
/// </summary>
/// *************************************************************************
template <class T>
void CVector4<T>::operator /= ( const CVector4<T> & value )
{
    x = value.IsEmptyX() ? IsEmptyX() ? (T)1 : 0 : x / value.x;
    y = value.IsEmptyY() ? IsEmptyY() ? (T)1 : 0 : y / value.y;
    z = value.IsEmptyZ() ? IsEmptyZ() ? (T)1 : 0 : z / value.z;
    w = value.IsEmptyW() ? IsEmptyW() ? (T)1 : 0 : w / value.w;
}

// 4D vector division.
template <class T>
void CVector4<T>::operator /= ( const CVector3<T> & value )
{
    x = value.IsEmptyX() ? IsEmptyX() ? (T)1 : 0 : x / value.x;
    y = value.IsEmptyY() ? IsEmptyY() ? (T)1 : 0 : y / value.y;
    z = value.IsEmptyZ() ? IsEmptyZ() ? (T)1 : 0 : z / value.z;
}

// 4D vector division.
template <class T>
void CVector4<T>::operator /= ( const CVector2<T> & value )
{
    x = value.IsEmptyX() ? IsEmptyX() ? (T)1 : 0 : x / value.x;
    y = value.IsEmptyY() ? IsEmptyY() ? (T)1 : 0 : y / value.y;
}

// 4D vector division.
template <class T>
void CVector4<T>::operator /= ( T value )
{
    if( *(int*)&value == 0 )
    {
        x = IsEmptyX() ? (T)1 : 0;
        y = IsEmptyY() ? (T)1 : 0;
        z = IsEmptyZ() ? (T)1 : 0;
        w = IsEmptyW() ? (T)1 : 0;
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
template <class T>
void CVector4<T>::operator %= ( T value )
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
template <class T>
bool CVector4<T>::IsEmpty() const
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
template <class T>
bool CVector4<T>::IsEmptyX() const
{
    return *(int*)&x == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's y component is empty.
/// </summary>
/// *************************************************************************
template <class T>
bool CVector4<T>::IsEmptyY() const
{
    return *(int*)&y == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's z component is empty.
/// </summary>
/// *************************************************************************
template <class T>
bool CVector4<T>::IsEmptyZ() const
{
    return *(int*)&z == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's w component is empty.
/// </summary>
/// *************************************************************************
template <class T>
bool CVector4<T>::IsEmptyW() const
{
    return *(int*)&w == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not each dimension has a value.
/// </summary>
/// *************************************************************************
template <class T>
bool CVector4<T>::IsFilled() const
{
    if( !IsEmptyX() && !IsEmptyY() && !IsEmptyZ() && !IsEmptyW() )
        return true;

    return false;
}

// Explicit template instantiation
template class CVector4<float>;
template class CVector4<int>;
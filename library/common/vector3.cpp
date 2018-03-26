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
template <class T>
CVector3<T>::CVector3( T value )
{
    x = y = z = value;
}

// Constructor
template <class T>
CVector3<T>::CVector3( T _x, T _y, T _z )
{
    x = _x; y = _y; z = _z;
}

// Constructor
template <class T>
CVector3<T>::CVector3( const CVector2<T> & value )
{
    x = value.x; y = value.y; z = 0;
}


/// *************************************************************************
/// <summary> 
/// 3D vector assignment.
/// </summary>
/// *************************************************************************
template <class T>
void CVector3<T>::operator = ( T value )
{
    x = y = z = value;
}

// 3D vector assignment.
template <class T>
void CVector3<T>::operator = ( const CVector2<T> & vec )
{
    x = vec.x;
    y = vec.y;
}


/// *************************************************************************
/// <summary> 
/// 3D vector addition.
/// </summary>
/// *************************************************************************
template <class T>
CVector3<T> CVector3<T>::operator + ( const CVector3<T> & vec ) const
{
    return CVector3<T>( x + vec.x,
                        y + vec.y,
                        z + vec.z );
}

// 3D vector addition.
template <class T>
CVector3<T> CVector3<T>::operator + ( const CVector2<T> & vec ) const
{
    return CVector3<T>( x + vec.x,
                        y + vec.y,
                        z );
}

// 3D vector addition.
template <class T>
CVector3<T> CVector3<T>::operator + ( T value ) const
{
    return CVector3<T>( x + value,
                        y + value,
                        z + value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector addition.
/// </summary>
/// *************************************************************************
template <class T>
void CVector3<T>::operator += ( const CVector3<T> & vec )
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
}

// 3D vector addition.
template <class T>
void CVector3<T>::operator += ( const CVector2<T> & vec )
{
    x += vec.x;
    y += vec.y;
}

// 3D vector addition.
template <class T>
void CVector3<T>::operator += ( T value )
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
template <class T>
CVector3<T> CVector3<T>::operator - ( const CVector3 & vec ) const
{
    return CVector3<T>( x - vec.x,
                        y - vec.y,
                        z - vec.z );
}

// 3D vector subtraction.
template <class T>
CVector3<T> CVector3<T>::operator - ( const CVector2<T> & vec ) const
{
    return CVector3<T>( x - vec.x,
                        y - vec.y,
                        z );
}

// 3D vector subtraction.
template <class T>
CVector3<T> CVector3<T>::operator - ( T value ) const
{
    return CVector3<T>( x - value,
                        y - value,
                        z - value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector subtraction.
/// </summary>
/// *************************************************************************
template <class T>
void CVector3<T>::operator -= ( const CVector3<T> & vec )
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
}

// 3D vector subtraction.
template <class T>
void CVector3<T>::operator -= ( const CVector2<T> & vec )
{
    x -= vec.x;
    y -= vec.y;
}

// 3D vector subtraction.
template <class T>
void CVector3<T>::operator -= ( T value )
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
template <class T>
CVector3<T> CVector3<T>::operator * ( const CVector3<T> & vec ) const
{
    return CVector3<T>( x * vec.x,
                        y * vec.y,
                        z * vec.z );
}

// 3D vector multiplation.
template <class T>
CVector3<T> CVector3<T>::operator * ( const CVector2<T> & vec ) const
{
    return CVector3<T>( x * vec.x,
                        y * vec.y,
                        z );
}

// 3D vector multiplation.
template <class T>
CVector3<T> CVector3<T>::operator * ( T value ) const
{
    return CVector3<T>( x * value,
                        y * value,
                        z * value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector multiplation.
/// </summary>
/// *************************************************************************
template <class T>
void CVector3<T>::operator *= ( const CVector3<T> & vec )
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
}

// 3D vector multiplation.
template <class T>
void CVector3<T>::operator *= ( const CVector2<T> & vec )
{
    x *= vec.x;
    y *= vec.y;
}

// 3D vector multiplation.
template <class T>
void CVector3<T>::operator *= ( T value )
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
template <class T>
CVector3<T> CVector3<T>::operator / ( const CVector3<T> & vec ) const
{
    return CVector3<T>( vec.IsEmptyX() ? IsEmptyX() ? (T)1 : 0 : x / vec.x,
                        vec.IsEmptyY() ? IsEmptyY() ? (T)1 : 0 : y / vec.y,
                        vec.IsEmptyZ() ? IsEmptyZ() ? (T)1 : 0 : z / vec.z );
}

// 3D vector division.
template <class T>
CVector3<T> CVector3<T>::operator / ( const CVector2<T> & vec ) const
{
    return CVector3<T>( vec.IsEmptyX() ? IsEmptyX() ? (T)1 : 0 : x / vec.x,
                        vec.IsEmptyY() ? IsEmptyY() ? (T)1 : 0 : y / vec.y,
                        z );
}

// 3D vector division.
template <class T>
CVector3<T> CVector3<T>::operator / ( T value ) const
{
    if( *(int*)&value == 0 )
        return CVector3<T>( IsEmptyX() ? (T)1 : 0,
                            IsEmptyY() ? (T)1 : 0,
                            IsEmptyZ() ? (T)1 : 0 );

    return CVector3<T>( x / value, 
                        y / value,
                        z / value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector division.
/// </summary>
/// *************************************************************************
template <class T>
void CVector3<T>::operator /= ( const CVector3<T> & vec )
{
    x = vec.IsEmptyX() ? IsEmptyX() ? (T)1 : 0 : x / vec.x;
    y = vec.IsEmptyY() ? IsEmptyY() ? (T)1 : 0 : y / vec.y;
    z = vec.IsEmptyZ() ? IsEmptyZ() ? (T)1 : 0 : z / vec.z;
}

// 3D vector division.
template <class T>
void CVector3<T>::operator /= ( const CVector2<T> & vec )
{
    x = vec.IsEmptyX() ? IsEmptyX() ? (T)1 : 0 : x / vec.x;
    y = vec.IsEmptyY() ? IsEmptyY() ? (T)1 : 0 : y / vec.y;
}

// 3D vector division.
template <class T>
void CVector3<T>::operator /= ( T value )
{
    if( *(int*)&value == 0 )
    {
        x = IsEmptyX() ? (T)1 : 0;
        y = IsEmptyY() ? (T)1 : 0;
        z = IsEmptyZ() ? (T)1 : 0;
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
template <class T>
void CVector3<T>::operator %= ( T value )
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
template <class T>
bool CVector3<T>::IsEmpty() const
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
template <class T>
bool CVector3<T>::IsEmptyX() const
{
    return *(int*)&x == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's y component is empty.
/// </summary>
/// *************************************************************************
template <class T>
bool CVector3<T>::IsEmptyY() const
{
    return *(int*)&y == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's z component is empty.
/// </summary>
/// *************************************************************************
template <class T>
bool CVector3<T>::IsEmptyZ() const
{
    return *(int*)&z == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not each dimension has a value.
/// </summary>
/// *************************************************************************
template <class T>
bool CVector3<T>::IsFilled() const
{
    if( !IsEmptyX() && !IsEmptyY() && !IsEmptyZ() )
        return true;

    return false;
}

// Explicit template instantiation
template class CVector3<float>;
template class CVector3<int>;
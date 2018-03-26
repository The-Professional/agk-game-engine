// Physical component dependency
#include "vector2.h"

// Game lib dependencies
#include <common\vector3.h>

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
template <class T>
CVector2<T>::CVector2( T value )
{
    x = y = value;
}

/// <summary> 
/// Constructor
/// </summary>
template <class T>
CVector2<T>::CVector2( T _x, T _y )
{
    x = _x; y = _y;
}

/// <summary> 
/// Constructor
/// </summary>
template <class T>
CVector2<T>::CVector2( const CVector3<T> & value )
{
    *this = value;
}


/// *************************************************************************
/// <summary> 
/// 2D vector assignment.
/// </summary>
/// *************************************************************************
template <class T>
void CVector2<T>::operator = ( T value )
{
    x = value;
    y = value;
}

// 2D vector assignment.
template <class T>
void CVector2<T>::operator = ( const CVector3<T> & value )
{
    x = value.x;
    y = value.y;
}


/// *************************************************************************
/// <summary> 
/// 3D vector addition.
/// </summary>
/// *************************************************************************
template <class T>
CVector2<T> CVector2<T>::operator + ( const CVector3<T> & value ) const
{
    return CVector2<T>( x + value.x, y + value.y );
}

// 3D vector addition.
template <class T>
CVector2<T> CVector2<T>::operator + ( const CVector2<T> & value ) const
{
    return CVector2<T>( x + value.x, y + value.y );
}

// 3D vector addition.
template <class T>
CVector2<T> CVector2<T>::operator + ( T value ) const
{
    return CVector2<T>( x + value, y + value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector addition.
/// </summary>
/// *************************************************************************
template <class T>
void CVector2<T>::operator += ( const CVector3<T> & value )
{
    x += value.x;
    y += value.y;
}

// 3D vector addition.
template <class T>
void CVector2<T>::operator += ( const CVector2<T> & value )
{
    x += value.x;
    y += value.y;
}

// 3D vector addition.
template <class T>
void CVector2<T>::operator += ( T value )
{
    x += value;
    y += value;
}


/// *************************************************************************
/// <summary> 
/// 3D vector subtraction.
/// </summary>
/// *************************************************************************
template <class T>
CVector2<T> CVector2<T>::operator - ( const CVector3<T> & value ) const
{
    return CVector2<T>( x - value.x, y - value.y );
}

// 3D vector subtraction.
template <class T>
CVector2<T> CVector2<T>::operator - ( const CVector2<T> & value ) const
{
    return CVector2<T>( x - value.x, y - value.y );
}

// 3D vector subtraction.
template <class T>
CVector2<T> CVector2<T>::operator - ( T value ) const
{
    return CVector2<T>( x - value, y - value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector subtraction.
/// </summary>
/// *************************************************************************
template <class T>
void CVector2<T>::operator -= ( const CVector3<T> & value )
{
    x -= value.x;
    y -= value.y;
}

// 3D vector subtraction.
template <class T>
void CVector2<T>::operator -= ( const CVector2<T> & value )
{
    x -= value.x;
    y -= value.y;
}

// 3D vector subtraction.
template <class T>
void CVector2<T>::operator -= ( T value )
{
    x -= value;
    y -= value;
}


/// *************************************************************************
/// <summary> 
/// 3D vector multiplation.
/// </summary>
/// *************************************************************************
template <class T>
CVector2<T> CVector2<T>::operator * ( const CVector3<T> & value ) const
{
    return CVector2<T>( x * value.x, y * value.y );
}

// 3D vector multiplation.
template <class T>
CVector2<T> CVector2<T>::operator * ( const CVector2<T> & value ) const
{
    return CVector2<T>( x * value.x, y * value.y );
}

// 3D vector multiplation.
template <class T>
CVector2<T> CVector2<T>::operator * ( T value ) const
{
    return CVector2<T>( x * value, y * value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector multiplation.
/// </summary>
/// *************************************************************************
template <class T>
void CVector2<T>::operator *= ( const CVector3<T> & value )
{
    x *= value.x;
    y *= value.y;
}

// 3D vector multiplation.
template <class T>
void CVector2<T>::operator *= ( const CVector2<T> & value )
{
    x *= value.x;
    y *= value.y;
}

// 3D vector multiplation.
template <class T>
void CVector2<T>::operator *= ( T value )
{
    x *= value;
    y *= value;
}


/// *************************************************************************
/// <summary> 
/// 3D vector division.
/// </summary>
/// *************************************************************************
template <class T>
CVector2<T> CVector2<T>::operator / ( const CVector3<T> & value ) const
{
    return CVector2<T>( value.IsEmptyX() ? 0 : x / value.x,
                        value.IsEmptyY() ? 0 : y / value.y );
}

// 3D vector division.
template <class T>
CVector2<T> CVector2<T>::operator / ( const CVector2<T> & value ) const
{
    return CVector2<T>( value.IsEmptyX() ? 0 : x / value.x,
                        value.IsEmptyY() ? 0 : y / value.y );
}

// 3D vector division.
template <class T>
CVector2<T> CVector2<T>::operator / ( T value ) const
{
    if( *(int*)&value == 0 )
        return CVector2<T>();

    return CVector2<T>( x / value, y / value );
}


/// *************************************************************************
/// <summary> 
/// 3D vector division.
/// </summary>
/// *************************************************************************
template <class T>
void CVector2<T>::operator /= ( const CVector3<T> & value )
{
    x = value.IsEmptyX() ? 0 : x / value.x;
    y = value.IsEmptyY() ? 0 : y / value.y;
}

// 3D vector division.
template <class T>
void CVector2<T>::operator /= ( const CVector2<T> & value )
{
    x = value.IsEmptyX() ? 0 : x / value.x;
    y = value.IsEmptyY() ? 0 : y / value.y;
}

// 3D vector division.
template <class T>
void CVector2<T>::operator /= ( T value )
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
template <class T>
bool CVector2<T>::IsEmpty() const
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
template <class T>
bool CVector2<T>::IsEmptyX() const
{
    return *(int*)&x == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the vector's y component is empty.
/// </summary>
/// *************************************************************************
template <class T>
bool CVector2<T>::IsEmptyY() const
{
    return *(int*)&y == 0;
}


/// *************************************************************************
/// <summary> 
/// Whether or not each dimension has a value.
/// </summary>
/// *************************************************************************
template <class T>
bool CVector2<T>::IsFilled() const
{
    if( !IsEmptyX() && !IsEmptyY() )
        return true;

    return false;
}

// Explicit template instantiation
template class CVector2<float>;
template class CVector2<int>;
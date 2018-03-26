#ifndef __vector_4_h__
#define __vector_4_h__

// Forward declarations
template <class T>
class CVector2;

template <class T>
class CVector3;

/// *************************************************************************
/// <summary> 
/// Class to hold four dimensions of values.
/// </summary>
/// *************************************************************************
template <class T>
class CVector4
{
public:

    CVector4( T value = 0 );
    CVector4( T _x, T _y, T _z, T _w = 0 );
    CVector4( const CVector3<T> & value );
    CVector4( const CVector2<T> & value );

    // 4D vector assignment.
    void operator = ( const CVector3<T> & value );
    void operator = ( const CVector2<T> & value );
    void operator = ( T value );

    // 4D vector addition.
    CVector4<T> operator + ( const CVector4<T> & value ) const;
    CVector4<T> operator + ( const CVector3<T> & value ) const;
    CVector4<T> operator + ( const CVector2<T> & value ) const;
    CVector4<T> operator + ( T value ) const;

    // 4D vector addition.
    void operator += ( const CVector4<T> & value );
    void operator += ( const CVector3<T> & value );
    void operator += ( const CVector2<T> & value );
    void operator += ( T value );

    // 4D vector subtraction.
    CVector4<T> operator - ( const CVector4<T> & value ) const;
    CVector4<T> operator - ( const CVector3<T> & value ) const;
    CVector4<T> operator - ( const CVector2<T> & value ) const;
    CVector4<T> operator - ( T value ) const;

    // 4D vector subtraction.
    void operator -= ( const CVector4<T> & value );
    void operator -= ( const CVector3<T> & value );
    void operator -= ( const CVector2<T> & value );
    void operator -= ( T value );

    // 4D vector multiplication.
    CVector4<T> operator * ( const CVector4<T> & value ) const;
    CVector4<T> operator * ( const CVector3<T> & value ) const;
    CVector4<T> operator * ( const CVector2<T> & value ) const;
    CVector4<T> operator * ( T value ) const;

    // 4D vector multiplication.
    void operator *= ( const CVector4<T> & value );
    void operator *= ( const CVector3<T> & value );
    void operator *= ( const CVector2<T> & value );
    void operator *= ( T value );

    // 4D vector division.
    CVector4<T> operator / ( const CVector4<T> & value ) const;
    CVector4<T> operator / ( const CVector3<T> & value ) const;
    CVector4<T> operator / ( const CVector2<T> & value ) const;
    CVector4<T> operator / ( T value ) const;

    // 4D vector division.
    void operator /= ( const CVector4<T> & value );
    void operator /= ( const CVector3<T> & value );
    void operator /= ( const CVector2<T> & value );
    void operator /= ( T value );

    // 4D vector modulus.
    void operator %= ( T value );

    // Functions to determine whether or not the vector is empty.
    bool IsEmpty() const;
    bool IsEmptyX() const;
    bool IsEmptyY() const;
    bool IsEmptyZ() const;
    bool IsEmptyW() const;

    // Whether or not each dimension has a value.
    bool IsFilled() const;

public:

    union
    {
        struct { T x, y, z, w; };
        struct { T top, bottom, left, right; };
        struct { T r, g, b, a; };
    };

};


#endif  // __vector_4_h__


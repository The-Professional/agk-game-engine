#ifndef __vector_3_h__
#define __vector_3_h__

// Forward declarations
template <class T>
class CVector2;

/// *************************************************************************
/// <summary> 
/// Class to hold three dimensions of values.
/// </summary>
/// *************************************************************************
template <class T>
class CVector3
{
public:

    // Constructor
    CVector3( T value = 0 );
    CVector3( T _x, T _y, T _z = 0 );
    CVector3( const CVector2<T> & value );

    // 3D vector assignment.
    void operator = ( T value );
    void operator = ( const CVector2<T> & vec );

    // 3D vector addition.
    CVector3<T> operator + ( const CVector3<T> & vec ) const;
    CVector3<T> operator + ( const CVector2<T> & vec ) const;
    CVector3<T> operator + ( T value ) const;

    // 3D vector addition.
    void operator += ( const CVector3<T> & vec );
    void operator += ( const CVector2<T> & vec );
    void operator += ( T value );

    // 3D vector subtraction.
    CVector3<T> operator - ( const CVector3<T> & vec ) const;
    CVector3<T> operator - ( const CVector2<T> & vec ) const;
    CVector3<T> operator - ( T value ) const;

    // 3D vector subtraction.
    void operator -= ( const CVector3<T> & vec );
    void operator -= ( const CVector2<T> & vec );
    void operator -= ( T value );

    // 3D vector multiplation.
    CVector3<T> operator * ( const CVector3<T> & vec ) const;
    CVector3<T> operator * ( const CVector2<T> & vec ) const;
    CVector3<T> operator * ( T value ) const;

    // 3D vector multiplation.
    void operator *= ( const CVector3<T> & vec );
    void operator *= ( const CVector2<T> & vec );
    void operator *= ( T value );

    // 3D vector division.
    CVector3<T> operator / ( const CVector3<T> & vec ) const;
    CVector3<T> operator / ( const CVector2<T> & vec ) const;
    CVector3<T> operator / ( T value ) const;

    // 3D vector division.
    void operator /= ( const CVector3<T> & vec );
    void operator /= ( const CVector2<T> & vec );
    void operator /= ( T value );

    // 3D vector modulus.
    void operator %= ( T value );

    // Functions to determine whether or not the vector is empty.
    bool IsEmpty() const;
    bool IsEmptyX() const;
    bool IsEmptyY() const;
    bool IsEmptyZ() const;

    // Whether or not each dimension has a value.
    bool IsFilled() const;

public:

    union
    {
        struct { T x, y, z; };
        struct { T w, h, d; };
    };

};

#endif  // __vector_3_h__

#ifndef __vector_2_h__
#define __vector_2_h__

// Forward declarations
template <class T>
class CVector3;

/// *************************************************************************
/// <summary> 
/// Class to hold two dimensions of values.
/// </summary>
/// *************************************************************************
template <class T>
class CVector2
{
public:

    CVector2( T value = 0 );
    CVector2( T _x, T _y );
    CVector2( const CVector3<T> & value );

    // 2D vector assignment.
    void operator = ( T value );
    void operator = ( const CVector3<T> & value );

    // 2D vector addition.
    CVector2<T> operator + ( const CVector3<T> & value ) const;
    CVector2<T> operator + ( const CVector2<T> & value ) const;
    CVector2<T> operator + ( T value ) const;

    // 2D vector addition.
    void operator += ( const CVector3<T> & value );
    void operator += ( const CVector2<T> & value );
    void operator += ( T value );

    // 2D vector subtraction.
    CVector2<T> operator - ( const CVector3<T> & value ) const;
    CVector2<T> operator - ( const CVector2<T> & value ) const;
    CVector2<T> operator - ( T value ) const;

    // 2D vector subtraction.
    void operator -= ( const CVector3<T> & value );
    void operator -= ( const CVector2<T> & value );
    void operator -= ( T value );

    // 2D vector multiplation.
    CVector2<T> operator * ( const CVector3<T> & value ) const;
    CVector2<T> operator * ( const CVector2<T> & value ) const;
    CVector2<T> operator * ( T value ) const;

    // 2D vector multiplation.
    void operator *= ( const CVector3<T> & value );
    void operator *= ( const CVector2<T> & value );
    void operator *= ( T value );

    // 2D vector division.
    CVector2<T> operator / ( const CVector3<T> & value ) const;
    CVector2<T> operator / ( const CVector2<T> & value ) const;
    CVector2<T> operator / ( T value ) const;

    // 2D vector division.
    void operator /= ( const CVector3<T> & vec );
    void operator /= ( const CVector2<T> & vec );
    void operator /= ( T value );

    // Functions to determine whether or not the vector is empty.
    bool IsEmpty() const;
    bool IsEmptyX() const;
    bool IsEmptyY() const;

    // Whether or not each dimension has a value.
    bool IsFilled() const;

public:

    union
    {
        struct { T x, y; };
        struct { T w, h; };
    };

};


#endif  // __vector_2_h__

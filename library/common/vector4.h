#ifndef __vector4_h__
#define __vector4_h__

// Forward declarations
class CVector2;
class CVector3;

/// *************************************************************************
/// <summary> 
/// Class to hold four dimensions of values.
/// </summary>
/// *************************************************************************
class CVector4
{
public:

    CVector4( float value = 0 );
    CVector4( float _x, float _y, float _z, float _w = 0 );
    CVector4( const CVector3 & value );
    CVector4( const CVector2 & value );

    // 4D vector assignment.
    void operator = ( const CVector3 & value );
    void operator = ( const CVector2 & value );
    void operator = ( float value );

    // 4D vector addition.
    CVector4 operator + ( const CVector4 & value ) const;
    CVector4 operator + ( const CVector3 & value ) const;
    CVector4 operator + ( const CVector2 & value ) const;
    CVector4 operator + ( float value ) const;

    // 4D vector addition.
    void operator += ( const CVector4 & value );
    void operator += ( const CVector3 & value );
    void operator += ( const CVector2 & value );
    void operator += ( float value );

    // 4D vector subtraction.
    CVector4 operator - ( const CVector4 & value ) const;
    CVector4 operator - ( const CVector3 & value ) const;
    CVector4 operator - ( const CVector2 & value ) const;
    CVector4 operator - ( float value ) const;

    // 4D vector subtraction.
    void operator -= ( const CVector4 & value );
    void operator -= ( const CVector3 & value );
    void operator -= ( const CVector2 & value );
    void operator -= ( float value );

    // 4D vector multiplication.
    CVector4 operator * ( const CVector4 & value ) const;
    CVector4 operator * ( const CVector3 & value ) const;
    CVector4 operator * ( const CVector2 & value ) const;
    CVector4 operator * ( float value ) const;

    // 4D vector multiplication.
    void operator *= ( const CVector4 & value );
    void operator *= ( const CVector3 & value );
    void operator *= ( const CVector2 & value );
    void operator *= ( float value );

    // 4D vector division.
    CVector4 operator / ( const CVector4 & value ) const;
    CVector4 operator / ( const CVector3 & value ) const;
    CVector4 operator / ( const CVector2 & value ) const;
    CVector4 operator / ( float value ) const;

    // 4D vector division.
    void operator /= ( const CVector4 & value );
    void operator /= ( const CVector3 & value );
    void operator /= ( const CVector2 & value );
    void operator /= ( float value );

    // 4D vector modulus.
    void operator %= ( float value );

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
        struct { float x, y, z, w; };
        struct { float top, bottom, left, right; };
        struct { float r, g, b, a; };
    };

};


#endif  // __vector4_h__


#ifndef __vector2_h__
#define __vector2_h__

// Forward declarations
class CVector3;

/// *************************************************************************
/// <summary> 
/// Class to hold two dimensions of values.
/// </summary>
/// *************************************************************************
class CVector2
{
public:

    CVector2( float value = 0 );
    CVector2( float _x, float _y );
    CVector2( const CVector3 & value );

    // 2D vector assignment.
    void operator = ( float value );
    void operator = ( const CVector3 & value );

    // 2D vector addition.
    CVector2 operator + ( const CVector3 & value ) const;
    CVector2 operator + ( const CVector2 & value ) const;
    CVector2 operator + ( float value ) const;

    // 2D vector addition.
    void operator += ( const CVector3 & value );
    void operator += ( const CVector2 & value );
    void operator += ( float value );

    // 2D vector subtraction.
    CVector2 operator - ( const CVector3 & value ) const;
    CVector2 operator - ( const CVector2 & value ) const;
    CVector2 operator - ( float value ) const;

    // 2D vector subtraction.
    void operator -= ( const CVector3 & value );
    void operator -= ( const CVector2 & value );
    void operator -= ( float value );

    // 2D vector multiplation.
    CVector2 operator * ( const CVector3 & value ) const;
    CVector2 operator * ( const CVector2 & value ) const;
    CVector2 operator * ( float value ) const;

    // 2D vector multiplation.
    void operator *= ( const CVector3 & value );
    void operator *= ( const CVector2 & value );
    void operator *= ( float value );

    // 2D vector division.
    CVector2 operator / ( const CVector3 & value ) const;
    CVector2 operator / ( const CVector2 & value ) const;
    CVector2 operator / ( float value ) const;

    // 2D vector division.
    void operator /= ( const CVector3 & vec );
    void operator /= ( const CVector2 & vec );
    void operator /= ( float value );

    // Functions to determine whether or not the vector is empty.
    bool IsEmpty() const;
    bool IsEmptyX() const;
    bool IsEmptyY() const;

    // Whether or not each dimension has a value.
    bool IsFilled() const;

public:

    union
    {
        struct { float x, y; };
        struct { float w, h; };
    };

};


#endif  // __vector2_h__

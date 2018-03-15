#ifndef __vector3_h__
#define __vector3_h__

// Forward declarations
class CVector2;

/// *************************************************************************
/// <summary> 
/// Class to hold three dimensions of values.
/// </summary>
/// *************************************************************************
class CVector3
{
public:

    // Constructor
    CVector3( float value = 0 );
    CVector3( float _x, float _y, float _z = 0 );
    CVector3( const CVector2 & value );

    // 3D vector assignment.
    void operator = ( float value );
    void operator = ( const CVector2 & vec );

    // 3D vector addition.
    CVector3 operator + ( const CVector3 & vec ) const;
    CVector3 operator + ( const CVector2 & vec ) const;
    CVector3 operator + ( float value ) const;

    // 3D vector addition.
    void operator += ( const CVector3 & vec );
    void operator += ( const CVector2 & vec );
    void operator += ( float value );

    // 3D vector subtraction.
    CVector3 operator - ( const CVector3 & vec ) const;
    CVector3 operator - ( const CVector2 & vec ) const;
    CVector3 operator - ( float value ) const;

    // 3D vector subtraction.
    void operator -= ( const CVector3 & vec );
    void operator -= ( const CVector2 & vec );
    void operator -= ( float value );

    // 3D vector multiplation.
    CVector3 operator * ( const CVector3 & vec ) const;
    CVector3 operator * ( const CVector2 & vec ) const;
    CVector3 operator * ( float value ) const;

    // 3D vector multiplation.
    void operator *= ( const CVector3 & vec );
    void operator *= ( const CVector2 & vec );
    void operator *= ( float value );

    // 3D vector division.
    CVector3 operator / ( const CVector3 & vec ) const;
    CVector3 operator / ( const CVector2 & vec ) const;
    CVector3 operator / ( float value ) const;

    // 3D vector division.
    void operator /= ( const CVector3 & vec );
    void operator /= ( const CVector2 & vec );
    void operator /= ( float value );

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
        struct { float x, y, z; };
        struct { float w, h, d; };
    };

};


#endif  // __vector3_h__

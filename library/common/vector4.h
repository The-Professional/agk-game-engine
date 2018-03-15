#ifndef __vector4_h__
#define __vector4_h__

// Forward declarations
class CVector2;

/// *************************************************************************
/// <summary> 
/// Class to hold three dimensions of values.
/// </summary>
/// *************************************************************************
class CVector4
{
public:

    // Constructor
    CVector4( float value = 0 );
    CVector4( float _x, float _y, float _z, float _w = 0 );

    // 3D vector assignment.
    void operator = ( float value );
    void operator = ( const CVector2 & vec );

    // 3D vector addition.
    CVector4 operator + ( const CVector4 & vec ) const;

    // 3D vector addition.
    void operator += ( const CVector4 & vec );

    // 3D vector subtraction.
    CVector4 operator - ( const CVector4 & vec ) const;

    // 3D vector subtraction.
    void operator -= ( const CVector4 & vec );

public:

    union
    {
        struct { float x, y, z, w; };
        struct { float top, bottom, right, left; };
        struct { float r, g, b, a; };
    };

};


#endif  // __vector4_h__


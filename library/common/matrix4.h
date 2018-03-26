#ifndef __matrix_4_h__
#define __matrix_4_h__

// Game lib dependencies
#include <common\defs.h>

// Forward declarations
template <class T>
class CVector2;
template <class T>
class CVector3;
template <class T>
class CVector4;

/// *************************************************************************
/// <summary> 
/// Class to hold a 4x4 matrix.
/// </summary>
/// *************************************************************************
class CMatrix4
{
public:

    CMatrix4();
    CMatrix4( const CMatrix4 & n );
    CMatrix4( float _m[16] );
    CMatrix4( const CVector3<float> & translation, const CVector3<float> & rotation, const CVector3<float> & scale );
    CMatrix4( float _m11, float _m12, float _m13, float _m14,
              float _m21, float _m22, float _m23, float _m24, 
              float _m31, float _m32, float _m33, float _m34, 
              float _m41, float _m42, float _m43, float _m44 );

    // 4x4 matrix multiplication.
    CMatrix4 operator * ( const CMatrix4 & n ) const;
    CVector3<float> operator * ( const CVector3<float> & v ) const;
    CVector4<float> operator * ( const CVector4<float> & v ) const;
    void operator *= ( const CMatrix4 & n );

    // Get inverted 4x4 matrix.
    CMatrix4 operator ! () const;

    // Overloaded bracket operator.
    float & operator [] ( uint i );

    // Reset the matrix to an identity matrix.
    void Clear();

    // Set the translation portion of the matrix.
    void SetTranslation( const CVector3<float> & value );
    void SetTranslation( const CVector2<float> & value );

    // Set the rotation portion of the matrix.
    void SetRotation( const CVector3<float> & value );
    void SetRotation( float value );

    // Set the scale portion of the matrix.
    void SetScale( const CVector3<float> & value );
    void SetScale( const CVector2<float> & value );
    void SetScale( float value );

    // Translate the matrix.
    void Translate( const CVector3<float> & value );
    void Translate( const CVector2<float> & value );

    // Rotate the matrix.
    void Rotate( const CVector3<float> & value );
    void Rotate( float value );

    // Scale the matrix.
    void Scale( const CVector3<float> & value );
    void Scale( const CVector2<float> & value );
    void Scale( float value );

private:

    // Set the x, y, or z rotation portion of the matrix.
    void SetRotationX( float value, int flags = 0 );
    void SetRotationY( float value, int flags = 0 );
    void SetRotationZ( float value );

public:

    union
    {
        struct { float m[16]; };
        struct
        {
            float m11, m12, m13, m14,
                  m21, m22, m23, m24,
                  m31, m32, m33, m34,
                  m41, m42, m43, m44;
        };
    };

};


#endif  // __matrix_4_h__


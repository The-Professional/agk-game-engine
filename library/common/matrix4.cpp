// Physical component dependency
#include "matrix4.h"

// Game lib dependencies
#include <common\bitmask.h>
#include <common\vector2.h>
#include <common\vector3.h>
#include <common\vector4.h>
#include <utilities\exceptionhandling.h>

// Standard lib dependencies
#include <cstring>

// Boost lib dependencies
#include <boost\format.hpp>

using namespace NDefs;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CMatrix4::CMatrix4() :
    m11( 1 ), m12( 0 ), m13( 0 ), m14( 0 ),
    m21( 0 ), m22( 1 ), m23( 0 ), m24( 0 ),
    m31( 0 ), m32( 0 ), m33( 1 ), m34( 0 ),
    m41( 0 ), m42( 0 ), m43( 0 ), m44( 1 )
{
}

/// <summary> 
/// Constructor
/// </summary>
CMatrix4::CMatrix4( float _m[16] )
{
    memcpy( m, _m, 16 * sizeof( float ) );
}

/// <summary> 
/// Constructor
/// </summary>
CMatrix4::CMatrix4( const CMatrix4 & n )
{
    memcpy( m, n.m, 16 * sizeof( float ) );
}

/// <summary> 
/// Constructor
/// </summary>
CMatrix4::CMatrix4( const CVector3 & translation, const CVector3 & rotation, const CVector3 & scale )
{
    SetRotation( rotation );
    SetTranslation( translation );
    SetScale( scale );
}

/// <summary> 
/// Constructor
/// </summary>
CMatrix4::CMatrix4( float _m11, float _m12, float _m13, float _m14,
                    float _m21, float _m22, float _m23, float _m24,
                    float _m31, float _m32, float _m33, float _m34,
                    float _m41, float _m42, float _m43, float _m44 )
{
    m11 = _m11; m12 = _m12; m13 = _m13; m13 = _m14;
    m21 = _m21; m22 = _m22; m23 = _m23; m24 = _m24;
    m31 = _m31; m32 = _m32; m33 = _m33; m34 = _m34;
    m41 = _m41; m42 = _m42; m43 = _m43; m44 = _m44;
}


/// *************************************************************************
/// <summary> 
/// 4x4 matrix multiplication.
/// </summary>
/// *************************************************************************
CMatrix4 CMatrix4::operator * ( const CMatrix4 & n ) const
{
    return CMatrix4( m11 * n.m11 + m12 * n.m21 + m13 * n.m31 + m14 * n.m41,
                     m11 * n.m12 + m12 * n.m22 + m13 * n.m32 + m14 * n.m42,
                     m11 * n.m13 + m12 * n.m23 + m13 * n.m33 + m14 * n.m43,
                     m11 * n.m14 + m12 * n.m24 + m13 * n.m34 + m14 * n.m44,
                     m21 * n.m11 + m22 * n.m21 + m23 * n.m31 + m24 * n.m41,
                     m21 * n.m12 + m22 * n.m22 + m23 * n.m32 + m24 * n.m42,
                     m21 * n.m13 + m22 * n.m23 + m23 * n.m33 + m24 * n.m43,
                     m21 * n.m14 + m22 * n.m24 + m23 * n.m34 + m24 * n.m44,
                     m31 * n.m11 + m32 * n.m21 + m33 * n.m31 + m34 * n.m41,
                     m31 * n.m12 + m32 * n.m22 + m33 * n.m32 + m34 * n.m42,
                     m31 * n.m13 + m32 * n.m23 + m33 * n.m33 + m34 * n.m43,
                     m31 * n.m14 + m32 * n.m24 + m33 * n.m34 + m34 * n.m44,
                     0, 0, 0, 1 );
}

/// <summary> 
/// 4x4 matrix multiplication.
/// </summary>
CVector3 CMatrix4::operator * ( const CVector3 & v ) const
{
    return CVector3( m11 * v.x + m12 * v.y + m13 * v.z + m14,
                     m21 * v.x + m22 * v.y + m23 * v.z + m24,
                     m31 * v.x + m32 * v.y + m33 * v.z + m34 );
}

/// <summary> 
/// 4x4 matrix multiplication.
/// </summary>
CVector4 CMatrix4::operator * ( const CVector4 & v ) const
{
    return CVector4( m11 * v.x + m12 * v.y + m13 * v.z + m14 * v.w,
                     m21 * v.x + m22 * v.y + m23 * v.z + m24 * v.w,
                     m31 * v.x + m32 * v.y + m33 * v.z + m34 * v.w,
                     m41 * v.x + m42 * v.y + m43 * v.z + m44 * v.w );
}


/// *************************************************************************
/// <summary> 
/// 4x4 matrix multiplication.
/// </summary>
/// *************************************************************************
void CMatrix4::operator *= ( const CMatrix4 & n )
{
    memcpy( m, (n * *this).m, 16 * sizeof( float ) );
}


/// *************************************************************************
/// <summary> 
/// Get inverted 4x4 matrix.
/// </summary>
/// *************************************************************************
CMatrix4 CMatrix4::operator ! () const
{
CMatrix4 r(  m22 * m33 * m44 - m22 * m34 * m43 - m32 * m23 * m44 + m32 * m24 * m43 + m42 * m23 * m34 - m42 * m24 * m33,
            -m12 * m33 * m44 + m12 * m34 * m43 + m32 * m13 * m44 - m32 * m14 * m43 - m42 * m13 * m34 + m42 * m14 * m33,
             m12 * m23 * m44 - m12 * m24 * m43 - m22 * m13 * m44 + m22 * m14 * m43 + m42 * m13 * m24 - m42 * m14 * m23,
            -m12 * m23 * m34 + m12 * m24 * m33 + m22 * m13 * m34 - m22 * m14 * m33 - m32 * m13 * m24 + m32 * m14 * m23,
            -m21 * m33 * m44 + m21 * m34 * m43 + m31 * m23 * m44 - m31 * m24 * m43 - m41 * m23 * m34 + m41 * m24 * m33, 
             m11 * m33 * m44 - m11 * m34 * m43 - m31 * m13 * m44 + m31 * m14 * m43 + m41 * m13 * m34 - m41 * m14 * m33,
            -m11 * m23 * m44 + m11 * m24 * m43 + m21 * m13 * m44 - m21 * m14 * m43 - m41 * m13 * m24 + m41 * m14 * m23,
             m11 * m23 * m34 - m11 * m24 * m33 - m21 * m13 * m34 + m21 * m14 * m33 + m31 * m13 * m24 - m31 * m14 * m23,
             m21 * m32 * m44 - m21 * m34 * m42 - m31 * m22 * m44 + m31 * m24 * m42 + m41 * m22 * m34 - m41 * m24 * m32,
            -m11 * m32 * m44 + m11 * m34 * m42 + m31 * m12 * m44 - m31 * m14 * m42 - m41 * m12 * m34 + m41 * m14 * m32,
             m11 * m22 * m44 - m11 * m24 * m42 - m21 * m12 * m44 + m21 * m14 * m42 + m41 * m12 * m24 - m41 * m14 * m22,
            -m11 * m22 * m34 + m11 * m24 * m32 + m21 * m12 * m34 - m21 * m14 * m32 - m31 * m12 * m24 + m31 * m14 * m22,
            -m21 * m32 * m43 + m21 * m33 * m42 + m31 * m22 * m43 - m31 * m23 * m42 - m41 * m22 * m33 + m41 * m23 * m32,
             m11 * m32 * m43 - m11 * m33 * m42 - m31 * m12 * m43 + m31 * m13 * m42 + m41 * m12 * m33 - m41 * m13 * m32,
            -m11 * m22 * m43 + m11 * m23 * m42 + m21 * m12 * m43 - m21 * m13 * m42 - m41 * m12 * m23 + m41 * m13 * m22,
             m11 * m22 * m33 - m11 * m23 * m32 - m21 * m12 * m33 + m21 * m13 * m32 + m31 * m12 * m23 - m31 * m13 * m22 );

    float det = m11 * r.m11 + m12 * r.m21 + m13 * r.m31 + m14 * r.m41;

    if( abs(det) < defs_EPSILON )
        throw NExcept::CCriticalException( "CMatrix4::operator ! Error!",
                boost::str( boost::format( "There was an error inverting the matrix.\n\n%s\nLine: %s" )
                                           % __FUNCTION__ % __LINE__ ) );

    det = 1.f / det;

    for( int i = 0; i < 16; i++ )
        r[i] *= det;

    return r;
}


/// *************************************************************************
/// <summary> 
/// Overloaded bracket operator.
/// </summary>
/// *************************************************************************
float & CMatrix4::operator [] ( uint i )
{
    return m[i];
}


/// *************************************************************************
/// <summary> 
/// Reset the matrix to an identity matrix.
/// </summary>
/// *************************************************************************
void CMatrix4::Clear()
{
    m11 = 1, m12 = 0, m13 = 0, m14 = 0;
    m21 = 0, m22 = 1, m23 = 0, m24 = 0;
    m31 = 0, m32 = 0, m33 = 1, m34 = 0;
    m41 = 0, m42 = 0, m43 = 0, m44 = 1;
}


/// *************************************************************************
/// <summary> 
/// Set the translation portion of the matrix.
/// </summary>
/// *************************************************************************
void CMatrix4::SetTranslation( const CVector3 & value )
{
    m14 = value.x;
    m24 = value.y;
    m34 = value.z;
}

/// <summary> 
/// Set the translation portion of the matrix.
/// </summary>
void CMatrix4::SetTranslation( const CVector2 & value )
{
    m14 = value.x;
    m24 = value.y;
    m34 = 0;
}


/// *************************************************************************
/// <summary> 
/// Set the rotation portion of the matrix.
/// </summary>
/// *************************************************************************
void CMatrix4::SetRotation( const CVector3 & value )
{
    CBitmask<uint> flags = EFD_NULL;

    // Apply Z rotation
    if( !value.IsEmptyZ() )
    {
        SetRotationZ( value.z );
        flags.Add( EFD_Z );
    }

    // Apply Y rotation
    if( !value.IsEmptyY() )
    {
        SetRotationY( value.y, flags );
        flags.Add( EFD_Y );
    }

    // Apply X rotation
    if( !value.IsEmptyZ() )
        SetRotationX( value.x, flags );
}

/// <summary> 
/// Set the rotation portion of the matrix.
/// </summary>
void CMatrix4::SetRotation( float value )
{
    SetRotationZ( value );
}


/// *************************************************************************
/// <summary> 
/// Set the x rotation portion of the matrix.
/// </summary>
/// *************************************************************************
void CMatrix4::SetRotationX( float value, int flags )
{
    value *= defs_DEG_TO_RAD;
    float cosX = cos( value );
    float sinX = sin( value );

    switch( flags )
    {
    case EFD_Z:
        {
            float tmp4 = m21 * cosX;
            float tmp5 = m22 * cosX;
            float tmp8 = m21 * sinX;
            float tmp9 = m22 * sinX;
            m21 = tmp4;
            m22 = tmp5;
            m23 = -sinX;
            m31 = tmp8;
            m32 = tmp9;
            m33 = cosX;
            break;
        }
    case EFD_Y:
        {
            float tmp4 = m31 * -sinX;
            float tmp6 = m33 * -sinX;
            float tmp8 = m31 * cosX;
            float tmp10 = m33 * cosX;
            m21 = tmp4;
            m22 = cosX;
            m23 = tmp6;
            m31 = tmp8;
            m32 = sinX;
            m33 = tmp10;
            break;
        }
    case EFD_Z | EFD_Y:
        {
            float tmp4 = (m21 * cosX) + (m31 * -sinX);
            float tmp5 = (m22 * cosX) + (m32 * -sinX);
            float tmp6 = m33 * -sinX;
            float tmp8 = (m21 * sinX) + (m31 * cosX);
            float tmp9 = (m22 * sinX) + (m32 * cosX);
            float tmp10 = m33 * cosX;
            m21 = tmp4;
            m22 = tmp5;
            m23 = tmp6;
            m31 = tmp8;
            m32 = tmp9;
            m33 = tmp10;
            break;
        }
    default:
        {
            m22 = cosX;
            m23 = -sinX;
            m32 = sinX;
            m33 = cosX;
            break;
        }
    }
}


/// *************************************************************************
/// <summary> 
/// Set the y rotation portion of the matrix.
/// </summary>
/// *************************************************************************
void CMatrix4::SetRotationY( float value, int flags )
{
    value *= defs_DEG_TO_RAD;
    float cosY = cos( value );
    float sinY = sin( value );

    switch( flags )
    {
    case EFD_Z:
        {
            float tmp0 = m11 * cosY;
            float tmp1 = m12 * cosY;
            float tmp8 = m11 * -sinY;
            float tmp9 = m12 * -sinY;
            m11 = tmp0;
            m12 = tmp1;
            m13 = sinY;
            m31 = tmp8;
            m32 = tmp9;
            m33 = cosY;
            break;
        }
    default:
        {
            m11 = cosY;
            m13 = sinY;
            m31 = -sinY;
            m33 = cosY;
            break;
        }
    }
}


/// *************************************************************************
/// <summary> 
/// Set the z rotation portion of the matrix.
/// </summary>
/// *************************************************************************
void CMatrix4::SetRotationZ( float value )
{
    value *= defs_DEG_TO_RAD;
    float cosZ = cos( value );
    float sinZ = sin( value );

    m11 = cosZ;
    m12 = -sinZ;
    m21 = sinZ;
    m22 = cosZ;
}


/// *************************************************************************
/// <summary> 
/// Set the scale portion of the matrix.
/// </summary>
/// *************************************************************************
void CMatrix4::SetScale( const CVector3 & value )
{
    m11 = value.x;
    m22 = value.y;
    m33 = value.z;
}

/// <summary> 
/// Set the scale portion of the matrix.
/// </summary>
void CMatrix4::SetScale( const CVector2 & value )
{
    m11 = value.x;
    m22 = value.y;
    m33 = 1;
}

/// <summary> 
/// Set the scale portion of the matrix.
/// </summary>
void CMatrix4::SetScale( float value )
{
    m11 = value;
    m22 = value;
    m33 = value;
}


/// *************************************************************************
/// <summary> 
/// Translate the matrix.
/// </summary>
/// *************************************************************************
void CMatrix4::Translate( const CVector3 & value )
{
    m14 += value.x;
    m24 += value.y;
    m34 += value.z;
}

/// <summary> 
/// Translate the matrix.
/// </summary>
void CMatrix4::Translate( const CVector2 & value )
{
    m14 += value.x;
    m24 += value.y;
}


/// *************************************************************************
/// <summary> 
/// Rotate the matrix.
/// </summary>
/// *************************************************************************
void CMatrix4::Rotate( const CVector3 & value )
{
    CMatrix4 matrix;
    matrix.SetRotation( value );
    *this *= matrix;
}

/// <summary> 
/// Rotate the matrix.
/// </summary>
void CMatrix4::Rotate( float value )
{
    CMatrix4 matrix;
    matrix.SetRotation( value );
    *this *= matrix;
}


/// *************************************************************************
/// <summary> 
/// Scale the matrix.
/// </summary>
/// *************************************************************************
void CMatrix4::Scale( const CVector3 & value )
{
    m14 *= value.x;
    m24 *= value.y;
    m34 *= value.z;
}

/// <summary> 
/// Scale the matrix.
/// </summary>
void CMatrix4::Scale( const CVector2 & value )
{
    m14 *= value.x;
    m24 *= value.y;
}

/// <summary> 
/// Scale the matrix.
/// </summary>
void CMatrix4::Scale( float value )
{
    m14 *= value;
    m24 *= value;
    m34 *= value;
}
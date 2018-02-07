// Physical dependency
#include "iobject.h"


/// *************************************************************************
/// <summary>
/// Return the id set by AGK. 
/// </summary>
/// *************************************************************************
uint iObject::GetID() const
{
    return _id;
}


/// *************************************************************************
/// <summary>
/// Return the id set by AGK. 
/// </summary>
/// *************************************************************************
void iObject::Clear()
{
    DeleteObject();

    _position = 0;
    _rotation = 0;
    _size = 0;
    _color = 255;
}


/// *************************************************************************
/// <summary>
/// Set the object's position. 
/// </summary>
/// *************************************************************************
void iObject::SetPos( float x, float y )
{
    _position.x = x;
    _position.y = y;

    UpdatePosAGK();
}

// Set the object's position. 
void iObject::SetPos( float x, float y, float z )
{
    _position.x = x;
    _position.y = y;
    _position.z = z;

    UpdatePosAGK();
}

// Set the object's position. 
void iObject::SetPos( const CVector2 & pos )
{
    _position = pos;

    UpdatePosAGK();
}

// Set the object's position. 
void iObject::SetPos( const CVector3 & pos )
{
    _position = pos;

    UpdatePosAGK();
}

// Set the object's x position. 
void iObject::SetPosX( float x )
{
    _position.x = x;

    UpdatePosAGK();
}

// Set the object's y position. 
void iObject::SetPosY( float y )
{
    _position.y = y;

    UpdatePosAGK();
}

// Set the object's z position. 
void iObject::SetPosZ( float z )
{
    _position.z = z;

    UpdatePosAGK();
}


/// *************************************************************************
/// <summary>
/// Increment the object's position. 
/// </summary>
/// *************************************************************************
void iObject::IncPos( float x, float y )
{
    _position.x += x;
    _position.y += y;

    UpdatePosAGK();
}

// Increment the object's position. 
void iObject::IncPos( float x, float y, float z )
{
    _position.x += x;
    _position.y += y;
    _position.z += z;

    UpdatePosAGK();
}

// Increment the object's position. 
void iObject::IncPos( const CVector2 & pos )
{
    _position += pos;

    UpdatePosAGK();
}

// Increment the object's position. 
void iObject::IncPos( const CVector3 & pos )
{
    _position += pos;

    UpdatePosAGK();
}


/// *************************************************************************
/// <summary>
/// Get the object's position. 
/// </summary>
/// *************************************************************************
const CVector3 & iObject::GetPos() const
{
    return _position;
}


/// *************************************************************************
/// <summary>
/// Set the object's rotation. 
/// </summary>
/// *************************************************************************
void iObject::SetRot( float x, float y, float z )
{
    _rotation.x = x;
    _rotation.y = y;
    _rotation.z = z;

    UpdateRotAGK();
}

// Set the object's rotation. 
void iObject::SetRot( const CVector3 & rot )
{
    _rotation = rot;

    UpdateRotAGK();
}

// Set the object's x rotation. 
void iObject::SetRotX( float x )
{
    _rotation.x = x;

    UpdateRotAGK();
}

// Set the object's x rotation. 
void iObject::SetRotY( float y )
{
    _rotation.y = y;

    UpdateRotAGK();
}

// Set the object's z rotation. 
void iObject::SetRotZ( float z )
{
    _rotation.z = z;

    UpdateRotAGK();
}


/// *************************************************************************
/// <summary>
/// Increment the object's rotation. 
/// </summary>
/// *************************************************************************
void iObject::IncRot( float x, float y, float z )
{
    _rotation.x += x;
    _rotation.y += y;
    _rotation.z += z;

    UpdateRotAGK();
}

// Increment the object's rotation. 
void iObject::IncRot( const CVector3 & rot )
{
    _rotation += rot;

    UpdateRotAGK();
}

// Increment the object's z rotation. 
void iObject::IncRot( float z )
{
    _rotation.z += z;

    UpdateRotAGK();
}


/// *************************************************************************
/// <summary>
/// Get the object's rotation. 
/// </summary>
/// *************************************************************************
const CVector3 & iObject::GetRot() const
{
    return _rotation;
}


/// *************************************************************************
/// <summary>
/// Set the object's size. 
/// </summary>
/// *************************************************************************
void iObject::SetSize( float w, float h, float d )
{
    _size.w = w;
    _size.h = h;
    _size.d = d;

    UpdateSizeAGK();
}

// Set the object's size. 
void iObject::SetSize( float w, float h )
{
    _size.w = w;
    _size.h = h;

    UpdateSizeAGK();
}

// Set the object's size. 
void iObject::SetSize( const CVector3 & size )
{
    _size = size;

    UpdateSizeAGK();
}

// Set the object's size. 
void iObject::SetSize( const CVector2 & size )
{
    _size = size;

    UpdateSizeAGK();
}

// Set the object's width. 
void iObject::SetSizeW( float w )
{
    _size.w = w;

    UpdateSizeAGK();
}

// Set the object's height. 
void iObject::SetSizeH( float h )
{
    _size.h = h;

    UpdateSizeAGK();
}

// Set the object's depth. 
void iObject::SetSizeD( float d )
{
    _size.d = d;

    UpdateSizeAGK();
}


/// *************************************************************************
/// <summary>
/// Increment the object's size. 
/// </summary>
/// *************************************************************************
void iObject::IncSize( float w, float h, float d )
{
    _size.w += w;
    _size.h += h;
    _size.d += d;

    UpdateSizeAGK();
}

// Increment the object's size.
void iObject::IncSize( float w, float h )
{
    _size.w += w;
    _size.h += h;

    UpdateSizeAGK();
}

// Increment the object's size.
void iObject::IncSize( const CVector3 & size )
{
    _size += size;

    UpdateSizeAGK();
}

// Increment the object's size.
void iObject::IncSize( const CVector2 & size )
{
    _size += size;

    UpdateSizeAGK();
}


/// *************************************************************************
/// <summary>
/// Get the object's size. 
/// </summary>
/// *************************************************************************
const CVector3 & iObject::GetSize() const
{
    return _size;
}



/// *************************************************************************
/// <summary>
/// Set the object's color. 
/// </summary>
/// *************************************************************************
void iObject::SetColor( int r, int g, int b, int a )
{
    _color.r = r;
    _color.g = g;
    _color.b = b;
    _color.a = a;

    UpdateColorAGK();
}

// Set the object's color. 
void iObject::SetColor( int r, int g, int b )
{
    _color.r = r;
    _color.g = g;
    _color.b = b;

    UpdateColorAGK();
}

// Set the object's color. 
void iObject::SetColor( const CColor & color )
{
    _color = color;

    UpdateColorAGK();
}

// Set the object's red value. 
void iObject::SetR( int r )
{
    _color.r = r;

    UpdateColorAGK();
}

// Set the object's green value. 
void iObject::SetG( int g )
{
    _color.g = g;

    UpdateColorAGK();
}

// Set the object's blue value. 
void iObject::SetB( int b )
{
    _color.b = b;

    UpdateColorAGK();
}

// Set the object's alpha value. 
void iObject::SetA( int a )
{
    _color.a = a;

    UpdateColorAGK();
}


/// *************************************************************************
/// <summary>
/// Increment the object's color.
/// </summary>
/// *************************************************************************
void iObject::IncColor( int r, int g, int b, int a )
{
    _color.r += r;
    _color.g += g;
    _color.b += b;
    _color.a += a;

    UpdateColorAGK();
}

// Increment the object's color.
void iObject::IncColor( int r, int g, int b )
{
    _color.r += r;
    _color.g += g;
    _color.b += b;

    UpdateColorAGK();
}

// Increment the object's color.
void iObject::IncColor( const CColor & color )
{
    _color += color;

    UpdateColorAGK();
}


/// *************************************************************************
/// <summary>
/// Get the object's color. 
/// </summary>
/// *************************************************************************
const CColor & iObject::GetColor() const
{
    return _color;
}
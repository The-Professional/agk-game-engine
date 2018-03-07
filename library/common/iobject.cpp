// Physical dependency
#include "iobject.h"

// Game lib dependencies
#include <script\animationcomponent.h>
#include <utilities\deletefuncs.h>

using namespace NDefs;

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
/// Get the type of object this is. 
/// </summary>
/// *************************************************************************
NDefs::EObjectType iObject::GetType() const
{
    return _type;
}


/// *************************************************************************
/// <summary>
/// Return the id set by AGK. 
/// </summary>
/// *************************************************************************
void iObject::Clear()
{
    DeleteObject();

    NDelFunc::Delete( _pAnimationComponent );

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

    UpdateAGKWithPos();
}

// Set the object's position. 
void iObject::SetPos( float x, float y, float z )
{
    _position.x = x;
    _position.y = y;
    _position.z = z;

    UpdateAGKWithPos();
}

// Set the object's position. 
void iObject::SetPos( const CVector2 & pos )
{
    _position = pos;

    UpdateAGKWithPos();
}

// Set the object's position. 
void iObject::SetPos( const CVector3 & pos )
{
    _position = pos;

    UpdateAGKWithPos();
}

// Set the object's x position. 
void iObject::SetPosX( float x )
{
    _position.x = x;

    UpdateAGKWithPos();
}

// Set the object's y position. 
void iObject::SetPosY( float y )
{
    _position.y = y;

    UpdateAGKWithPos();
}

// Set the object's z position. 
void iObject::SetPosZ( float z )
{
    _position.z = z;

    UpdateAGKWithPos();
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

    UpdateAGKWithPos();
}

// Increment the object's position. 
void iObject::IncPos( float x, float y, float z )
{
    _position.x += x;
    _position.y += y;
    _position.z += z;

    UpdateAGKWithPos();
}

// Increment the object's position. 
void iObject::IncPos( const CVector2 & pos )
{
    _position += pos;

    UpdateAGKWithPos();
}

// Increment the object's position. 
void iObject::IncPos( const CVector3 & pos )
{
    _position += pos;

    UpdateAGKWithPos();
}


/// *************************************************************************
/// <summary>
/// Get the object's position. 
/// </summary>
/// *************************************************************************
const CVector3 & iObject::GetPos()
{
    if( !_updatedValues.Contains( NDefs::ETT_POSITION ) )
    {
        _updatedValues.Add( NDefs::ETT_POSITION );
        UpdatePosFromAGK();
    }

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

    UpdateAGKWithRot();
}

// Set the object's rotation. 
void iObject::SetRot( const CVector3 & rot )
{
    _rotation = rot;

    UpdateAGKWithRot();
}

// Set the object's x rotation. 
void iObject::SetRotX( float x )
{
    _rotation.x = x;

    UpdateAGKWithRot();
}

// Set the object's x rotation. 
void iObject::SetRotY( float y )
{
    _rotation.y = y;

    UpdateAGKWithRot();
}

// Set the object's z rotation. 
void iObject::SetRotZ( float z )
{
    _rotation.z = z;

    UpdateAGKWithRot();
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

    UpdateAGKWithRot();
}

// Increment the object's rotation. 
void iObject::IncRot( const CVector3 & rot )
{
    _rotation += rot;

    UpdateAGKWithRot();
}

// Increment the object's z rotation. 
void iObject::IncRot( float z )
{
    _rotation.z += z;

    UpdateAGKWithRot();
}


/// *************************************************************************
/// <summary>
/// Get the object's rotation. 
/// </summary>
/// *************************************************************************
const CVector3 & iObject::GetRot()
{
    if( !_updatedValues.Contains( NDefs::ETT_ROTATION ) )
    {
        _updatedValues.Add( NDefs::ETT_ROTATION );
        UpdateRotFromAGK();
    }

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

    UpdateAGKWithSize();
}

// Set the object's size. 
void iObject::SetSize( float w, float h )
{
    _size.w = w;
    _size.h = h;

    UpdateAGKWithSize();
}

// Set the object's size. 
void iObject::SetSize( const CVector3 & size )
{
    _size = size;

    UpdateAGKWithSize();
}

// Set the object's size. 
void iObject::SetSize( const CVector2 & size )
{
    _size = size;

    UpdateAGKWithSize();
}

// Set the object's width. 
void iObject::SetSizeW( float w )
{
    _size.w = w;

    UpdateAGKWithSize();
}

// Set the object's height. 
void iObject::SetSizeH( float h )
{
    _size.h = h;

    UpdateAGKWithSize();
}

// Set the object's depth. 
void iObject::SetSizeD( float d )
{
    _size.d = d;

    UpdateAGKWithSize();
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

    UpdateAGKWithSize();
}

// Increment the object's size.
void iObject::IncSize( float w, float h )
{
    _size.w += w;
    _size.h += h;

    UpdateAGKWithSize();
}

// Increment the object's size.
void iObject::IncSize( const CVector3 & size )
{
    _size += size;

    UpdateAGKWithSize();
}

// Increment the object's size.
void iObject::IncSize( const CVector2 & size )
{
    _size += size;

    UpdateAGKWithSize();
}


/// *************************************************************************
/// <summary>
/// Get the object's size. 
/// </summary>
/// *************************************************************************
const CVector3 & iObject::GetSize()
{
    if( !_updatedValues.Contains( NDefs::ETT_SIZE ) )
    {
        _updatedValues.Add( NDefs::ETT_SIZE );
        UpdateSizeFromAGK();
    }

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

    UpdateAGKWithColor();
}

// Set the object's color. 
void iObject::SetColor( int r, int g, int b )
{
    _color.r = r;
    _color.g = g;
    _color.b = b;

    UpdateAGKWithColor();
}

// Set the object's color. 
void iObject::SetColor( const CColor & color )
{
    _color = color;

    UpdateAGKWithColor();
}

// Set the object's red value. 
void iObject::SetColorR( int r )
{
    _color.r = r;

    UpdateAGKWithColor();
}

// Set the object's green value. 
void iObject::SetColorG( int g )
{
    _color.g = g;

    UpdateAGKWithColor();
}

// Set the object's blue value. 
void iObject::SetColorB( int b )
{
    _color.b = b;

    UpdateAGKWithColor();
}

// Set the object's alpha value. 
void iObject::SetColorA( int a )
{
    _color.a = a;

    UpdateAGKWithColor();
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

    UpdateAGKWithColor();
}

// Increment the object's color.
void iObject::IncColor( int r, int g, int b )
{
    _color.r += r;
    _color.g += g;
    _color.b += b;

    UpdateAGKWithColor();
}

// Increment the object's color.
void iObject::IncColor( const CColor & color )
{
    _color += color;

    UpdateAGKWithColor();
}


/// *************************************************************************
/// <summary>
/// Get the object's color. 
/// </summary>
/// *************************************************************************
const CColor & iObject::GetColor()
{
    if( !_updatedValues.Contains( NDefs::ETT_COLOR ) )
    {
        _updatedValues.Add( NDefs::ETT_COLOR );
        UpdatePosFromAGK();
    }

    return _color;
}


/// *************************************************************************
/// <summary>
/// Play an animation. 
/// </summary>
/// <param name="name"> Name of the animation to play. </param>
/// <param name="stopType"> How to end any conflicting animations. </param>
/// *************************************************************************
void iObject::Play( const std::string & name, EStopType stopType )
{
    if( _pAnimationComponent )
        _pAnimationComponent->Play( name, stopType );
}


/// *************************************************************************
/// <summary>
/// Update the object. 
/// </summary>
/// *************************************************************************
void iObject::Update()
{
    if( _pAnimationComponent )
        _pAnimationComponent->Update();
}
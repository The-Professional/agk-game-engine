// Physical dependency
#include "iobject.h"

// Game lib dependencies
#include <common\collectionobject.h>
#include <common\matrix4.h>
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
    NDelFunc::Delete( _pMatrix );

    _position = 0;
    _rotation = 0;
    _size = 0;
    _color = 255;
}


/// *************************************************************************
/// <summary>
/// Set the object's fields using a collection object. 
/// </summary>
/// *************************************************************************
void iObject::Set( const CCollectionObject & collectionObject )
{
    if( collectionObject.fields.Contains( CCollectionObject::POSITION ) )
        SetPos( collectionObject.position );

    if( collectionObject.fields.Contains( CCollectionObject::ROTATION ) )
        SetRot( collectionObject.rotation );

    if( collectionObject.fields.Contains( CCollectionObject::SIZE ) )
        SetSize( collectionObject.size );

    if( collectionObject.fields.Contains( CCollectionObject::COLOR ) )
        SetColor( collectionObject.color );

    if( collectionObject.fields.Contains( CCollectionObject::VISIBLE ) )
        SetVisible( collectionObject.visible );

    if( collectionObject.fields.Contains( CCollectionObject::ALIGNMENT ) )
        SetAlignment( collectionObject.alignment );

    if( collectionObject.fields.Contains( CCollectionObject::TEXT_ALIGNMENT ) )
        SetTextAlignment( collectionObject.textAlignment );

    if( collectionObject.fields.Contains( CCollectionObject::TEXT_SIZE ) )
        SetTextSize( collectionObject.size.d );
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

    _modified.Add( ETT_POSITION );
}

// Set the object's position. 
void iObject::SetPos( float x, float y, float z )
{
    _position.x = x;
    _position.y = y;
    _position.z = z;

    _modified.Add( ETT_POSITION );
}

// Set the object's position. 
void iObject::SetPos( const CVector2 & pos )
{
    _position = pos;

    _modified.Add( ETT_POSITION );
}

// Set the object's position. 
void iObject::SetPos( const CVector3 & pos )
{
    _position = pos;

    _modified.Add( ETT_POSITION );
}

// Set the object's x position. 
void iObject::SetPosX( float x )
{
    _position.x = x;

    _modified.Add( ETT_POSITION );
}

// Set the object's y position. 
void iObject::SetPosY( float y )
{
    _position.y = y;

    _modified.Add( ETT_POSITION );
}

// Set the object's z position. 
void iObject::SetPosZ( float z )
{
    _position.z = z;

    _modified.Add( ETT_POSITION );
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

    _modified.Add( ETT_POSITION );
}

// Increment the object's position. 
void iObject::IncPos( float x, float y, float z )
{
    _position.x += x;
    _position.y += y;
    _position.z += z;

    _modified.Add( ETT_POSITION );
}

// Increment the object's position. 
void iObject::IncPos( const CVector2 & pos )
{
    _position += pos;

    _modified.Add( ETT_POSITION );
}

// Increment the object's position. 
void iObject::IncPos( const CVector3 & pos )
{
    _position += pos;

    _modified.Add( ETT_POSITION );
}


/// *************************************************************************
/// <summary>
/// Get the object's position. 
/// </summary>
/// *************************************************************************
const CVector3 & iObject::GetPos()
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

    _modified.Add( ETT_ROTATION );
}

// Set the object's rotation. 
void iObject::SetRot( const CVector3 & rot )
{
    _rotation = rot;

    _modified.Add( ETT_ROTATION );
}

// Set the object's x rotation. 
void iObject::SetRotX( float x )
{
    _rotation.x = x;

    _modified.Add( ETT_ROTATION );
}

// Set the object's x rotation. 
void iObject::SetRotY( float y )
{
    _rotation.y = y;

    _modified.Add( ETT_ROTATION );
}

// Set the object's z rotation. 
void iObject::SetRotZ( float z )
{
    _rotation.z = z;

    _modified.Add( ETT_ROTATION );
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

    _modified.Add( ETT_ROTATION );
}

// Increment the object's rotation. 
void iObject::IncRot( const CVector3 & rot )
{
    _rotation += rot;

    _modified.Add( ETT_ROTATION );
}

// Increment the object's z rotation. 
void iObject::IncRot( float z )
{
    _rotation.z += z;

    _modified.Add( ETT_ROTATION );
}


/// *************************************************************************
/// <summary>
/// Get the object's rotation. 
/// </summary>
/// *************************************************************************
const CVector3 & iObject::GetRot()
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

    _modified.Remove( ETT_SCALE );
    _modified.Add( ETT_SIZE );
}

// Set the object's size. 
void iObject::SetSize( float w, float h )
{
    _size.w = w;
    _size.h = h;

    _modified.Remove( ETT_SCALE );
    _modified.Add( ETT_SIZE );
}

// Set the object's size. 
void iObject::SetSize( const CVector3 & size )
{
    _size = size;

    _modified.Remove( ETT_SCALE );
    _modified.Add( ETT_SIZE );
}

// Set the object's size. 
void iObject::SetSize( const CVector2 & size )
{
    _size = size;

    _modified.Remove( ETT_SCALE );
    _modified.Add( ETT_SIZE );
}

// Set the object's width. 
void iObject::SetSizeW( float w, bool uniform )
{
    if( uniform )
    {
        float ratio = w / _size.w;
        _size.h *= ratio;
        _size.d *= ratio;
    }

    _size.w = w;

    _modified.Remove( ETT_SCALE );
    _modified.Add( ETT_SIZE );
}

// Set the object's height. 
void iObject::SetSizeH( float h, bool uniform )
{
    if( uniform )
    {
        float ratio = h / _size.h;
        _size.w *= ratio;
        _size.d *= ratio;
    }

    _size.h = h;

    _modified.Remove( ETT_SCALE );
    _modified.Add( ETT_SIZE );
}

// Set the object's depth. 
void iObject::SetSizeD( float d, bool uniform )
{
    if( uniform )
    {
        float ratio = d / _size.d;
        _size.w *= ratio;
        _size.h *= ratio;
    }

    _size.d = d;

    _modified.Remove( ETT_SCALE );
    _modified.Add( ETT_SIZE );
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

    _modified.Remove( ETT_SCALE );
    _modified.Add( ETT_SIZE );
}

// Increment the object's size.
void iObject::IncSize( float w, float h )
{
    _size.w += w;
    _size.h += h;

    _modified.Remove( ETT_SCALE );
    _modified.Add( ETT_SIZE );
}

// Increment the object's size.
void iObject::IncSize( const CVector3 & size )
{
    _size += size;

    _modified.Remove( ETT_SCALE );
    _modified.Add( ETT_SIZE );
}

// Increment the object's size.
void iObject::IncSize( const CVector2 & size )
{
    _size += size;

    _modified.Remove( ETT_SCALE );
    _modified.Add( ETT_SIZE );
}


/// *************************************************************************
/// <summary>
/// Get the object's size. 
/// </summary>
/// *************************************************************************
const CVector3 & iObject::GetSize()
{
    return _size;
}


/// *************************************************************************
/// <summary>
/// Set the object's scale. 
/// </summary>
/// *************************************************************************
void iObject::SetScale( float x, float y )
{
    _scale.x = x;
    _scale.y = y;

    _modified.Remove( ETT_SIZE );
    _modified.Add( ETT_SCALE );
}

// Set the object's scale. 
void iObject::SetScale( float x, float y, float z )
{
    _scale.x = x;
    _scale.y = y;
    _scale.z = z;

    _modified.Remove( ETT_SIZE );
    _modified.Add( ETT_SCALE );
}

// Set the object's scale. 
void iObject::SetScale( const CVector2 & scale )
{
    _position = scale;

    _modified.Remove( ETT_SIZE );
    _modified.Add( ETT_SCALE );
}

// Set the object's scale. 
void iObject::SetScale( const CVector3 & scale )
{
    _scale = scale;

    _modified.Remove( ETT_SIZE );
    _modified.Add( ETT_SCALE );
}

// Set the object's x scale. 
void iObject::SetScaleX( float x )
{
    _scale.x = x;

    _modified.Remove( ETT_SIZE );
    _modified.Add( ETT_SCALE );
}

// Set the object's y scale. 
void iObject::SetScaleY( float y )
{
    _scale.y = y;

    _modified.Remove( ETT_SIZE );
    _modified.Add( ETT_SCALE );
}

// Set the object's z scale. 
void iObject::SetScaleZ( float z )
{
    _scale.z = z;

    _modified.Remove( ETT_SIZE );
    _modified.Add( ETT_SCALE );
}


/// *************************************************************************
/// <summary>
/// Increment the object's scale. 
/// </summary>
/// *************************************************************************
void iObject::IncScale( float x, float y )
{
    _scale.x += x;
    _scale.y += y;

    _modified.Remove( ETT_SIZE );
    _modified.Add( ETT_SCALE );
}

// Increment the object's scale. 
void iObject::IncScale( float x, float y, float z )
{
    _scale.x += x;
    _scale.y += y;
    _scale.z += z;

    _modified.Remove( ETT_SIZE );
    _modified.Add( ETT_SCALE );
}

// Increment the object's scale. 
void iObject::IncScale( const CVector2 & scale )
{
    _scale += scale;

    _modified.Remove( ETT_SIZE );
    _modified.Add( ETT_SCALE );
}

// Increment the object's scale. 
void iObject::IncScale( const CVector3 & scale )
{
    _scale += scale;

    _modified.Remove( ETT_SIZE );
    _modified.Add( ETT_SCALE );
}


/// *************************************************************************
/// <summary>
/// Get the object's scale. 
/// </summary>
/// *************************************************************************
const CVector3 & iObject::GetScale()
{
    return _scale;
}


/// *************************************************************************
/// <summary>
/// Get the object's world scale. 
/// </summary>
/// *************************************************************************
CVector3 iObject::GetWorldScale() const
{
    if( _pParent )
        return _scale * _pParent->GetWorldScale();

    return _scale;
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

    _modified.Add( ETT_COLOR );
}

// Set the object's color. 
void iObject::SetColor( int r, int g, int b )
{
    _color.r = r;
    _color.g = g;
    _color.b = b;

    _modified.Add( ETT_COLOR );
}

// Set the object's color. 
void iObject::SetColor( const CColor & color )
{
    _color = color;

    _modified.Add( ETT_COLOR );
}

// Set the object's red value. 
void iObject::SetColorR( int r )
{
    _color.r = r;

    _modified.Add( ETT_COLOR );
}

// Set the object's green value. 
void iObject::SetColorG( int g )
{
    _color.g = g;

    _modified.Add( ETT_COLOR );
}

// Set the object's blue value. 
void iObject::SetColorB( int b )
{
    _color.b = b;

    _modified.Add( ETT_COLOR );
}

// Set the object's alpha value. 
void iObject::SetColorA( int a )
{
    _color.a = a;

    _modified.Add( ETT_COLOR );
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

    _modified.Add( ETT_COLOR );
}

// Increment the object's color.
void iObject::IncColor( int r, int g, int b )
{
    _color.r += r;
    _color.g += g;
    _color.b += b;

    _modified.Add( ETT_COLOR );
}

// Increment the object's color.
void iObject::IncColor( const CColor & color )
{
    _color += color;

    _modified.Add( ETT_COLOR );
}


/// *************************************************************************
/// <summary>
/// Get the object's color. 
/// </summary>
/// *************************************************************************
const CColor & iObject::GetColor()
{
    return _color;
}


/// *************************************************************************
/// <summary>
/// Set the object's parent. 
/// </summary>
/// *************************************************************************
void iObject::SetParent( iObject * pParent )
{
    _pParent = pParent;
}


/// *************************************************************************
/// <summary>
/// Get the object's parent. 
/// </summary>
/// *************************************************************************
const iObject * iObject::GetParent() const
{
    return _pParent;
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
/// Get the transformed bitmask. 
/// </summary>
/// *************************************************************************
CBitmask<uint> iObject::GetModified() const
{
    return _modified;
}


/// *************************************************************************
/// <summary>
/// Get the object's matrix. 
/// </summary>
/// *************************************************************************
const CMatrix4 * iObject::GetMatrix()
{
    return _pMatrix;
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


/// *************************************************************************
/// <summary>
/// Function to call the functions that update AGK. 
/// </summary>
/// <param name="updateMatrix"> Update the object's transformation matrix. </param>
/// *************************************************************************
void iObject::Transform( bool updateMatrix )
{
    // Make sure all parents are updated before updating this object.
    if( _pParent )
    {
        _pParent->Transform( true );

        if( _pParent->GetModified().Contains( ETT_APPLIED ) )
        {
            if( _pParent->GetModified().ContainsOne( ETT_POSITION | ETT_ROTATION | ETT_SIZE | ETT_SCALE ) )
                _modified.Add( ETT_POSITION );

            if( _pParent->GetModified().Contains( ETT_ROTATION ) )
                _modified.Add( ETT_ROTATION );

            if( _pParent->GetModified().Contains( ETT_SIZE ) )
                _modified.Add( ETT_SIZE );

            if( _pParent->GetModified().Contains( ETT_SCALE ) )
                _modified.Add( ETT_SCALE );
        }
    }

    // Apply changes if there were changes and they haven't already been applied.
    if( _modified > ETT_NULL && !_modified.Contains( ETT_APPLIED ) )
    {
        if( _modified.Contains( ETT_POSITION ) )
            ApplyPosition();

        if( _modified.Contains( ETT_ROTATION ) )
            ApplyRotation();

        if( _modified.Contains( ETT_SIZE ) )
            ApplySize();

        if( _modified.Contains( ETT_COLOR ) )
            ApplyColor();
    }

    // Update the object's matrix or create one if it doesn't have one.
    if( updateMatrix )
    {
        if( !_pMatrix )
            _pMatrix = new CMatrix4();
        else if( _modified.Contains( ETT_MATRIX ) )
            return;
        else
            _pMatrix->Clear();

        _pMatrix->SetRotation( _rotation );
        _pMatrix->Scale( _scale );
        _pMatrix->SetTranslation( _position );

        if( _pParent && _pParent->GetMatrix() )
            *_pMatrix *= *_pParent->GetMatrix();

        _modified.Add( ETT_MATRIX );
    }

    _modified.Add( ETT_APPLIED );
}


/// *************************************************************************
/// <summary>
/// Clear the bitmask of modified fields. 
/// </summary>
/// *************************************************************************
void iObject::ClearModified()
{
    _modified = ETT_NULL;
}
// Physical component dependency
#include "sprite2d.h"

// Game lib dependencies
#include <agk.h>
#include <common\matrix4.h>
#include <2d\spritedata2d.h>
#include <managers\resourcemanager.h>
#include <utilities\mathfunc.h>
#include <script\animationcomponent.h>

/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CSprite2D::CSprite2D()
{
    _type = NDefs::EOT_SPRITE_2D;
}


/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// <param name="pData"> Sprite data used to create the sprite. </param> 
/// *************************************************************************
CSprite2D::CSprite2D( const CSpriteData2D * pData )
{
    _type = NDefs::EOT_SPRITE_2D;

    Init( pData );
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CSprite2D::~CSprite2D()
{
    Clear();
}


/// *************************************************************************
/// <summary>
/// Initialize the sprite using its sprite data.
/// </summary>
/// <param name="pData"> Sprite data used to create the sprite. </param> 
/// *************************************************************************
void CSprite2D::Init( const CSpriteData2D * pData )
{
    // Leave if there's no data to initialize with.
    if( !pData )
        return;

    Clear();

    _pData = pData;
    const CSpriteVisualData2D * pVisual = _pData->GetVisualData();

    // Set the visual settings if a visual component exists.
    if( pVisual )
    {
        // Create the sprite using the texture map name. No name suggests a solid color.
        int imageId = CResourceManager::Instance().LoadImage( pVisual->GetTextureMap() );
        _id = agk::CreateSprite( imageId );

        // The height and width must be greater than zero to set the size.
        if( pVisual->GetSize().w > 0 && pVisual->GetSize().h > 0 )
        {
            _size = pVisual->GetSize();
            agk::SetSpriteSize( _size.w, _size.h );
        }
        else
        {
            _size.w = agk::GetSpriteWidth( _id );
            _size.h = agk::GetSpriteHeight( _id );
        }

        // Set the sprite color.
        SetColor( pVisual->GetColor() );
    }

    if( _pData->GetAnimationList().size() > 0 )
        _pAnimationComponent = new CAnimationComponent(this, _pData->GetAnimationList() );

    _alignment = _pData->GetAlignment();
}


/// *************************************************************************
/// <summary>
/// Get the data used to create the sprite.
/// </summary>
/// *************************************************************************
const CSpriteData2D * CSprite2D::GetData() const
{
    return _pData;
}


/// *************************************************************************
/// <summary>
/// Delete the object that belongs to the AGK id.
/// </summary>
/// *************************************************************************
void CSprite2D::DeleteObject()
{
    if( _id > 0 )
    {
        agk::DeleteSprite( _id );

        _id = 0;
    }
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current position.
/// </summary>
/// *************************************************************************
void CSprite2D::ApplyPosition()
{
    if( _pParent && _pParent->GetMatrix() )
    {
        CVector3 newPos = *_pParent->GetMatrix() * _position;
        agk::SetSpritePosition( _id, newPos.x, newPos.y );
    }
    else
        agk::SetSpritePosition( _id, _position.x, _position.y );

    agk::SetSpriteDepth( _id, (int)(_position.z + 0.5f) );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current rotation.
/// </summary>
/// *************************************************************************
void CSprite2D::ApplyRotation()
{
    if( _pParent )
        agk::SetSpriteAngle( _id, _pParent->GetWorldRot().z + _rotation.z );
    else
        agk::SetSpriteAngle( _id, _rotation.z );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current size.
/// </summary>
/// *************************************************************************
void CSprite2D::ApplySize()
{
    _scale = _size / _pData->GetSize();

    if( _pParent )
    {
        CVector2 newScale = _pParent->GetWorldScale() * _scale;
        agk::SetSpriteScale( _id, newScale.w, newScale.h );
    }
    else
        agk::SetSpriteScale( _id, _scale.w, _scale.h );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current scale.
/// </summary>
/// *************************************************************************
void CSprite2D::ApplyScale()
{
    _size = _pData->GetSize() * _scale;

    if( _pParent )
    {
        CVector2 newScale = _pParent->GetWorldScale() * _scale;
        agk::SetSpriteScale( _id, newScale.w, newScale.h );
    }
    else
        agk::SetSpriteScale( _id, _scale.w, _scale.h );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current color.
/// </summary>
/// *************************************************************************
void CSprite2D::ApplyColor()
{
    agk::SetSpriteColor( _id, _color.r, _color.g, _color.b, _color.a );
}


/// *************************************************************************
/// <summary>
/// Get the current position set in AGK.
/// </summary>
/// *************************************************************************
CVector3 CSprite2D::GetWorldPos() const
{
    return CVector3( agk::GetSpriteX( _id ), 
                     agk::GetSpriteY( _id ), 
                     (float)agk::GetSpriteDepth( _id ) );
}


/// *************************************************************************
/// <summary>
/// Get the current rotation set in AGK.
/// </summary>
/// *************************************************************************
CVector3 CSprite2D::GetWorldRot() const
{
    return CVector3( 0, 0, agk::GetSpriteAngle( _id ) );
}


/// *************************************************************************
/// <summary>
/// Get the current size set in AGK.
/// </summary>
/// *************************************************************************
CVector3 CSprite2D::GetWorldSize() const
{
    return CVector3( agk::GetSpriteWidth( _id ), 
                     agk::GetSpriteHeight( _id ) );
}


/// *************************************************************************
/// <summary>
/// Clears all of the sprite's data that belong to it.
/// </summary>
/// *************************************************************************
void CSprite2D::Clear()
{
    iObject::Clear();

    _alignment = NDefs::EA_CENTER;
    _pData = nullptr;
}


/// *************************************************************************
/// <summary>
/// Set the sprite's visibility.
/// </summary>
/// *************************************************************************
void CSprite2D::SetVisible( bool visible )
{
    agk::SetSpriteVisible( _id, visible );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's visibility.
/// </summary>
/// *************************************************************************
bool CSprite2D::IsVisible() const
{
    return agk::GetSpriteVisible( _id );
}


/// *************************************************************************
/// <summary>
/// Set the sprite's alignment.
/// </summary>
/// *************************************************************************
void CSprite2D::SetAlignment( const CBitmask<uint> & alignment )
{
    _alignment = alignment;
}


/// *************************************************************************
/// <summary>
/// Get the sprite's alignment.
/// </summary>
/// *************************************************************************
CBitmask<uint> CSprite2D::GetAlignment() const
{
    return _alignment;
}


/// *************************************************************************
/// <summary>
/// Reset the sprite's position using its previous position.
/// </summary>
/// *************************************************************************
void CSprite2D::Reposition()
{
    NMathFunc::AlignPosition( _alignment, _position );
    agk::SetSpritePosition( _id, _position.x, _position.y );
}
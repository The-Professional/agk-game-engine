// Physical component dependency
#include "sprite2d.h"

// Game lib dependencies
#include <agk.h>
#include <common\size.h>
#include <2d\spritedata2d.h>
#include <managers\resourcemanager.h>
#include <utilities\mathfunc.h>

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
            SetSize( pVisual->GetSize().w, pVisual->GetSize().h );
        else
        {
            _size.w = agk::GetSpriteWidth( _id );
            _size.h = agk::GetSpriteHeight( _id );
        }

        // Set the sprite color.
        SetColor( pVisual->GetColor() );
    }

    _alignment = _pData->GetAlignment();
}


/// *************************************************************************
/// <summary>
/// Set the data used to create the sprite.
/// </summary>
/// *************************************************************************
void CSprite2D::SetData( CSpriteData2D * pData )
{
    _pData = pData;
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
void CSprite2D::UpdateAGKWithPos()
{
    agk::SetSpritePosition( _id, _position.x, _position.y );
    agk::SetSpriteDepth( _id, (int)_position.z );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current rotation.
/// </summary>
/// *************************************************************************
void CSprite2D::UpdateAGKWithRot()
{
    agk::SetSpriteAngle( _id, _rotation.z );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current size.
/// </summary>
/// *************************************************************************
void CSprite2D::UpdateAGKWithSize()
{
    agk::SetSpriteSize( _id, _size.w, _size.h );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current color.
/// </summary>
/// *************************************************************************
void CSprite2D::UpdateAGKWithColor()
{
    agk::SetSpriteColor( _id, _color.r, _color.g, _color.b, _color.a );
}


/// *************************************************************************
/// <summary>
/// Update the current position from AGK.
/// </summary>
/// *************************************************************************
void CSprite2D::UpdatePosFromAGK()
{
    _position.x = agk::GetSpriteX( _id );
    _position.y = agk::GetSpriteY( _id );
    _position.z = (float)agk::GetSpriteDepth( _id );
}

/// *************************************************************************
/// <summary>
/// Update the current rotation from AGK.
/// </summary>
/// *************************************************************************
void CSprite2D::UpdateRotFromAGK()
{
    _rotation.z = agk::GetSpriteAngle( _id );
}

/// *************************************************************************
/// <summary>
/// Update the current size from AGK.
/// </summary>
/// *************************************************************************
void CSprite2D::UpdateSizeFromAGK()
{
    _size.w = agk::GetSpriteWidth( _id );
    _size.h = agk::GetSpriteHeight( _id );
}

/// *************************************************************************
/// <summary>
/// Update the current color from AGK.
/// </summary>
/// *************************************************************************
void CSprite2D::UpdateColorFromAGK()
{
    _color.r = agk::GetSpriteColorRed( _id );
    _color.g = agk::GetSpriteColorGreen( _id );
    _color.b = agk::GetSpriteColorBlue( _id );
    _color.a = agk::GetSpriteColorAlpha( _id );
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
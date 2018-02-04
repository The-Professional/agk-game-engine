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
}


/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// <param name="pData"> Sprite data used to create the sprite. </param> 
/// *************************************************************************
CSprite2D::CSprite2D( const CSpriteData2D * pData )
{
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
/// Initialize the sprite with the passed in object type.
/// </summary>
/// <param name="pData"> Sprite data used to create the sprite. </param>  
/// *************************************************************************
void CSprite2D::Init( const CSpriteData2D * pData )
{
    Clear();

    _pData = pData;
    const CSpriteVisualData2D * pVisual = pData->GetVisualData();

    if( pVisual )
    {
        int imageId = CResourceManager::Instance().LoadImage( pVisual->GetTextureMap() );
        _id = agk::CreateSprite( imageId );

        if( pVisual->GetSize().w > 0 && pVisual->GetSize().h > 0 )
            agk::SetSpriteSize( _id, (float)pVisual->GetSize().w, (float)pVisual->GetSize().h );

        agk::SetSpriteColor( _id, pVisual->GetColor().r, pVisual->GetColor().g, pVisual->GetColor().b, pVisual->GetColor().a );
    }

    _alignment = pData->GetAlignment();
}


/// *************************************************************************
/// <summary>
/// Get the name of the sprite.
/// </summary>
/// *************************************************************************
const std::string & CSprite2D::GetName() const
{
    return _pData->GetName();
}


/// *************************************************************************
/// <summary>
/// Clears all of the sprites data that belong to it.
/// </summary>
/// *************************************************************************
void CSprite2D::Clear()
{
    if( _id > 0 )
    {
        agk::DeleteSprite( _id );
        _id = 0;
    }
}


/// *************************************************************************
/// <summary>
/// Get the id of the sprite.
/// </summary>
/// *************************************************************************
uint CSprite2D::GetID() const
{
    return _id;
}


/// *************************************************************************
/// <summary>
/// Set the sprite's position.
/// </summary>
/// *************************************************************************
void CSprite2D::SetPos( float x, float y )
{
    _vPos.x = x;
    _vPos.y = y;
    agk::SetSpritePosition( _id, x, y );
}

/// <summary>
/// Set the sprite's position and depth.
/// </summary>
void CSprite2D::SetPos( float x, float y, float z )
{
    SetPos( x, y );
    agk::SetSpriteDepth( _id, (int)z );
}

/// <summary>
/// Set the sprite's position.
/// </summary>
void CSprite2D::SetPos( const CVector2 & pos )
{
    SetPos( pos.x, pos.y );
}

/// <summary>
/// Set the sprite's position and depth.
/// </summary>
void CSprite2D::SetPos( const CVector3 & pos )
{
    SetPos( pos.x, pos.y );
    agk::SetSpriteDepth( _id, (int)pos.z );
}

/// <summary>
/// Set the sprite's x position.
/// </summary>
void CSprite2D::SetPosX( float x )
{
    _vPos.x = x;
    agk::SetSpriteX( _id, x );
}

/// <summary>
/// Set the sprite's y position.
/// </summary>
void CSprite2D::SetPosY( float y )
{
    _vPos.y = y;
    agk::SetSpriteY( _id, y );
}

/// <summary>
/// Set the sprite's z position.
/// </summary>
void CSprite2D::SetPosZ( float z )
{
    agk::SetSpriteDepth( _id, (int)z );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's position.
/// </summary>
/// *************************************************************************
CVector2 CSprite2D::GetPos() const
{
    return CVector2( agk::GetSpriteX( _id ), agk::GetSpriteY( _id ) );
}

/// <summary>
/// Get the sprite's x position.
/// </summary>
float CSprite2D::GetPosX() const
{
    return agk::GetSpriteX( _id );
}

/// <summary>
/// Get the sprite's y position.
/// </summary>
float CSprite2D::GetPosY() const
{
    return agk::GetSpriteY( _id );
}

/// <summary>
/// Get the sprite's z position.
/// </summary>
float CSprite2D::GetPosZ() const
{
    return (float)agk::GetSpriteDepth( _id );
}


/// *************************************************************************
/// <summary>
/// Set the sprite's rotation.
/// </summary>
/// *************************************************************************
void CSprite2D::SetRot( float angle )
{
    agk::SetSpriteAngle( _id, angle );
}


/// *************************************************************************
/// <summary>
/// Increment the sprite's rotation.
/// </summary>
/// *************************************************************************
void CSprite2D::IncRot( float angle )
{
    agk::SetSpriteAngle( _id, GetRot() + angle );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's rotation.
/// </summary>
/// *************************************************************************
float CSprite2D::GetRot() const
{
    return agk::GetSpriteAngle( _id );
}


/// *************************************************************************
/// <summary>
/// Set the sprite's scale.
/// </summary>
/// *************************************************************************
void CSprite2D::SetScale( float uniform )
{
    _scale = CVector2( uniform );
    agk::SetSpriteScale( _id, uniform, uniform );
}

void CSprite2D::SetScale( float x, float y )
{
    _scale = CVector2( x, y );
    agk::SetSpriteScale( _id, x, y );
}

/// <summary>
/// Set the sprite's scale.
/// </summary>
void CSprite2D::SetScale( const CVector2 & scale )
{
    _scale = scale;
    agk::SetSpriteScale( _id, scale.x, scale.y );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's scale.
/// </summary>
/// *************************************************************************
const CVector2 & CSprite2D::GetScale() const
{
    return _scale;
}

/// <summary>
/// Get the sprite's X scale.
/// </summary>
float CSprite2D::GetScaleX() const
{
    return _scale.x;
}

/// <summary>
/// Get the sprite's Y scale.
/// </summary>
float CSprite2D::GetScaleY() const
{
    return _scale.y;
}


/// *************************************************************************
/// <summary>
/// Set the sprite's size.
/// </summary>
/// *************************************************************************
void CSprite2D::SetSize( const CSize<float> & size )
{
    agk::SetSpriteSize( _id, size.w, size.h );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's size.
/// </summary>
/// *************************************************************************
CSize<float> CSprite2D::GetSize() const
{
    return CSize<float>( agk::GetSpriteWidth( _id ), agk::GetSpriteHeight( _id ) );
}

/// *************************************************************************
/// <summary>
/// Set the sprite's color.
/// </summary>
/// *************************************************************************
void CSprite2D::SetColor( const CColor & color )
{
    agk::SetSpriteColor( _id, color.r, color.g, color.b, color.a );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's color.
/// </summary>
/// *************************************************************************
CColor CSprite2D::GetColor() const
{
    return CColor( agk::GetSpriteColorRed( _id ), agk::GetSpriteColorGreen( _id ), agk::GetSpriteColorBlue( _id ), agk::GetSpriteColorAlpha( _id ) );
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
/// Reset the sprite's position using its previous position.
/// </summary>
/// *************************************************************************
void CSprite2D::Reposition()
{
    CVector2 newPos = NMathFunc::GetAlignedPos( _alignment, _vPos );
    agk::SetSpritePosition( _id, newPos.x, newPos.y );
}
// Physical component dependency
#include "textsprite.h"

// Game lib dependencies
#include <agk.h>
#include <2d\textspritedata.h>
#include <managers\resourcemanager.h>

/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CTextSprite::CTextSprite()
{
}


/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// <param name="pData"> Sprite data used to create the sprite. </param> 
/// *************************************************************************
CTextSprite::CTextSprite( const CTextSpriteData * pData )
{
    Init( pData );
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CTextSprite::~CTextSprite()
{
    Clear();
}


/// *************************************************************************
/// <summary>
/// Initialize the sprite with the passed in object type.
/// </summary>
/// <param name="pData"> Sprite data used to create the sprite. </param>  
/// *************************************************************************
void CTextSprite::Init( const CTextSpriteData * pData )
{
    Clear();

    _pData = pData;
    /*const CSpriteVisualData2D * pVisual = pData->GetVisualData();

    if( pVisual )
    {
        int imageId = CResourceManager::Instance().LoadImage( pVisual->GetTextureMap() );
        _id = agk::CreateSprite( imageId );

        if( pVisual->GetWidth() > 0 && pVisual->GetHeight() > 0 )
            agk::SetSpriteSize( _id, pVisual->GetWidth(), pVisual->GetHeight() );

        agk::SetSpriteColor( _id, pVisual->GetColor().r, pVisual->GetColor().g, pVisual->GetColor().b, pVisual->GetColor().a );
    }*/
}


/// *************************************************************************
/// <summary>
/// Get the name of the sprite.
/// </summary>
/// *************************************************************************
const std::string & CTextSprite::GetName() const
{
    return _pData->GetName();
}


/// *************************************************************************
/// <summary>
/// Clears all of the sprites data that belong to it.
/// </summary>
/// *************************************************************************
void CTextSprite::Clear()
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
uint CTextSprite::GetID() const
{
    return _id;
}


/// *************************************************************************
/// <summary>
/// Set the sprite's position.
/// </summary>
/// *************************************************************************
void CTextSprite::SetPos( float x, float y )
{
    agk::SetSpritePosition( _id, x, y );
}

/// <summary>
/// Set the sprite's position and depth.
/// </summary>
void CTextSprite::SetPos( float x, float y, int depth )
{
    agk::SetSpritePosition( _id, x, y );
    agk::SetSpriteDepth( _id, depth );
}

/// <summary>
/// Set the sprite's position.
/// </summary>
void CTextSprite::SetPos( const CVector2 & pos )
{
    agk::SetSpritePosition( _id, pos.x, pos.y );
}

/// <summary>
/// Set the sprite's position and depth.
/// </summary>
void CTextSprite::SetPos( const CVector2 & pos, int depth )
{
    agk::SetSpritePosition( _id, pos.x, pos.y );
    agk::SetSpriteDepth( _id, depth );
}


/// *************************************************************************
/// <summary>
/// Set the sprite's depth.
/// </summary>
/// *************************************************************************
void CTextSprite::SetDepth( int depth )
{
    agk::SetSpriteDepth( _id, depth );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's position.
/// </summary>
/// *************************************************************************
CVector2 CTextSprite::GetPos() const
{
    return CVector2( agk::GetSpriteX( _id ), agk::GetSpriteX( _id ) );
}

/// <summary>
/// Get the sprite's X position.
/// </summary>
float CTextSprite::GetPosX() const
{
    return agk::GetObjectX( _id );
}

/// <summary>
/// Get the sprite's Y position.
/// </summary>
float CTextSprite::GetPosY() const
{
    return agk::GetObjectY( _id );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's depth.
/// </summary>
/// *************************************************************************
int CTextSprite::GetDepth() const
{
    return agk::GetSpriteDepth( _id );
}


/// *************************************************************************
/// <summary>
/// Set the sprite's rotation.
/// </summary>
/// *************************************************************************
void CTextSprite::SetRot( float angle )
{
    agk::SetSpriteAngle( _id, angle );
}


/// *************************************************************************
/// <summary>
/// Increment the sprite's rotation.
/// </summary>
/// *************************************************************************
void CTextSprite::IncRot( float angle )
{
    agk::SetSpriteAngle( _id, GetRot() + angle );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's rotation.
/// </summary>
/// *************************************************************************
float CTextSprite::GetRot() const
{
    return agk::GetSpriteAngle( _id );
}


/// *************************************************************************
/// <summary>
/// Set the sprite's scale.
/// </summary>
/// *************************************************************************
void CTextSprite::SetScale( float uniform )
{
    _scale = CVector2( uniform );
    agk::SetSpriteScale( _id, uniform, uniform );
}

void CTextSprite::SetScale( float x, float y )
{
    _scale = CVector2( x, y );
    agk::SetSpriteScale( _id, x, y );
}

/// <summary>
/// Set the sprite's scale.
/// </summary>
void CTextSprite::SetScale( const CVector2 & scale )
{
    _scale = scale;
    agk::SetSpriteScale( _id, scale.x, scale.y );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's scale.
/// </summary>
/// *************************************************************************
const CVector2 & CTextSprite::GetScale() const
{
    return _scale;
}

/// <summary>
/// Get the sprite's X scale.
/// </summary>
float CTextSprite::GetScaleX() const
{
    return _scale.x;
}

/// <summary>
/// Get the sprite's Y scale.
/// </summary>
float CTextSprite::GetScaleY() const
{
    return _scale.y;
}


/// *************************************************************************
/// <summary>
/// Set the sprite's visibility.
/// </summary>
/// *************************************************************************
void CTextSprite::SetVisible( bool visible )
{
    agk::SetSpriteVisible( _id, visible );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's visibility.
/// </summary>
/// *************************************************************************
bool CTextSprite::IsVisible() const
{
    return agk::GetSpriteVisible( _id );
}
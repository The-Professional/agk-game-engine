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

    _id = agk::CreateText( pData->GetText().c_str() );
    if( _id > 0 )
    {
        _text = pData->GetText();
        SetFont( CResourceManager::Instance().LoadFont( pData->GetFont() ) );
        SetTextSpacing( pData->GetTextSpacing() );
        SetLineSpacing( pData->GetLineSpacing() );
        SetScale( pData->GetFontSize() );
        SetMaxWidth( pData->GetMaxWidth() );
        SetColor( pData->GetColor() );
        SetTextAlignment( pData->GetTextAlignment() );
        SetAlignment( pData->GetAlignment() );
    }
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
        agk::DeleteText( _id );
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
    agk::SetTextPosition( _id, x, y );
}

/// <summary>
/// Set the sprite's position and depth.
/// </summary>
void CTextSprite::SetPos( float x, float y, float z )
{
    agk::SetTextPosition( _id, x, y );
    agk::SetTextDepth( _id, (int)z );
}

/// <summary>
/// Set the sprite's position.
/// </summary>
void CTextSprite::SetPos( const CVector2 & pos )
{
    agk::SetTextPosition( _id, pos.x, pos.y );
}

/// <summary>
/// Set the sprite's position and depth.
/// </summary>
void CTextSprite::SetPos( const CVector3 & pos )
{
    agk::SetTextPosition( _id, pos.x, pos.y );
    agk::SetTextDepth( _id, (int)pos.z );
}


/// *************************************************************************
/// <summary>
/// Set the sprite's x position.
/// </summary>
/// *************************************************************************
void CTextSprite::SetPosX( float x )
{
    agk::SetTextX( _id, x );
}

/// <summary>
/// Set the sprite's y position.
/// </summary>
void CTextSprite::SetPosY( float y )
{
    agk::SetTextY( _id, y );
}

/// <summary>
/// Set the sprite's x position.
/// </summary>
void CTextSprite::SetPosZ( float z )
{
    agk::SetTextDepth( _id, (int)z );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's position.
/// </summary>
/// *************************************************************************
CVector3 CTextSprite::GetPos() const
{
    return CVector3( agk::GetTextX( _id ), agk::GetTextY( _id ), (float)agk::GetTextDepth( _id ) );
}

/// <summary>
/// Get the sprite's X position.
/// </summary>
float CTextSprite::GetPosX() const
{
    return agk::GetTextX( _id );
}

/// <summary>
/// Get the sprite's Y position.
/// </summary>
float CTextSprite::GetPosY() const
{
    return agk::GetTextY( _id );
}

/// <summary>
/// Get the sprite's Z position.
/// </summary>
float CTextSprite::GetPosZ() const
{
    return (float)agk::GetTextDepth( _id );
}


/// *************************************************************************
/// <summary>
/// Set the sprite's rotation.
/// </summary>
/// *************************************************************************
void CTextSprite::SetRot( float angle )
{
    agk::SetTextAngle( _id, angle );
}


/// *************************************************************************
/// <summary>
/// Increment the sprite's rotation.
/// </summary>
/// *************************************************************************
void CTextSprite::IncRot( float angle )
{
    agk::SetTextAngle( _id, GetRot() + angle );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's rotation.
/// </summary>
/// *************************************************************************
float CTextSprite::GetRot() const
{
    // Weirdly enough there's no get angle function. This may or may not work.
    return agk::GetTextCharAngle( _id, 0 );
}


/// *************************************************************************
/// <summary>
/// Set the sprite's scale.
/// </summary>
/// *************************************************************************
void CTextSprite::SetScale( float uniform )
{
    agk::SetTextSize( _id, uniform );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's scale.
/// </summary>
/// *************************************************************************
float CTextSprite::GetScale() const
{
    return agk::GetTextSize( _id );
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


/// *************************************************************************
/// <summary>
/// Set the text sprite's font.
/// </summary>
/// *************************************************************************
void CTextSprite::SetFont( uint fontId )
{
    _fontId = fontId;
    agk::SetTextFont( _id, fontId );
}


/// *************************************************************************
/// <summary>
/// Get the text sprite's font.
/// </summary>
/// *************************************************************************
uint CTextSprite::GetFont() const
{
    return _fontId;
}


/// *************************************************************************
/// <summary>
/// Set the text sprite's text.
/// </summary>
/// *************************************************************************
void CTextSprite::SetText( const std::string & text )
{
    _text = text;
    agk::SetTextString( _id, text.c_str() );
}


/// *************************************************************************
/// <summary>
/// Get the text sprite's text.
/// </summary>
/// *************************************************************************
std::string CTextSprite::GetText() const
{
    return _text;
}


/// *************************************************************************
/// <summary>
/// Set the text sprite's text spacing.
/// </summary>
/// *************************************************************************
void CTextSprite::SetTextSpacing( float textSpacing )
{
    agk::SetTextSpacing( _id, textSpacing );
}


/// *************************************************************************
/// <summary>
/// Get the text sprite's text spacing.
/// </summary>
/// *************************************************************************
float CTextSprite::GetTextSpacing() const
{
    return agk::GetTextSpacing( _id );
}


/// *************************************************************************
/// <summary>
/// Set the text sprite's line spacing.
/// </summary>
/// *************************************************************************
void CTextSprite::SetLineSpacing( float lineSpacing )
{
    agk::SetTextLineSpacing( _id, lineSpacing );
}


/// *************************************************************************
/// <summary>
/// Get the text sprite's line spacing.
/// </summary>
/// *************************************************************************
float CTextSprite::GetLineSpacing() const
{
    return agk::GetTextLineSpacing( _id );
}


/// *************************************************************************
/// <summary>
/// Set the text sprite's max width.
/// </summary>
/// *************************************************************************
void CTextSprite::SetMaxWidth( float maxWidth )
{
    _maxWidth = maxWidth;
    agk::SetTextMaxWidth( _id, maxWidth );
}

/// *************************************************************************
/// <summary>
/// Get the text sprite's max width before text begins to wrap.
/// </summary>
/// *************************************************************************
float CTextSprite::GetMaxWidth() const
{
    return _maxWidth;
}

/// *************************************************************************
/// <summary>
/// Set the sprite's color.
/// </summary>
/// *************************************************************************
void CTextSprite::SetColor( const CColor & color )
{
    agk::SetTextColor( _id, color.r, color.g, color.b, color.a );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's color.
/// </summary>
/// *************************************************************************
CColor CTextSprite::GetColor() const
{
    return CColor( agk::GetTextColorRed( _id ), agk::GetTextColorGreen( _id ), agk::GetTextColorBlue( _id ), agk::GetTextColorAlpha( _id ) );
}


/// *************************************************************************
/// <summary>
/// Set the text sprite's text alignment.
/// </summary>
/// *************************************************************************
void CTextSprite::SetTextAlignment( NDefs::ETextAlignment alignment )
{
    _textAlignment = alignment;
    agk::SetTextAlignment( _id, alignment );
}


/// *************************************************************************
/// <summary>
/// Get the text sprite's text alignment.
/// </summary>
/// *************************************************************************
NDefs::ETextAlignment CTextSprite::GetTextAlignment() const
{
    return _textAlignment;
}


/// *************************************************************************
/// <summary>
/// Set the text sprite's alignment.
/// </summary>
/// *************************************************************************
void CTextSprite::SetAlignment( const CBitmask<uint> & alignment )
{
    _alignment = alignment;
}


/// *************************************************************************
/// <summary>
/// Get the text sprite's alignment.
/// </summary>
/// *************************************************************************
const CBitmask<uint> & CTextSprite::GetAlignment() const
{
    return _alignment;
}
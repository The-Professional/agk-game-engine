// Physical component dependency
#include "textsprite.h"

// Game lib dependencies
#include <agk.h>
#include <2d\textspritedata.h>
#include <managers\resourcemanager.h>
#include <utilities\mathfunc.h>

using namespace std;

/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CTextSprite::CTextSprite()
{
    _type = NDefs::EOT_TEXT_SPRITE;
}


/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// <param name="pData"> Sprite data used to create the sprite. </param> 
/// <param name="text"> The text to display. </param>
/// *************************************************************************
CTextSprite::CTextSprite( const CTextSpriteData * pData, const string & text )
{
    _type = NDefs::EOT_TEXT_SPRITE;
    _pData = pData;
    Init( text );
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
/// Initialize the sprite using its sprite data.
/// </summary>
/// *************************************************************************
void CTextSprite::Init()
{
    Init( _text );
}

/// <summary>
/// Initialize the sprite using its sprite data.
/// </summary>
/// <param name="text"> The text to display. </param>
void CTextSprite::Init( const string & text )
{
    // Leave if there's no data to initialize with.
    if( !_pData )
        return;

    Clear();

    if( !text.empty() )
    {
        _text = text;
        _id = agk::CreateText( text.c_str() );
    }
    
    if( _id > 0 )
    {
        SetFont( CResourceManager::Instance().LoadFont( _pData->GetFont() ) );
        SetTextSpacing( _pData->GetTextSpacing() );
        SetLineSpacing( _pData->GetLineSpacing() );
        SetTextSize( _pData->GetSize() );
        SetMaxWidth( _pData->GetMaxWidth() );
        SetColor( _pData->GetColor() );
        SetTextAlignment( _pData->GetTextAlignment() );
        SetAlignment( _pData->GetAlignment() );
    }
}


/// *************************************************************************
/// <summary>
/// Set the data used to create the sprite.
/// </summary>
/// *************************************************************************
void CTextSprite::SetData( CTextSpriteData * pData )
{
    _pData = pData;
}


/// *************************************************************************
/// <summary>
/// Get the data used to create the sprite.
/// </summary>
/// *************************************************************************
const CTextSpriteData * CTextSprite::GetData() const
{
    return _pData;
}


/// *************************************************************************
/// <summary>
/// Clears all of the text sprite's data that belong to it.
/// </summary>
/// *************************************************************************
void CTextSprite::Clear()
{
    iObject::Clear();

    _fontId = 0;
    _maxWidth = 0;
    _textAlignment = NDefs::ETA_LEFT;
    _alignment = NDefs::EA_CENTER;
    _text = "";
}


/// *************************************************************************
/// <summary>
/// Delete the object that belongs to the AGK id.
/// </summary>
/// *************************************************************************
void CTextSprite::DeleteObject()
{
    if( _id > 0 )
    {
        agk::DeleteText( _id );
        _id = 0;
    }
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current position.
/// </summary>
/// *************************************************************************
void CTextSprite::UpdateAGKWithPos()
{
    agk::SetTextPosition( _id, _position.x, _position.y );
    agk::SetTextDepth( _id, (int)_position.z );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current rotation.
/// </summary>
/// *************************************************************************
void CTextSprite::UpdateAGKWithRot()
{
    agk::SetTextAngle( _id, _rotation.z );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current size.
/// </summary>
/// *************************************************************************
void CTextSprite::UpdateAGKWithSize()
{
    agk::SetTextSize( _id, _size.d );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current color.
/// </summary>
/// *************************************************************************
void CTextSprite::UpdateAGKWithColor()
{
    agk::SetTextColor( _id, _color.r, _color.g, _color.b, _color.a );
}


/// *************************************************************************
/// <summary>
/// Update the current position from AGK.
/// </summary>
/// *************************************************************************
void CTextSprite::UpdatePosFromAGK()
{
    _position.x = agk::GetTextX( _id );
    _position.y = agk::GetTextY( _id );
    _position.z = (float)agk::GetTextDepth( _id );
}

/// *************************************************************************
/// <summary>
/// Update the current rotation from AGK.
/// </summary>
/// *************************************************************************
void CTextSprite::UpdateRotFromAGK()
{
    // There doesn't seem to be a way to get a text's color from AGK, which is very strange.
}

/// *************************************************************************
/// <summary>
/// Update the current size from AGK.
/// </summary>
/// *************************************************************************
void CTextSprite::UpdateSizeFromAGK()
{
    _size.w = agk::GetTextTotalWidth( _id );
    _size.h = agk::GetTextTotalHeight( _id );
    _size.d = agk::GetTextSize( _id );
}

/// *************************************************************************
/// <summary>
/// Update the current color from AGK.
/// </summary>
/// *************************************************************************
void CTextSprite::UpdateColorFromAGK()
{
    _color.r = agk::GetTextColorRed( _id );
    _color.g = agk::GetTextColorGreen( _id );
    _color.b = agk::GetTextColorBlue( _id );
    _color.a = agk::GetTextColorAlpha( _id );
}


/// *************************************************************************
/// <summary>
/// Set the text sprite's visibility.
/// </summary>
/// *************************************************************************
void CTextSprite::SetVisible( bool visible )
{
    agk::SetTextVisible( _id, visible );
}


/// *************************************************************************
/// <summary>
/// Get the text sprite's visibility.
/// </summary>
/// *************************************************************************
bool CTextSprite::IsVisible() const
{
    return agk::GetTextVisible( _id );
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

    UpdateSizeFromAGK();
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
void CTextSprite::SetText( const string & text )
{
    _text = text;
    agk::SetTextString( _id, text.c_str() );

    UpdateSizeFromAGK();
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
/// Set the text sprite's size.
/// </summary>
/// *************************************************************************
void CTextSprite::SetTextSize( float size )
{
    SetSizeD( size );

    UpdateSizeFromAGK();
}


/// *************************************************************************
/// <summary>
/// Get the text sprite's size.
/// </summary>
/// *************************************************************************
float CTextSprite::GetTextSize() const
{
    return _size.d;
}


/// *************************************************************************
/// <summary>
/// Set the text sprite's text spacing.
/// </summary>
/// *************************************************************************
void CTextSprite::SetTextSpacing( float textSpacing )
{
    agk::SetTextSpacing( _id, textSpacing );

    UpdateSizeFromAGK();
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

    UpdateSizeFromAGK();
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

    UpdateSizeFromAGK();
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
CBitmask<uint> CTextSprite::GetAlignment() const
{
    return _alignment;
}


/// *************************************************************************
/// <summary>
/// Reset the sprite's position using its previous position.
/// </summary>
/// *************************************************************************
void CTextSprite::Reposition()
{
    NMathFunc::AlignPosition( _alignment, _position );
    agk::SetTextPosition( _id, _position.x, _position.y );
}
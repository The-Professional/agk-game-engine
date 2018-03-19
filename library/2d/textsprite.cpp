// Physical component dependency
#include "textsprite.h"

// Game lib dependencies
#include <agk.h>
#include <common\matrix4.h>
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

    Init( pData, text );
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
/// <param name="pData"> Sprite data used to create the sprite. </param> 
/// <param name="text"> The text to display. </param>
/// *************************************************************************
void CTextSprite::Init( const CTextSpriteData * pData, const string & text )
{
    // Leave if there's no data to initialize with.
    if( !pData )
        return;

    Clear();

    _pData = pData;
    _text = text;
    _id = agk::CreateText( text.c_str() );
    
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
void CTextSprite::ApplyPosition()
{
    if( _pParent )
    {
        CVector2 newPos = *_pParent->GetMatrix() * _position;
        agk::SetTextPosition( _id, newPos.x, newPos.y );
    }
    else
        agk::SetTextPosition( _id, _position.x, _position.y );

    agk::SetTextDepth( _id, (int)(_position.z + 0.5f) );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current rotation.
/// </summary>
/// *************************************************************************
void CTextSprite::ApplyRotation()
{
    _rotation %= 360;

    if( _pParent )
        agk::SetTextAngle( _id, _pParent->GetWorldRot().z + _rotation.z );
    else
        agk::SetTextAngle( _id, _rotation.z );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current scale.
/// </summary>
/// *************************************************************************
void CTextSprite::ApplyScale()
{
    if( _pParent )
        agk::SetTextSize( _id, _size.x * _pParent->GetWorldScale().x );
    else
        agk::SetTextSize( _id, _size.x );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current color.
/// </summary>
/// *************************************************************************
void CTextSprite::ApplyColor()
{
    agk::SetTextColor( _id, _color.r, _color.g, _color.b, _color.a );
}


/// *************************************************************************
/// <summary>
/// Get the current position set in AGK.
/// </summary>
/// *************************************************************************
CVector3 CTextSprite::GetWorldPos() const
{
    return CVector3( agk::GetTextX( _id ),
                     agk::GetTextY( _id ),
                     (float)agk::GetTextDepth( _id ) );
}


/// *************************************************************************
/// <summary>
/// Get the current rotation set in AGK.
/// </summary>
/// *************************************************************************
CVector3 CTextSprite::GetWorldRot() const
{
    return _rotation.z;
}


/// *************************************************************************
/// <summary>
/// Get the current size set in AGK.
/// </summary>
/// *************************************************************************
CVector3 CTextSprite::GetWorldSize() const
{
    return CVector3( agk::GetTextTotalWidth( _id ),
                     agk::GetTextTotalHeight( _id ),
                     agk::GetTextSize( _id ) );
}


/// *************************************************************************
/// <summary>
/// Update the sprite's size using the scale.
/// </summary>
/// *************************************************************************
void CTextSprite::UpdateSize()
{
    _size.x = _pData->GetSize() * _scale.x;
}


/// *************************************************************************
/// <summary>
/// Update the sprite's scale using the size.
/// </summary>
/// *************************************************************************
void CTextSprite::UpdateScale()
{
    _scale.x = _size.x / _pData->GetSize();
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
    SetSizeW( size );
}


/// *************************************************************************
/// <summary>
/// Get the text sprite's size.
/// </summary>
/// *************************************************************************
float CTextSprite::GetTextSize() const
{
    return _size.x;
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
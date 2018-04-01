// Physical component dependency
#include "menu.h"

// Game lib dependencies
#include <agk.h>
#include <common\matrix4.h>
#include <controls\menudata.h>
#include <controls\control.h>
#include <utilities\mathfunc.h>
#include <utilities\exceptionhandling.h>

using namespace std;
using namespace NDefs;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CMenu::CMenu( const string & name )
{
    _type = EOT_MENU;

    Init( name );
}


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CMenu::~CMenu()
{
    Clear();
}


/// *************************************************************************
/// <summary>
/// Get the name of the menu.
/// </summary>
/// *************************************************************************
const string & CMenu::GetName() const
{
    return _pData->GetName();
}


/// *************************************************************************
/// <summary>
/// Clears all of the menu's data that belong to it.
/// </summary>
/// *************************************************************************
void CMenu::Clear()
{
    iObject::Clear();

    _pSpriteList.clear();
    _pControlList.clear();
    _alignment = EA_CENTER;
}


/// *************************************************************************
/// <summary>
/// Delete the object that belongs to the AGK id.
/// </summary>
/// *************************************************************************
void CMenu::DeleteObject()
{
    if( _id > 0 )
    {
        agk::DeleteSprite( _id );

        _id = 0;
    }
}


/// *************************************************************************
/// <summary>
/// Mark the menu for deletion.
/// </summary>
/// *************************************************************************
void CMenu::MarkForDeletion()
{
    _pData = nullptr;
}


/// *************************************************************************
/// <summary>
/// Whether the menu is marked for deletion.
/// </summary>
/// *************************************************************************
bool CMenu::IsMarkedForDeletion() const
{
    return !_pData;
}


/// *************************************************************************
/// <summary>
/// Get the data used to create the menu.
/// </summary>
/// *************************************************************************
const CMenuData * CMenu::GetData() const
{
    return _pData;
}


/// *************************************************************************
/// <summary>
/// Update AGK with the menu's current position.
/// </summary>
/// *************************************************************************
void CMenu::ApplyPosition()
{
    if( _pParent )
    {
        CVector2<float> newPos = *_pParent->GetMatrix() * _position;
        agk::SetSpritePosition( _id, newPos.x, newPos.y );
    }
    else
        agk::SetSpritePosition( _id, _position.x, _position.y );

    agk::SetSpriteDepth( _id, (int)(_position.z + 0.5f) );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the menu's current rotation.
/// </summary>
/// *************************************************************************
void CMenu::ApplyRotation()
{
    _rotation %= 360;

    if( _pParent )
        agk::SetSpriteAngle( _id, _pParent->GetWorldRot().z + _rotation.z );
    else
        agk::SetSpriteAngle( _id, _rotation.z );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the menu's current scale.
/// </summary>
/// *************************************************************************
void CMenu::ApplyScale()
{
    if( _pParent )
    {
        CVector2<float> newScale = _pParent->GetWorldScale() * _scale;
        agk::SetSpriteScale( _id, newScale.w, newScale.h );
    }
    else
        agk::SetSpriteScale( _id, _scale.w, _scale.h );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the menu's current color.
/// </summary>
/// *************************************************************************
void CMenu::ApplyColor()
{
    // Does nothing. Color is only for child inheritance purposes.
}


/// *************************************************************************
/// <summary>
/// Update AGK with the menu's current visibility.
/// </summary>
/// *************************************************************************
void CMenu::ApplyVisibility()
{
    // Does nothing. Visibility is only for child inheritance purposes.
}


/// *************************************************************************
/// <summary>
/// Get the current position set in AGK.
/// </summary>
/// *************************************************************************
CVector3<float> CMenu::GetWorldPos() const
{
    return CVector3<float>( agk::GetSpriteX( _id ),
                            agk::GetSpriteY( _id ),
                            (float)agk::GetSpriteDepth( _id ) );
}


/// *************************************************************************
/// <summary>
/// Get the current rotation set in AGK.
/// </summary>
/// *************************************************************************
CVector3<float> CMenu::GetWorldRot() const
{
    return CVector3<float>( 0, 0, agk::GetSpriteAngle( _id ) );
}


/// *************************************************************************
/// <summary>
/// Get the current size set in AGK.
/// </summary>
/// *************************************************************************
CVector3<float> CMenu::GetWorldSize() const
{
    return CVector3<float>( agk::GetSpriteWidth( _id ),
                            agk::GetSpriteHeight( _id ) );
}


/// *************************************************************************
/// <summary>
/// Update the menu's size using the scale.
/// </summary>
/// *************************************************************************
void CMenu::UpdateSize()
{
    _size = _pData->GetSize() * _scale;
}


/// *************************************************************************
/// <summary>
/// Update the menu's scale using the size.
/// </summary>
/// *************************************************************************
void CMenu::UpdateScale()
{
    _scale = _size / _pData->GetSize();
}


/// *************************************************************************
/// <summary>
/// Get the menu's visibility.
/// </summary>
/// *************************************************************************
bool CMenu::IsVisible() const
{
    if( _pParent )
        return _pParent->IsVisible() && _visible;

    return _visible;
}


/// *************************************************************************
/// <summary>
/// Set the menu's alignment.
/// </summary>
/// *************************************************************************
void CMenu::SetAlignment( const CBitmask<uint> & alignment )
{
    _alignment = alignment;
}


/// *************************************************************************
/// <summary>
/// Get the menu's alignment.
/// </summary>
/// *************************************************************************
CBitmask<uint> CMenu::GetAlignment() const
{
    return _alignment;
}


/// *************************************************************************
/// <summary>
/// Reset the menu's position using its previous position.
/// </summary>
/// *************************************************************************
void CMenu::Reposition()
{
    // The parent's alignment overrides the child's alignment.
    if( _pParent )
        return;

    CVector3<float> pos = _position;
    if( NMathFunc::AlignPosition( _alignment, pos ) )
        SetPos( pos );
}


/// *************************************************************************
/// <summary>
/// Set the menu's state.
/// </summary>
/// *************************************************************************
void CMenu::SetEnabled( bool enabled )
{
    _enabled = enabled;
}


/// *************************************************************************
/// <summary>
/// Get the menu's state.
/// </summary>
/// *************************************************************************
bool CMenu::IsEnabled() const
{
    return _enabled;
}


/// *************************************************************************
/// <summary>
/// Play an animation. 
/// </summary>
/// <param name="name"> Name of the animation to play. </param>
/// <param name="stopType"> How to end any conflicting animations. </param>
/// *************************************************************************
void CMenu::Play( const string & name, EStopType stopType )
{
    iObject::Play( name, stopType );

    for( auto pSprite : _pSpriteList )
        pSprite->Play( name, stopType );
}


/// *************************************************************************
/// <summary>
/// Stop all animations.
/// </summary>
/// <param name="stopType"> How to end the animations. </param>
/// *************************************************************************
void CMenu::Stop( NDefs::EStopType stopType )
{
    iObject::Stop( stopType );

    for( auto pSprite : _pSpriteList )
        pSprite->Stop( stopType );
}

/// <summary>
/// Stop an animation.
/// </summary>
/// <param name="name"> Name of the animation to stop. </param>
/// <param name="stopType"> How to end the animation. </param>
void CMenu::Stop( const std::string & name, NDefs::EStopType stopType )
{
    iObject::Stop( name, stopType );

    for( auto pSprite : _pSpriteList )
        pSprite->Stop( name, stopType );
}


/// *************************************************************************
/// <summary>
/// Whether or not an animation is playing.
/// </summary>
/// <param name="includePaused"> If paused animations should be consider "playing". </param>
/// *************************************************************************
bool CMenu::IsPlaying( bool includePaused )
{
    if( iObject::IsPlaying( includePaused ) )
        return true;

    for( auto pSprite : _pSpriteList )
        if( pSprite->IsPlaying( includePaused ) )
            return true;

    return false;
}

/// <summary>
/// Whether or not an animation is playing.
/// </summary>
/// <param name="name"> Name of the animation to stop. </param>
/// <param name="includePaused"> If paused animations should be consider "playing". </param>
bool CMenu::IsPlaying( const std::string & name, bool includePaused )
{
    if( iObject::IsPlaying( name, includePaused ) )
        return true;

    for( auto pSprite : _pSpriteList )
        if( pSprite->IsPlaying( name, includePaused ) )
            return true;

    return false;
}
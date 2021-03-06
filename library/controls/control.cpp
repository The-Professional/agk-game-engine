// Physical component dependency
#include "control.h"

// Game lib dependencies
#include <agk.h>
#include <common\matrix4.h>
#include <controls\controldata.h>
#include <utilities\mathfunc.h>
#include <utilities\exceptionhandling.h>

using namespace std;
using namespace NDefs;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
iControl::iControl()
{
    _type = EOT_CONTROL;
}


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
iControl::~iControl()
{
    Clear();
}


/// *************************************************************************
/// <summary>
/// Get the name of the control.
/// </summary>
/// *************************************************************************
const string & iControl::GetName() const
{
    return _pData->GetName();
}


/// *************************************************************************
/// <summary>
/// Clears all of the control's data that belong to it.
/// </summary>
/// *************************************************************************
void iControl::Clear()
{
    iObject::Clear();

    _pSpriteList.clear();
    _state = ECS_DISABLED;
    _alignment = EA_CENTER;
}


/// *************************************************************************
/// <summary>
/// Delete the object that belongs to the AGK id.
/// </summary>
/// *************************************************************************
void iControl::DeleteObject()
{
    if( _id > 0 )
    {
        agk::DeleteSprite( _id );

        _id = 0;
    }
}


/// *************************************************************************
/// <summary>
/// Mark the control for deletion.
/// </summary>
/// *************************************************************************
void iControl::MarkForDeletion()
{
    _pData = nullptr;
}


/// *************************************************************************
/// <summary>
/// Whether the control is marked for deletion.
/// </summary>
/// *************************************************************************
bool iControl::IsMarkedForDeletion() const
{
    return !_pData;
}


/// *************************************************************************
/// <summary>
/// Get the data used to create the control.
/// </summary>
/// *************************************************************************
const CControlData * iControl::GetData() const
{
    return _pData;
}


/// *************************************************************************
/// <summary>
/// Update AGK with the control's current position.
/// </summary>
/// *************************************************************************
void iControl::ApplyPosition()
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
/// Update AGK with the control's current rotation.
/// </summary>
/// *************************************************************************
void iControl::ApplyRotation()
{
    _rotation %= 360;

    if( _pParent )
        agk::SetSpriteAngle( _id, _pParent->GetWorldRot().z + _rotation.z );
    else
        agk::SetSpriteAngle( _id, _rotation.z );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the control's current scale.
/// </summary>
/// *************************************************************************
void iControl::ApplyScale()
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
/// Update AGK with the control's current color.
/// </summary>
/// *************************************************************************
void iControl::ApplyColor()
{
    // Does nothing. Color is only for child inheritance purposes.
}


/// *************************************************************************
/// <summary>
/// Update AGK with the control's current visibility.
/// </summary>
/// *************************************************************************
void iControl::ApplyVisibility()
{
    // Does nothing. Visibility is only for child inheritance purposes.
}


/// *************************************************************************
/// <summary>
/// Get the current position set in AGK.
/// </summary>
/// *************************************************************************
CVector3<float> iControl::GetWorldPos() const
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
CVector3<float> iControl::GetWorldRot() const
{
    return CVector3<float>( 0, 0, agk::GetSpriteAngle( _id ) );
}


/// *************************************************************************
/// <summary>
/// Get the current size set in AGK.
/// </summary>
/// *************************************************************************
CVector3<float> iControl::GetWorldSize() const
{
    return CVector3<float>( agk::GetSpriteWidth( _id ),
                            agk::GetSpriteHeight( _id ) );
}


/// *************************************************************************
/// <summary>
/// Update the control's size using the scale.
/// </summary>
/// *************************************************************************
void iControl::UpdateSize()
{
    _size = _pData->GetSize() * _scale;
}


/// *************************************************************************
/// <summary>
/// Update the control's scale using the size.
/// </summary>
/// *************************************************************************
void iControl::UpdateScale()
{
    _scale = _size / _pData->GetSize();
}


/// *************************************************************************
/// <summary>
/// Get the control's visibility.
/// </summary>
/// *************************************************************************
bool iControl::IsVisible() const
{
    if( _pParent )
        return _pParent->IsVisible() && _visible;

    return _visible;
}


/// *************************************************************************
/// <summary>
/// Set the control's alignment.
/// </summary>
/// *************************************************************************
void iControl::SetAlignment( const CBitmask<uint> & alignment )
{
    _alignment = alignment;
}


/// *************************************************************************
/// <summary>
/// Get the control's alignment.
/// </summary>
/// *************************************************************************
CBitmask<uint> iControl::GetAlignment() const
{
    return _alignment;
}


/// *************************************************************************
/// <summary>
/// Reset the control's position using its previous position.
/// </summary>
/// *************************************************************************
void iControl::Reposition()
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
/// Get the control type.
/// </summary>
/// *************************************************************************
EControlType iControl::GetControlType() const
{
    return _controlType;
}


/// *************************************************************************
/// <summary>
/// Set the control's state.
/// </summary>
/// *************************************************************************
void iControl::SetState( EControlState state )
{
    switch( state )
    {
    case NDefs::ECS_DISABLED:
        Play( "disable", EST_FINISH );
        break;
    case NDefs::ECS_INACTIVE:
        Play( "inactive", EST_FINISH );
        break;
    case NDefs::ECS_ACTIVE:
        Play( "active", EST_FINISH );
        break;
    case NDefs::ECS_PRESSED:
        Play( "pressed", EST_FINISH );
        break;
    case NDefs::ECS_RELEASED:
        Play( "released", EST_FINISH );
        break;
    case NDefs::ECS_TRANSITION_IN:
        Play( "transition in", EST_FINISH );
        break;
    case NDefs::ECS_TRANSITION_OUT:
        Play( "transition out", EST_FINISH );
        break;
    }

    _state = state;
}


/// *************************************************************************
/// <summary>
/// Get the control's state.
/// </summary>
/// *************************************************************************
EControlState iControl::GetState() const
{
    return _state;
}


/// *************************************************************************
/// <summary>
/// Play an animation. 
/// </summary>
/// <param name="name"> Name of the animation to play. </param>
/// <param name="stopType"> How to end any conflicting animations. </param>
/// *************************************************************************
void iControl::Play( const string & name, EStopType stopType )
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
void iControl::Stop( NDefs::EStopType stopType )
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
void iControl::Stop( const std::string & name, NDefs::EStopType stopType )
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
bool iControl::IsPlaying( bool includePaused )
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
bool iControl::IsPlaying( const std::string & name, bool includePaused )
{
    if( iObject::IsPlaying( name, includePaused ) )
        return true;

    for( auto pSprite : _pSpriteList )
        if( pSprite->IsPlaying( name, includePaused ) )
            return true;

    return false;
}
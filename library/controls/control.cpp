// Physical component dependency
#include "control.h"

// Game lib dependencies
#include <agk.h>
#include <common\vector2.h>
#include <utilities\mathfunc.h>

using namespace std;
using namespace NDefs;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CControl::CControl()
{
    _type = EOT_CONTROL;
}

/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CControl::~CControl()
{
    Clear();
}


/// *************************************************************************
/// <summary>
/// Delete the dummy sprite that belongs to the AGK id.
/// </summary>
/// *************************************************************************
void CControl::DeleteObject()
{
    CSprite2D::DeleteObject();

    _pSpriteList.clear();
    _state = ECS_DISABLED;
    _alignment = EA_CENTER;
}


/// *************************************************************************
/// <summary>
/// Update AGK with the control's current color.
/// </summary>
/// *************************************************************************
void CControl::ApplyColor()
{
    // Does nothing. Color is only for child inheritance purposes.
}


/// *************************************************************************
/// <summary>
/// Get the control type.
/// </summary>
/// *************************************************************************
EControlType CControl::GetControlType() const
{
    return _controlType;
}


/// *************************************************************************
/// <summary>
/// Set the control's state.
/// </summary>
/// *************************************************************************
void CControl::SetState( EControlState state )
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
EControlState CControl::GetState() const
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
void CControl::Play( const string & name, EStopType stopType )
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
void CControl::Stop( NDefs::EStopType stopType )
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
void CControl::Stop( const std::string & name, NDefs::EStopType stopType )
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
bool CControl::IsPlaying( bool includePaused )
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
bool CControl::IsPlaying( const std::string & name, bool includePaused )
{
    if( iObject::IsPlaying( name, includePaused ) )
        return true;

    for( auto pSprite : _pSpriteList )
        if( pSprite->IsPlaying( name, includePaused ) )
            return true;

    return false;
}
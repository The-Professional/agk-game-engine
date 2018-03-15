// Physical component dependency
#include "control.h"

// Game lib dependencies
#include <agk.h>
#include <common\vector2.h>
#include <utilities\mathfunc.h>

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
    if( _id > 0 )
    {
        agk::DeleteSprite( _id );
        _id = 0;
    }

    _pSpriteList.clear();
    _state = ECS_DISABLED;
}


/// *************************************************************************
/// <summary>
/// Update AGK with the control's current position.
/// </summary>
/// *************************************************************************
void CControl::ApplyPosition( const CVector3 & position )
{
    agk::SetSpritePosition( _id, position.x, position.y );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the control's current rotation.
/// </summary>
/// *************************************************************************
void CControl::ApplyRotation( const CVector3 & rotation )
{
    // This doesn't do anything.
}


/// *************************************************************************
/// <summary>
/// Update AGK with the control's current size.
/// </summary>
/// *************************************************************************
void CControl::ApplySize( const CVector3 & size )
{
    // This doesn't do anything.
}


/// *************************************************************************
/// <summary>
/// Get the current position set in AGK.
/// </summary>
/// *************************************************************************
CVector3 CControl::GetWorldPos() const
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
CVector3 CControl::GetWorldRot() const
{
    return CVector3( 0, 0, agk::GetSpriteAngle( _id ) );
}


/// *************************************************************************
/// <summary>
/// Get the current size set in AGK.
/// </summary>
/// *************************************************************************
CVector3 CControl::GetWorldSize() const
{
    return CVector3( agk::GetSpriteWidth( _id ),
                     agk::GetSpriteHeight( _id ) );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the control's current color.
/// </summary>
/// *************************************************************************
void CControl::ApplyColor( const CColor & color )
{
    for( auto pSprite : _pSpriteList )
        pSprite->SetColor( color );
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
        for( auto pSprite : _pSpriteList )
            pSprite->Play( "disable", EST_FINISH );
        break;
    case NDefs::ECS_INACTIVE:
        for( auto pSprite : _pSpriteList )
            pSprite->Play( "inactive", EST_FINISH );
        break;
    case NDefs::ECS_ACTIVE:
        for( auto pSprite : _pSpriteList )
            pSprite->Play( "active", EST_FINISH );
        break;
    case NDefs::ECS_PRESSED:
        for( auto pSprite : _pSpriteList )
            pSprite->Play( "pressed", EST_FINISH );
        break;
    case NDefs::ECS_RELEASED:
        for( auto pSprite : _pSpriteList )
            pSprite->Play( "released", EST_FINISH );
        break;
    case NDefs::ECS_TRANSITION_IN:
        for( auto pSprite : _pSpriteList )
            pSprite->Play( "transition in", EST_FINISH );
        break;
    case NDefs::ECS_TRANSITION_OUT:
        for( auto pSprite : _pSpriteList )
            pSprite->Play( "transition out", EST_FINISH );
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
/// Reset the sprite's position using its previous position.
/// </summary>
/// *************************************************************************
void CControl::Reposition()
{
    NMathFunc::AlignPosition( _alignment, _position );
    agk::SetSpritePosition( _id, _position.x, _position.y );
}
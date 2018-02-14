// Physical dependency
#include "tween.h"

// Game lib dependencies
#include <agk.h>
#include <common\iobject.h>
#include <common\vector3.h>
#include <utilities\exceptionhandling.h>
#include <managers\animationmanager.h>

// Standard lib dependencies
#include <fstream>

using namespace NDefs;
using namespace std;
using namespace nlohmann;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CTween::CTween()
{
}

/// <summary> 
/// Initialize the tween.
/// </summary>
/// <param name="pObject"> The object this animation is for. </param>
/// <param name="iter"> JSON iterator into where. </param>
CTween::CTween( iObject * pObject, json::const_iterator iter )
{
    Init( pObject, iter );
}


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CTween::~CTween()
{
    Clear();
}


/// *************************************************************************
/// <summary> 
/// Clear the tween data.
/// </summary>
/// *************************************************************************
void CTween::Clear()
{
    _pObject = nullptr;

    if( _id )
        agk::DeleteTween( _id );
}


/// *************************************************************************
/// <summary> 
/// Initialize the tween animation.
/// </summary>
/// <param name="pObject"> The object this animation is for. </param>
/// <param name="iter"> JSON iterator to a tween animation. </param>
/// *************************************************************************
void CTween::Init( iObject * pObject, json::const_iterator iter )
{
    Clear();

    _pObject = pObject;

    float duration = 0;
    NParseHelper::GetFloat( iter, "duration", duration );

    // Create the tween in AGK.
    switch( _pObject->GetType() )
    {
    case EOT_SPRITE_3D:
        _id = agk::CreateTweenObject( duration );
        break;
    case EOT_SPRITE_2D:
        _id = agk::CreateTweenSprite( duration );
        break;
    case EOT_TEXT_SPRITE:
        _id = agk::CreateTweenText( duration );
        break;
    }

    AddPositionTween( iter );
    AddRotationTween( iter );
    AddSizeTween( iter );
    AddColorTween( iter );
}


/// *************************************************************************
/// <summary> 
/// Add a translation tween to the animation.
/// </summary>
/// <param name="iter"> JSON iterator to a translation. </param>
/// *************************************************************************
void CTween::AddPositionTween( json::const_iterator iter )
{
    auto posIter = iter->find( "position" );
    if( posIter != iter->end() )
    {
        int interpolation = GetInterpolation( posIter );

        float end = 0;
        if( NParseHelper::GetFloat( posIter, "ex", end ) )
        {
            float start = _pObject->GetPos().x;
            NParseHelper::GetFloat( posIter, "sx", start );

            SetTween( ETT_POSITION, EAVT_X, start, end, interpolation );
        }

        if( NParseHelper::GetFloat( posIter, "ey", end ) )
        {
            float start = _pObject->GetPos().y;
            NParseHelper::GetFloat( posIter, "sy", start );

            SetTween( ETT_POSITION, EAVT_Y, start, end, interpolation );
        }

        if( NParseHelper::GetFloat( posIter, "ez", end ) )
        {
            float start = _pObject->GetPos().z;
            NParseHelper::GetFloat( posIter, "sz", start );

            SetTween( ETT_POSITION, EAVT_Z, start, end, interpolation );
        }
    }
}


/// *************************************************************************
/// <summary> 
/// Add a rotation tween to the animation.
/// </summary>
/// <param name="iter"> JSON iterator to a rotation. </param>
/// *************************************************************************
void CTween::AddRotationTween( json::const_iterator iter )
{
    auto rotIter = iter->find( "rotation" );
    if( rotIter != iter->end() )
    {
        int interpolation = GetInterpolation( rotIter );

        float end = 0;
        if( NParseHelper::GetFloat( rotIter, "ex", end ) )
        {
            float start = _pObject->GetRot().x;
            NParseHelper::GetFloat( rotIter, "sx", start );

            SetTween( ETT_ROTATION, EAVT_X, start, end, interpolation );
        }

        if( NParseHelper::GetFloat( rotIter, "ey", end ) )
        {
            float start = _pObject->GetRot().y;
            NParseHelper::GetFloat( rotIter, "sy", start );

            SetTween( ETT_ROTATION, EAVT_Y, start, end, interpolation );
        }

        if( NParseHelper::GetFloat( rotIter, "ez", end ) )
        {
            float start = _pObject->GetRot().z;
            NParseHelper::GetFloat( rotIter, "sz", start );

            SetTween( ETT_ROTATION, EAVT_Z, start, end, interpolation );
        }
    }
}


/// *************************************************************************
/// <summary> 
/// Add a size tween to the animation.
/// </summary>
/// <param name="iter"> JSON iterator to a size. </param>
/// *************************************************************************
void CTween::AddSizeTween( json::const_iterator iter )
{
    auto sizeIter = iter->find( "size" );
    if( sizeIter != iter->end() )
    {
        int interpolation = GetInterpolation( sizeIter );

        float end = 0;
        if( NParseHelper::GetFloat( sizeIter, "ew", end ) )
        {
            float start = _pObject->GetSize().w;
            NParseHelper::GetFloat( sizeIter, "sw", start );

            SetTween( ETT_SIZE, EAVT_W, start, end, interpolation );
        }

        if( NParseHelper::GetFloat( sizeIter, "eh", end ) )
        {
            float start = _pObject->GetSize().h;
            NParseHelper::GetFloat( sizeIter, "sh", start );

            SetTween( ETT_SIZE, EAVT_H, start, end, interpolation );
        }

        if( NParseHelper::GetFloat( sizeIter, "ed", end ) )
        {
            float start = _pObject->GetSize().d;
            NParseHelper::GetFloat( sizeIter, "sd", start );

            SetTween( ETT_SIZE, EAVT_D, start, end, interpolation );
        }
    }
}


/// *************************************************************************
/// <summary> 
/// Add a color tween to the animation.
/// </summary>
/// <param name="iter"> JSON iterator to a color. </param>
/// *************************************************************************
void CTween::AddColorTween( json::const_iterator iter )
{
    auto colorIter = iter->find( "color" );
    if( colorIter != iter->end() )
    {
        int interpolation = GetInterpolation( colorIter );

        float end = 0;
        if( NParseHelper::GetFloat( colorIter, "er", end ) )
        {
            float start = (float)_pObject->GetColor().r;
            NParseHelper::GetFloat( colorIter, "sr", start );

            SetTween( ETT_COLOR, EAVT_R, start, end, interpolation );
        }

        if( NParseHelper::GetFloat( colorIter, "eg", end ) )
        {
            float start = (float)_pObject->GetColor().g;
            NParseHelper::GetFloat( colorIter, "sg", start );

            SetTween( ETT_COLOR, EAVT_G, start, end, interpolation );
        }

        if( NParseHelper::GetFloat( colorIter, "eb", end ) )
        {
            float start = (float)_pObject->GetColor().b;
            NParseHelper::GetFloat( colorIter, "sb", start );

            SetTween( ETT_COLOR, EAVT_B, start, end, interpolation );
        }
    }
}


/// *************************************************************************
/// <summary> 
/// Get the interpolation of the tween.
/// </summary>
/// <param name="iter"> JSON iterator to an interpolation mode. </param>
/// *************************************************************************
int CTween::GetInterpolation( nlohmann::json::const_iterator iter )
{
    string interpolation;
    if( NParseHelper::GetString( iter, "interpolation", interpolation ) )
        return CAnimationManager::Instance().GetInterpolation( interpolation );

    return agk::TweenLinear();
}


/// *************************************************************************
/// <summary> 
/// Set a tween value.
/// </summary>
/// <param name="start"> The initial value of the tween. </param>
/// <param name="end"> The resultant value of the tween. </param>
/// <param name="interpolation"> The interpolation method of the tween. </param>
/// *************************************************************************
void CTween::SetTween( uint animationType, EAnimationValueType vType, float start, float end, int interpolation )
{
    switch( _pObject->GetType() )
    {
    case EOT_SPRITE_3D:
        switch( animationType )
        {
        case ETT_POSITION:
            switch( vType )
            {
            case EAVT_X:
                agk::SetTweenObjectX( _id, start, end, interpolation );
                break;
            case EAVT_Y:
                agk::SetTweenObjectY( _id, start, end, interpolation );
                break;
            case EAVT_Z:
                agk::SetTweenObjectZ( _id, start, end, interpolation );
                break;
            }
            break;
        case ETT_ROTATION:
            switch( vType )
            {
            case EAVT_X:
                agk::SetTweenObjectAngleX( _id, start, end, interpolation );
                break;
            case EAVT_Y:
                agk::SetTweenObjectAngleY( _id, start, end, interpolation );
                break;
            case EAVT_Z:
                agk::SetTweenObjectAngleZ( _id, start, end, interpolation );
                break;
            }
            break;
        case ETT_SIZE:
            switch( vType )
            {
            case EAVT_W:
                break;
            case EAVT_H:
                break;
            case EAVT_D:
                break;
            }
            break;
        case ETT_COLOR:
            switch( vType )
            {
            case EAVT_R:
                agk::SetTweenObjectRed( _id, (int)start, (int)end, interpolation );
                break;
            case EAVT_G:
                agk::SetTweenObjectGreen( _id, (int)start, (int)end, interpolation );
                break;
            case EAVT_B:
                agk::SetTweenObjectBlue( _id, (int)start, (int)end, interpolation );
                break;
            case EAVT_A:
                agk::SetTweenObjectAlpha( _id, (int)start, (int)end, interpolation );
                break;
            }
            break;
        }
        break;
    case EOT_SPRITE_2D:
        switch( animationType )
        {
        case ETT_POSITION:
            switch( vType )
            {
            case EAVT_X:
                agk::SetTweenSpriteX( _id, start, end, interpolation );
                break;
            case EAVT_Y:
                agk::SetTweenSpriteY( _id, start, end, interpolation );
                break;
            }
            break;
        case ETT_ROTATION:
            agk::SetTweenSpriteAngle( _id, start, end, interpolation );
            break;
        case ETT_SIZE:
            switch( vType )
            {
            case EAVT_W:
                agk::SetTweenSpriteSizeX( _id, start, end, interpolation );
                break;
            case EAVT_H:
                agk::SetTweenSpriteSizeY( _id, start, end, interpolation );
                break;
            }
            break;
        case ETT_COLOR:
            switch( vType )
            {
            case NDefs::EAVT_R:
                agk::SetTweenSpriteRed( _id, (int)start, (int)end, interpolation );
                break;
            case NDefs::EAVT_G:
                agk::SetTweenSpriteGreen( _id, (int)start, (int)end, interpolation );
                break;
            case NDefs::EAVT_B:
                agk::SetTweenSpriteBlue( _id, (int)start, (int)end, interpolation );
                break;
            case NDefs::EAVT_A:
                agk::SetTweenSpriteAlpha( _id, (int)start, (int)end, interpolation );
                break;
            }
            break;
        }
        break;
    case EOT_TEXT_SPRITE:
        switch( animationType )
        {
        case ETT_POSITION:
            switch( vType )
            {
            case EAVT_X:
                agk::SetTweenTextX( _id, start, end, interpolation );
                break;
            case EAVT_Y:
                agk::SetTweenTextY( _id, start, end, interpolation );
                break;
            }
            break;
        case ETT_ROTATION:
            agk::SetTweenTextAngle( _id, start, end, interpolation );
            break;
        case ETT_SIZE:
            agk::SetTweenTextSize( _id, start, end, interpolation );
            break;
        case ETT_COLOR:
            switch( vType )
            {
            case NDefs::EAVT_R:
                agk::SetTweenTextRed( _id, (int)start, (int)end, interpolation );
                break;
            case NDefs::EAVT_G:
                agk::SetTweenTextGreen( _id, (int)start, (int)end, interpolation );
                break;
            case NDefs::EAVT_B:
                agk::SetTweenTextBlue( _id, (int)start, (int)end, interpolation );
                break;
            case NDefs::EAVT_A:
                agk::SetTweenTextAlpha( _id, (int)start, (int)end, interpolation );
                break;
            }
            break;
        }
        break;
    }
}
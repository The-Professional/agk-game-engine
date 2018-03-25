// Physical component dependency
#include "inputmapping.h"

// Game lib dependencies
#include <agk.h>

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CInputMapping::CInputMapping()
{
}

/// <summary> 
/// Constructor
/// </summary>
CInputMapping::CInputMapping( NDefs::EInputDevice device, int inputId )
{
    AddInput( device, inputId );
}

/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CInputMapping::~CInputMapping()
{
}


/// *************************************************************************
/// <summary> 
/// Add an input mapping for the given device.
/// </summary>
/// *************************************************************************
void CInputMapping::AddInput( NDefs::EInputDevice device, int inputId )
{
    switch( device )
    {
    case NDefs::EID_MOUSE:
        _mouse.push_back( inputId );
        break;

    case NDefs::EID_KEYBOARD:
        _keyboard.push_back( inputId );
        break;

    case NDefs::EID_GAMEPAD:
        _gamepad.push_back( inputId );
        break;
    }
}


/// *************************************************************************
/// <summary> 
/// Remove an input mapping for the given device.
/// </summary>
/// *************************************************************************
void CInputMapping::RemoveInput( NDefs::EInputDevice device, int inputId )
{
    std::vector<int>::iterator iter;
    switch( device )
    {
    case NDefs::EID_MOUSE:
        iter = std::find( _mouse.begin(), _mouse.end(), inputId );
        if( iter != _mouse.end() )
            _mouse.erase( iter );
        break;

    case NDefs::EID_KEYBOARD:
        iter = std::find( _keyboard.begin(), _keyboard.end(), inputId );
        if( iter != _keyboard.end() )
            _keyboard.erase( iter );
        break;

    case NDefs::EID_GAMEPAD:
        iter = std::find( _gamepad.begin(), _gamepad.end(), inputId );
        if( iter != _gamepad.end() )
            _gamepad.erase( iter );
        break;
    }
}


/// *************************************************************************
/// <summary> 
/// Whether or not any device inputs were pressed down on this frame.
/// Hold inputs are ignored.
/// </summary>
/// *************************************************************************
bool CInputMapping::IsPressed( uint gamepadId ) const
{
    if( agk::GetMouseExists() )
    {
        for( int i = 0; i < _mouse.size(); ++i )
            switch( _mouse[i] )
            {
            case LEFT_MOUSE:
                if( agk::GetRawMouseLeftPressed() )
                    return true;
                break;
            case RIGHT_MOUSE:
                if( agk::GetRawMouseRightPressed() )
                    return true;
                break;
            case MIDDLE_MOUSE:
                if( agk::GetRawMouseMiddlePressed() )
                    return true;
                break;
            }
    }

    if( agk::GetKeyboardExists() )
    {
        for( int i = 0; i < _keyboard.size(); ++i )
            if( agk::GetRawKeyPressed( _keyboard[i] ) )
                return true;
    }

    if( agk::GetJoystickExists() )
    {
        for( int i = 0; i < _gamepad.size(); ++i )
            if( agk::GetRawJoystickButtonPressed( gamepadId, _gamepad[i] ) )
                return true;
    }

    return false;
}


/// *************************************************************************
/// <summary> 
/// Whether or not any device inputs were released on this frame.
/// Inactivity is ignored.
/// </summary>
/// *************************************************************************
bool CInputMapping::IsReleased( uint gamepadId ) const
{
    if( agk::GetMouseExists() )
    {
        for( int i = 0; i < _mouse.size(); ++i )
            switch( _mouse[i] )
            {
            case LEFT_MOUSE:
                if( agk::GetRawMouseLeftReleased() )
                    return true;
                break;
            case RIGHT_MOUSE:
                if( agk::GetRawMouseRightReleased() )
                    return true;
                break;
            case MIDDLE_MOUSE:
                if( agk::GetRawMouseMiddleReleased() )
                    return true;
                break;
            }
    }

    if( agk::GetKeyboardExists() )
    {
        for( int i = 0; i < _keyboard.size(); ++i )
            if( agk::GetRawKeyReleased( _keyboard[i] ) )
                return true;
    }

    if( agk::GetJoystickExists() )
    {
        for( int i = 0; i < _gamepad.size(); ++i )
            if( agk::GetRawJoystickButtonReleased( gamepadId, _gamepad[i] ) )
                return true;
    }

    return false;
}


/// *************************************************************************
/// <summary> 
/// Whether or not any device is being held down. Hold inputs are included.
/// </summary>
/// *************************************************************************
bool CInputMapping::IsDown( uint gamepadId ) const
{
    if( agk::GetMouseExists() )
    {
        for( int i = 0; i < _mouse.size(); ++i )
            switch( _mouse[i] )
            {
            case LEFT_MOUSE:
                if( agk::GetRawMouseLeftState() )
                    return true;
                break;
            case RIGHT_MOUSE:
                if( agk::GetRawMouseRightState() )
                    return true;
                break;
            case MIDDLE_MOUSE:
                if( agk::GetRawMouseMiddleState() )
                    return true;
                break;
            }
    }

    if( agk::GetKeyboardExists() )
    {
        for( int i = 0; i < _keyboard.size(); ++i )
            if( agk::GetRawKeyState( _keyboard[i] ) )
                return true;
    }

    if( agk::GetJoystickExists() )
    {
        for( int i = 0; i < _gamepad.size(); ++i )
            if( agk::GetRawJoystickButtonState( gamepadId, _gamepad[i] ) )
                return true;
    }

    return false;
}
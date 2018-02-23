// Physical component dependency
#include "inputstate.h"

// Game lib dependencies
#include <utilities\exceptionhandling.h>

using namespace std;


/// *************************************************************************
/// <summary> 
/// Add an input for a given action and device.
/// </summary>
/// *************************************************************************
void CInputState::AddInput( const string & action, NDefs::EInputDevice device, int inputId )
{
    auto iter = _actionList.find( action );
    if( iter != _actionList.end() )
        iter->second.AddInput( device, inputId );
    else
        _actionList.emplace( action, CInputMapping( device, inputId ) );
}


/// *************************************************************************
/// <summary> 
/// Remove an input for a given action and device.
/// </summary>
/// *************************************************************************
void CInputState::RemoveInput( const string & action, NDefs::EInputDevice device, int inputId )
{
    auto iter = _actionList.find( action );
    if( iter != _actionList.end() )
        iter->second.RemoveInput( device, inputId );
}


/// *************************************************************************
/// <summary> 
/// Add an action to the action list.
/// </summary>
/// *************************************************************************
void CInputState::AddAction( const std::string & action )
{
    auto iter = _actionList.find( action );
    if( iter == _actionList.end() )
        _actionList.emplace( action, CInputMapping() );
}

/// <summary> 
/// Add an action to the action list.
/// </summary>
void CInputState::AddAction( const std::string & action, const CInputMapping & mapping )
{
    auto iter = _actionList.find( action );
    if( iter == _actionList.end() )
        _actionList.emplace( action, mapping );
}


/// *************************************************************************
/// <summary> 
/// Remove an action from the action list.
/// </summary>
/// *************************************************************************
void CInputState::RemoveAction( const std::string & action )
{
    auto iter = _actionList.find( action );
    if( iter != _actionList.end() )
        _actionList.erase( iter );
}


/// *************************************************************************
/// <summary> 
/// Get the input mapping for the provided action.
/// </summary>
/// *************************************************************************
const CInputMapping & CInputState::operator [] ( const std::string & action )
{
    auto iter = _actionList.find( action );
    if( iter != _actionList.end() )
        return iter->second;


    throw NExcept::CCriticalException( "Error",
                                       "CInputState::operator []",
                                       "Failed to retrieve action '" + action + "'." );
}

/// <summary> 
/// Get the input mapping for the provided action.
/// </summary>
const CInputMapping & CInputState::operator [] ( const std::string & action ) const
{
    auto iter = _actionList.find( action );
    if( iter != _actionList.end() )
        return iter->second;


    throw NExcept::CCriticalException( "Error",
                                       "CInputState::operator []",
                                       "Failed to retrieve action '" + action + "'." );
}


/// *************************************************************************
/// <summary> 
/// Whether or not any device inputs were pressed down on this frame.
/// Hold inputs are ignored.
/// </summary>
/// *************************************************************************
bool CInputState::IsPressed( const std::string & action, uint gamepadId ) const
{
    auto iter = _actionList.find( action );
    if( iter != _actionList.end() )
        return iter->second.IsPressed( gamepadId );

    return false;
}


/// *************************************************************************
/// <summary> 
/// Whether or not any device inputs were released on this frame.
/// Inactivity is ignored.
/// </summary>
/// *************************************************************************
bool CInputState::IsReleased( const std::string & action, uint gamepadId ) const
{
    auto iter = _actionList.find( action );
    if( iter != _actionList.end() )
        return iter->second.IsReleased( gamepadId );

    return false;
}


/// *************************************************************************
/// <summary> 
/// Whether or not any device is being held down. Hold inputs are included.
/// </summary>
/// *************************************************************************
bool CInputState::IsDown( const std::string & action, uint gamepadId ) const
{
    auto iter = _actionList.find( action );
    if( iter != _actionList.end() )
        return iter->second.IsDown( gamepadId );

    return false;
}
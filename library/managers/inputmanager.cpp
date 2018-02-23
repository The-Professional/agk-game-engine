// Physical component dependency
#include "inputmanager.h"

// Game lib dependencies
#include <agk.h>
#include <utilities\jsonparsehelper.h>
#include <utilities\exceptionhandling.h>

// Standard lib dependencies
#include <fstream>

using namespace std;
using namespace nlohmann;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CInputManager::CInputManager()
{
    _mouseIdList.emplace( "left",   CInputMapping::LEFT_MOUSE );
    _mouseIdList.emplace( "right",  CInputMapping::RIGHT_MOUSE );
    _mouseIdList.emplace( "middle", CInputMapping::MIDDLE_MOUSE );

    _keyIdList.emplace( "back",      8 );
    _keyIdList.emplace( "tab",       9 );
    _keyIdList.emplace( "enter",    13 );
    _keyIdList.emplace( "shift",    16 );
    _keyIdList.emplace( "control",  17 );
    _keyIdList.emplace( "escape",   27 );
    _keyIdList.emplace( "space",    32 );
    _keyIdList.emplace( "pageup",   33 );
    _keyIdList.emplace( "pagedown", 34 );
    _keyIdList.emplace( "end",      35 );
    _keyIdList.emplace( "home",     36 );
    _keyIdList.emplace( "left",     37 );
    _keyIdList.emplace( "up",       38 );
    _keyIdList.emplace( "right",    39 );
    _keyIdList.emplace( "down",     40 );
    _keyIdList.emplace( "insert",   45 );
    _keyIdList.emplace( "delete",   46 );

    _keyIdList.emplace( "0", 48 );
    _keyIdList.emplace( "1", 49 );
    _keyIdList.emplace( "2", 50 );
    _keyIdList.emplace( "3", 51 );
    _keyIdList.emplace( "4", 52 );
    _keyIdList.emplace( "5", 53 );
    _keyIdList.emplace( "6", 54 );
    _keyIdList.emplace( "7", 55 );
    _keyIdList.emplace( "8", 56 );
    _keyIdList.emplace( "9", 57 );

    _keyIdList.emplace( "a", 65 );
    _keyIdList.emplace( "b", 66 );
    _keyIdList.emplace( "c", 67 );
    _keyIdList.emplace( "d", 68 );
    _keyIdList.emplace( "e", 69 );
    _keyIdList.emplace( "f", 70 );
    _keyIdList.emplace( "g", 71 );
    _keyIdList.emplace( "h", 72 );
    _keyIdList.emplace( "i", 73 );
    _keyIdList.emplace( "j", 74 );
    _keyIdList.emplace( "k", 75 );
    _keyIdList.emplace( "l", 76 );
    _keyIdList.emplace( "m", 77 );
    _keyIdList.emplace( "n", 78 );
    _keyIdList.emplace( "o", 79 );
    _keyIdList.emplace( "p", 80 );
    _keyIdList.emplace( "q", 81 );
    _keyIdList.emplace( "r", 82 );
    _keyIdList.emplace( "s", 83 );
    _keyIdList.emplace( "t", 84 );
    _keyIdList.emplace( "u", 85 );
    _keyIdList.emplace( "v", 86 );
    _keyIdList.emplace( "w", 87 );
    _keyIdList.emplace( "x", 88 );
    _keyIdList.emplace( "y", 89 );
    _keyIdList.emplace( "z", 90 );

    _keyIdList.emplace( "f1", 112 );
    _keyIdList.emplace( "f2", 113 );
    _keyIdList.emplace( "f3", 114 );
    _keyIdList.emplace( "f4", 115 );
    _keyIdList.emplace( "f5", 116 );
    _keyIdList.emplace( "f6", 117 );
    _keyIdList.emplace( "f7", 118 );
    _keyIdList.emplace( "f8", 119 );

    _keyIdList.emplace( ";",  186 );
    _keyIdList.emplace( "=",  187 );
    _keyIdList.emplace( ",",  188 );
    _keyIdList.emplace( "-",  189 );
    _keyIdList.emplace( ".",  190 );
    _keyIdList.emplace( "/",  191 );
    _keyIdList.emplace( "'",  192 );
    _keyIdList.emplace( "[",  219 );
    _keyIdList.emplace( "\\", 220 );
    _keyIdList.emplace( "]",  221 );
    _keyIdList.emplace( "#",  222 );
    _keyIdList.emplace( "`",  223 );
}


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CInputManager::~CInputManager()
{
    Clear();
}


/// *************************************************************************
/// <summary> 
/// Set the path to the input map file.
/// </summary>
/// *************************************************************************
void CInputManager::SetPath( const std::string & path )
{
    _path = path;
}


/// *************************************************************************
/// <summary> 
/// Read the file and compile the list of resource files.
/// </summary>
/// *************************************************************************
void CInputManager::LoadInputMap()
{
    try
    {
        // Load the settings file.
        ifstream ifile( _path );

        // Parse the content into a json object.
        json j;
        ifile >> j;

        auto inputStateListIter = j.find( "inputStateList" );
        if( inputStateListIter != j.end() )
        {
            // Loop through each input state.
            auto stateIter = inputStateListIter->begin();
            while( stateIter != inputStateListIter->end() )
            {
                string name;
                NParseHelper::GetString( stateIter, "name", name );

                CInputState state;
                NParseHelper::GetInputState( stateIter, state );

                _inputStateList.emplace( name, state );
                ++stateIter;
            }
        }
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CInputManager::LoadInputMap()",
                                           "Failed to open '" + _path + "'.", e );
    }
}


/// *************************************************************************
/// <summary> 
/// Clear all input mapping.
/// </summary>
/// *************************************************************************
void CInputManager::Clear()
{

}


/// *************************************************************************
/// <summary> 
/// Get the id of the passed in input and device.
/// </summary>
/// <param name"device"> Type of device we want the input id for. </param>
/// <param name"input"> Name of the button or key we want the id for. </param>
/// *************************************************************************
int CInputManager::GetInputID( NDefs::EInputDevice device, const std::string & input )
{
    map<string, int>::iterator iter;

    switch( device )
    {
    case NDefs::EID_MOUSE:
        iter = _mouseIdList.find( input );
        if( iter != _mouseIdList.end() )
            return iter->second;
        break;

    case NDefs::EID_KEYBOARD:
        iter = _keyIdList.find( input );
        if( iter != _keyIdList.end() )
            return iter->second;
        break;
    }

    // And input id should always be found.
    throw NExcept::CCriticalException( "Error",
                                       "CInputManager::GetInputID()",
                                       "There is no input '" + input + "' for the device '" + to_string(device) + "'." );

    return -1;
}


/// *************************************************************************
/// <summary> 
/// Whether or not an input is pressed this frame for the passed in state and
/// action. Hold inputs are ignored.
/// </summary>
/// <param name"state"> Name of the state the game is in. </param>
/// <param name"action"> Name of the action we're checking. </param>
/// <param name"gamepadId"> The id of the gamepad we're checking. </param>
/// *************************************************************************
bool CInputManager::IsPressed( const std::string & state, const std::string & action, uint gamepadId ) const
{
    auto iter = _inputStateList.find( state );
    if( iter != _inputStateList.end() )
        return iter->second.IsPressed( action, gamepadId );

    return false;
}


/// *************************************************************************
/// <summary> 
/// Whether or not an input is released this frame for the passed in state 
/// and action. Inactivity is ignored.
/// </summary>
/// <param name"state"> Name of the state the game is in. </param>
/// <param name"input"> Name of the action we're checking. </param>
/// <param name"gamepadId"> The id of the gamepad we're checking. </param>
/// *************************************************************************
bool CInputManager::IsReleased( const std::string & state, const std::string & action, uint gamepadId ) const
{
    auto iter = _inputStateList.find( state );
    if( iter != _inputStateList.end() )
        return iter->second.IsReleased( action, gamepadId );

    return false;
}


/// *************************************************************************
/// <summary> 
/// Whether or not an input is pressed down for the passed in state and 
/// action. Hold inputs are included.
/// </summary>
/// <param name"state"> Name of the state the game is in. </param>
/// <param name"input"> Name of the action we're checking. </param>
/// <param name"gamepadId"> The id of the gamepad we're checking. </param>
/// *************************************************************************
bool CInputManager::IsDown( const std::string & state, const std::string & action, uint gamepadId ) const
{
    auto iter = _inputStateList.find( state );
    if( iter != _inputStateList.end() )
        return iter->second.IsDown( action, gamepadId );

    return false;
}
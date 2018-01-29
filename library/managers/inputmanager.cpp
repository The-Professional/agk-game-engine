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
    _mouseIdList.insert( pair<string, int>( "left",   CInputMapping::LEFT_MOUSE ) );
    _mouseIdList.insert( pair<string, int>( "right",  CInputMapping::RIGHT_MOUSE ) );
    _mouseIdList.insert( pair<string, int>( "middle", CInputMapping::MIDDLE_MOUSE ) );

    _keyIdList.insert( pair<string, int>( "back",      8 ) );
    _keyIdList.insert( pair<string, int>( "tab",       9 ) );
    _keyIdList.insert( pair<string, int>( "enter",    13 ) );
    _keyIdList.insert( pair<string, int>( "shift",    16 ) );
    _keyIdList.insert( pair<string, int>( "control",  17 ) );
    _keyIdList.insert( pair<string, int>( "escape",   27 ) );
    _keyIdList.insert( pair<string, int>( "space",    32 ) );
    _keyIdList.insert( pair<string, int>( "pageup",   33 ) );
    _keyIdList.insert( pair<string, int>( "pagedown", 34 ) );
    _keyIdList.insert( pair<string, int>( "end",      35 ) );
    _keyIdList.insert( pair<string, int>( "home",     36 ) );
    _keyIdList.insert( pair<string, int>( "left",     37 ) );
    _keyIdList.insert( pair<string, int>( "up",       38 ) );
    _keyIdList.insert( pair<string, int>( "right",    39 ) );
    _keyIdList.insert( pair<string, int>( "down",     40 ) );
    _keyIdList.insert( pair<string, int>( "insert",   45 ) );
    _keyIdList.insert( pair<string, int>( "delete",   46 ) );

    _keyIdList.insert( pair<string, int>( "0", 48 ) );
    _keyIdList.insert( pair<string, int>( "1", 49 ) );
    _keyIdList.insert( pair<string, int>( "2", 50 ) );
    _keyIdList.insert( pair<string, int>( "3", 51 ) );
    _keyIdList.insert( pair<string, int>( "4", 52 ) );
    _keyIdList.insert( pair<string, int>( "5", 53 ) );
    _keyIdList.insert( pair<string, int>( "6", 54 ) );
    _keyIdList.insert( pair<string, int>( "7", 55 ) );
    _keyIdList.insert( pair<string, int>( "8", 56 ) );
    _keyIdList.insert( pair<string, int>( "9", 57 ) );

    _keyIdList.insert( pair<string, int>( "a", 65 ) );
    _keyIdList.insert( pair<string, int>( "b", 66 ) );
    _keyIdList.insert( pair<string, int>( "c", 67 ) );
    _keyIdList.insert( pair<string, int>( "d", 68 ) );
    _keyIdList.insert( pair<string, int>( "e", 69 ) );
    _keyIdList.insert( pair<string, int>( "f", 70 ) );
    _keyIdList.insert( pair<string, int>( "g", 71 ) );
    _keyIdList.insert( pair<string, int>( "h", 72 ) );
    _keyIdList.insert( pair<string, int>( "i", 73 ) );
    _keyIdList.insert( pair<string, int>( "j", 74 ) );
    _keyIdList.insert( pair<string, int>( "k", 75 ) );
    _keyIdList.insert( pair<string, int>( "l", 76 ) );
    _keyIdList.insert( pair<string, int>( "m", 77 ) );
    _keyIdList.insert( pair<string, int>( "n", 78 ) );
    _keyIdList.insert( pair<string, int>( "o", 79 ) );
    _keyIdList.insert( pair<string, int>( "p", 80 ) );
    _keyIdList.insert( pair<string, int>( "q", 81 ) );
    _keyIdList.insert( pair<string, int>( "r", 82 ) );
    _keyIdList.insert( pair<string, int>( "s", 83 ) );
    _keyIdList.insert( pair<string, int>( "t", 84 ) );
    _keyIdList.insert( pair<string, int>( "u", 85 ) );
    _keyIdList.insert( pair<string, int>( "v", 86 ) );
    _keyIdList.insert( pair<string, int>( "w", 87 ) );
    _keyIdList.insert( pair<string, int>( "x", 88 ) );
    _keyIdList.insert( pair<string, int>( "y", 89 ) );
    _keyIdList.insert( pair<string, int>( "z", 90 ) );

    _keyIdList.insert( pair<string, int>( "f1", 112 ) );
    _keyIdList.insert( pair<string, int>( "f2", 113 ) );
    _keyIdList.insert( pair<string, int>( "f3", 114 ) );
    _keyIdList.insert( pair<string, int>( "f4", 115 ) );
    _keyIdList.insert( pair<string, int>( "f5", 116 ) );
    _keyIdList.insert( pair<string, int>( "f6", 117 ) );
    _keyIdList.insert( pair<string, int>( "f7", 118 ) );
    _keyIdList.insert( pair<string, int>( "f8", 119 ) );

    _keyIdList.insert( pair<string, int>( ";",  186 ) );
    _keyIdList.insert( pair<string, int>( "=",  187 ) );
    _keyIdList.insert( pair<string, int>( ",",  188 ) );
    _keyIdList.insert( pair<string, int>( "-",  189 ) );
    _keyIdList.insert( pair<string, int>( ".",  190 ) );
    _keyIdList.insert( pair<string, int>( "/",  191 ) );
    _keyIdList.insert( pair<string, int>( "'",  192 ) );
    _keyIdList.insert( pair<string, int>( "[",  219 ) );
    _keyIdList.insert( pair<string, int>( "\\", 220 ) );
    _keyIdList.insert( pair<string, int>( "]",  221 ) );
    _keyIdList.insert( pair<string, int>( "#",  222 ) );
    _keyIdList.insert( pair<string, int>( "`",  223 ) );
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
                NParseHelper::GetName( stateIter, name );

                CInputState state;
                NParseHelper::GetInputState( stateIter, state );

                _inputStateList.insert( pair<string, CInputState>( name, state ) );
                ++stateIter;
            }
        }
    }
    catch( NExcept::CCriticalException e )
    {
        throw e;
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
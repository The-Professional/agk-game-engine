#ifndef __input_state_h__
#define __input_state_h__

// Game lib dependencies
#include <common\defs.h>
#include <managers\inputmapping.h>

// Standard lib dependencies
#include <string>
#include <map>


/// *************************************************************************
/// <summary> 
/// Class to the input mappings for the input state. Different states of the
/// game will make different inputs do different things. Knowing these states
/// ahead of time will allow us to know if an actual conflict will occur if
/// the user binds the same button to two different actions.
/// </summary>
/// *************************************************************************
class CInputState
{
public:

    // Add an input for a given action and device.
    void AddInput( const std::string & action, NDefs::EInputDevice device, int inputId );

    // Remove an input for a given action and device.
    void RemoveInput( const std::string & action, NDefs::EInputDevice device, int inputId );

    // Add an action to the action list.
    void AddAction( const std::string & action );
    void AddAction( const std::string & action, const CInputMapping & mapping );

    // Remove an action from the action list.
    void RemoveAction( const std::string & action );

    // Get the input mapping for the provided action.
    const CInputMapping & operator [] ( const std::string & action );
    const CInputMapping & operator [] ( const std::string & action ) const;

    // Whether or not any device inputs were pressed down on this frame.
    // Hold inputs are ignored.
    bool IsPressed( const std::string & action, uint gamepadId = 0 ) const;

    // Whether or not any device inputs were released on this frame.
    // Inactivity is ignored.
    bool IsReleased( const std::string & action, uint gamepadId = 0 ) const;

    // Whether or not any device inputs are pressed down.
    // Hold inputs are included.
    bool IsDown( const std::string & action, uint gamepadId = 0 ) const;

private:
    // Map to hold each kind of action input for the state.
    std::map<const std::string, CInputMapping> _actionList;
};

#endif  // __input_state_h__

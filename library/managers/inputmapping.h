#ifndef __input_mapping_h__
#define __input_mapping_h__

// Game lib dependencies
#include <common\defs.h>

// Standard lib dependencies
#include <vector>

/// *************************************************************************
/// <summary> 
/// Class to hold the mapped inputs for a kind of input.
/// </summary>
/// *************************************************************************
class CInputMapping
{
public:
    enum
    {
        LEFT_MOUSE = 1,
        RIGHT_MOUSE,
        MIDDLE_MOUSE
    };

    CInputMapping();
    CInputMapping( NDefs::EInputDevice device, int inputId );
    ~CInputMapping();

    // Add an input mapping for the given device.
    void AddInput( NDefs::EInputDevice device, int inputId );

    // Remove an input mapping for the given device.
    void RemoveInput( NDefs::EInputDevice device, int inputId );

    // Whether or not any device inputs were pressed down on this frame.
    // Hold inputs are ignored.
    bool IsPressed( uint gamepadId = 0 ) const;

    // Whether or not any device inputs were released on this frame.
    // Inactivity is ignored.
    bool IsReleased( uint gamepadId = 0 ) const;

    // Whether or not any device inputs are pressed down.
    // Hold inputs are included.
    bool IsDown( uint gamepadId = 0 ) const;

private:

    std::vector<int> _mouse;
    std::vector<int> _keyboard;
    std::vector<int> _gamepad;
};

#endif  // __input_mapping_h__

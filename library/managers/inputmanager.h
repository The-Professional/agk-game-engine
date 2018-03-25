#ifndef __input_manager_h__
#define __input_manager_h__

// Game lib dependencies
#include <common\defs.h>
#include <input\inputstate.h>

// Standard lib dependencies
#include <string>
#include <map>


/// *************************************************************************
/// <summary> 
/// Class to hold all mapped inputs.
/// </summary>
/// *************************************************************************
class CInputManager
{
public:
    
    // Get the instance of the singleton class
    static CInputManager & Instance()
    {
        static CInputManager resourceManager;
        return resourceManager;
    }

    // Set the path to the input map file.
    void SetPath( const std::string & path );

    // Read the file and compile the list of resource files.
    void LoadInputMap();

    // Clear all input mapping.
    void Clear();

    // Get the id of the passed in input and device.
    int GetInputID( NDefs::EInputDevice device, const std::string & input );

    // Whether or not an input is pressed this frame for the passed in state and action.
    // Hold inputs are ignored.
    bool IsPressed( const std::string & state, const std::string & action, uint gamepadId = 0 ) const;

    // Whether or not an input is released this frame for the passed in state and action.
    // Inactivity is ignored.
    bool IsReleased( const std::string & state, const std::string & action, uint gamepadId = 0 ) const;

    // Whether or not an input is pressed down for the passed in state and action.
    // Hold inputs are included.
    bool IsDown( const std::string & state, const std::string & action, uint gamepadId = 0 ) const;

private:

    // Constructor
    CInputManager();

    // Destructor
    virtual ~CInputManager();
    
    // Path to the file containing the input mapping.
    std::string _path;

    // A map of keyboard keys and their corresponding ids.
    std::map<const std::string, int> _keyIdList;
    std::map<const std::string, int> _mouseIdList;

    // A map of input states and their input mappings.
    std::map<const std::string, CInputState> _inputStateList;
};

#endif  // __input_manager_h__

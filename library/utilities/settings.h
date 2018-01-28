#ifndef __settings_h__
#define __settings_h__

// Game lib dependencies
#include <common\size.h>
#include <common\defs.h>

// Standard lib dependencies
#include <string>

/// *************************************************************************
/// <summary> 
/// Singleton class containing the game's general settings.
/// </summary>
/// *************************************************************************
class CSettings
{
public:
    // Get the instance of the singleton class
    static CSettings & Instance()
    {
        static CSettings settings;
        return settings;
    }

    // Save the settings file
    void SaveSettings();

    // Set the file path for loading the settings file.
    void SetFilePath( const std::string & filePath );

    // Load settings data from xml file
    void LoadSettings();

    // Apply the settings currently set.
    void ApplySettings();

    // Get the window resolution.
    const CSize & GetResolution() const;

    // If the game is full screen.
    bool IsFullscreen() const;

    // Get the orientation of the game window.
    NDefs::EOrentation GetOrientation() const;

    // If antialias is enabled.
    bool IsAntialias() const;

private:

    // Constructor
    CSettings();

    // Destructor
    virtual ~CSettings();

private:

    // Path to the settings file.
    std::string _filePath;

    // Resolution of the game window.
    CSize _resolution;

    // Whether game is displaying in fullscreen mode or not.
    bool _fullscreen;

    // Orientation of game window.
    NDefs::EOrentation _orientation;

    // If antialiasing is active.
    bool _antialias;
};

#endif  // __settings_h__


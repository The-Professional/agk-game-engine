#ifndef __settings_h__
#define __settings_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\vector2.h>
#include <common\vector4.h>

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
    void SetPath( const std::string & path );

    // Load settings data from xml file
    void LoadSettings();

    // Apply the settings currently set.
    void ApplySettings();

    // Get the window resolution.
    const CVector2 & GetResolution() const;
    const CVector2 & GetVirtualResolution() const;

    // Get the window aspect ratios.
    float GetAspectRatio() const;
    float GetVirtualAspectRatio() const;

    // If the game is full screen.
    bool IsFullscreen() const;

    // Get the orientation of the game window.
    NDefs::EOrentation GetOrientation() const;

    // If antialias is enabled.
    bool IsAntialias() const;

    // Whether or not shadows are enabled.
    bool ShadowsEnabled() const;

    // Get the amount to shift a shadow so objects don't cast shadows on themselves and cause artifacts.
    float GetShadowBias() const;

    // Get the current shadow rendering mode.
    int GetShadowMode() const;

    // Get the size of the map used for shadows.
    const CVector2 & GetShadowSize() const;

    // Get the amount of shadow smoothing. (0 = off, 1 = min, 2 = max)
    int GetShadowSmoothingLevel() const;

    // Get the distance to stop casting shadows.
    float GetShadowRange() const;

    // Access functions for when the windows is being resized.
    void SetWindowResized( bool resized );
    bool IsWindowResized() const;

    // Check to see if the window has been resized. If so, reposition all sprites with alignments.
    void CheckForWindowSizeChange();

    // Access functions for the positions of each screen boundary.
    void SetScreenBounds();
    const CVector4 & GetScreenBounds() const;

private:

    // Constructor
    CSettings();

    // Destructor
    virtual ~CSettings();

private:

    // Path to the settings file.
    std::string _path;

    // Resolution of the game window.
    CVector2 _resolution;

    // Virtual resolution fo the game window. 
    // This is the resolution your art was made for.
    CVector2 _vResolution;

    // Window aspect ratios.
    float _aspectRatio;
    float _vAspectRatio;

    // Whether game is displaying in fullscreen mode or not.
    bool _fullscreen;

    // Orientation of game window.
    NDefs::EOrentation _orientation;

    // If antialiasing is active.
    bool _antialias;

    // Whether or not shadows are enabled.
    bool _shadowsEnabled;

    // The amount to shift a shadow so objects don't cast shadows on themselves and cause artifacts.
    float _shadowBias;

    // Shadow rendering mode.
    int _shadowMode;

    // Size of the map used for shadows.
    CVector2 _shadowSize;

    // The amount of shadow smoothing. (0 = off, 1 = min, 2 = max)
    int _shadowSmoothing;

    // Distance to stop casting shadows.
    float _shadowRange;

    // Whether or not the window has been resized.
    bool _windowResized;

    // The positions of each screen boundary.
    CVector4 _screenBounds;
};

#endif  // __settings_h__


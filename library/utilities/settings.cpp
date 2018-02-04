// Physical component dependency
#include "settings.h"

// Game lib dependencies
#include <agk.h>
#include <utilities\jsonparsehelper.h>
#include <utilities\exceptionhandling.h>
#include <managers\spritemanager.h>

// Standard lib dependencies
#include <fstream>

using namespace nlohmann;
using namespace std;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CSettings::CSettings() :
    _fullscreen( false ),
    _orientation( NDefs::EO_LANDSCAPE ),
    _antialias( false )
{
}


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CSettings::~CSettings()
{
}


/// *************************************************************************
/// <summary> 
/// Set the file path for loading the settings file.
/// </summary>
/// *************************************************************************
void CSettings::SetPath( const std::string & path )
{
    _path = path;
}


/// *************************************************************************
/// <summary> 
/// Load settings data from xml file.
/// </summary>
/// *************************************************************************
void CSettings::LoadSettings()
{
    try
    {
        // Load the settings file.
        ifstream ifile( _path );

        // Parse the content into a json object.
        json j;
        ifile >> j;

        auto settingsIter = j.find( "settings" );
        if( settingsIter != j.end() )
        {
            auto displayIter = settingsIter->find( "display" );
            if( displayIter != settingsIter->end() )
            {
                NParseHelper::GetWH( displayIter, "resolution", _resolution );
                NParseHelper::GetWH( displayIter, "vResolution", _vResolution );
                NParseHelper::GetBool( displayIter, "fullscreen", _fullscreen );
                NParseHelper::GetOrientation( displayIter, _orientation );
                NParseHelper::GetBool( displayIter, "anitalias", _antialias );

                _aspectRatio = (float)_resolution.h / (float)_resolution.w;
                _vAspectRatio = (float)_vResolution.h / (float)_vResolution.w;
            }

            auto shadowsIter = settingsIter->find( "shadows" );
            if( shadowsIter != settingsIter->end() )
            {
                NParseHelper::GetBool( shadowsIter, "enabled", _shadowsEnabled );
                NParseHelper::GetFloat( shadowsIter, "bias", _shadowBias );
                NParseHelper::GetInt( shadowsIter, "shadowMode", _shadowMode );
                NParseHelper::GetWH( shadowsIter, "size", _shadowSize );
                NParseHelper::GetInt( shadowsIter, "smoothing", _shadowSmoothing );
                NParseHelper::GetFloat( shadowsIter, "range", _shadowRange );
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
                                           "CSettings::LoadSettings()",
                                           "Failed to open " + _path + ".", e );
    }
}


/// *************************************************************************
/// <summary> 
/// Apply the settings currently set.
/// </summary>
/// *************************************************************************
void CSettings::ApplySettings()
{
    try
    {
        agk::SetWindowSize( _resolution.w, _resolution.h, _fullscreen );

        // Virtual resolution is the resolution your art is designed for in size and position.
        agk::SetVirtualResolution( _vResolution.w, _vResolution.h );

        if( !_fullscreen )
        {
            int xPos = (GetSystemMetrics( SM_CXSCREEN ) - _resolution.w) / 2;
            int yPos = (GetSystemMetrics( SM_CYSCREEN ) - _resolution.h) / 2;

            agk::SetWindowPosition( xPos, yPos );
        }

        agk::SetAntialiasMode( _antialias );

        if( _shadowsEnabled )
        {
            agk::SetShadowBias( _shadowBias );
            agk::SetShadowMappingMode( _shadowMode );
            agk::SetShadowMapSize( _shadowSize.w, _shadowSize.h );
            agk::SetShadowSmoothing( _shadowSmoothing );
            agk::SetShadowRange( _shadowRange );
        }
    }
    catch( NExcept::CCriticalException e )
    {
        throw e;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CSettings::ApplySettings()",
                                           "Failed to apply settings.", e );
    }
}


/// *************************************************************************
/// <summary> 
/// Save the settings to the file.
/// </summary>
/// *************************************************************************
void CSettings::SaveSettings()
{
}


/// *************************************************************************
/// <summary> 
/// Get the window resolution.
/// </summary>
/// *************************************************************************
const CSize<int> & CSettings::GetResolution() const
{
    return _resolution;
}


/// *************************************************************************
/// <summary> 
/// Get the virtual resolution. This is the resolution your art was made for.
/// </summary>
/// *************************************************************************
const CSize<int> & CSettings::GetVirtualResolution() const
{
    return _vResolution;
}


/// *************************************************************************
/// <summary> 
/// Get the window aspect ratio.
/// </summary>
/// *************************************************************************
float CSettings::GetAspectRatio() const
{
    return _aspectRatio;
}


/// *************************************************************************
/// <summary> 
/// Get the virtual aspect ratio.
/// </summary>
/// *************************************************************************
float CSettings::GetVirtualAspectRatio() const
{
    return _vAspectRatio;
}


/// *************************************************************************
/// <summary> 
/// If the game is full screen.
/// </summary>
/// *************************************************************************
bool CSettings::IsFullscreen() const
{
    return _fullscreen;
}


/// *************************************************************************
/// <summary> 
/// Get the orientation of the game window.
/// </summary>
/// *************************************************************************
NDefs::EOrentation CSettings::GetOrientation() const
{
    return _orientation;
}


/// *************************************************************************
/// <summary> 
/// If antialias is enabled.
/// </summary>
/// *************************************************************************
bool CSettings::IsAntialias() const
{
    return _antialias;
}


/// *************************************************************************
/// <summary> 
/// Whether or not shadows are enabled.
/// </summary>
/// *************************************************************************
bool CSettings::ShadowsEnabled() const
{
    return _shadowsEnabled;
}


/// *************************************************************************
/// <summary> 
/// Get the amount to shift a shadow so objects don't cast shadows on 
/// themselves and cause artifacts.
/// </summary>
/// *************************************************************************
float CSettings::GetShadowBias() const
{
    return _shadowBias;
}


/// *************************************************************************
/// <summary> 
/// Get the current shadow rendering mode.
/// </summary>
/// *************************************************************************
int CSettings::GetShadowMode() const
{
    return _shadowMode;
}


/// *************************************************************************
/// <summary> 
/// Get the size of the map used for shadows.
/// </summary>
/// *************************************************************************
const CSize<int> & CSettings::GetShadowSize() const
{
    return _shadowSize;
}


/// *************************************************************************
/// <summary> 
/// Get the amount of shadow smoothing. (0 = off, 1 = min, 2 = max)
/// </summary>
/// *************************************************************************
int CSettings::GetShadowSmoothingLevel() const
{
    return _shadowSmoothing;
}


/// *************************************************************************
/// <summary> 
/// Get the distance to stop casting shadows.
/// </summary>
/// *************************************************************************
float CSettings::GetShadowRange() const
{
    return _shadowRange;
}


/// *************************************************************************
/// <summary> 
/// Set whether the window has been resized.
/// </summary>
/// *************************************************************************
void CSettings::SetWindowResized( bool resized )
{
    _windowResized = resized;
}


/// *************************************************************************
/// <summary> 
/// Get whether the window has been resized.
/// </summary>
/// *************************************************************************
bool CSettings::IsWindowResized() const
{
    return _windowResized;
}


// Check to see if the window has been resized. If so, reposition all sprites with alignments.
void CSettings::CheckForWindowSizeChange()
{
    if( _windowResized )
    {
        _windowResized = false;

        CSpriteManager::Instance().RepositionAllSprites2D();
    }
}
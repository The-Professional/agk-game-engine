// Physical component dependency
#include "settings.h"

// Game lib dependencies
#include <agk.h>
#include <utilities\jsonparsehelper.h>
#include <utilities\exceptionhandling.h>

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
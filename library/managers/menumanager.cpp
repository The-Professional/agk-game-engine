// Physical component dependency
#include "menumanager.h"

// Game lib dependencies
#include <controls\menu.h>
#include <controls\menudata.h>
#include <controls\control.h>
#include <controls\controldata.h>
#include <utilities\jsonparsehelper.h>
#include <utilities\generalfuncs.h>
#include <utilities\deletefuncs.h>

// Standard lib dependencies
#include <fstream>

using namespace std;
using namespace nlohmann;
using namespace NDefs;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CMenuManager::CMenuManager()
{
}


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CMenuManager::~CMenuManager()
{
    Clear();
}


/// *************************************************************************
/// <summary> 
/// Free the loaded menu/control data.
/// </summary>
/// <param name="name"> Name of the sprite to free. 
///                     Empty string frees everything. </param>
/// *************************************************************************
void CMenuManager::Clear( const string & name )
{
    try
    {
        if( name.empty() )
        {
            NDelFunc::DeleteMapPointers( _pMenuList );
            NDelFunc::DeleteMapVectorPointers( _pControlList );
            NDelFunc::DeleteMapPointers( _pMenuDataList );
            NDelFunc::DeleteMapPointers( _pControlDataList );
        }
        else
        {
            NDelFunc::DeleteMapPointer( name, _pMenuList );
            NDelFunc::DeleteMapVectorPointers( name, _pControlList );
            NDelFunc::DeleteMapPointer( name, _pMenuDataList );
            NDelFunc::DeleteMapPointer( name, _pControlDataList );
        }
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CMenuManager::Clear()",
                                           name.empty() ? "Failed to clear all sprites and sprite data." :
                                           "Failed to clear sprite '" + name + "'.", e );
    }
}


/// *************************************************************************
/// <summary> 
/// Read the file and compile the list of menu data files.
/// </summary>
/// *************************************************************************
void CMenuManager::LoadMenuDataFileList( const std::string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _controlDataFileList );
}


/// *************************************************************************
/// <summary> 
/// Read the file and compile the list of control data files.
/// </summary>
/// *************************************************************************
void CMenuManager::LoadControlDataFileList( const std::string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _menuDataFileList );
}


/// *************************************************************************
/// <summary> 
/// Load the menu data.
/// </summary>
/// *************************************************************************
CMenuData * CMenuManager::GetMenuData( const std::string & name )
{
    try
    {
        // See if the sprite data is already loaded.
        auto loadedIter = _pMenuDataList.find( name );
        if( loadedIter != _pMenuDataList.end() )
            return loadedIter->second;

        // If not, load the sprite data.
        const string & filepath = NGeneralFuncs::GetMapValue( name, _menuDataFileList );

        // Load the sprite data file.
        ifstream ifile( filepath );

        // Parse the content into a json object.
        json j;
        ifile >> j;

        auto menuIter = j.find( "menu" );
        if( menuIter != j.end() )
        {
            CMenuData * pData = new CMenuData();
            _pMenuDataList.emplace( name, pData );

            pData->LoadFromIter( name, menuIter );

            return pData;
        }
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CMenuManager::GetMenuData()",
                                           "Failed to get menu data '" + name + "'.", e );
    }

    return nullptr;
}


/// *************************************************************************
/// <summary> 
/// Load the control data.
/// </summary>
/// *************************************************************************
CControlData * CMenuManager::GetControlData( const std::string & name )
{
    try
    {
        // See if the sprite data is already loaded.
        auto loadedIter = _pControlDataList.find( name );
        if( loadedIter != _pControlDataList.end() )
            return loadedIter->second;

        // If not, load the sprite data.
        const string & filepath = NGeneralFuncs::GetMapValue( name, _controlDataFileList );

        // Load the sprite data file.
        ifstream ifile( filepath );

        // Parse the content into a json object.
        json j;
        ifile >> j;

        auto controlIter = j.find( "menu" );
        if( controlIter != j.end() )
        {
            CControlData * pData = new CControlData();
            _pControlDataList.emplace( name, pData );

            pData->LoadFromIter( name, controlIter );

            return pData;
        }
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CMenuManager::GetControlData()",
                                           "Failed to get control data '" + name + "'.", e );
    }

    return nullptr;
}


/// *************************************************************************
/// <summary> 
/// Create the menu.
/// </summary>
/// <param name="name"> Name of the menu. </param>
/// <param name="key"> Key value to locate the menu. 
/// If not defined, the key will be the menu's name. </param>
/// *************************************************************************
CMenu * CMenuManager::CreateMenu( const std::string & name, const string & key )
{
    try
    {
        // Create the menu and add it to the menu list.
        CMenu * pMenu = new CMenu( name );

        if( key.empty() )
        {
            auto iter = _pMenuList.find( name );
            if( iter == _pMenuList.end() )
                _pMenuList.emplace( name, pMenu );
            else
                throw NExcept::CCriticalException( "Error",
                                                   "CMenuManager::CreateMenu()",
                                                   "Menu '" + name + "' already exists." );
        }
        else
        {
            auto iter = _pMenuList.find( key );
            if( iter == _pMenuList.end() )
                _pMenuList.emplace( key, pMenu );
            else
                throw NExcept::CCriticalException( "Error",
                                                   "CMenuManager::CreateMenu()",
                                                   "Menu '" + name + "' already exists." );
        }

        return pMenu;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CMenuManager::CreateMenu()",
                                           "Failed to create menu '" + name + "'.", e );
    }

    return nullptr;
}


/// *************************************************************************
/// <summary> 
/// Create the control.
/// </summary>
/// <param name="name"> Name of the control. </param>
/// <param name="key"> Key value to locate the control. 
/// If not defined, the key will be the control's name. </param>
/// *************************************************************************
iControl * CMenuManager::CreateControl( const std::string & name, const string & key )
{
    try
    {
        CControlData * pData = GetControlData( name );

        iControl * pControl = nullptr;

        // New up the control as its proper control.
        switch( pData->GetControlType() )
        {
        case ECT_BUTTON:
            break;
        case ECT_CHECKBOX:
            break;
        case ECT_SLIDER:
            break;
        case ECT_BUTTON_LIST:
            break;
        default:
            break;
        }

        // If the control wasn't created, throw an exception.
        if( !pControl )
            throw NExcept::CCriticalException( "Error",
                                               "CMenuManager::CreateControl()",
                                               "Invalid control type for control '" + name + "'." );

        // Add the control to the list.
        if( key.empty() )
            _pControlList[name].push_back( pControl );
        else
            _pControlList[key].push_back( pControl );

        return pControl;
    }
    catch( exception e )
    {
        throw NExcept::CCriticalException( "Error",
                                           "CMenuManager::CreateControl()",
                                           "Failed to create control '" + name + "'.", e );
    }

    return nullptr;
}
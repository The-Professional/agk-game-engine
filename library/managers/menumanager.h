#ifndef __menu_manager_h__
#define __menu_manager_h__

// Game lib dependencies
#include <common\defs.h>

// Standard lib dependencies
#include <string>
#include <map>
#include <vector>

// Forward declarations
class CControlData;
class CMenuData;
class iObject;
class iControl;
class CMenu;

/// *************************************************************************
/// <summary> 
/// Class to load and hold menus and controls.
/// </summary>
/// *************************************************************************
class CMenuManager
{
public:
    // Get the instance of the singleton class
    static CMenuManager & Instance()
    {
        static CMenuManager menuManager;
        return menuManager;
    }

    // Free the loaded menu.
    void Clear( const std::string & name = "" );

    // Read the file and compile the list of menu/control data files.
    void LoadMenuDataFileList( const std::string & path );
    void LoadControlDataFileList( const std::string & path );

    // Load the menu/control data.
    CMenuData * GetMenuData( const std::string & name );
    CControlData * GetControlData( const std::string & name );

    // Create the menu/control.
    CMenu * CreateMenu( const std::string & name, const std::string & key = "" );
    iControl * CreateControl( const std::string & name, const std::string & key = "" );

private:

    CMenuManager();
    virtual ~CMenuManager();

private:

    // Map containing the list of menu/control data files.
    std::map<const std::string, const std::string> _menuDataFileList;
    std::map<const std::string, const std::string> _controlDataFileList;

    // Map containing the list of loaded menu/control data.
    std::map<const std::string, CMenuData *> _pMenuDataList;
    std::map<const std::string, CControlData *> _pControlDataList;

    // Map containing the list of loaded menus/controls.
    std::map<const std::string, CMenu *> _pMenuList;
    std::map<const std::string, std::vector<iControl *>> _pControlList;
};

#endif  // __menu_manager_h__

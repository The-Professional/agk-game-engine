#ifndef __control_data_h__
#define __control_data_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\bitmask.h>
#include <utilities\jsonparsehelper.h>

// Standard lib dependencies
#include <string>
#include <vector>

// Forward declarations
class CCollectionObject;

/// *************************************************************************
/// <summary>
/// Class containing the default creation data for a control.
/// </summary>
/// *************************************************************************
class CControlData
{
public:

    CControlData();
    ~CControlData();

    // Load the sprite data from the passed in iterator.
    void LoadFromIter( const std::string & name, nlohmann::json::const_iterator iter );

    // Access functions for the text sprite data.
    const std::string & GetName() const;
    NDefs::EControlType GetControlType() const;
    NDefs::EControlState GetState() const;
    const CBitmask<uint> & GetAlignment() const;
    const std::vector<CCollectionObject> & GetSpriteList() const;

private:

    // The name of the control.
    std::string _name;

    // The type of the control.
    NDefs::EControlType _type = NDefs::ECT_NULL;

    // The state of the control.
    NDefs::EControlState _state = NDefs::ECS_DISABLED;

    // The window alignment of the control.
    CBitmask<uint> _alignment = NDefs::EA_CENTER;

    // The list sprites and their default transformations relative to the control.
    std::vector<CCollectionObject> _spriteList;
};

#endif  // __control_data_h__

#ifndef __control_data_h__
#define __control_data_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\bitmask.h>
#include <common\vector2.h>
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
    const CBitmask<uint> & GetAlignment() const;
    NDefs::EControlType GetControlType() const;
    NDefs::EControlState GetState() const;
    const std::vector<std::vector<std::string>> & GetAnimationList() const;
    const std::vector<CCollectionObject> & GetSpriteList() const;

    // Access functions for the visual sprite's size.
    void SetSize( const CVector2<float> & size );
    const CVector2<float> & GetSize() const;

    // Whether or not the size has been set.
    bool IsSizeSet() const;

    // Whether or not the size is the same as the file.
    bool IsSizeSameAsFile() const;

private:

    // The name of the control.
    std::string _name;

    // The window alignment of the control.
    CBitmask<uint> _alignment = NDefs::EA_CENTER;

    // Size of the control.
    CVector2<float> _size;

    // Whether or not the size has been set.
    bool _sizeSet = false;

    // Whether or not the size is the same as the file.
    bool _sizeSameAsFile = false;

    // The type of the control.
    NDefs::EControlType _type = NDefs::ECT_NULL;

    // The state of the control.
    NDefs::EControlState _state = NDefs::ECS_DISABLED;

    // The list of animations this control can perform.
    std::vector<std::vector<std::string>> _animationList;

    // The list sprites and their default transformations relative to the control.
    std::vector<CCollectionObject> _spriteList;
};

#endif  // __control_data_h__

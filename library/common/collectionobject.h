#ifndef __transform_data_h__
#define __transform_data_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\vector3.h>
#include <common\vector4.h>
#include <common\bitmask.h>
#include <utilities\jsonparsehelper.h>

// Standard lib dependencies
#include <string>

/// *************************************************************************
/// <summary> 
/// Class to hold an object's default transformation, color, and visibility.
/// </summary>
/// *************************************************************************
class CCollectionObject
{
public:

    enum : uint
    {
        NAME = 1,
        POSITION = NAME << 1,
        ROTATION = POSITION << 1,
        SIZE = ROTATION << 1,
        COLOR = SIZE << 1,
        VISIBLE = COLOR << 1,
        ALIGNMENT = VISIBLE << 1,
        TEXT = ALIGNMENT << 1,
        TEXT_ALIGNMENT = TEXT << 1,
        TEXT_SIZE = TEXT_ALIGNMENT << 1
    };

    // Name of the object.
    std::string name;

    // The object's transformation.
    CVector3 position, rotation, size;

    // The object's color.
    CVector4 color;

    // The object's visibility.
    bool visible = true;

    // The object's alignment relative to the window.
    CBitmask<uint> alignment = NDefs::EA_CENTER;

    // Object's display text. Only used with text sprites.
    std::string text;

    // The object's text alignment.
    NDefs::ETextAlignment textAlignment = NDefs::ETA_CENTER;

    CBitmask<uint> fields;
};

#endif  // __transform_data_h__

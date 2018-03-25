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
        TYPE            = 1,
        NAME            = 1 << 1,
        POSITION        = 1 << 2,
        ROTATION        = 1 << 3,
        SIZE            = 1 << 4,
        COLOR           = 1 << 5,
        VISIBLE         = 1 << 6,
        ALIGNMENT       = 1 << 7,
        TEXT            = 1 << 8,
        TEXT_ALIGNMENT  = 1 << 9,
        TEXT_SIZE       = 1 << 10
    };

    // Type of object.
    NDefs::EObjectType type;

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

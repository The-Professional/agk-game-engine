#ifndef __defs_h__
#define __defs_h__

// define an unsigned int
typedef unsigned int uint;

#define defs_DEG_TO_RAD 0.0174532925199432957
#define defs_RAD_TO_DEG 57.29577951308232
#define defs_EPSILON 8.854187817e-12
#define defs_RGB_TO_DEC 0.00390625

/// <summary>
/// Namespace to hold all general game library definitions. 
/// </summary>
namespace NDefs
{
    // The types of objects.
    enum EObjectType
    {
        EOT_NONE,
        EOT_BOX,
        EOT_CONE,
        EOT_CYLINDER,
        EOT_CAPSULE,
        EOT_PLANE,
        EOT_SPHERE,
        EOT_MESH,
        EOT_LIGHT
    };

    // The types of textures.
    enum EImageType
    {
        ETS_TEXTURE = 0,
        ETS_NORMAL = 1,
        ETS_SPECULAR = 2
    };

    // The types of resources.
    enum EResourceType
    {
        ERT_NULL,
        ERT_MESH,
        ERT_ANIMATED_MESH,
        ERT_IMAGE
    };

    // The types of data.
    enum EDataType
    {
        EDT_NULL,
        EDT_STAGE,
        EDT_SPRITE,
        EDT_CONTROL
    };
    
    // The types of alignment.
    enum EAlignment
    {
        EA_NULL     = 0,
        EA_LEFT     = 1,
        EA_RIGHT    = 2,
        EA_TOP      = 4,
        EA_BOTTOM   = 8
    };

    // Orientation of the screen.
    enum EOrentation
    {
        EO_LANDSCAPE,
        EO_PORTRAIT
    };

    // Type of device we can receive inputs from.
    enum EInputDevice
    {
        EID_NULL,
        EID_MOUSE,
        EID_KEYBOARD,
        EID_GAMEPAD
    };
}

#endif // __defs_h__
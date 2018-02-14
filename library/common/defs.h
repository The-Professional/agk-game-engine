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
    // The types of meshs.
    enum EMeshType
    {
        EMT_NONE,
        EMT_BOX,
        EMT_CONE,
        EMT_CYLINDER,
        EMT_CAPSULE,
        EMT_PLANE,
        EMT_SPHERE,
        EMT_MESH
    };

    // The types of objects
    enum EObjectType
    {
        EOT_NULL,
        EOT_SPRITE_3D,
        EOT_SPRITE_2D,
        EOT_TEXT_SPRITE,
        EOT_LIGHT
    };

    // The types of transformation.
    enum
    {
        ETT_NULL        = 0,
        ETT_POSITION    = 1,
        ETT_ROTATION    = 2,
        ETT_SIZE        = 4,
        ETT_COLOR       = 8
    };

    // The type of value to be animated.
    enum EAnimationValueType
    {
        EAVT_X,
        EAVT_Y,
        EAVT_Z,
        
        EAVT_W,
        EAVT_H,
        EAVT_D,
        
        EAVT_R,
        EAVT_G,
        EAVT_B,
        EAVT_A
    };

    // The type of animation end.
    enum EEndType
    {
        EET_IGNORE,         // Ignore the ending animation. Effectively a pause.
        EET_FINISH_LOOP,    // Continue to the end of the current loop before beginning the end animation.
        EET_TRANSITION      // Immediately begin transitioning from current object values.
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
        ERT_IMAGE,
        ERT_FONT
    };

    enum EControlType
    {
        ECT_NULL,
        ECT_BUTTON,
        ECT_CHECKBOX,
        ECT_SLIDER,
        ECT_BUTTON_LIST
    };

    enum EControlState
    {
        ECS_DISABLED,
        ECS_INACTIVE,
        ECS_ACTIVE,
        ECS_PRESSED,
        ECS_RELEASED,
        ECS_TRANSITION
    };
    
    // The types of alignment.
    enum
    {
        EA_CENTER   = 0,
        EA_LEFT     = 1,
        EA_RIGHT    = 2,
        EA_TOP      = 4,
        EA_BOTTOM   = 8
    };

    // The types of text alignment.
    enum ETextAlignment
    {
        ETA_LEFT,
        ETA_CENTER,
        ETA_RIGHT
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

    // The types of shadow rendering modes.
    enum
    {
        ESM_UNIFORM = 1,
        ESM_LIGHT_SPACE_PERSPECTIVE,
        ESM_CASCADE
    };
}

#endif // __defs_h__
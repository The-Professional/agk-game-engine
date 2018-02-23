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
    enum : uint
    {
		ETD_NULL        = 0,
        ETD_POSITION_X  = 1,
        ETD_POSITION_Y  = ETD_POSITION_X << 1,
        ETD_POSITION_Z  = ETD_POSITION_Y << 1,

		ETD_ROTATION_X  = ETD_POSITION_Z << 1,
		ETD_ROTATION_Y  = ETD_ROTATION_X << 1,
		ETD_ROTATION_Z  = ETD_ROTATION_Y << 1,
        
        ETD_WIDTH       = ETD_ROTATION_Z << 1,
        ETD_HEIGHT      = ETD_WIDTH << 1,
        ETD_DEPTH       = ETD_HEIGHT << 1,
        
        ETD_RED         = ETD_DEPTH << 1,
        ETD_GREEN       = ETD_RED << 1,
        ETD_BLUE        = ETD_GREEN << 1,
        ETD_ALPHA       = ETD_BLUE << 1
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

    // The types of script endings.
    enum EScriptEndType
    {
        ESE_STOP,   // Stop the script completely in whatever state it currently is in.
        ESE_BREAK,  // Break out of any loops but still play any script outside of the loop.
        ESE_FINISH, // Finish out the current loop and play any script outside of the loop.
        ESE_RESET   // Stop the script completely and reset the modified values to their initial values.
    };
}

#endif // __defs_h__
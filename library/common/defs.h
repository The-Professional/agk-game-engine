#ifndef __defs_h__
#define __defs_h__

// Standard lib dependencies
#include <string>
#include <map>

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

    // The types of object fields.
    enum : uint
    {
        ETT_NULL        = 0,
        ETT_POSITION    = 1,
        ETT_ROTATION    = 2,
        ETT_SIZE        = 4,
        ETT_COLOR       = 8,
        ETT_FRAME       = 16,
        ETT_BONE        = 32
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
    enum : uint
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
    enum EShadowMode
    {
        ESM_UNIFORM = 1,
        ESM_LIGHT_SPACE_PERSPECTIVE,
        ESM_CASCADE
    };

    // The types of animation endings.
    enum : int
    {
        ESE_NULL,
        ESE_DEFAULT, // Use whatever is the default end type.
        ESE_STOP,    // Stop the animation completely in whatever state it currently is in.
        ESE_BREAK,   // Break out of any loops but still play any animation outside of the loop.
        ESE_FINISH,  // Finish out the current loop and play any animation outside of the loop.
        ESE_RESET    // Stop the animation completely and reset the modified values to their initial values.
    };

    /// *************************************************************************
    /// <summary> 
    /// Class to load and hold 3d mesh id's.
    /// </summary>
    /// *************************************************************************
    class CDefs
    {
    public:
        // Get the instance of the singleton class
        static CDefs & Instance()
        {
            static CDefs defs;
            return defs;
        }

        // Access functions for each list.
        EMeshType GetMeshType( const std::string & value );
        EObjectType GetObjectType( const std::string & value );
        uint GetObjectField( const std::string & value );
        EImageType GetImageType( const std::string & value );
        EResourceType GetResourceType( std::string & value );
        EControlType GetControlType( const std::string & value );
        EControlState GetControlState( const std::string & value );
        uint GetAlignment( const std::string & value );
        ETextAlignment GetTextAlignment( const std::string & value );
        EOrentation GetOrientation( const std::string & value );
        EInputDevice GetInputDevice( const std::string & value );
        EShadowMode GetShadowMode( const std::string & value );
        int GetAnimationEndType( const std::string & value );

    private:

        CDefs();
        virtual ~CDefs();

        // Map containing the list of meshes types.
        std::map<const std::string, EMeshType> _meshTypeList;

        // Map containing the list of object types.
        std::map<const std::string, EObjectType> _objectTypeList;

        // Map containing the list of object field types.
        std::map<const std::string, uint> _objectFieldList;

        // Map containing the list of image types.
        std::map<const std::string, EImageType> _imageTypeList;

        // Map containing the list of resource types.
        std::map<const std::string, EResourceType> _resourceTypeList;

        // Map containing the list of control types.
        std::map<const std::string, EControlType> _controlTypeList;

        // Map containing the list of control states.
        std::map<const std::string, EControlState> _controlStateList;

        // Map containing the list of alignments.
        std::map<const std::string, uint> _alignmentList;

        // Map containing the list of text alignments.
        std::map<const std::string, ETextAlignment> _textAlignmentList;

        // Map containing the list of orientations.
        std::map<const std::string, EOrentation> _orientationList;

        // Map containing the list of input devices.
        std::map<const std::string, EInputDevice> _inputDeviceList;

        // Map containing the list of shadow modes.
        std::map<const std::string, EShadowMode> _shadowModeList;

        // Map containing the list of animation end types.
        std::map<const std::string, int> _animationEndTypeList;
    };
}

#endif // __defs_h__
// Physical component dependency
#include "defs.h"

// Game lib dependencies
#include <utilities\generalfuncs.h>

/// <summary>
/// Namespace to hold all general game library definitions. 
/// </summary>
namespace NDefs
{
    /// *************************************************************************
    /// <summary> 
    /// Contructor
    /// </summary>
    /// *************************************************************************
    CDefs::CDefs()
    {
        _meshTypeList.emplace( "box", EMT_BOX );
        _meshTypeList.emplace( "cone", EMT_CONE );
        _meshTypeList.emplace( "cylinder", EMT_CYLINDER );
        _meshTypeList.emplace( "capsule", EMT_CAPSULE );
        _meshTypeList.emplace( "plane", EMT_PLANE );
        _meshTypeList.emplace( "sphere", EMT_SPHERE );
        _meshTypeList.emplace( "mesh", EMT_MESH );
        
        _objectTypeList.emplace( "sprite3d", EOT_SPRITE_3D );
        _objectTypeList.emplace( "sprite2d", EOT_SPRITE_2D );
        _objectTypeList.emplace( "text sprite", EOT_TEXT_SPRITE );
        _objectTypeList.emplace( "sprite3d", EOT_LIGHT );
        
        _objectFieldList.emplace( "position", ETT_POSITION );
        _objectFieldList.emplace( "rotation", ETT_ROTATION );
        _objectFieldList.emplace( "size", ETT_SIZE );
        _objectFieldList.emplace( "color", ETT_COLOR );
        _objectFieldList.emplace( "frame", ETT_FRAME );
        _objectFieldList.emplace( "bone", ETT_BONE );

        _imageTypeList.emplace( "texture", ETS_TEXTURE );
        _imageTypeList.emplace( "normal", ETS_NORMAL );
        _imageTypeList.emplace( "specular", ETS_SPECULAR );

        _resourceTypeList.emplace( "mesh", ERT_MESH );
        _resourceTypeList.emplace( "animated mesh", ERT_ANIMATED_MESH );
        _resourceTypeList.emplace( "image", ERT_IMAGE );
        _resourceTypeList.emplace( "font", ERT_FONT );

        _controlTypeList.emplace( "button", ECT_BUTTON );
        _controlTypeList.emplace( "checkbox", ECT_CHECKBOX );
        _controlTypeList.emplace( "slider", ECT_SLIDER );
        _controlTypeList.emplace( "button list", ECT_BUTTON_LIST );

        _controlStateList.emplace( "disabled", ECS_DISABLED );
        _controlStateList.emplace( "inactive", ECS_INACTIVE );
        _controlStateList.emplace( "active", ECS_ACTIVE );
        _controlStateList.emplace( "pressed", ECS_PRESSED );
        _controlStateList.emplace( "released", ECS_RELEASED );
        _controlStateList.emplace( "transition", ECS_TRANSITION );

        _alignmentList.emplace( "center", EA_CENTER );
        _alignmentList.emplace( "left", EA_LEFT );
        _alignmentList.emplace( "right", EA_RIGHT );
        _alignmentList.emplace( "top", EA_TOP );
        _alignmentList.emplace( "bottom", EA_BOTTOM );

        _textAlignmentList.emplace( "left", ETA_LEFT );
        _textAlignmentList.emplace( "center", ETA_CENTER );
        _textAlignmentList.emplace( "right", ETA_RIGHT );

        _orientationList.emplace( "landscape", EO_LANDSCAPE );
        _orientationList.emplace( "portrait", EO_PORTRAIT );

        _inputDeviceList.emplace( "mouse", EID_MOUSE );
        _inputDeviceList.emplace( "keyboard", EID_KEYBOARD );
        _inputDeviceList.emplace( "gamepad", EID_GAMEPAD );

        _shadowModeList.emplace( "uniform", ESM_UNIFORM );
        _shadowModeList.emplace( "light space perspective", ESM_LIGHT_SPACE_PERSPECTIVE );
        _shadowModeList.emplace( "cascade", ESM_CASCADE );

        _animationEndTypeList.emplace( "stop", ESE_STOP );
        _animationEndTypeList.emplace( "break", ESE_BREAK );
        _animationEndTypeList.emplace( "finish", ESE_FINISH );
        _animationEndTypeList.emplace( "reset", ESE_RESET );
    }


    /// *************************************************************************
    /// <summary> 
    /// Destructor
    /// </summary>
    /// *************************************************************************
    CDefs::~CDefs()
    {
    }


    /// *************************************************************************
    /// <summary> 
    /// Get the mesh type.
    /// </summary>
    /// *************************************************************************
    EMeshType CDefs::GetMeshType( const std::string & value )
    {
        return NGeneralFuncs::GetMapValue( value, _meshTypeList );
    }


    /// *************************************************************************
    /// <summary> 
    /// Get the object type.
    /// </summary>
    /// *************************************************************************
    EObjectType CDefs::GetObjectType( const std::string & value )
    {
        return NGeneralFuncs::GetMapValue( value, _objectTypeList );
    }


    /// *************************************************************************
    /// <summary> 
    /// Get the object field.
    /// </summary>
    /// *************************************************************************
    uint CDefs::GetObjectField( const std::string & value )
    {
        return NGeneralFuncs::GetMapValue( value, _objectFieldList );
    }


    /// *************************************************************************
    /// <summary> 
    /// Get the image type.
    /// </summary>
    /// *************************************************************************
    EImageType CDefs::GetImageType( const std::string & value )
    {
        return NGeneralFuncs::GetMapValue( value, _imageTypeList );
    }


    /// *************************************************************************
    /// <summary> 
    /// Get the resource type.
    /// </summary>
    /// *************************************************************************
    EResourceType CDefs::GetResourceType( std::string & value )
    {
        return NGeneralFuncs::GetMapValue( value, _resourceTypeList );
    }


    /// *************************************************************************
    /// <summary> 
    /// Get the control type.
    /// </summary>
    /// *************************************************************************
    EControlType CDefs::GetControlType( const std::string & value )
    {
        return NGeneralFuncs::GetMapValue( value, _controlTypeList );
    }


    /// *************************************************************************
    /// <summary> 
    /// Get the control state.
    /// </summary>
    /// *************************************************************************
    EControlState CDefs::GetControlState( const std::string & value )
    {
        return NGeneralFuncs::GetMapValue( value, _controlStateList );
    }


    /// *************************************************************************
    /// <summary> 
    /// Get the alignment.
    /// </summary>
    /// *************************************************************************
    uint CDefs::GetAlignment( const std::string & value )
    {
        return NGeneralFuncs::GetMapValue( value, _alignmentList );
    }


    /// *************************************************************************
    /// <summary> 
    /// Get the text alignment.
    /// </summary>
    /// *************************************************************************
    ETextAlignment CDefs::GetTextAlignment( const std::string & value )
    {
        return NGeneralFuncs::GetMapValue( value, _textAlignmentList );
    }


    /// *************************************************************************
    /// <summary> 
    /// Get the orientation.
    /// </summary>
    /// *************************************************************************
    EOrentation CDefs::GetOrientation( const std::string & value )
    {
        return NGeneralFuncs::GetMapValue( value, _orientationList );
    }


    /// *************************************************************************
    /// <summary> 
    /// Get the input device.
    /// </summary>
    /// *************************************************************************
    EInputDevice CDefs::GetInputDevice( const std::string & value )
    {
        return NGeneralFuncs::GetMapValue( value, _inputDeviceList );
    }


    /// *************************************************************************
    /// <summary> 
    /// Get the shadow mode.
    /// </summary>
    /// *************************************************************************
    EShadowMode CDefs::GetShadowMode( const std::string & value )
    {
        return NGeneralFuncs::GetMapValue( value, _shadowModeList );
    }


    /// *************************************************************************
    /// <summary> 
    /// Get the animation end type.
    /// </summary>
    /// *************************************************************************
    int CDefs::GetAnimationEndType( const std::string & value )
    {
        return NGeneralFuncs::GetMapValue( value, _animationEndTypeList );
    }
}
#ifndef __tween_h__
#define __tween_h__

// Game lib dependencies
#include <common\defs.h>
#include <utilities\jsonparsehelper.h>

// Standard lib dependencies
#include <string>
#include <vector>

// Forward declarations
class iObject;

/// *************************************************************************
/// <summary> 
/// Class to animate an object.
/// </summary>
/// *************************************************************************
class CTween
{
public:

    CTween();
    CTween( iObject * pObject, nlohmann::json::const_iterator iter );
    ~CTween();

    // Initialize the tween.
    void Init( iObject * pObject, nlohmann::json::const_iterator iter );

    // Clear the tween data.
    virtual void Clear();

private:

    // Add a translation tween to the animation.
    void AddPositionTween( nlohmann::json::const_iterator iter );

    // Add a rotation tween to the animation.
    void AddRotationTween( nlohmann::json::const_iterator iter );

    // Add a size tween to the animation.
    void AddSizeTween( nlohmann::json::const_iterator iter );

    // Add a color tween to the animation.
    void AddColorTween( nlohmann::json::const_iterator iter );

    // Get the interpolation of the tween.
    int GetInterpolation( nlohmann::json::const_iterator iter );

    // Set a tween value.
    void SetTween( uint animationType, NDefs::EAnimationValueType vType, float start, float end, int interpolation );

private:

    // AGK tween id.
    uint _id;

    // Object that is transformed by the tween.
    iObject * _pObject;

};

#endif  // __tween_h__
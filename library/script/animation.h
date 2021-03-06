#ifndef __animation_h__
#define __animation_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\vector3.h>
#include <common\vector4.h>

// Standard lib dependencies
#include <string>
#include <vector>

// Forward declarations
class iObject;
class CAnimationData;
class asIScriptContext;
class asIScriptEngine;

/// *************************************************************************
/// <summary> 
/// Class to hold animation information.
/// </summary>
/// *************************************************************************
class CAnimation
{
public:

    CAnimation();
    CAnimation( const CAnimationData * pData, iObject * pObject, uint conflictIndex );
    ~CAnimation();

    // Initialize the animation.
    void Init( const CAnimationData * pData, iObject * pObject, uint conflictIndex );

    // Clear the animation.
    void Clear();

    // Play the animation.
    void Play();

    // Stop the animation.
    void Stop( NDefs::EStopType stopType = NDefs::EST_STOP );

    // Stop any animations and recycle all contexts.
    void Recycle();

    // Get the end type.
    NDefs::EEndType GetEndType() const;

    // Get the end type.
    NDefs::EStopType GetStopType() const;

    // Whether or not the animation has been initialized.
    bool IsInitalized() const;

    // Access functions for the object's position.
    void SetPos( const CVector3<float> & pos );
    void IncPos( const CVector3<float> & pos );
    const CVector3<float> & GetPos() const;

    // Access functions for the object's rotation. 
    void SetRot( const CVector3<float> & rot );
    void IncRot( const CVector3<float> & rot );
    const CVector3<float> & GetRot() const;

    // Access functions for the object's size.
    void SetSize( const CVector3<float> & size );
    void IncSize( const CVector3<float> & size );
    const CVector3<float> & GetSize() const;

    // Access functions for the object's color.
    void SetColor( const CVector4<float> & color );
    void IncColor( const CVector4<float> & color );
    const CVector4<float> & GetColor() const;

    // Access functions for the object's transparency.
    void SetColorA( float alpha );
    void IncColorA( float alpha );
    float GetColorA() const;

    // Access functions for the object's visibility.
    void SetVisible( bool visible );
    bool IsVisible() const;

    // Whether or not the animation is playing.
    bool IsPlaying() const;

    // Get the number of times to loop the animation.
    int GetLoopCount() const;

    // Get the animation data.
    const CAnimationData * GetData() const;

    // Get the index of whichever conflict list this animation belongs to.
    uint GetConflictIndex() const;

    // Spawn another context to run concurrently.
    void Spawn( const std::string & function );

    // Update the animation.
    void Update();

    // Register the class with AngelScript.
    static void Register( asIScriptEngine * pEngine );

private:

    // Default data of the animation.
    const CAnimationData * _pData = nullptr;

    // The object to animate. This is not owned by the animation.
    iObject * _pObject = nullptr;

    // A list of each function that needs to play when this animation is played.
    std::vector<std::string> _functionList;

    // The context used to animate the object. These are not owned by the animation.
    std::vector<asIScriptContext *> _pContextList;

    // This variable is set when the animation needs to stop prematurely.
    NDefs::EStopType _stopType = NDefs::EST_NULL;

    // The index into whichever conflict list this animation belongs to. 
    uint _conflictIndex = 0;
};


#endif  // __animation_h__
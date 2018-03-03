#ifndef __animation_h__
#define __animation_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\vector3.h>
#include <common\color.h>

// Standard lib dependencies
#include <string>
#include <vector>
#include <map>

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
    CAnimation( const CAnimationData * pData, iObject * pObject );
    ~CAnimation();

    // Initialize the animation.
    void Init( const CAnimationData * pData, iObject * pObject );

    // Clear the animation.
    void Clear();

    // Play the animation.
    void Play( bool restartIfPlaying = true );

    // Stop the animation.
    void Stop( int endType = NDefs::ESE_DEFAULT );

    // Stop any animations and recycle all contexts.
    void Recycle();

    // Get the end type. This also tells us if we need to begin ending the animation.
    int GetEndType() const;

    // Whether or not the animation has been initialized.
    bool IsInitalized() const;

    // Finish the animation, making it ready to play again.
    void Finish( const std::string & function );

    // Access functions for the object's position.
    void SetPos( const CVector3 & pos );
    void IncPos( const CVector3 & pos );
    const CVector3 & GetPos() const;

    // Access functions for the object's rotation. 
    void SetRot( const CVector3 & rot );
    void IncRot( const CVector3 & rot );
    const CVector3 & GetRot() const;

    // Access functions for the object's size.
    void SetSize( const CVector3 & size );
    void IncSize( const CVector3 & size );
    const CVector3 & GetSize() const;

    // Access functions for the object's color.
    void SetColor( const CColor & color );
    void IncColor( const CColor & color );
    const CColor & GetColor() const;

    // Access functions for the object's transparency.
    void SetColorA( int alpha );
    void IncColorA( int alpha );
    int GetColorA() const;

    // Access functions for the object's visibility.
    void SetVisible( bool visible );
    bool IsVisible() const;

    // Whether or not the animation is playing.
    bool IsPlaying() const;

    // Get the number of times to loop the animation.
    int GetLoopCount() const;

    // Get the animation data.
    const CAnimationData * GetData() const;

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
    std::map<const std::string, asIScriptContext *> _pContextList;

    // This variable is set when the animation needs to end. Whichever end type it's set to
    // will determine how this animation will end.
    int _endType = NDefs::ESE_DEFAULT;

    // If the animation is currently playing.
    bool _playing = false;
};


#endif  // __animation_h__
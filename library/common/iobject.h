#ifndef __i_object_h__
#define __i_object_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\vector2.h>
#include <common\vector3.h>
#include <common\vector4.h>
#include <common\bitmask.h>

// Standard lib dependencies
#include <string>

// Forward declarations
class CAnimationComponent;
class CCollectionObject;
class CMatrix4;

/// *************************************************************************
/// <summary>
/// Interface class for the various sprite classes.
/// </summary>
/// *************************************************************************
class iObject
{
public:

    // Delete the object that belongs to the AGK id.
    virtual void DeleteObject() = 0;

    // Clear the object and reset its id.
    virtual void Clear();

    // Return the id set by AGK.
    uint GetID() const;

    // Get the type of object this is.
    NDefs::EObjectType GetType() const;

    // Get the current transformation data set in AGK.
    virtual CVector3 GetWorldPos() const = 0;
    virtual CVector3 GetWorldRot() const = 0;
    virtual CVector3 GetWorldSize() const = 0;
    virtual CVector3 GetWorldScale() const;
    virtual CVector4 GetWorldColor() const;

    // Update the size or scale, depending on which has been changed.
    virtual void UpdateSize() = 0;
    virtual void UpdateScale() = 0;

    // Set the object's fields using a collection object.
    virtual void Set( const CCollectionObject & collectionObject );

    // Access functions for the object's visibility.
    virtual void SetVisible( bool visible ) = 0;
    virtual bool IsVisible() const = 0;

    // Access functions for the object's position.
    virtual void SetPos( float x, float y );
    virtual void SetPos( float x, float y, float z );
    virtual void SetPos( const CVector2 & pos );
    virtual void SetPos( const CVector3 & pos );
    virtual void SetPosX( float x );
    virtual void SetPosY( float y );
    virtual void SetPosZ( float z );
    virtual void IncPos( float x, float y );
    virtual void IncPos( float x, float y, float z );
    virtual void IncPos( const CVector2 & pos );
    virtual void IncPos( const CVector3 & pos );
    virtual const CVector3 & GetPos() const;

    // Access functions for the object's rotation.
    virtual void SetRot( float x, float y, float z );
    virtual void SetRot( const CVector3 & rot );
    virtual void SetRotX( float x );
    virtual void SetRotY( float y );
    virtual void SetRotZ( float z );
    virtual void IncRot( float x, float y, float z );
    virtual void IncRot( const CVector3 & rot );
    virtual void IncRot( float z );
    virtual const CVector3 & GetRot() const;

    // Access functions for the object's size.
    virtual void SetSize( float w, float h, float d );
    virtual void SetSize( float w, float h );
    virtual void SetSize( float whd );
    virtual void SetSize( const CVector3 & size );
    virtual void SetSize( const CVector2 & size );
    virtual void SetSizeW( float w, bool uniform = false );
    virtual void SetSizeH( float h, bool uniform = false );
    virtual void SetSizeD( float d, bool uniform = false );
    virtual void IncSize( float w, float h, float d );
    virtual void IncSize( float w, float h );
    virtual void IncSize( float wfd );
    virtual void IncSize( const CVector3 & size );
    virtual void IncSize( const CVector2 & size );
    virtual const CVector3 & GetSize() const;

    // Access functions for the object's scale
    virtual void SetScale( float x, float y, float z );
    virtual void SetScale( float x, float y );
    virtual void SetScale( float xyz );
    virtual void SetScale( const CVector2 & scale );
    virtual void SetScale( const CVector3 & scale );
    virtual void SetScaleX( float x );
    virtual void SetScaleY( float y );
    virtual void SetScaleZ( float z );
    virtual void IncScale( float x, float y, float z );
    virtual void IncScale( float x, float y );
    virtual void IncScale( float xyz );
    virtual void IncScale( const CVector2 & scale );
    virtual void IncScale( const CVector3 & scale );
    virtual const CVector3 & GetScale() const;

    // Access functions for the object's color.
    virtual void SetColor( float r, float g, float b, float a );
    virtual void SetColor( float r, float g, float b );
    virtual void SetColor( const CVector4 & color );
    virtual void SetColorR( float r );
    virtual void SetColorG( float g );
    virtual void SetColorB( float b );
    virtual void SetColorA( float a );
    virtual void IncColor( float r, float g, float b, float a );
    virtual void IncColor( float r, float g, float b );
    virtual void IncColor( const CVector4 & color );
    virtual const CVector4 & GetColor() const;

    // Text sprite related access functions.
    virtual void SetFont( uint font ) {}
    virtual void SetText( const std::string & text ) {}
    virtual void SetTextSize( float value ) {}
    virtual void SetTextSpacing( float value ) {}
    virtual void SetLineSpacing( float value ) {}
    virtual void SetMaxWidth( float value ) {}
    virtual void SetTextAlignment( NDefs::ETextAlignment alignment ) {}
    virtual uint GetFont() const { return 0; }
    virtual std::string GetString() const { return ""; }
    virtual float GetTextSize() const { return 0; }
    virtual float GetTextSpacing() const { return 0; }
    virtual float GetLineSpacing() const { return 0; }
    virtual float GetMaxWidth() const { return 0; }
    virtual NDefs::ETextAlignment GetTextAlignment() const { return NDefs::ETA_LEFT; }

    // Access functions for the object's alignment.
    virtual void SetAlignment( const CBitmask<uint> alignment ) {}
    virtual CBitmask<uint> GetAlignment() const { return 0; }

    // Access functions for the object's parent.
    virtual void SetParent( iObject * pParent, bool ignore = false );
    virtual const iObject * GetParent() const;

    // Reset the object's position using its previous position.
    virtual void Reposition() {}

    // Play an animation.
    virtual void Play( const std::string & name, NDefs::EStopType stopType = NDefs::EST_NULL );

    // Stop an animation.
    virtual void Stop( NDefs::EStopType = NDefs::EST_STOP );
    virtual void Stop( const std::string & name, NDefs::EStopType stopType = NDefs::EST_STOP );

    // Whether or not an animation is playing.
    virtual bool IsPlaying( bool includePaused = false );
    virtual bool IsPlaying( const std::string & name, bool includePaused = false );

    // Get the transformed bitmask.
    virtual CBitmask<uint> GetModified() const;

    // Create a matrix for the object's transformations, if it doesn't already have one.
    virtual void CreateMatrix();

    // Get the object's matrix
    const CMatrix4 * GetMatrix();

    // Update the object.
    virtual void Update();

    // Function to call the functions that update AGK.
    virtual void Transform();

    // Clear the bitmask of modified fields.
    virtual void ClearModified();

protected:

    // Constructor
    iObject() {}

    // Destructor
    virtual ~iObject() {}

    // Apply the current transformations and color to AGK.
    virtual void ApplyPosition() = 0;
    virtual void ApplyRotation() = 0;
    virtual void ApplyScale() = 0;
    virtual void ApplyColor() = 0;

protected:

    // The id AGK has given the object.
    uint _id = 0;

    // The type of object.
    NDefs::EObjectType _type;

    // Translation of the object.
    CVector3 _position = 0;

    // Rotation of the object.
    CVector3 _rotation = 0;

    // Size of the object.
    CVector3 _size = 0;

    // Scale of the object. 
    CVector3 _scale = 1;

    // Color of the object.
    CVector4 _color = 1;

    // A bit mask of all the fields that have been changed.
    CBitmask<uint> _modified = NDefs::ETT_NULL;

    // Component to handle playing any animations.
    CAnimationComponent * _pAnimationComponent = nullptr;

    // The object's transformation matrix.
    CMatrix4 * _pMatrix = nullptr;

    // The parent object. This pointer does not belong to this object.
    iObject * _pParent = nullptr;
};

#endif  // __i_object_h__
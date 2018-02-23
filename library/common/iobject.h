#ifndef __i_object_h__
#define __i_object_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\vector2.h>
#include <common\vector3.h>
#include <common\color.h>
#include <common\bitmask.h>

// Standard lib dependencies
#include <string>

/// *************************************************************************
/// <summary>
/// Interface class for the various sprite classes.
/// </summary>
/// *************************************************************************
class iObject
{
public:
    // Initialize the object.
    //virtual void Init() = 0;

    // Delete the object that belongs to the AGK id.
    virtual void DeleteObject() = 0;

    // Clear the object and reset its id.
    virtual void Clear();

    // Return the id set by AGK.
    uint GetID() const;

    // Get the type of object this is.
    NDefs::EObjectType GetType() const;

    // Update AGK with the current color and transformation data.
    virtual void UpdateAGKWithPos() = 0;
    virtual void UpdateAGKWithRot() = 0;
    virtual void UpdateAGKWithSize() = 0;
    virtual void UpdateAGKWithColor() = 0;

    // Access functions for the sprite's visibility.
    virtual void SetVisible( bool visible ) = 0;
    virtual bool IsVisible() const = 0;

    // Access functions for the sprite's position.
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
    virtual const CVector3 & GetPos();

    // Access functions for the sprite's rotation.
    virtual void SetRot( float x, float y, float z );
    virtual void SetRot( const CVector3 & rot );
    virtual void SetRotX( float x );
    virtual void SetRotY( float y );
    virtual void SetRotZ( float z );
    virtual void IncRot( float x, float y, float z );
    virtual void IncRot( const CVector3 & rot );
    virtual void IncRot( float z );
    virtual const CVector3 & GetRot();

    // Access functions for the sprite's size.
    virtual void SetSize( float w, float h, float d );
    virtual void SetSize( float w, float h );
    virtual void SetSize( const CVector3 & size );
    virtual void SetSize( const CVector2 & size );
    virtual void SetSizeW( float w );
    virtual void SetSizeH( float h );
    virtual void SetSizeD( float d );
    virtual void IncSize( float w, float h, float d );
    virtual void IncSize( float w, float h );
    virtual void IncSize( const CVector3 & size );
    virtual void IncSize( const CVector2 & size );
    virtual const CVector3 & GetSize();

    // Access functions for the sprite's color.
    virtual void SetColor( int r, int g, int b, int a );
    virtual void SetColor( int r, int g, int b );
    virtual void SetColor( const CColor & color );
    virtual void SetColorR( int r );
    virtual void SetColorG( int g );
    virtual void SetColorB( int b );
    virtual void SetColorA( int a );
    virtual void IncColor( int r, int g, int b, int a );
    virtual void IncColor( int r, int g, int b );
    virtual void IncColor( const CColor & color );
    virtual const CColor & GetColor();

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

    // Reset the object's position using its previous position.
    virtual void Reposition() {}

protected:

    // Constructor
    iObject() {}

    // Destructor
    virtual ~iObject() {}

    // Update the current color and transformation data from AGK.
    virtual void UpdatePosFromAGK() = 0;
    virtual void UpdateRotFromAGK() = 0;
    virtual void UpdateSizeFromAGK() = 0;
    virtual void UpdateColorFromAGK() = 0;

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

    // Color of the object.
    CColor _color = 255;

    // Keep track of what values we've retrieved from AGK this frame.
    CBitmask<uint> _updatedValues;
};

#endif  // __i_object_h__
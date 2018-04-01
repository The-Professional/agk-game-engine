// Physical component dependency
#include "sprite2d.h"

// Game lib dependencies
#include <agk.h>
#include <common\matrix4.h>
#include <2d\spritedata2d.h>
#include <managers\resourcemanager.h>
#include <managers\spritemanager.h>
#include <utilities\mathfunc.h>
#include <utilities\exceptionhandling.h>
#include <script\animationcomponent.h>

using namespace std;
using namespace NDefs;


/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// <param name="name"> Name of the sprite to create. </param> 
/// *************************************************************************
CSprite2D::CSprite2D( const std::string & name )
{
    _type = EOT_SPRITE_2D;

    Init( name );
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CSprite2D::~CSprite2D()
{
    Clear();
}


/// *************************************************************************
/// <summary>
/// Get the name of the sprite.
/// </summary>
/// *************************************************************************
const string & CSprite2D::GetName() const
{
    return _pData->GetName();
}


/// *************************************************************************
/// <summary>
/// Initialize the sprite using its sprite data.
/// </summary>
/// <param name="pData"> Name of the sprite to initialize. </param> 
/// *************************************************************************
void CSprite2D::Init( const std::string & name )
{
    CSpriteData2D * pData = CSpriteManager::Instance().GetSpriteData2D( name );

    // Leave if there's no data to initialize with.
    if( !pData )
        throw NExcept::CCriticalException( "Error",
                                           "CSprite2D::Init()",
                                           "No sprite exists by the name of '" + name + "'." );

    Clear();

    _pData = pData;
    CSpriteVisualData2D * pVisual = _pData->GetVisualData();

    // Set the visual settings if a visual component exists.
    if( pVisual )
    {
        // Create the sprite using the texture map name. No name suggests a solid color.
        int imageId = CResourceManager::Instance().LoadImage( pVisual->GetTextureMap() );
        _id = agk::CreateSprite( imageId );

        // Set the sprite color.
        SetColor( pVisual->GetColor() );

        // Handle the sprite size, if its set in the data.
        if( pVisual->IsSizeSet() )
        {
            _size = pVisual->GetSize();

            // If the size is different from the file's, set the size in AGK.
            if( !pVisual->IsSizeSameAsFile() )
            {
                // If both width and height are set, set the sprite size.
                if( _size.w > 0 && _size.h > 0 )
                    agk::SetSpriteSize( _id, _size.w, _size.h );
                // If only the width is set, calculate the height.
                else if( _size.w > 0 )
                {
                    float ratio = _size.w / agk::GetSpriteWidth( _id );
                    _size.h *= ratio;
                    agk::SetSpriteSize( _id, _size.w, _size.h );
                }
                // If only the height is set, calculate the width.
                else if( _size.h > 0 )
                {
                    float ratio = _size.h / agk::GetSpriteHeight( _id );
                    _size.w *= ratio;
                    agk::SetSpriteSize( _id, _size.w, _size.h );
                }
            }
        }
        else
        {
            // If the data does not have a default size, set it to whatever the created sprite's size is.
            pVisual->SetSize( GetWorldSize() );
            _size = pVisual->GetSize();
        }
    }

    if( _pData->GetAnimationList().size() > 0 )
        _pAnimationComponent = new CAnimationComponent(this, _pData->GetAnimationList() );

    _alignment = _pData->GetAlignment();
}


/// *************************************************************************
/// <summary>
/// Clears all of the sprite's data that belong to it.
/// </summary>
/// *************************************************************************
void CSprite2D::Clear()
{
    iObject::Clear();

    _alignment = NDefs::EA_CENTER;
    _pData = nullptr;
}


/// *************************************************************************
/// <summary>
/// Delete the object that belongs to the AGK id.
/// </summary>
/// *************************************************************************
void CSprite2D::DeleteObject()
{
    if( _id > 0 )
    {
        agk::DeleteSprite( _id );

        _id = 0;
    }
}


/// *************************************************************************
/// <summary>
/// Mark the sprite for deletion.
/// </summary>
/// *************************************************************************
void CSprite2D::MarkForDeletion()
{
    _pData = nullptr;
}


/// *************************************************************************
/// <summary>
/// Whether the sprite is marked for deletion.
/// </summary>
/// *************************************************************************
bool CSprite2D::IsMarkedForDeletion() const
{
    return !_pData;
}


/// *************************************************************************
/// <summary>
/// Get the data used to create the sprite.
/// </summary>
/// *************************************************************************
const CSpriteData2D * CSprite2D::GetData() const
{
    return _pData;
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current position.
/// </summary>
/// *************************************************************************
void CSprite2D::ApplyPosition()
{
    if( _pParent )
    {
        CVector2<float> newPos = *_pParent->GetMatrix() * _position;
        agk::SetSpritePosition( _id, newPos.x, newPos.y );
    }
    else
        agk::SetSpritePosition( _id, _position.x, _position.y );

    agk::SetSpriteDepth( _id, (int)(_position.z + 0.5f) );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current rotation.
/// </summary>
/// *************************************************************************
void CSprite2D::ApplyRotation()
{
    _rotation %= 360;

    if( _pParent )
        agk::SetSpriteAngle( _id, _pParent->GetWorldRot().z + _rotation.z );
    else
        agk::SetSpriteAngle( _id, _rotation.z );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current scale.
/// </summary>
/// *************************************************************************
void CSprite2D::ApplyScale()
{
    if( _pParent )
    {
        CVector2<float> newScale = _pParent->GetWorldScale() * _scale;
        agk::SetSpriteScale( _id, newScale.w, newScale.h );
    }
    else
        agk::SetSpriteScale( _id, _scale.w, _scale.h );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current color.
/// </summary>
/// *************************************************************************
void CSprite2D::ApplyColor()
{
    if( _pParent )
    {
        CVector2<float> newScale = _pParent->GetWorldScale() * _scale;
        agk::SetSpriteScale( _id, newScale.w, newScale.h );
    }
    else
        agk::SetSpriteColor( _id, (int)(_color.r * 255 + 0.5f),
                                  (int)(_color.g * 255 + 0.5f),
                                  (int)(_color.b * 255 + 0.5f),
                                  (int)(_color.a * 255 + 0.5f) );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current visibility.
/// </summary>
/// *************************************************************************
void CSprite2D::ApplyVisibility()
{
    if( _pParent )
        agk::SetSpriteVisible( _id, _pParent->IsVisible() && _visible );
    else
        agk::SetSpriteVisible( _id, _visible );
}


/// *************************************************************************
/// <summary>
/// Get the current position set in AGK.
/// </summary>
/// *************************************************************************
CVector3<float> CSprite2D::GetWorldPos() const
{
    return CVector3<float>( agk::GetSpriteX( _id ), 
                            agk::GetSpriteY( _id ), 
                            (float)agk::GetSpriteDepth( _id ) );
}


/// *************************************************************************
/// <summary>
/// Get the current rotation set in AGK.
/// </summary>
/// *************************************************************************
CVector3<float> CSprite2D::GetWorldRot() const
{
    return CVector3<float>( 0, 0, agk::GetSpriteAngle( _id ) );
}


/// *************************************************************************
/// <summary>
/// Get the current size set in AGK.
/// </summary>
/// *************************************************************************
CVector3<float> CSprite2D::GetWorldSize() const
{
    return CVector3<float>( agk::GetSpriteWidth( _id ), 
                            agk::GetSpriteHeight( _id ) );
}


/// *************************************************************************
/// <summary>
/// Update the sprite's size using the scale.
/// </summary>
/// *************************************************************************
void CSprite2D::UpdateSize()
{
    _size = _pData->GetSize() * _scale;
}


/// *************************************************************************
/// <summary>
/// Update the sprite's scale using the size.
/// </summary>
/// *************************************************************************
void CSprite2D::UpdateScale()
{
    _scale = _size / _pData->GetSize();
}


/// *************************************************************************
/// <summary>
/// Get the sprite's visibility.
/// </summary>
/// *************************************************************************
bool CSprite2D::IsVisible() const
{
    return agk::GetSpriteVisible( _id );
}


/// *************************************************************************
/// <summary>
/// Set the sprite's alignment.
/// </summary>
/// *************************************************************************
void CSprite2D::SetAlignment( const CBitmask<uint> & alignment )
{
    _alignment = alignment;
}


/// *************************************************************************
/// <summary>
/// Get the sprite's alignment.
/// </summary>
/// *************************************************************************
CBitmask<uint> CSprite2D::GetAlignment() const
{
    return _alignment;
}


/// *************************************************************************
/// <summary>
/// Reset the sprite's position using its previous position.
/// </summary>
/// *************************************************************************
void CSprite2D::Reposition()
{
    // The parent's alignment overrides the child's alignment.
    if( _pParent )
        return;

    CVector3<float> pos = _position;
    if( NMathFunc::AlignPosition( _alignment, pos ) )
        SetPos( pos );
}
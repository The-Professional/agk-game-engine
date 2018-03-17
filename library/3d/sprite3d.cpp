// Physical component dependency
#include "sprite3d.h"

// Game lib dependencies
#include <agk.h>
#include <common\matrix4.h>
#include <3d\spritedata3d.h>
#include <managers\resourcemanager.h>
#include <utilities\settings.h>

using namespace std;
using namespace NDefs;

/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CSprite3D::CSprite3D()
{
    _type = EOT_SPRITE_3D;
}


/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// <param name="pData"> Sprite data used to create the sprite. </param> 
/// *************************************************************************
CSprite3D::CSprite3D( const CSpriteData3D * pData )
{
    _type = EOT_SPRITE_3D;

    Init( pData );
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CSprite3D::~CSprite3D()
{
    Clear();
}


/// *************************************************************************
/// <summary>
/// Initialize the sprite using its sprite data.
/// </summary>
/// <param name="pData"> Sprite data used to create the sprite. </param> 
/// *************************************************************************
void CSprite3D::Init( const CSpriteData3D * pData )
{
    // Leave if there's no data to initialize with.
    if( !pData )
        return;

    Clear();

    _pData = pData;
    const CSpriteVisualData3D * pVisual = _pData->GetVisualData();

    if( pVisual )
    {
        switch( pVisual->GetType() )
        {
            // Boxes must have a width, height, and length.
        case EMT_BOX:
            if( pVisual->GetWidth() > 0 && pVisual->GetHeight() > 0 && pVisual->GetDepth() > 0 )
                _id = agk::CreateObjectBox( pVisual->GetWidth(), pVisual->GetHeight(), pVisual->GetDepth() );
            break;

            // Cones must have a height, radius, and at least 3 columns.
        case EMT_CONE:
            if( pVisual->GetHeight() > 0 && pVisual->GetRadius() > 0 && pVisual->GetColumns() > 2 )
                _id = agk::CreateObjectCone( pVisual->GetHeight(), pVisual->GetDiameter(), pVisual->GetColumns() );
            break;

            // Cylinders must have a height, radius, and at least 3 columns.
        case EMT_CYLINDER:
            if( pVisual->GetHeight() > 0 && pVisual->GetRadius() > 0 && pVisual->GetColumns() > 2 )
                _id = agk::CreateObjectCylinder( pVisual->GetHeight(), pVisual->GetDiameter(), pVisual->GetColumns() );
            break;

            // Capsules must have a radius and height.
        case EMT_CAPSULE:
            if( pVisual->GetRadius() > 0 && pVisual->GetHeight() > 0 )
                _id = agk::CreateObjectCapsule( pVisual->GetDiameter(), pVisual->GetHeight(), Y_AXIS );
            break;

            // Planes must have a width and height.
        case EMT_PLANE:
            if( pVisual->GetWidth() > 0 && pVisual->GetHeight() > 0 )
                _id = agk::CreateObjectPlane( pVisual->GetWidth(), pVisual->GetHeight() );
            break;

            // Spheres must have a radius, at least 2 rows, and at least 3 columns.
        case EMT_SPHERE:
            if( pVisual->GetRadius() > 0 && pVisual->GetRows() > 1 && pVisual->GetColumns() > 2 )
                _id = agk::CreateObjectSphere( pVisual->GetDiameter(), pVisual->GetRows(), pVisual->GetColumns() );
            break;

            // Meshes must have a name.
        case EMT_MESH:
            if( !pVisual->GetMesh().empty() )
                _id = agk::CloneObject( CResourceManager::Instance().LoadMesh( pVisual->GetMesh() ) );
            break;
        }

        // If an object was created, apply any textures, shaders, and coloring.
        if( _id > 0 )
        {
            // Set any texture maps the sprite has.
            if( !pVisual->GetTextureMap().empty() )
            {
                int imageId = CResourceManager::Instance().LoadImage( pVisual->GetTextureMap() );
                agk::SetObjectImage( _id, imageId, ETS_TEXTURE );
            }
            if( !pVisual->GetNormalMap().empty() )
            {
                int imageId = CResourceManager::Instance().LoadImage( pVisual->GetNormalMap() );
                agk::SetObjectNormalMap( _id, imageId );
            }
            if( !pVisual->GetSpecularMap().empty() )
            {
                int imageId = CResourceManager::Instance().LoadImage( pVisual->GetSpecularMap() );
                agk::SetObjectImage( _id, imageId, ETS_SPECULAR );
            }

            // Only apply these if shadows are enabled.
            if( CSettings::Instance().ShadowsEnabled() )
            {
                agk::SetObjectCastShadow( _id, pVisual->WillCastShadow() );
                agk::SetObjectReceiveShadow( _id, pVisual->WillReceiveShadow() );
            }

            // Get the size of the sprite.
            SetSize( GetWorldSize() );

            // Set the sprite's color.
            SetColor( pVisual->GetColor() );
        }
    }
}


/// *************************************************************************
/// <summary>
/// Get the data used to create the sprite.
/// </summary>
/// *************************************************************************
const CSpriteData3D * CSprite3D::GetData() const
{
    return _pData;
}


/// *************************************************************************
/// <summary>
/// Delete the object that belongs to the AGK id.
/// </summary>
/// *************************************************************************
void CSprite3D::DeleteObject()
{
    if( _id > 0 )
    {
        // If the object has children then delete all of them. Otherwise delete normally.
        if( agk::GetObjectNumChildren( _id ) > 0 )
            agk::DeleteObjectWithChildren( _id );
        else
            agk::DeleteObject( _id );

        _id = 0;
    }

    _pData = nullptr;
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current position.
/// </summary>
/// *************************************************************************
void CSprite3D::ApplyPosition()
{
    if( _pParent )
    {
        CVector3 newPos = *_pParent->GetMatrix() * _position;
        agk::SetObjectPosition( _id, newPos.x, newPos.y, newPos.z );
    }
    else
        agk::SetObjectPosition( _id, _position.x, _position.y, _position.z );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current rotation.
/// </summary>
/// *************************************************************************
void CSprite3D::ApplyRotation()
{
    _rotation %= 360;

    if( _pParent )
    {
        CVector3 newRot = _pParent->GetWorldRot() + _rotation;
        agk::SetObjectRotation( _id, newRot.x, newRot.y, newRot.z );
    }
    else
        agk::SetObjectRotation( _id, _rotation.x, _rotation.y, _rotation.z );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current size.
/// </summary>
/// *************************************************************************
void CSprite3D::ApplySize()
{
    _scale = _size / _pData->GetSize();

    if( _pParent )
    {
        CVector3 newScale = _pParent->GetWorldScale() * _scale;
        agk::SetObjectScale( _id, newScale.w, newScale.h, newScale.d );
    }
    else
        agk::SetObjectScale( _id, _scale.w, _scale.h, _scale.d );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current scale.
/// </summary>
/// *************************************************************************
void CSprite3D::ApplyScale()
{
    _size = _pData->GetSize() * _scale;

    if( _pParent )
    {
        CVector3 newScale = _pParent->GetWorldScale() * _scale;
        agk::SetObjectScale( _id, newScale.w, newScale.h, newScale.d );
    }
    else
        agk::SetObjectScale( _id, _scale.w, _scale.h, _scale.d );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current color.
/// </summary>
/// *************************************************************************
void CSprite3D::ApplyColor()
{
    agk::SetObjectColor( _id, _color.r, _color.g, _color.b, _color.a );
}


/// *************************************************************************
/// <summary>
/// Get the current position set in AGK.
/// </summary>
/// *************************************************************************
CVector3 CSprite3D::GetWorldPos() const
{
    return CVector3( agk::GetObjectX( _id ),
                     agk::GetObjectY( _id ),
                     agk::GetObjectZ( _id ) );
}


/// *************************************************************************
/// <summary>
/// Get the current rotation set in AGK.
/// </summary>
/// *************************************************************************
CVector3 CSprite3D::GetWorldRot() const
{
    return CVector3( agk::GetObjectAngleX( _id ),
                     agk::GetObjectAngleY( _id ), 
                     agk::GetObjectAngleZ( _id ) );
}


/// *************************************************************************
/// <summary>
/// Get the current size set in AGK.
/// </summary>
/// *************************************************************************
CVector3 CSprite3D::GetWorldSize() const
{
    return CVector3( abs( agk::GetObjectSizeMaxX( _id ) - agk::GetObjectSizeMinX( _id ) ),
                     abs( agk::GetObjectSizeMaxY( _id ) - agk::GetObjectSizeMinY( _id ) ),
                     abs( agk::GetObjectSizeMaxZ( _id ) - agk::GetObjectSizeMinZ( _id ) ) );
}


/// *************************************************************************
/// <summary>
/// Set the sprite's visibility.
/// </summary>
/// *************************************************************************
void CSprite3D::SetVisible( bool visible )
{
    agk::SetObjectVisible( _id, visible );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's visibility.
/// </summary>
/// *************************************************************************
bool CSprite3D::IsVisible() const
{
    return agk::GetObjectVisible( _id );
}
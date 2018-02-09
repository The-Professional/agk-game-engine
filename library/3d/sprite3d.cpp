// Physical component dependency
#include "sprite3d.h"

// Game lib dependencies
#include <agk.h>
#include <3d\spritedata3d.h>
#include <managers\resourcemanager.h>
#include <utilities\settings.h>

/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CSprite3D::CSprite3D()
{
    _type = NDefs::EOT_SPRITE_3D;
}


/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// <param name="pData"> Sprite data used to create the sprite. </param> 
/// *************************************************************************
CSprite3D::CSprite3D( const CSpriteData3D * pData )
{
    _type = NDefs::EOT_SPRITE_3D;
    _pData = pData;
    Init();
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
/// *************************************************************************
void CSprite3D::Init()
{
    // Leave if there's no data to initialize with.
    if( !_pData )
        return;

    Clear();

    const CSpriteVisualData3D * pVisual = _pData->GetVisualData();

    if( pVisual )
    {
        switch( pVisual->GetType() )
        {
            // Boxes must have a width, height, and length.
        case NDefs::EMT_BOX:
            if( pVisual->GetWidth() > 0 && pVisual->GetHeight() > 0 && pVisual->GetDepth() > 0 )
                _id = agk::CreateObjectBox( pVisual->GetWidth(), pVisual->GetHeight(), pVisual->GetDepth() );
            break;

            // Cones must have a height, radius, and at least 3 columns.
        case NDefs::EMT_CONE:
            if( pVisual->GetHeight() > 0 && pVisual->GetRadius() > 0 && pVisual->GetColumns() > 2 )
                _id = agk::CreateObjectCone( pVisual->GetHeight(), pVisual->GetDiameter(), pVisual->GetColumns() );
            break;

            // Cylinders must have a height, radius, and at least 3 columns.
        case NDefs::EMT_CYLINDER:
            if( pVisual->GetHeight() > 0 && pVisual->GetRadius() > 0 && pVisual->GetColumns() > 2 )
                _id = agk::CreateObjectCylinder( pVisual->GetHeight(), pVisual->GetDiameter(), pVisual->GetColumns() );
            break;

            // Capsules must have a radius and height.
        case NDefs::EMT_CAPSULE:
            if( pVisual->GetRadius() > 0 && pVisual->GetHeight() > 0 )
                _id = agk::CreateObjectCapsule( pVisual->GetDiameter(), pVisual->GetHeight(), Y_AXIS );
            break;

            // Planes must have a width and height.
        case NDefs::EMT_PLANE:
            if( pVisual->GetWidth() > 0 && pVisual->GetHeight() > 0 )
                _id = agk::CreateObjectPlane( pVisual->GetWidth(), pVisual->GetHeight() );
            break;

            // Spheres must have a radius, at least 2 rows, and at least 3 columns.
        case NDefs::EMT_SPHERE:
            if( pVisual->GetRadius() > 0 && pVisual->GetRows() > 1 && pVisual->GetColumns() > 2 )
                _id = agk::CreateObjectSphere( pVisual->GetDiameter(), pVisual->GetRows(), pVisual->GetColumns() );
            break;

            // Meshes must have a name.
        case NDefs::EMT_MESH:
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
                agk::SetObjectImage( _id, imageId, NDefs::ETS_TEXTURE );
            }
            if( !pVisual->GetNormalMap().empty() )
            {
                int imageId = CResourceManager::Instance().LoadImage( pVisual->GetNormalMap() );
                agk::SetObjectNormalMap( _id, imageId );
            }
            if( !pVisual->GetSpecularMap().empty() )
            {
                int imageId = CResourceManager::Instance().LoadImage( pVisual->GetSpecularMap() );
                agk::SetObjectImage( _id, imageId, NDefs::ETS_SPECULAR );
            }

            // Only apply these if shadows are enabled.
            if( CSettings::Instance().ShadowsEnabled() )
            {
                agk::SetObjectCastShadow( _id, pVisual->WillCastShadow() );
                agk::SetObjectReceiveShadow( _id, pVisual->WillReceiveShadow() );
            }

            // Get the size of the sprite.
            _size.x = std::abs( agk::GetObjectSizeMaxX( _id ) - agk::GetObjectSizeMinX( _id ) );
            _size.y = std::abs( agk::GetObjectSizeMaxY( _id ) - agk::GetObjectSizeMinY( _id ) );
            _size.z = std::abs( agk::GetObjectSizeMaxZ( _id ) - agk::GetObjectSizeMinZ( _id ) );

            // Set the sprite's color.
            SetColor( pVisual->GetColor() );
        }
    }
}


/// *************************************************************************
/// <summary>
/// Set the data used to create the sprite.
/// </summary>
/// *************************************************************************
void CSprite3D::SetData( CSpriteData3D * pData )
{
    _pData = pData;
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
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current position.
/// </summary>
/// *************************************************************************
void CSprite3D::UpdatePosAGK()
{
    agk::SetObjectPosition( _id, _position.x, _position.y, _position.z );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current rotation.
/// </summary>
/// *************************************************************************
void CSprite3D::UpdateRotAGK()
{
    agk::SetObjectRotation( _id, _rotation.x, _rotation.y, _rotation.z );
}


/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current size.
/// </summary>
/// *************************************************************************
void CSprite3D::UpdateSizeAGK()
{
    // TODO: Add logic here to get the size and adjust the scale.
}

/// *************************************************************************
/// <summary>
/// Update AGK with the sprite's current color.
/// </summary>
/// *************************************************************************
void CSprite3D::UpdateColorAGK()
{
    agk::SetObjectColor( _id, _color.r, _color.g, _color.b, _color.a );
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
// Physical component dependency
#include "sprite3d.h"

// Game lib dependencies
#include <agk.h>
#include <3d\spritedata3d.h>
#include <managers\resourcemanager.h>

/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CSprite3D::CSprite3D()
{
}


/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// <param name="pData"> Sprite data used to create the sprite. </param> 
/// *************************************************************************
CSprite3D::CSprite3D( const CSpriteData3D * pData )
{
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
/// Initialize the sprite with the passed in object type.
/// </summary>
/// <param name="pData"> Sprite data used to create the sprite. </param>  
/// *************************************************************************
void CSprite3D::Init( const CSpriteData3D * pData )
{
    Clear();

    _pData = pData;
    const CSpriteVisualData3D & visual = pData->GetVisualData();

    switch( visual.GetType() )
    {
    // Boxes must have a width, height, and length.
    case NDefs::EOT_BOX:
        if( visual.GetWidth() > 0 && visual.GetHeight() > 0 && visual.GetLength() > 0 )
            _id = agk::CreateObjectBox( visual.GetWidth(), visual.GetHeight(), visual.GetLength() );
        break;

    // Cones must have a height, radius, and at least 3 columns.
    case NDefs::EOT_CONE:
        if( visual.GetHeight() > 0 && visual.GetRadius() > 0 && visual.GetColumns() > 2 )
            _id = agk::CreateObjectCone( visual.GetHeight(), visual.GetDiameter(), visual.GetColumns() );
        break;

    // Cylinders must have a height, radius, and at least 3 columns.
    case NDefs::EOT_CYLINDER:
        if( visual.GetHeight() > 0 && visual.GetRadius() > 0 && visual.GetColumns() > 2 )
            _id = agk::CreateObjectCylinder( visual.GetHeight(), visual.GetDiameter(), visual.GetColumns() );
        break;

    // Capsules must have a radius and height.
    case NDefs::EOT_CAPSULE:
        if( visual.GetRadius() > 0 && visual.GetHeight() > 0 )
            _id = agk::CreateObjectCapsule( visual.GetDiameter(), visual.GetHeight(), X_AXIS );
        break;

    // Planes must have a width and height.
    case NDefs::EOT_PLANE:
        if( visual.GetWidth() > 0 && visual.GetHeight() > 0 )
            _id = agk::CreateObjectPlane( visual.GetWidth(), visual.GetHeight() );
        break;

    // Spheres must have a radius, at least 2 rows, and at least 3 columns.
    case NDefs::EOT_SPHERE:
        if( visual.GetRadius() > 0 && visual.GetRows() > 1 && visual.GetColumns() > 2 )
            _id = agk::CreateObjectSphere( visual.GetDiameter(), visual.GetRows(), visual.GetColumns() );
        break;

    // Meshes must have a name.
    case NDefs::EOT_MESH:
        if( !visual.GetMesh().empty() )
            _id = agk::CloneObject( CResourceManager::Instance().LoadMesh( visual.GetMesh() ) );
        break;
    }

    // If an object was created, apply any textures, shaders, and coloring.
    if( _id > 0 )
    {
        // Set any texture maps the sprite has.
        if( !visual.GetTextureMap().empty() )
        {
            int imageId = CResourceManager::Instance().LoadImage( visual.GetTextureMap() );
            agk::SetObjectImage( _id, imageId, NDefs::ETS_TEXTURE );
        }
        if( !visual.GetNormalMap().empty() )
        {
            int imageId = CResourceManager::Instance().LoadImage( visual.GetNormalMap() );
            agk::SetObjectNormalMap( _id, imageId );
        }
        if( !visual.GetSpecularMap().empty() )
        {
            int imageId = CResourceManager::Instance().LoadImage( visual.GetSpecularMap() );
            agk::SetObjectImage( _id, imageId, NDefs::ETS_SPECULAR );
        }

        //// Set the sprite's shader.
        //if( visual.GetShaderID() > 0 )
        //    agk::SetObjectShader( _objectId, visual.GetShaderID() );

        // Set the sprite's color.
        agk::SetObjectColor( _id, visual.GetColor().r, visual.GetColor().g, visual.GetColor().b, visual.GetColor().a );
    }
}


/// *************************************************************************
/// <summary>
/// Get the name of the sprite.
/// </summary>
/// *************************************************************************
const std::string & CSprite3D::GetName() const
{
    return _pData->GetName();
}


/// *************************************************************************
/// <summary>
/// Clears all of the sprites data that belong to it.
/// </summary>
/// *************************************************************************
void CSprite3D::Clear()
{
    if( _id > 0 )
    {
        agk::DeleteObject( _id );
        _id = 0;
    }
}


/// *************************************************************************
/// <summary>
/// Set the sprite's position.
/// </summary>
/// *************************************************************************
void CSprite3D::SetPos( float x, float y, float z ) 
{ 
    agk::SetObjectPosition( _id, x, y, z );
}

/// <summary>
/// Set the sprite's position.
/// </summary>
void CSprite3D::SetPos( const CVector3 & pos )
{ 
    agk::SetObjectPosition( _id, pos.x, pos.y, pos.z );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's position.
/// </summary>
/// *************************************************************************
CVector3 CSprite3D::GetPos() const 
{ 
    return CVector3( agk::GetObjectX( _id ), agk::GetObjectY( _id ), agk::GetObjectZ( _id ) );
}

/// <summary>
/// Get the sprite's X position.
/// </summary>
float CSprite3D::GetPosX() const
{
    return agk::GetObjectX( _id );
}

/// <summary>
/// Get the sprite's Y position.
/// </summary>
float CSprite3D::GetPosY() const
{
    return agk::GetObjectY( _id );
}

/// <summary>
/// Get the sprite's Z position.
/// </summary>
float CSprite3D::GetPosZ() const
{
    return agk::GetObjectZ( _id );
}


/// *************************************************************************
/// <summary>
/// Set the sprite's rotation.
/// </summary>
/// *************************************************************************
void CSprite3D::SetRot( float x, float y, float z )
{
    agk::SetObjectRotation( _id, x, y, z );
}

/// <summary>
/// Set the sprite's rotation.
/// </summary>
void CSprite3D::SetRot( const CVector3 & rot )
{
    agk::SetObjectRotation( _id, rot.x, rot.y, rot.z );
}


/// *************************************************************************
/// <summary>
/// Increment the sprite's rotation.
/// </summary>
/// *************************************************************************
void CSprite3D::IncRot( float x, float y, float z )
{
    agk::RotateObjectLocalY( _id, y );
    agk::RotateObjectLocalX( _id, x );
    agk::RotateObjectLocalZ( _id, z );
}

/// <summary>
/// Increment the sprite's rotation.
/// </summary>
void CSprite3D::IncRotX( float value )
{
    agk::RotateObjectLocalX( _id, value );
}

/// <summary>
/// Increment the sprite's rotation.
/// </summary>
void CSprite3D::IncRotY( float value )
{
    agk::RotateObjectLocalY( _id, value );
}

/// <summary>
/// Increment the sprite's rotation.
/// </summary>
void CSprite3D::IncRotZ( float value )
{
    agk::RotateObjectLocalZ( _id, value );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's rotation.
/// </summary>
/// *************************************************************************
CVector3 CSprite3D::GetRot() const
{
    return CVector3( agk::GetObjectAngleX( _id ), agk::GetObjectAngleY( _id ), agk::GetObjectAngleZ( _id ) );
}

/// <summary>
/// Get the sprite's X rotation.
/// </summary>
float CSprite3D::GetRotX() const
{
    return agk::GetObjectAngleX( _id );
}

/// <summary>
/// Get the sprite's Y rotation.
/// </summary>
float CSprite3D::GetRotY() const
{
    return agk::GetObjectAngleY( _id );
}

/// <summary>
/// Get the sprite's Z rotation.
/// </summary>
float CSprite3D::GetRotZ() const
{
    return agk::GetObjectAngleZ( _id );
}


/// *************************************************************************
/// <summary>
/// Set the sprite's scale.
/// </summary>
/// *************************************************************************
void CSprite3D::SetScale( float uniform )
{
    _scale = CVector3( uniform );
    agk::SetObjectScale( _id, uniform, uniform, uniform );
}

void CSprite3D::SetScale( float x, float y, float z )
{
    _scale = CVector3( x, y, z );
    agk::SetObjectScale( _id, x, y, z );
}

/// <summary>
/// Set the sprite's scale.
/// </summary>
void CSprite3D::SetScale( const CVector3 & scale )
{
    _scale = scale;
    agk::SetObjectScale( _id, scale.x, scale.y, scale.z );
}


/// *************************************************************************
/// <summary>
/// Get the sprite's scale.
/// </summary>
/// *************************************************************************
const CVector3 & CSprite3D::GetScale() const
{
    return _scale;
}

/// <summary>
/// Get the sprite's X scale.
/// </summary>
float CSprite3D::GetScaleX() const
{
    return _scale.x;
}

/// <summary>
/// Get the sprite's Y scale.
/// </summary>
float CSprite3D::GetScaleY() const
{
    return _scale.y;
}

/// <summary>
/// Get the sprite's Z scale.
/// </summary>
float CSprite3D::GetScaleZ() const
{
    return _scale.z;
}
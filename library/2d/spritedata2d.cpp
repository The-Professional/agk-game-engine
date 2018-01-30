// Physical component dependency
#include "spritedata2d.h"

// Game lib dependencies
#include <utilities\deletefuncs.h>

/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CSpriteData2D::CSpriteData2D()
{
}


/// *************************************************************************
/// <summary>
/// Copy constructor
/// </summary>
/// *************************************************************************
CSpriteData2D::CSpriteData2D( const CSpriteData2D & obj )
{
    *this = obj;
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CSpriteData2D::~CSpriteData2D()
{
    NDelFunc::Delete( _pVisualData );
}


/// *************************************************************************
/// <summary>
/// Load the sprite data from the passed in iterator.
/// </summary>
/// <param name="iter"> JSON node to parse. </param>
/// *************************************************************************
void CSpriteData2D::LoadFromIter( const std::string & name, nlohmann::json::const_iterator iter )
{
    _name = name;

    auto visualIter = iter->find( "visual" );
    if( visualIter != iter->end() )
    {
        _pVisualData = new CSpriteVisualData2D();
        _pVisualData->LoadFromIter( visualIter );
    }
}


/// *************************************************************************
/// <summary>
/// Get the visual data of the sprite.
/// </summary>
/// <returns> Object holding all of the sprite's visual data. </returns>
/// *************************************************************************
const CSpriteVisualData2D * CSpriteData2D::GetVisualData() const
{
    return _pVisualData;
}


///// *************************************************************************
///// <summary> 
///// Get the physics data of the sprite.
///// </summary>
///// <returns> Object holding all of the sprite's physics data. </returns>
///// *************************************************************************
//const CSpritePhysicsData2D & CSpriteData2D::GetPhysicsData() const
//{
//    return _physicsData;
//}


/// *************************************************************************
/// <summary> 
/// Get the name of the sprite.
/// </summary>
/// <returns> Sprite's name. </returns>
/// *************************************************************************
const std::string & CSpriteData2D::GetName() const
{
    return _name;
}


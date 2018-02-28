// Physical component dependency
#include "spritedata3d.h"

// Game lib dependencies
#include <utilities\deletefuncs.h>

using namespace std;
using namespace nlohmann;


/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CSpriteData3D::CSpriteData3D()
{
}


/// *************************************************************************
/// <summary>
/// Copy constructor
/// </summary>
/// *************************************************************************
CSpriteData3D::CSpriteData3D( const CSpriteData3D & obj )
{
    *this = obj;
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CSpriteData3D::~CSpriteData3D()
{
    NDelFunc::Delete( _pVisualData );
}


/// *************************************************************************
/// <summary>
/// Load the sprite data from the passed in iterator.
/// </summary>
/// <param name="iter"> JSON node to parse. </param>
/// *************************************************************************
void CSpriteData3D::LoadFromIter( const std::string & name, nlohmann::json::const_iterator iter )
{
    _name = name;

    auto visualIter = iter->find( "visual" );
    if( visualIter != iter->end() )
    {
        _pVisualData = new CSpriteVisualData3D();
        _pVisualData->LoadFromIter( visualIter );
    }

    NParseHelper::GetString( iter, "animations", _animationList );
}


/// *************************************************************************
/// <summary>
/// Get the visual data of the sprite.
/// </summary>
/// <returns> Object holding all of the sprite's visual data. </returns>
/// *************************************************************************
const CSpriteVisualData3D * CSpriteData3D::GetVisualData() const
{
    return _pVisualData;
}


/// *************************************************************************
/// <summary> 
/// Get the name of the sprite.
/// </summary>
/// <returns> Sprite's name. </returns>
/// *************************************************************************
const std::string & CSpriteData3D::GetName() const
{
    return _name;
}


/// *************************************************************************
/// <summary> 
/// Get the list of animations this sprite can perform.
/// </summary>
/// *************************************************************************
const vector<string> & CSpriteData3D::GetAnimationList() const
{
    return _animationList;
}

// Physical component dependency
#include "spritedata2d.h"

// Game lib dependencies
#include <utilities\deletefuncs.h>

using namespace std;
using namespace nlohmann;

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
void CSpriteData2D::LoadFromIter( const string & name, json::const_iterator iter )
{
    _name = name;

    auto visualIter = iter->find( "visual" );
    if( visualIter != iter->end() )
    {
        _pVisualData = new CSpriteVisualData2D();
        _pVisualData->LoadFromIter( visualIter );
    }

    NParseHelper::GetAlignment( iter, "alignment", _alignment );
    NParseHelper::GetString( iter, "animations", _animationList );
}


/// *************************************************************************
/// <summary>
/// Get the visual data of the sprite.
/// </summary>
/// *************************************************************************
const CSpriteVisualData2D * CSpriteData2D::GetVisualData() const
{
    return _pVisualData;
}


/// *************************************************************************
/// <summary> 
/// Get the name of the sprite.
/// </summary>
/// *************************************************************************
const string & CSpriteData2D::GetName() const
{
    return _name;
}


/// *************************************************************************
/// <summary> 
/// Get the window alignment of the sprite.
/// </summary>
/// *************************************************************************
const CBitmask<uint> & CSpriteData2D::GetAlignment() const
{
    return _alignment;
}


/// *************************************************************************
/// <summary> 
/// Get the list of animations this sprite can perform.
/// </summary>
/// *************************************************************************
const vector<string> & CSpriteData2D::GetAnimationList() const
{
    return _animationList;
}
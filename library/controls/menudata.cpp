// Physical component dependency
#include "menudata.h"

// Game lib dependencies
#include <common\collectionobject.h>

using namespace std;
using namespace nlohmann;
using namespace NDefs;


/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CMenuData::CMenuData()
{
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CMenuData::~CMenuData()
{
}


/// *************************************************************************
/// <summary>
/// Load the menu data from the passed in iterator.
/// </summary>
/// <param name="name"> Name of the menu. </param>
/// <param name="iter"> JSON node to parse. </param>
/// *************************************************************************
void CMenuData::LoadFromIter( const string & name, json::const_iterator iter )
{
    _name = name;

    _sizeSet = NParseHelper::GetWH( iter, "size", _size );
    NParseHelper::GetValue( iter, "enabled", _enabled );
    NParseHelper::GetAlignment( iter, "alignment", _alignment );
    NParseHelper::GetAnimationList( iter, "animations", _animationList );

    auto collectionIter = iter->find( "collection" );
    if( collectionIter != iter->end() )
    {
        auto objectIter = collectionIter->begin();
        while( objectIter != collectionIter->end() )
        {
            _spriteList.push_back( CCollectionObject() );
            NParseHelper::GetCollectionObject( objectIter, _spriteList.back() );
            ++objectIter;
        }
    }
}


/// *************************************************************************
/// <summary>
/// Get the menu's name.
/// </summary>
/// *************************************************************************
const string & CMenuData::GetName() const
{
    return _name;
}


/// *************************************************************************
/// <summary>
/// Get the menu's alignment.
/// </summary>
/// *************************************************************************
const CBitmask<uint> & CMenuData::GetAlignment() const
{
    return _alignment;
}


/// *************************************************************************
/// <summary>
/// Whether or not the menu should be enabled.
/// </summary>
/// *************************************************************************
bool CMenuData::IsEnabled() const
{
    return _enabled;
}


/// *************************************************************************
/// <summary> 
/// Get the list of animations this menu can perform.
/// </summary>
/// *************************************************************************
const vector<vector<string>> & CMenuData::GetAnimationList() const
{
    return _animationList;
}


/// *************************************************************************
/// <summary>
/// Get the list of sprites owned by the menu.
/// </summary>
/// *************************************************************************
const vector<CCollectionObject> & CMenuData::GetSpriteList() const
{
    return _spriteList;
}


/// *************************************************************************
/// <summary>
/// Get the list of controls owned by the menu.
/// </summary>
/// *************************************************************************
const vector<CCollectionObject> & CMenuData::GetControlList() const
{
    return _controlList;
}


/// *************************************************************************
/// <summary> 
/// Set the menu's size. This is considered the default size, so we'll want
/// to know this. If it's not set in the menu's data, we'll need to set this
/// after we create the first menu and know its size.
/// </summary>
/// *************************************************************************
void CMenuData::SetSize( const CVector2<float> & size )
{
    if( size.IsFilled() )
    {
        _size = size;
        _sizeSet = true;
    }
}


/// *************************************************************************
/// <summary> 
/// Get the menu's size.
/// </summary>
/// *************************************************************************
const CVector2<float> & CMenuData::GetSize() const
{
    return _size;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the size was set.
/// </summary>
/// *************************************************************************
bool CMenuData::IsSizeSet() const
{
    return _sizeSet;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the menu is the same as the file.
/// </summary>
/// *************************************************************************
bool CMenuData::IsSizeSameAsFile() const
{
    return _sizeSameAsFile;
}
// Physical component dependency
#include "controldata.h"

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
CControlData::CControlData()
{
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CControlData::~CControlData()
{
}


/// *************************************************************************
/// <summary>
/// Load the control data from the passed in iterator.
/// </summary>
/// <param name="name"> Name of the control. </param>
/// <param name="iter"> JSON node to parse. </param>
/// *************************************************************************
void CControlData::LoadFromIter( const string & name, json::const_iterator iter )
{
    _name = name;

    NParseHelper::GetControlType( iter, "type", _type );
    _sizeSet = NParseHelper::GetWH( iter, "size", _size );
    NParseHelper::GetControlState( iter, "state", _state );
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
/// Get the control's name.
/// </summary>
/// *************************************************************************
const string & CControlData::GetName() const
{
    return _name;
}


/// *************************************************************************
/// <summary>
/// Get the control's alignment.
/// </summary>
/// *************************************************************************
const CBitmask<uint> & CControlData::GetAlignment() const
{
    return _alignment;
}


/// *************************************************************************
/// <summary>
/// Get the control's type.
/// </summary>
/// *************************************************************************
EControlType CControlData::GetControlType() const
{
    return _type;
}


/// *************************************************************************
/// <summary>
/// Get the control's initial state.
/// </summary>
/// *************************************************************************
EControlState CControlData::GetState() const
{
    return _state;
}


/// *************************************************************************
/// <summary> 
/// Get the list of animations this control can perform.
/// </summary>
/// *************************************************************************
const vector<vector<string>> & CControlData::GetAnimationList() const
{
    return _animationList;
}


/// *************************************************************************
/// <summary>
/// Get the list of sprites owned by the control.
/// </summary>
/// *************************************************************************
const vector<CCollectionObject> & CControlData::GetSpriteList() const
{
    return _spriteList;
}


/// *************************************************************************
/// <summary> 
/// Set the control's size. This is considered the default size, so we'll want
/// to know this. If it's not set in the control's data, we'll need to set this
/// after we create the first control and know its size.
/// </summary>
/// *************************************************************************
void CControlData::SetSize( const CVector2<float> & size )
{
    if( size.IsFilled() )
    {
        _size = size;
        _sizeSet = true;
    }
}


/// *************************************************************************
/// <summary> 
/// Get the control's size.
/// </summary>
/// *************************************************************************
const CVector2<float> & CControlData::GetSize() const
{
    return _size;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the size was set.
/// </summary>
/// *************************************************************************
bool CControlData::IsSizeSet() const
{
    return _sizeSet;
}


/// *************************************************************************
/// <summary> 
/// Whether or not the size is the same as the file.
/// </summary>
/// *************************************************************************
bool CControlData::IsSizeSameAsFile() const
{
    return _sizeSameAsFile;
}
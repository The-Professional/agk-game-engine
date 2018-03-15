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
/// Load the sprite data from the passed in iterator.
/// </summary>
/// <param name="name"> Name of the control. </param>
/// <param name="iter"> JSON node to parse. </param>
/// *************************************************************************
void CControlData::LoadFromIter( const string & name, json::const_iterator iter )
{
    _name = name;

    NParseHelper::GetControlType( iter, "type", _type );
    NParseHelper::GetControlState( iter, "state", _state );
    NParseHelper::GetAlignment( iter, "alignment", _alignment );

    auto collectionIter = iter->find( "sprites" );
    if( collectionIter != iter->end() )
    {
        auto spriteIter = collectionIter->begin();
        while( spriteIter != collectionIter->end() )
        {
            _spriteList.push_back( CCollectionObject() );
            NParseHelper::GetCollectionObject( spriteIter, _spriteList.back() );
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
/// Get the control's alignment.
/// </summary>
/// *************************************************************************
const CBitmask<uint> & CControlData::GetAlignment() const
{
    return _alignment;
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
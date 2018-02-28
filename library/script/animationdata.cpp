// Physical component dependency
#include "animationdata.h"


/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CAnimationData::CAnimationData()
{
}


/// *************************************************************************
/// <summary>
/// Copy constructor
/// </summary>
/// *************************************************************************
CAnimationData::CAnimationData( const CAnimationData & obj )
{
    *this = obj;
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CAnimationData::~CAnimationData()
{
}


/// *************************************************************************
/// <summary>
/// Load the animation data from the passed in iterator.
/// </summary>
/// <param name="iter"> JSON node to parse. </param>
/// *************************************************************************
void CAnimationData::LoadFromIter( nlohmann::json::const_iterator iter )
{
    NParseHelper::GetString( iter, "name", _name );
    NParseHelper::GetString( iter, "functions", _functionList );
    NParseHelper::GetInt( iter, "loop", _loopCount );
    NParseHelper::GetScriptEndType( iter, _endType );

}


/// *************************************************************************
/// <summary> 
/// Get the name of the animation.
/// </summary>
/// *************************************************************************
const std::string & CAnimationData::GetName() const
{
    return _name;
}


/// *************************************************************************
/// <summary> 
/// Get the number of times to loop the animation.
/// </summary>
/// *************************************************************************
int CAnimationData::GetLoopCount() const
{
    return _loopCount;
}


/// *************************************************************************
/// <summary> 
/// Get the end type of the script.
/// </summary>
/// *************************************************************************
NDefs::EAnimationEndType CAnimationData::GetScriptEndType() const
{
    return _endType;
}


/// *************************************************************************
/// <summary> 
/// Get the list of script functions.
/// </summary>
/// *************************************************************************
const std::vector<std::string> & CAnimationData::GetFunctionList() const
{
    return _functionList;
}


/// *************************************************************************
/// <summary> 
/// Get the fields that are modified in the animation. This is used to determine
/// which scripts conflict with each other.
/// </summary>
/// *************************************************************************
CBitmask<uint> CAnimationData::Modifies() const
{
    return _modifies;
}
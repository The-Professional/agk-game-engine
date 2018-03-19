// Physical component dependency
#include "animationdata.h"

using namespace NDefs;
using namespace std;

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
    NParseHelper::GetEndType( iter, _endType );
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
EEndType CAnimationData::GetEndType() const
{
    return _endType;
}


/// *************************************************************************
/// <summary> 
/// Get the list of script functions.
/// </summary>
/// *************************************************************************
const vector<string> & CAnimationData::GetFunctionList() const
{
    return _functionList;
}
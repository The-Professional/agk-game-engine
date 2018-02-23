// Physical component dependency
#include "scriptdata.h"


/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CScriptData::CScriptData()
{
}


/// *************************************************************************
/// <summary>
/// Copy constructor
/// </summary>
/// *************************************************************************
CScriptData::CScriptData( const CScriptData & obj )
{
    *this = obj;
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CScriptData::~CScriptData()
{
}


/// *************************************************************************
/// <summary>
/// Load the script data from the passed in iterator.
/// </summary>
/// <param name="name"> Name of the script. </param>
/// <param name="iter"> JSON node to parse. </param>
/// *************************************************************************
void CScriptData::LoadFromIter( const std::string & name, nlohmann::json::const_iterator iter )
{
    _name = name;

    NParseHelper::GetInt( iter, "loop", _loopCount );
    NParseHelper::GetScriptEndType( iter, _endType );
}


/// *************************************************************************
/// <summary> 
/// Get the name of the script.
/// </summary>
/// *************************************************************************
const std::string & CScriptData::GetName() const
{
    return _name;
}


/// *************************************************************************
/// <summary> 
/// Get the number of times to loop the script.
/// </summary>
/// *************************************************************************
int CScriptData::GetLoopCount() const
{
    return _loopCount;
}


/// *************************************************************************
/// <summary> 
/// Get the end type of the script.
/// </summary>
/// *************************************************************************
NDefs::EScriptEndType CScriptData::GetScriptEndType() const
{
    return _endType;
}
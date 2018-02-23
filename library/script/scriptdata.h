#ifndef __script_data_h__
#define __script_data_h__

// Game lib dependencies
#include <common\defs.h>
#include <utilities\jsonparsehelper.h>

// Standard lib dependencies
#include <string>
#include <vector>

/// *************************************************************************
/// <summary>
/// Class containing the default creation data for a script.
/// </summary>
/// *************************************************************************
class CScriptData
{
public:

    CScriptData();
    CScriptData( const CScriptData & obj );
    ~CScriptData();

    // Load the script data from the passed in iterator.
    void LoadFromIter( const std::string & name, nlohmann::json::const_iterator iter );

    // Get the name of the script data.
    const std::string & GetName() const;

    // Get the number of times to loop the script.
    int GetLoopCount() const;

    // Get the end type of the script.
    NDefs::EScriptEndType GetScriptEndType() const;

private:

    // The name of the script data
    std::string _name;

    // The number of times the script should loop.
    int _loopCount = 0;

    // The list of functions used in the script.
    std::vector<std::string> _functionList;

    // How the script should end when it is stopped before it finishes.
    NDefs::EScriptEndType _endType = NDefs::ESE_STOP;
};

#endif  // __script_data_h__

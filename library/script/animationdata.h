#ifndef __animation_data_h__
#define __animation_data_h__

// Game lib dependencies
#include <common\defs.h>
#include <common\bitmask.h>
#include <utilities\jsonparsehelper.h>

// Standard lib dependencies
#include <string>
#include <vector>

/// *************************************************************************
/// <summary>
/// Class containing the default creation data for an animation.
/// </summary>
/// *************************************************************************
class CAnimationData
{
public:

    CAnimationData();
    CAnimationData( const CAnimationData & obj );
    ~CAnimationData();

    // Load the animation data from the passed in iterator.
    void LoadFromIter( nlohmann::json::const_iterator iter );

    // Get the name of the animation.
    const std::string & GetName() const;

    // Get the number of times to loop the animation.
    int GetLoopCount() const;

    // Get the end type of the animation.
    NDefs::EEndType GetEndType() const;

    // Get the list of script functions.
    const std::vector<std::string> & GetFunctionList() const;

private:

    // The name of the animation.
    std::string _name;

    // The number of times the animation should loop.
    int _loopCount = 0;

    // The list of script functions used in the animation.
    std::vector<std::string> _functionList;

    // How the animation should end when it is stopped before it finishes.
    NDefs::EEndType _endType = NDefs::EET_NULL;
};

#endif  // __animation_data_h__

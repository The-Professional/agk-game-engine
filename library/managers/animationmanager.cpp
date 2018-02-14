// Physical dependency
#include "animationmanager.h"

// Game lib dependencies
#include <agk.h>
#include <utilities\deletefuncs.h>
#include <utilities\generalfuncs.h>
#include <animation\tweenanimation.h>

using namespace std;
using namespace NDefs;

/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// *************************************************************************
CAnimationManager::CAnimationManager()
{
    _interpolationList.insert( pair<string, int>( "linear", agk::TweenLinear() ) );
    _interpolationList.insert( pair<string, int>( "easeIn1", agk::TweenEaseIn1() ) );
    _interpolationList.insert( pair<string, int>( "easeIn2", agk::TweenEaseIn2() ) );
    _interpolationList.insert( pair<string, int>( "bounce", agk::TweenBounce() ) );
    _interpolationList.insert( pair<string, int>( "easeOut1", agk::TweenEaseOut1() ) );
    _interpolationList.insert( pair<string, int>( "easeOut2", agk::TweenEaseOut2() ) );
    _interpolationList.insert( pair<string, int>( "overshoot", agk::TweenOvershoot() ) );
    _interpolationList.insert( pair<string, int>( "smooth1", agk::TweenSmooth1() ) );
    _interpolationList.insert( pair<string, int>( "smooth2", agk::TweenSmooth2() ) );

    _transformTypeList.insert( pair<string, uint>( "translate", ETT_POSITION ) );
    _transformTypeList.insert( pair<string, uint>( "rotate", ETT_ROTATION ) );
    _transformTypeList.insert( pair<string, uint>( "size", ETT_SIZE ) );
    _transformTypeList.insert( pair<string, uint>( "color", ETT_COLOR ) );
}


/// *************************************************************************
/// <summary> 
/// Destructor
/// </summary>
/// *************************************************************************
CAnimationManager::~CAnimationManager()
{
    Clear();
}


/// *************************************************************************
/// <summary> 
/// Free the animation resources.
/// </summary>
/// *************************************************************************
void CAnimationManager::Clear()
{
    NDelFunc::DeleteMapPointers( _animationList );
}


/// *************************************************************************
/// <summary> 
/// Get the interpolation id from AGK.
/// </summary>
/// *************************************************************************
int CAnimationManager::GetInterpolation( const string & interpolation ) const
{
    auto iter = _interpolationList.find( interpolation );
    if( iter != _interpolationList.end() )
        return iter->second;

    return 0;
}


/// *************************************************************************
/// <summary> 
/// Get the transform type from the passed in string.
/// </summary>
/// *************************************************************************
uint CAnimationManager::GetTransformType( const string & type ) const
{
    auto iter = _transformTypeList.find( type );
    if( iter != _transformTypeList.end() )
        return iter->second;

    return ETT_NULL;
}


/// *************************************************************************
/// <summary> 
/// Load the list of animations from the passed in folder.
/// </summary>
/// *************************************************************************
void CAnimationManager::LoadAnimationList( const std::string & path )
{
    NGeneralFuncs::AddFilesToMap( path, _animationFileList );
}
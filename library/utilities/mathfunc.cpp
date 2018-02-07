// Physical component dependency
#include "mathfunc.h"

// Game lib dependencies
#include <agk.h>
#include <utilities\exceptionhandling.h>
#include <utilities\settings.h>

using namespace std;

namespace NMathFunc
{
    /// *************************************************************************
    /// <summary>
    /// Get whether the two values are approximately equal 
    /// </summary>
    /// <param name="v1"> First float to compare. </param>
    /// <param name="v2"> Second float to compare. </param>
    /// <param name="error"> The margin of error. </param>
    /// *************************************************************************
    bool Approximate( float v1, float v2, float error )
    {
        if( fabs( v1 - v2 ) > 0 )
            return false;

        return true;
    }

    /// *************************************************************************
    /// <summary>
    /// Align the passed in position with the change in the screen boundaries. 
    /// </summary>
    /// <param name="alignment"> Alignment of the sprite with the screen. </param>
    /// <param name="pos"> Position to be converted. </param>
    /// *************************************************************************
    void AlignPosition( const CBitmask<uint> & alignment, CVector3 & pos )
    {
        if( alignment == NDefs::EA_CENTER )
            return;

        AlignPositionX( alignment, pos.x );
        AlignPositionY( alignment, pos.y );
    }


    /// *************************************************************************
    /// <summary>
    /// Align the passed in x position with the change in the screen boundaries. 
    /// </summary>
    /// <param name="alignment"> Alignment of the sprite with the screen. </param>
    /// <param name="x"> X position in virtual space to be converted. </param>
    /// *************************************************************************
    void AlignPositionX( const CBitmask<uint> & alignment, float & x )
    {
        if( alignment.Contains( NDefs::EA_LEFT ) )
            x = x - CSettings::Instance().GetScreenBounds().left + agk::GetScreenBoundsLeft();
        else if( alignment.Contains( NDefs::EA_RIGHT ) )
            x = x - CSettings::Instance().GetScreenBounds().right + agk::GetScreenBoundsRight();
    }


    /// *************************************************************************
    /// <summary>
    /// Align the passed in y position with the change in the screen boundaries. 
    /// </summary>
    /// <param name="alignment"> Alignment of the sprite with the screen. </param>
    /// <param name="y"> Y position in virtual space to be converted. </param>
    /// *************************************************************************
    void AlignPositionY( const CBitmask<uint> & alignment, float & y )
    {
        if( alignment.Contains( NDefs::EA_TOP ) )
            y = y - CSettings::Instance().GetScreenBounds().top + agk::GetScreenBoundsTop();
        else if( alignment.Contains( NDefs::EA_BOTTOM ) )
            y = y - CSettings::Instance().GetScreenBounds().bottom + agk::GetScreenBoundsBottom();
    }
}
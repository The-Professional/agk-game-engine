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
    /// Get the new position correctly aligned with the window 
    /// </summary>
    /// <param name="alignment"> Alignment of the sprite with the window. </param>
    /// <param name="vPos"> Position in virtual space to be converted. </param>
    /// *************************************************************************
    CVector2 GetAlignedPos( const CBitmask<uint> & alignment, const CVector2 & vPos )
    {
        if( alignment == NDefs::EA_CENTER )
            return vPos;

        return CVector2( GetAlignedPosX( alignment, vPos.x ), 
                         GetAlignedPosY( alignment, vPos.y ) );
    }


    /// *************************************************************************
    /// <summary>
    /// Get the new x position correctly aligned with the window 
    /// </summary>
    /// <param name="alignment"> Alignment of the sprite with the window. </param>
    /// <param name="vPos"> X position in virtual space to be converted. </param>
    /// *************************************************************************
    float GetAlignedPosX( const CBitmask<uint> & alignment, float x )
    {
        if( alignment.Contains( NDefs::EA_LEFT ) )
            return x + agk::GetScreenBoundsLeft();
        else if( alignment.Contains( NDefs::EA_RIGHT ) )
            return x + agk::GetScreenBoundsRight() - (float)CSettings::Instance().GetVirtualResolution().w;

        return x;
    }


    /// *************************************************************************
    /// <summary>
    /// Get the new y position correctly aligned with the window 
    /// </summary>
    /// <param name="alignment"> Alignment of the sprite with the window. </param>
    /// <param name="vPos"> Y position in virtual space to be converted. </param>
    /// *************************************************************************
    float GetAlignedPosY( const CBitmask<uint> & alignment, float y )
    {
        if( alignment.Contains( NDefs::EA_TOP ) )
            return y + agk::GetScreenBoundsTop();
        else if( alignment.Contains( NDefs::EA_BOTTOM ) )
            return y + agk::GetScreenBoundsBottom() - (float)CSettings::Instance().GetVirtualResolution().h;

        return y;
    }
}
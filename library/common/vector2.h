#ifndef __vector2_h__
#define __vector2_h__

/// *************************************************************************
/// <summary> 
/// Class to hold two dimensions of values.
/// </summary>
/// *************************************************************************
class CVector2
{
public:

    float x;
    float y;


    /// *************************************************************************
    /// <summary> 
    /// Constructor
    /// </summary>
    /// *************************************************************************
    CVector2( float value = 0 )
    {
        x = y = value;
    }

    /// <summary> 
    /// Constructor
    /// </summary>
    CVector2( float _x, float _y )
    {
        x = _x; y = _y;
    }


    /// *************************************************************************
    /// <summary> 
    /// Assignment the value of the float to the entire vector.
    /// </summary>
    /// *************************************************************************
    void operator = ( const float value )
    {
        x = value;
        y = value;
    }

};


#endif  // __vector2_h__

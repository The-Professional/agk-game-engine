#ifndef __vector3_h__
#define __vector3_h__

/// *************************************************************************
/// <summary> 
/// Class to hold three dimensions of values.
/// </summary>
/// *************************************************************************
class CVector3
{
public:

    float x;
    float y;
    float z;


    /// *************************************************************************
    /// <summary> 
    /// Constructor
    /// </summary>
    /// *************************************************************************
    CVector3( float value = 0)
    {
        x = y = z = value;
    }

    /// <summary> 
    /// Constructor
    /// </summary>
    CVector3( float _x, float _y, float _z = 0 )
    {
        x = _x; y = _y; z = _z;
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
        z = value;
    }

};


#endif  // __vector3_h__

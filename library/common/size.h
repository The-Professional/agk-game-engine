#ifndef __size_h__
#define __size_h__

/// *************************************************************************
/// <summary> 
/// Class to hold a width and height value.
/// </summary>
/// *************************************************************************
class CSize
{
public:

    int w;
    int h;

    /// *************************************************************************
    /// <summary> 
    /// Constructor
    /// </summary>
    /// *************************************************************************
    CSize() : w( 0 ), h( 0 )
    {}

    /// <summary> 
    /// Constructor
    /// </summary>
    CSize( int _w, int _h)
    {
        w = _w; h = _h;
    }

};


#endif  // __size_h__
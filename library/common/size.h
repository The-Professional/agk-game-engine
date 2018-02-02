#ifndef __size_h__
#define __size_h__

/// *************************************************************************
/// <summary> 
/// Class to hold a width and height value.
/// </summary>
/// *************************************************************************
template <typename type>
class CSize
{
public:

    type w;
    type h;

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
    CSize( type _w, type _h)
    {
        w = _w; h = _h;
    }

};


#endif  // __size_h__
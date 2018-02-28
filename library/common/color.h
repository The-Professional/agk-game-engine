#ifndef __color_h__
#define __color_h__

/// *************************************************************************
/// <summary> 
/// Class to hold color values.
/// </summary>
/// *************************************************************************
class CColor
{
public:

    int r;    // Red value.
    int g;    // Green value.
    int b;    // Blue value.
    int a;    // Transparency value.


    /// *************************************************************************
    /// <summary> 
    /// Constructor
    /// </summary>
    /// *************************************************************************
    CColor( int rgb = 255, int alpha = 255 )
    {
        r = g = b = rgb;
        a = alpha;
    }

    /// <summary> 
    /// Constructor
    /// </summary>
    CColor( int red, int green, int blue, int alpha = 255 )
    {
        r = red; g = green; b = blue; a = alpha;
    }


    /// *************************************************************************
    /// <summary> 
    /// Color addition.
    /// </summary>
    /// *************************************************************************
    CColor operator + ( const CColor & color ) const
    {
        return CColor( r + color.r, g + color.g, b + color.b, a + color.a );
    }


    /// *************************************************************************
    /// <summary> 
    /// Color addition.
    /// </summary>
    /// *************************************************************************
    void operator += ( const CColor & color )
    {
        r += color.r;
        g += color.g;
        b += color.b;
        a += color.a;
    }


    /// *************************************************************************
    /// <summary> 
    /// Color subtraction.
    /// </summary>
    /// *************************************************************************
    CColor operator - ( const CColor & color ) const
    {
        return CColor( r - color.r, g - color.g, b - color.b, a - color.a );
    }

    /// *************************************************************************
    /// <summary> 
    /// Color subtraction.
    /// </summary>
    /// *************************************************************************
    void operator -= ( const CColor & color )
    {
        r -= color.r;
        g -= color.g;
        b -= color.b;
        a -= color.a;
    }
};


#endif  // __color_h__
#ifndef __bit_mask_h__
#define __bit_mask_h__


/// *************************************************************************
/// <summary> 
/// Class to manage a bitmask.
/// </summary>
/// *************************************************************************
template <typename type>
class CBitmask
{
public:

    // Constructor
    CBitmask() : bitmask(0)
    {}

    // Copy Constructors
    CBitmask( const type args ) : bitmask(args)
    {}
    
    template <typename U>
    CBitmask( const CBitmask<U> bitmask ) : bitmask(bitmask.bitmask)
    {}

    
    /// *************************************************************************
    /// <summary> 
    /// Add a bit to the bitmask.
    /// </summary>
    /// *************************************************************************
    void Add( const type args )
    {
        bitmask |= args;
    }


    /// *************************************************************************
    /// <summary> 
    /// Remove a bit from the bitmask.
    /// </summary>
    /// *************************************************************************
    void Remove( const type args )
    {
        bitmask &= args ^ -1;
    }


    /// *************************************************************************
    /// <summary> 
    /// Remove all bits except for the ones passed in.
    /// </summary>
    /// *************************************************************************
    void RemoveAllExcept( const type args )
    {
        bitmask &= args;
    }


    /// *************************************************************************
    /// <summary> 
    /// Clear all bits.
    /// </summary>
    /// *************************************************************************
    void Clear()
    {
        bitmask = 0;
    }
    
    
    /// *************************************************************************
    /// <summary> 
    /// Check if no bits are set.
    /// </summary>
    /// *************************************************************************
    bool IsEmpty() const
    {
        return (bitmask == 0);
    }


    /// *************************************************************************
    /// <summary> 
    /// Check if one of the bit is set.
    /// </summary>
    /// *************************************************************************
    bool Contains( const type args ) const
    {
        return (bitmask & args) != 0;
    }


    /// *************************************************************************
    /// <summary> 
    /// Get a copy of the bitmask including the passed in bits.
    /// </summary>
    /// *************************************************************************
    type GetIncluding( const type args ) const
    {
        return bitmask | args;
    }


    /// *************************************************************************
    /// <summary> 
    /// Get a copy of the bitmask excluding the parameters.
    /// </summary>
    /// *************************************************************************
    type GetExcluding( const type args ) const
    {
        return bitmask & (args ^ -1);
    }


    /// *************************************************************************
    /// <summary> 
    /// Overloaded assignment operator.
    /// </summary>
    /// *************************************************************************
    void operator = ( const type value )
    {
        bitmask = value;
    }


    /// *************************************************************************
    /// <summary> 
    /// Overloaded equality operator.
    /// </summary>
    /// *************************************************************************
    bool operator == ( const type value )
    {
        return bitmask == value;
    }

private:

    // bit mask
    type bitmask;

};

#endif  // __bit_mask_h__

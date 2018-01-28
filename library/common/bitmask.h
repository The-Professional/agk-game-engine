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

    }   // Set


    /// *************************************************************************
    /// <summary> 
    /// Remove a bit from the bitmask.
    /// </summary>
    /// *************************************************************************
    void Remove( const type args )
    {
        bitmask &= args ^ -1;

    }   // Remove


    /// *************************************************************************
    /// <summary> 
    /// Remove all bits except for the ones passed in.
    /// </summary>
    /// *************************************************************************
    void RemoveAllExcept( const type args )
    {
        bitmask &= args;

    }   // RemoveAllExcept


    /// *************************************************************************
    /// <summary> 
    /// Clear all bits.
    /// </summary>
    /// *************************************************************************
    void Clear()
    {
        bitmask = 0;

    }   // Clear
    
    
    /// *************************************************************************
    /// <summary> 
    /// Check if no bits are set.
    /// </summary>
    /// *************************************************************************
    bool IsEmpty() const
    {
        return (bitmask == 0);

    }   // AreAllSet


    /// *************************************************************************
    /// <summary> 
    /// Check if one of the bit is set.
    /// </summary>
    /// *************************************************************************
    bool IsSet( const type args ) const
    {
        return (bitmask & args) != 0;

    }   // IsSet


    /// *************************************************************************
    /// <summary> 
    /// Check if all of the bits are set.
    /// </summary>
    /// *************************************************************************
    bool AreAllSet( const type args ) const
    {
        return (bitmask & args) == args;

    }   // AreAllSet


    /// *************************************************************************
    /// <summary> 
    /// Get a copy of the bitmask including the passed in bits.
    /// </summary>
    /// *************************************************************************
    type GetIncluding( const type args ) const
    {
        return bitmask | args;

    }   // GetIncluding


    /// *************************************************************************
    /// <summary> 
    /// Get a copy of the bitmask excluding the parameters.
    /// </summary>
    /// *************************************************************************
    type GetExcluding( const type args ) const
    {
        return bitmask & (args ^ -1);

    }   // GetExcluding


    /// *************************************************************************
    /// <summary> 
    /// Overloaded assignment operator.
    /// </summary>
    /// *************************************************************************
    void operator = ( const type value )
    {
        bitmask = value;

    }   // operator =

private:

    // bit mask
    type bitmask;

};

#endif  // __bit_mask_h__

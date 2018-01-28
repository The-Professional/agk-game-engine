#ifndef __exception_handling_h__
#define __exception_handling_h__

// Standard lib dependencies
#include <string>

/// *************************************************************************
/// <summary>
/// Namespace for exception handling classes.
/// </summary>
/// *************************************************************************
namespace NExcept
{
    /// *************************************************************************
    /// <summary>
    /// Basic exception interface class.
    /// </summary>
    /// *************************************************************************
    class IException
    {
    public:
        
        IException( std::string title, std::string msg ) : errorTitle(title), errorMsg(msg)
        {}

        // Return the error info
        std::string & GetErrorMsg(){ return errorMsg; }
        std::string & GetErrorTitle(){ return errorTitle; }

    protected:

        std::string errorTitle;
        std::string errorMsg;
        
    };

    
    /// *************************************************************************
    /// <summary>
    /// Critical exception class. Used for non-recoverable exceptions.
    /// </summary>
    /// *************************************************************************
    class CCriticalException : public IException
    {
    public:

        CCriticalException( std::string title, std::string msg ) : 
            IException( title, msg ) {}
        CCriticalException( std::string title, std::string location, std::string msg ) :
            IException( title, location + "\n" + msg ) {}
        CCriticalException( std::string title, std::string location, std::string msg, std::exception e ) : 
            IException( title, location + "\n" + msg + "\n" + e.what() ) {}
    };
}

#endif  // __exception_handling_h__
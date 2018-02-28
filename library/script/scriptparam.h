#ifndef __script_param_h__
#define __script_param_h__

// Game lib dependencies
#include <common/defs.h>

/// *************************************************************************
/// <summary> 
/// Class to hold a script parameter type and value.
/// </summary>
/// *************************************************************************
class CScriptParam
{
public:

    enum EParamType
    {
        EPT_NULL,
        EPT_BOOL,
        EPT_INT,
        EPT_UINT,
        EPT_FLOAT,
        EPT_PTR, // Registered Object
    };

    // Constructors
    CScriptParam() : _paramVal( 0 ), _type( EPT_NULL ) {}
    CScriptParam( bool val ) : _paramVal( val ), _type( EPT_BOOL ) {}
    CScriptParam( int val ) : _paramVal( val ), _type( EPT_INT ) {}
    CScriptParam( uint val ) : _paramVal( val ), _type( EPT_UINT ) {}
    CScriptParam( float val ) : _paramVal( val ), _type( EPT_FLOAT ) {}
    CScriptParam( void * val ) : _paramVal( val ), _type( EPT_PTR ) {}

private:

    union UParamValue
    {
        bool boolVal;
        int intVal;
        uint uintVal;
        float floatVal;
        void * pRegObjVal;

        UParamValue( bool val ) : boolVal( val ) {}
        UParamValue( int val ) : intVal( val ) {}
        UParamValue( uint val ) : uintVal( val ) {}
        UParamValue( float val ) : floatVal( val ) {}
        UParamValue( void * val ) : pRegObjVal( val ) {}
    };

    UParamValue _paramVal;

    EParamType _type;

public:

    template<typename T>
    T Get() const;

    EParamType GetType() const
    {
        return _type;
    }
};

template<> inline bool   CScriptParam::Get() const { return _paramVal.boolVal; }
template<> inline int    CScriptParam::Get() const { return _paramVal.intVal; }
template<> inline uint   CScriptParam::Get() const { return _paramVal.uintVal; }
template<> inline float  CScriptParam::Get() const { return _paramVal.floatVal; }
template<> inline void * CScriptParam::Get() const { return _paramVal.pRegObjVal; }

#endif  // __script_param_h__



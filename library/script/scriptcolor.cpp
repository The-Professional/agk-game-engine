
/************************************************************************
*    FILE NAME:       scriptcolor.cpp
*
*    DESCRIPTION:     CVector4 script object registration
************************************************************************/

// Physical component dependency
#include <script/scriptcolor.h>

// Game lib dependencies
#include <common/vector4.h>
#include <utilities/exceptionhandling.h>

// AngelScript lib dependencies
#include <angelscript.h>

// Boost lib dependencies
#include <boost/format.hpp>

namespace NScriptColor
{
    /************************************************************************
    *    desc:  Constructor
    ************************************************************************/
    void Constructor( void * thisPointer )
    {
        new(thisPointer) CVector4<float>();
    }

    /************************************************************************
    *    desc:  Copy Constructor
    ************************************************************************/
    void CopyConstructor( const CVector4<float> & other, void * pThisPointer )
    {
        new(pThisPointer) CVector4<float>( other );
    }

    void ConstructorFromInts( float r, float g, float b, float a, void * pThisPointer )
    {
        new(pThisPointer) CVector4<float>( r, g, b, a );
    }

    /************************************************************************
    *    desc:  Destructor
    ************************************************************************/
    void Destructor( void * pThisPointer )
    {
        ((CVector4<float>*)pThisPointer)->~CVector4();
    }


    /************************************************************************
    *    desc:  Throw an exception for values less then 0
    ************************************************************************/
    void Throw( int value )
    {
        if( value < 0 )
            throw NExcept::CCriticalException( "Error Registering CColor type!",
                                               boost::str( boost::format( "CColor type could not be created.\n\n%s\nLine: %s" )
                                                           % __FUNCTION__ % __LINE__ ) );
    }


    /************************************************************************
    *    desc:  Register the type
    ************************************************************************/
    void Register( asIScriptEngine * pEngine )
    {
        // Register type
        Throw( pEngine->RegisterObjectType( "CColor", sizeof( CVector4<float> ), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS | asOBJ_APP_CLASS_CONSTRUCTOR | asOBJ_APP_CLASS_COPY_CONSTRUCTOR | asOBJ_APP_CLASS_DESTRUCTOR ) );

        // Register the object constructor
        Throw( pEngine->RegisterObjectBehaviour( "CColor", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION( Constructor ), asCALL_CDECL_OBJLAST ) );
        Throw( pEngine->RegisterObjectBehaviour( "CColor", asBEHAVE_CONSTRUCT, "void f(const CColor & in)", asFUNCTION( CopyConstructor ), asCALL_CDECL_OBJLAST ) );
        Throw( pEngine->RegisterObjectBehaviour( "CColor", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION( ConstructorFromInts ), asCALL_CDECL_OBJLAST ) );
        Throw( pEngine->RegisterObjectBehaviour( "CColor", asBEHAVE_DESTRUCT, "void f()", asFUNCTION( Destructor ), asCALL_CDECL_OBJLAST ) );

        // assignment operator
        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor & opAssign(const CColor & in)", asMETHODPR( CVector4<float>, operator =, (const CVector4<float> &), CVector4<float> & ), asCALL_THISCALL ) );

        // binary operators
        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opAdd ( const CColor & in )", asMETHODPR( CVector4<float>, operator +, (const CVector4<float> &) const, CVector4<float> ), asCALL_THISCALL ) );
        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opSub ( const CColor & in )", asMETHODPR( CVector4<float>, operator -, (const CVector4<float> &) const, CVector4<float> ), asCALL_THISCALL ) );

        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opAdd ( float )", asMETHODPR( CVector4<float>, operator +, (float) const, CVector4<float> ), asCALL_THISCALL ) );
        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opSub ( float )", asMETHODPR( CVector4<float>, operator -, (float) const, CVector4<float> ), asCALL_THISCALL ) );
        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opMul ( float )", asMETHODPR( CVector4<float>, operator *, (float) const, CVector4<float> ), asCALL_THISCALL ) );
        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opDiv ( float )", asMETHODPR( CVector4<float>, operator /, (float) const, CVector4<float> ), asCALL_THISCALL ) );

        // compound assignment operators
        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opAddAssign ( const CColor & in )", asMETHODPR( CVector4<float>, operator +=, (const CVector4<float> &), void ), asCALL_THISCALL ) );
        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opSubAssign ( const CColor & in )", asMETHODPR( CVector4<float>, operator -=, (const CVector4<float> &), void ), asCALL_THISCALL ) );
        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opMulAssign ( const CColor & in )", asMETHODPR( CVector4<float>, operator *=, (const CVector4<float> &), void ), asCALL_THISCALL ) );
        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opDivAssign ( const CColor & in )", asMETHODPR( CVector4<float>, operator /=, (const CVector4<float> &), void ), asCALL_THISCALL ) );

        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opAddAssign ( float )", asMETHODPR( CVector4<float>, operator +=, (float), void ), asCALL_THISCALL ) );
        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opSubAssign ( float )", asMETHODPR( CVector4<float>, operator -=, (float), void ), asCALL_THISCALL ) );
        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opMulAssign ( float )", asMETHODPR( CVector4<float>, operator *=, (float), void ), asCALL_THISCALL ) );
        Throw( pEngine->RegisterObjectMethod( "CColor", "CColor opDivAssign ( float )", asMETHODPR( CVector4<float>, operator /=, (float), void ), asCALL_THISCALL ) );

        // Register property
        Throw( pEngine->RegisterObjectProperty( "CColor", "float r", asOFFSET( CVector4<float>, r ) ) );
        Throw( pEngine->RegisterObjectProperty( "CColor", "float g", asOFFSET( CVector4<float>, g ) ) );
        Throw( pEngine->RegisterObjectProperty( "CColor", "float b", asOFFSET( CVector4<float>, b ) ) );
        Throw( pEngine->RegisterObjectProperty( "CColor", "float a", asOFFSET( CVector4<float>, a ) ) );

        // Class members
        //Throw( pEngine->RegisterObjectMethod( "CColor", "void Set( float r, float g, float b, float a )", asMETHOD( CColor, Set ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CColor", "void TransformHSV( float hue, float sat, float val )", asMETHOD( CColor, TransformHSV ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CColor", "void Convert()", asMETHOD( CColor, Convert ), asCALL_THISCALL ) );
    }

}   // NScriptColor
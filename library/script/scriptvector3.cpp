// Physical component dependency
#include "scriptvector3.h"

// Game lib dependencies
#include <common/vector3.h>
#include <utilities/exceptionhandling.h>

// AngelScript lib dependencies
#include <angelscript.h>

// Boost lib dependencies
#include <boost/format.hpp>

namespace NScriptVector3
{
    /// *************************************************************************
    /// <summary>
    /// Constructor
    /// </summary>
    /// *************************************************************************
    void Constructor( void * thisPointer )
    {
        new(thisPointer) CVector3();
    }


    /// *************************************************************************
    /// <summary>
    /// Copy Constructor.
    /// </summary>
    /// *************************************************************************
    void CopyConstructor( const CVector3 & other, void * pThisPointer )
    {
        new(pThisPointer) CVector3( other );
    }

    /// <summary>
    /// Copy Constructor.
    /// </summary>
    void ConstructorFromThreeFloats( float x, float y, float z, void * pThisPointer )
    {
        new(pThisPointer) CVector3( x, y, z );
    }

    /// <summary>
    /// Copy Constructor.
    /// </summary>
    void ConstructorFromTwoFloats( float x, float y, void * pThisPointer )
    {
        new(pThisPointer) CVector3( x, y );
    }


    /// *************************************************************************
    /// <summary>
    /// Destructor
    /// </summary>
    /// *************************************************************************
    void Destructor( void * pThisPointer )
    {
        ((CVector3*)pThisPointer)->~CVector3();
    }


    /// *************************************************************************
    /// <summary>
    /// Throw an exception for values less then 0.
    /// </summary>
    /// *************************************************************************
    void Throw( int value )
    {
        if( value < 0 )
            throw NExcept::CCriticalException( "Error Registering CVector3 type!",
                                               boost::str( boost::format( "CVector3 type could not be created.\n\n%s\nLine: %s" )
                                                           % __FUNCTION__ % __LINE__ ) );
    }


    /// *************************************************************************
    /// <summary>
    /// Register the type.
    /// </summary>
    /// *************************************************************************
    void Register( asIScriptEngine * pEngine )
    {
        // Register type
        Throw( pEngine->RegisterObjectType( "CVector3", sizeof( CVector3 ), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS | asOBJ_APP_CLASS_CONSTRUCTOR | asOBJ_APP_CLASS_COPY_CONSTRUCTOR | asOBJ_APP_CLASS_DESTRUCTOR ) );

        // Register the object operator overloads
        Throw( pEngine->RegisterObjectBehaviour( "CVector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION( Constructor ), asCALL_CDECL_OBJLAST ) );
        Throw( pEngine->RegisterObjectBehaviour( "CVector3", asBEHAVE_CONSTRUCT, "void f(const CVector3 & in)", asFUNCTION( CopyConstructor ), asCALL_CDECL_OBJLAST ) );
        Throw( pEngine->RegisterObjectBehaviour( "CVector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION( ConstructorFromThreeFloats ), asCALL_CDECL_OBJLAST ) );
        Throw( pEngine->RegisterObjectBehaviour( "CVector3", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION( ConstructorFromTwoFloats ), asCALL_CDECL_OBJLAST ) );
        Throw( pEngine->RegisterObjectBehaviour( "CVector3", asBEHAVE_DESTRUCT, "void f()", asFUNCTION( Destructor ), asCALL_CDECL_OBJLAST ) );

        // assignment operator
        Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 & opAssign(const CVector3 & in)", asMETHODPR( CVector3, operator =, (const CVector3 &), CVector3 & ), asCALL_THISCALL ) );

        // binary operators
        Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opAdd ( const CVector3 & in )", asMETHODPR( CVector3, operator +, (const CVector3 &) const, CVector3 ), asCALL_THISCALL ) );
        Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opSub ( const CVector3 & in )", asMETHODPR( CVector3, operator -, (const CVector3 &) const, CVector3 ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opMul ( const CVector3 & in )", asMETHODPR( CVector3, operator *, (const CVector3 &) const, CVector3 ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opDiv ( const CVector3 & in )", asMETHODPR( CVector3, operator /, (const CVector3 &) const, CVector3 ), asCALL_THISCALL ) );

        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opAdd ( float )", asMETHODPR( CVector3, operator +, (float) const, CVector3 ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opSub ( float )", asMETHODPR( CVector3, operator -, (float) const, CVector3 ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opMul ( float )", asMETHODPR( CVector3, operator *, (float) const, CVector3 ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opDiv ( float )", asMETHODPR( CVector3, operator /, (float) const, CVector3 ), asCALL_THISCALL ) );

        // compound assignment operators
        Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opAddAssign ( const CVector3 & in )", asMETHODPR( CVector3, operator +=, (const CVector3 &), void ), asCALL_THISCALL ) );
        Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opSubAssign ( const CVector3 & in )", asMETHODPR( CVector3, operator -=, (const CVector3 &), void ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opMulAssign ( const CVector3 & in )", asMETHODPR( CVector3, operator *=, (const CVector3 &), CVector3 ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opDivAssign ( const CVector3 & in )", asMETHODPR( CVector3, operator /=, (const CVector3 &), CVector3 ), asCALL_THISCALL ) );

        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opAddAssign ( float )", asMETHODPR( CVector3, operator +=, (float), void ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opSubAssign ( float )", asMETHODPR( CVector3, operator -=, (float), CVector3 ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opMulAssign ( float )", asMETHODPR( CVector3, operator *=, (float), CVector3 ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 opDivAssign ( float )", asMETHODPR( CVector3, operator /=, (float), CVector3 ), asCALL_THISCALL ) );

        // Register property
        Throw( pEngine->RegisterObjectProperty( "CVector3", "float x", asOFFSET( CVector3, x ) ) );
        Throw( pEngine->RegisterObjectProperty( "CVector3", "float y", asOFFSET( CVector3, y ) ) );
        Throw( pEngine->RegisterObjectProperty( "CVector3", "float z", asOFFSET( CVector3, z ) ) );

        // Class members
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "void ClearX()", asMETHOD( CVector3, ClearX ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "void ClearY()", asMETHOD( CVector3, ClearY ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "void ClearZ()", asMETHOD( CVector3, ClearZ ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "void Clear()", asMETHOD( CVector3, Clear ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "void Cap( float x )", asMETHOD( CVector3, CapFloat ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "bool IsEmpty()", asMETHOD( CVector3, IsEmpty ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "bool IsXEmpty()", asMETHOD( CVector3, IsXEmpty ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "bool IsYEmpty()", asMETHOD( CVector3, IsYEmpty ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "bool IsZEmpty()", asMETHOD( CVector3, IsZEmpty ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "void Invert()", asMETHOD( CVector3, Invert ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "void InvertX()", asMETHOD( CVector3, Invert ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "void InvertY()", asMETHOD( CVector3, Invert ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "void InvertZ()", asMETHOD( CVector3, Invert ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 GetInvert()", asMETHOD( CVector3, GetInvert ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "void Normalize()", asMETHOD( CVector3, Normalize ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "void Normalize2D()", asMETHOD( CVector3, Normalize2D ), asCALL_THISCALL ) );

        //Throw( pEngine->RegisterObjectMethod( "CVector3", "bool IsEquilEnough( const CVector3 & in, float val )", asMETHOD( CVector3, IsEquilEnoughFloat ), asCALL_THISCALL ) );

        //Throw( pEngine->RegisterObjectMethod( "CVector3", "float GetDotProduct( const CVector3 & in )", asMETHOD( CVector3, GetDotProductFloat ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "float GetDotProduct2D( const CVector3 & in )", asMETHOD( CVector3, GetDotProduct2DFloat ), asCALL_THISCALL ) );
        //Throw( pEngine->RegisterObjectMethod( "CVector3", "CVector3 GetCrossProduct( const CVector3 & in )", asMETHOD( CVector3, GetCrossProduct ), asCALL_THISCALL ) );
    }

}   // NScriptColor
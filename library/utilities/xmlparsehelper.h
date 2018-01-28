#ifndef __xml_parse_helper_h__
#define __xml_parse_helper_h__

// Game lib dependencies
#include <common/defs.h>
#include <common/vector3.h>
#include <common/color.h>
#include <common/size.h>
#include <common/bitmask.h>
#include <utilities/xmlParser.h>

// Standard lib dependencies
//#include <assert.h>
//#include <utility>
//#include <string>


/// *************************************************************************
/// <summary> 
/// Namespace with general functions to parse common xml tags.
/// </summary>
/// *************************************************************************
namespace NParseHelper
{
    // Parse position tags.
    bool LoadPosition( const XMLNode & node, CVector3 & pos );

    // Parse rotation tags.
    bool LoadRotation( const XMLNode & node, CVector3 & rot );

    // Parse scale tags.
    bool LoadScale( const XMLNode & node, CVector3 & scale );
    
    // Parse center point tags.
    bool LoadCenterPos( const XMLNode & node, CVector3 & center );

    // Parse color tags.
    bool LoadColor(const XMLNode & node, CColor & color );

    bool LoadSize( const XMLNode & node, CSize & size );

    // Parse alignment tags.
    bool LoadAlignment( const XMLNode & node, CBitmask<uint> & alignment );

    // Parse generic x, y, z tags.
    CVector3 LoadXYZ( const XMLNode & node );
}

#endif  // __xml_parse_helper_h__

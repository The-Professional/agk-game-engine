#ifndef __json_parse_helper_h__
#define __json_parse_helper_h__

// Game lib dependencies
#include <common\defs.h>
#include <utilities\json.hpp>

// Standard lib dependencies
#include <string>

// Forward declarations
class CVector3;
class CSize;
class CColor;
class CSpriteData3D;
class CInputState;
class CInputMapping;

template <typename type>
class CBitmask;

namespace NParseHelper
{
    ////////////////////////////////////////////////////////////////
    // General Functions                                          //
    ////////////////////////////////////////////////////////////////

	// Parse position tag.
	bool GetPosition( nlohmann::json::const_iterator iter, CVector3 & pos );

	// Parse rotation tag.
	bool GetRotation( nlohmann::json::const_iterator iter, CVector3 & rot );

	// Parse scale tag.
	bool GetScale( nlohmann::json::const_iterator iter, CVector3 & scale );

	// Parse center point tag.
	bool GetCenterPos( nlohmann::json::const_iterator iter, CVector3 & center );

	// Parse generic x, y, z tags.
	CVector3 GetXYZ( nlohmann::json::const_iterator iter );

	// Parse color tag.
	bool GetColor( nlohmann::json::const_iterator iter, CColor & color );

	// Parse size tag.
	bool GetSize( nlohmann::json::const_iterator iter, CSize & size );

    // Parse name tag.
    bool GetName( nlohmann::json::const_iterator iter, std::string & name );

    ////////////////////////////////////////////////////////////////
    // Settings Functions                                         //
    ////////////////////////////////////////////////////////////////

	// Parse alignment tag.
	bool GetAlignment( nlohmann::json::const_iterator iter, CBitmask<uint> & alignment );

	// Parse fullscreen tag.
	bool GetFullscreen( nlohmann::json::const_iterator iter, bool & fullscreen );

	// Parse orientation tag.
	bool GetOrientation( nlohmann::json::const_iterator iter, NDefs::EOrentation & orientation );

    // Parse antialias tag.
    bool GetAntialias( nlohmann::json::const_iterator iter, bool & antialias );

    ////////////////////////////////////////////////////////////////
    // Visual Sprite Data Functions                               //
    ////////////////////////////////////////////////////////////////

    // Parse the mesh tag.
    bool GetMesh( nlohmann::json::const_iterator iter, std::string & mesh );

    // Parse the texture map tag.
    bool GetTextureMap( nlohmann::json::const_iterator iter, std::string & image );
    
    // Parse the normal map tag.
    bool GetNormalMap( nlohmann::json::const_iterator iter, std::string & image );

    // Parse the specular map tag.
    bool GetSpecularMap( nlohmann::json::const_iterator iter, std::string & image );

    // Parse the dimension tags.
    void GetDimensions( nlohmann::json::const_iterator iter, float & width, float & height, float & length, float & radius, int & rows, int & columns );
    void GetDimensions( nlohmann::json::const_iterator iter, float & width, float & height );

    ////////////////////////////////////////////////////////////////
    // Input Functions                                            //
    ////////////////////////////////////////////////////////////////

    // Parse the input state tags.
    void GetInputState( nlohmann::json::const_iterator iter, CInputState & inputState );

    // Parse the input mapping tags.
    void GetInputMapping( nlohmann::json::const_iterator iter, CInputMapping & mapping );
}

#endif  // __json_parse_helper_h__
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
    // Primitive Functions                                        //
    ////////////////////////////////////////////////////////////////

    // Parse a string value.
    bool GetString( nlohmann::json::const_iterator iter, const std::string & tag, std::string & value );

    // Parse an int value.
    bool GetInt( nlohmann::json::const_iterator iter, const std::string & tag, int & value );

    // Parse a float value.
    bool GetFloat( nlohmann::json::const_iterator iter, const std::string & tag, float & value );

    // Parse a bool value.
    bool GetBool( nlohmann::json::const_iterator iter, const std::string & tag, bool & value );

    // Whether the tag exists.
    bool TagExists( nlohmann::json::const_iterator iter, const std::string & tag );

    // Parse generic x, y, z tags.
    bool GetXYZ( nlohmann::json::const_iterator iter, const std::string & tag, CVector3 & vec, bool checkUniform = false );

    // Parse generic w, h tags.
    bool GetWH( nlohmann::json::const_iterator iter, const std::string & tag, CSize & wh );

    // Parse generic top, bottom, left, right, and center tags.
    bool GetTBLRC( nlohmann::json::const_iterator iter, const std::string & tag, CBitmask<uint> & alignment );

	// Parse color tag.
	bool GetColor( nlohmann::json::const_iterator iter, CColor & color );

	// Parse orientation tag.
	bool GetOrientation( nlohmann::json::const_iterator iter, NDefs::EOrentation & orientation );

    // Parse the dimension tags.
    void GetDimensions( nlohmann::json::const_iterator iter, float & width, float & height, float & length, float & radius, int & rows, int & columns );

    // Parse the input state tags.
    void GetInputState( nlohmann::json::const_iterator iter, CInputState & inputState );

    // Parse the input mapping tags.
    void GetInputMapping( nlohmann::json::const_iterator iter, CInputMapping & mapping );
}

#endif  // __json_parse_helper_h__
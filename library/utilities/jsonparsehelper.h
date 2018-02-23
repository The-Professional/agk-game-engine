#ifndef __json_parse_helper_h__
#define __json_parse_helper_h__

// Game lib dependencies
#include <common\defs.h>
#include <utilities\json.hpp>

// Standard lib dependencies
#include <string>
#include <vector>

// Forward declarations
class CVector3;
class CColor;
class CSpriteData3D;
class CInputState;
class CInputMapping;
class iObject;

template <typename type>
class CBitmask;

template <typename type>
class CSize;

namespace NParseHelper
{
    // Parse a string value.
    bool GetString( nlohmann::json::const_iterator iter, const std::string & tag, std::string & value );
    bool GetString( nlohmann::json::const_iterator iter, const std::string & tag, std::vector<std::string> & value );

    // Parse an int value.
    bool GetInt( nlohmann::json::const_iterator iter, const std::string & tag, int & value );

    // Parse a float value.
    bool GetFloat( nlohmann::json::const_iterator iter, const std::string & tag, float & value );

    // Parse a bool value.
    bool GetBool( nlohmann::json::const_iterator iter, const std::string & tag, bool & value );

    // Whether the tag exists.
    bool TagExists( nlohmann::json::const_iterator iter, const std::string & tag );

    // Parse generic x, y, z tags.
    bool GetXYZ( nlohmann::json::const_iterator iter, const std::string & tag, CVector3 & xyz );

    // Parse generic w, h, d tags.
    bool GetWHD( nlohmann::json::const_iterator iter, const std::string & tag, CVector3 & whd );

    // Parse generic w, h tags.
    bool GetWH( nlohmann::json::const_iterator iter, const std::string & tag, CSize<int> & wh );
    bool GetWH( nlohmann::json::const_iterator iter, const std::string & tag, CSize<float> & wh );

    // Parse alignment tags.
    bool GetAlignment( nlohmann::json::const_iterator iter, const std::string & tag, CBitmask<uint> & alignment );

	// Parse color tag.
	bool GetColor( nlohmann::json::const_iterator iter, CColor & color );

	// Parse orientation tag.
	bool GetOrientation( nlohmann::json::const_iterator iter, NDefs::EOrentation & orientation );

    // Parse text alignment tag.
    bool GetTextAlignment( nlohmann::json::const_iterator iter, NDefs::ETextAlignment & alignment );

    // Parse script end type tags.
    bool GetScriptEndType( nlohmann::json::const_iterator iter, NDefs::EScriptEndType & endType );

    // Parse the dimension tags.
    void GetDimensions( nlohmann::json::const_iterator iter, float & width, float & height, float & depth, float & radius, int & rows, int & columns );

    // Parse the input state tags.
    void GetInputState( nlohmann::json::const_iterator iter, CInputState & inputState );

    // Parse the input mapping tags.
    void GetInputMapping( nlohmann::json::const_iterator iter, CInputMapping & mapping );

    // Parse object data tags.
    void GetCollectionObject( nlohmann::json::const_iterator iter, iObject * pObject );
}

#endif  // __json_parse_helper_h__
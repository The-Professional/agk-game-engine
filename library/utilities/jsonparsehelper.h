#ifndef __json_parse_helper_h__
#define __json_parse_helper_h__

// Game lib dependencies
#include <common\defs.h>
#include <utilities\json.hpp>

// Standard lib dependencies
#include <string>
#include <vector>

// Forward declarations
class CSpriteData3D;
class CInputState;
class CInputMapping;
class iObject;
class CCollectionObject;

template <class T>
class CBitmask;

template <class T>
class CVector2;

template <class T>
class CVector3;

template <class T>
class CVector4;


namespace NParseHelper
{
    // Parse a value.
    template <class T>
    bool GetValue( nlohmann::json::const_iterator iter, const std::string & tag, T & value );

    // Parse a list of values.
    template <class T>
    bool GetValueList( nlohmann::json::const_iterator iter, const std::string & tag, std::vector<T> & value );

    // Whether the tag exists.
    bool TagExists( nlohmann::json::const_iterator iter, const std::string & tag );

    // Parse generic x, y, z tags.
    template <class T>
    bool GetXYZ( nlohmann::json::const_iterator iter, const std::string & tag, CVector3<T> & xyz );

    // Parse generic w, h, d tags.
    template <class T>
    bool GetWHD( nlohmann::json::const_iterator iter, const std::string & tag, CVector3<T> & whd );

    // Parse generic w, h tags.
    template <class T>
    bool GetWH( nlohmann::json::const_iterator iter, const std::string & tag, CVector2<T> & wh )
    {
        auto whIter = iter->find( tag );
        if( whIter != iter->end() )
        {
            GetValue( whIter, "w", wh.w );
            GetValue( whIter, "h", wh.h );

            return true;
        }

        return false;
    }

    // Parse mesh type tags.
    bool GetMeshType( nlohmann::json::const_iterator iter, NDefs::EMeshType & meshType );

    // Parse alignment tags.
    template <class T>
    bool GetAlignment( nlohmann::json::const_iterator iter, const std::string & tag, CBitmask<T> & alignment );

	// Parse color tags.
    template <class T>
	bool GetColor( nlohmann::json::const_iterator iter, CVector4<T> & color );

	// Parse orientation tags.
	bool GetOrientation( nlohmann::json::const_iterator iter, NDefs::EOrentation & orientation );

    // Parse text alignment tags.
    bool GetTextAlignment( nlohmann::json::const_iterator iter, NDefs::ETextAlignment & alignment );

    // Parse script end type tags.
    bool GetEndType( nlohmann::json::const_iterator iter, NDefs::EEndType & endType );

    // Parse object field tags.
    template <class T>
    bool GetObjectFields( nlohmann::json::const_iterator iter, const std::string & tag, CBitmask<T> & fieldType );

    // Parse animation list tags.
    bool GetAnimationList( nlohmann::json::const_iterator iter, const std::string & tag, std::vector<std::vector<std::string>> & animationList );

    // Parse control type tags.
    bool GetControlType( nlohmann::json::const_iterator iter, const std::string & tag, NDefs::EControlType & controlType );

    // Parse control state tags.
    bool GetControlState( nlohmann::json::const_iterator iter, const std::string & tag, NDefs::EControlState & controlState );

    // Parse the dimension tags.
    void GetDimensions( nlohmann::json::const_iterator iter, float & width, float & height, float & depth, float & radius, int & rows, int & columns );

    // Parse the input state tags.
    void GetInputState( nlohmann::json::const_iterator iter, CInputState & inputState );

    // Parse the input mapping tags.
    void GetInputMapping( nlohmann::json::const_iterator iter, CInputMapping & mapping );

    // Parse collection object data tags.
    void GetCollectionObject( nlohmann::json::const_iterator iter, CCollectionObject & collectionObject );
}

#endif  // __json_parse_helper_h__
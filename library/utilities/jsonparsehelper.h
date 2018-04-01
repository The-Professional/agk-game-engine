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
    // Whether the tag exists.
    bool TagExists( nlohmann::json::const_iterator iter, const std::string & tag );

    // Parse mesh type tags.
    bool GetMeshType( nlohmann::json::const_iterator iter, NDefs::EMeshType & meshType );

    // Parse orientation tags.
    bool GetOrientation( nlohmann::json::const_iterator iter, NDefs::EOrentation & orientation );

    // Parse text alignment tags.
    bool GetTextAlignment( nlohmann::json::const_iterator iter, NDefs::ETextAlignment & alignment );

    // Parse script end type tags.
    bool GetEndType( nlohmann::json::const_iterator iter, NDefs::EEndType & endType );

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


    /// *************************************************************************
    /// <summary> 
    /// Parse a value.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="value"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    template <typename T>
    bool GetValue( nlohmann::json::const_iterator iter, const std::string & tag, T & value )
    {
        auto valueIter = iter->find( tag );
        if( valueIter != iter->end() )
        {
            value = valueIter->get<T>();
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse a list of values.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="list"> List to add to. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    template <class T>
    bool GetValueList( nlohmann::json::const_iterator iter, const std::string & tag, std::vector<T> & list )
    {
        auto valueListIter = iter->find( tag );
        if( valueListIter != iter->end() )
        {
            for( auto & valueIter : *valueListIter )
                list.push_back( valueIter.get<T>() );

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse generic x, y, z tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="xyz"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    template <class T>
    bool GetXYZ( nlohmann::json::const_iterator iter, const std::string & tag, CVector3<T> & xyz )
    {
        auto xyzIter = iter->find( tag );
        if( xyzIter != iter->end() )
        {
            T u = 0;
            if( GetValue( xyzIter, "xyz", u ) )
            {
                xyz = u;
                return true;
            }

            GetValue( xyzIter, "x", xyz.x );
            GetValue( xyzIter, "y", xyz.y );
            GetValue( xyzIter, "z", xyz.z );

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse generic w, h, d tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="whd"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    template <class T>
    bool GetWHD( nlohmann::json::const_iterator iter, const std::string & tag, CVector3<T> & whd )
    {
        auto whdIter = iter->find( tag );
        if( whdIter != iter->end() )
        {
            GetValue( whdIter, "w", whd.w );
            GetValue( whdIter, "h", whd.h );
            GetValue( whdIter, "d", whd.d );

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse generic w, h tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="wh"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
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


    /// *************************************************************************
    /// <summary> 
    /// Parse color tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="color"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    template <class T>
    bool GetColor( nlohmann::json::const_iterator iter, CVector4<T> & color )
    {
        auto colorIter = iter->find( "color" );
        if( colorIter != iter->end() )
        {
            GetValue( colorIter, "r", color.r );
            GetValue( colorIter, "g", color.g );
            GetValue( colorIter, "b", color.b );
            GetValue( colorIter, "a", color.a );

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse alignment tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="alignment"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    template <class T>
    bool GetAlignment( nlohmann::json::const_iterator iter, const std::string & tag, CBitmask<T> & alignment )
    {
        std::vector<std::string> align;
        if( GetValueList( iter, tag, align ) )
        {
            for( auto & a : align )
                alignment.Add( NDefs::CDefs::Instance().GetAlignment( a ) );

            if( alignment.Contains( NDefs::EA_LEFT | NDefs::EA_RIGHT ) )
                alignment.Remove( NDefs::EA_LEFT | NDefs::EA_RIGHT );

            if( alignment.Contains( NDefs::EA_TOP | NDefs::EA_BOTTOM ) )
                alignment.Remove( NDefs::EA_TOP | NDefs::EA_BOTTOM );

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse object field tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="fieldType"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    template <class T>
    bool GetObjectFields( nlohmann::json::const_iterator iter, const std::string & tag, CBitmask<T> & fieldType )
    {
        vector<string> field;
        if( GetValueList( iter, tag, field ) )
        {
            for( auto & f : field )
                fieldType.Add( NDefs::CDefs::Instance().GetObjectField( f ) );

            return true;
        }

        return false;
    }
}

#endif  // __json_parse_helper_h__
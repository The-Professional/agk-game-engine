// Physical component dependency
#include "jsonparsehelper.h"

// Game lib dependencies
#include <agk.h>
#include <common\size.h>
#include <common\vector2.h>
#include <common\vector3.h>
#include <common\color.h>
#include <common\bitmask.h>
#include <common\iobject.h>
#include <common\collectionobject.h>
#include <managers\inputstate.h>
#include <managers\inputmapping.h>
#include <managers\inputmanager.h>

// Standard lib dependencies
#include <utility>

using namespace nlohmann;
using namespace std;
using namespace NDefs;

namespace NParseHelper
{
    /// *************************************************************************
    /// <summary> 
    /// Parse a string value.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="value"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetString( json::const_iterator iter, const string & tag, string & value )
    {
        auto strIter = iter->find( tag );
        if( strIter != iter->end() )
        {
            value = strIter->get<string>();
            return true;
        }

        return false;
    }

    /// <summary> 
    /// Parse a list of string values.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="value"> List to add to. </param>
    /// <returns> If the tag exists. </returns>
    bool GetString( json::const_iterator iter, const string & tag, vector<string> & value )
    {
        auto strListIter = iter->find( tag );
        if( strListIter != iter->end() )
        {
            for( auto & strIter : *strListIter )
                value.push_back( strIter.get<string>() );

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse an int value.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="value"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetInt( json::const_iterator iter, const string & tag, int & value )
    {
        auto intIter = iter->find( tag );
        if( intIter != iter->end() )
        {
            value = intIter->get<int>();
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse a float value.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="value"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetFloat( json::const_iterator iter, const string & tag, float & value )
    {
        auto floatIter = iter->find( tag );
        if( floatIter != iter->end() )
        {
            value = floatIter->get<float>();
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse a bool value.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="value"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetBool( json::const_iterator iter, const string & tag, bool & value )
    {
        auto boolIter = iter->find( tag );
        if( boolIter != iter->end() )
        {
            value = boolIter->get<bool>();
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Whether the tag exists.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool TagExists( json::const_iterator iter, const string & tag )
    {
        auto tagIter = iter->find( tag );
        if( tagIter != iter->end() )
            return true;

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
    bool GetXYZ( json::const_iterator iter, const string & tag, CVector3 & xyz )
    {
        auto xyzIter = iter->find( tag );
        if( xyzIter != iter->end() )
        {
            float u = 0;
            if( GetFloat( xyzIter, "xyz", u ) )
            {
                xyz = u;
                return true;
            }

            GetFloat( xyzIter, "x", xyz.x );
            GetFloat( xyzIter, "y", xyz.y );
            GetFloat( xyzIter, "z", xyz.z );

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
    bool GetWHD( json::const_iterator iter, const string & tag, CVector3 & whd )
    {
        auto whdIter = iter->find( tag );
        if( whdIter != iter->end() )
        {
            GetFloat( whdIter, "w", whd.w );
            GetFloat( whdIter, "h", whd.h );
            GetFloat( whdIter, "d", whd.d );

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
    bool GetWH( nlohmann::json::const_iterator iter, const string & tag, CSize<int> & wh )
    {
        auto whIter = iter->find( tag );
        if( whIter != iter->end() )
        {
            GetInt( whIter, "w", wh.w );
            GetInt( whIter, "h", wh.h );

            return true;
        }

        return false;
    }

    /// <summary> 
    /// Parse generic w, h tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="wh"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    bool GetWH( nlohmann::json::const_iterator iter, const string & tag, CSize<float> & wh )
    {
        auto whIter = iter->find( tag );
        if( whIter != iter->end() )
        {
            GetFloat( whIter, "w", wh.w );
            GetFloat( whIter, "h", wh.h );

            return true;
        }

        return false;
    }

    /// <summary> 
    /// Parse generic w, h tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="wh"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    bool GetWH( nlohmann::json::const_iterator iter, const string & tag, CVector2 & wh )
    {
        auto whIter = iter->find( tag );
        if( whIter != iter->end() )
        {
            GetFloat( whIter, "w", wh.w );
            GetFloat( whIter, "h", wh.h );

            return true;
        }

        return false;
    }


    // .
    /// *************************************************************************
    /// <summary> 
    /// Parse mesh type tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="meshType"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetMeshType( nlohmann::json::const_iterator iter, NDefs::EMeshType & meshType )
    {
        string str;
        if( GetString( iter, "type", str ) )
        {
            meshType = CDefs::Instance().GetMeshType( str );
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
    bool GetAlignment( json::const_iterator iter, const string & tag, CBitmask<uint> & alignment )
    {
        vector<string> align;
        if( GetString( iter, tag, align ) )
        {
            for( auto & a : align )
                alignment.Add( CDefs::Instance().GetAlignment( a ) );

            if( alignment.Contains( EA_LEFT | EA_RIGHT ) )
                alignment.Remove( EA_LEFT | EA_RIGHT );

            if( alignment.Contains( EA_TOP | EA_BOTTOM ) )
                alignment.Remove( EA_TOP | EA_BOTTOM );

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
    bool GetColor( json::const_iterator iter, CColor & color)
    {
        auto colorIter = iter->find("color");
        if( colorIter != iter->end() )
        {
            GetInt( colorIter, "r", color.r );
            GetInt( colorIter, "g", color.g );
            GetInt( colorIter, "b", color.b );
            GetInt( colorIter, "a", color.a );

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse orientation tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="orientation"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetOrientation( json::const_iterator iter, EOrentation & orientation )
    {
        string str;
        if( GetString( iter, "orientation", str ) )
        {
            orientation = CDefs::Instance().GetOrientation( str );
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse text alignment tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="alignment"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetTextAlignment( json::const_iterator iter, ETextAlignment & alignment )
    {
        string str;
        if( GetString( iter, "textAlignment", str ) )
        {
            alignment = CDefs::Instance().GetTextAlignment( str );
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse script end type tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="endType"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetEndType( json::const_iterator iter, NDefs::EEndType & endType )
    {
        string str;
        if( GetString( iter, "end", str ) )
        {
            endType = CDefs::Instance().GetEndType( str );
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
    bool GetObjectFields( json::const_iterator iter, const string & tag, CBitmask<uint> & fieldType )
    {
        vector<string> field;
        if( GetString( iter, tag, field ) )
        {
            for( auto & f : field )
                fieldType.Add( CDefs::Instance().GetObjectField( f ) );

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse control type tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="fieldType"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetControlType( json::const_iterator iter, const string & tag, EControlType & controlType )
    {
        string str;
        if( GetString( iter, tag, str ) )
        {
            controlType = CDefs::Instance().GetControlType( str );
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse control state tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="fieldType"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetControlState( json::const_iterator iter, const string & tag, EControlState & controlState )
    {
        string str;
        if( GetString( iter, tag, str ) )
        {
            controlState = CDefs::Instance().GetControlState( str );
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse the dimension tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    void GetDimensions( json::const_iterator iter, float & width, float & height, float & depth, float & radius, int & rows, int & columns )
    {
        GetFloat( iter, "width", width );
        GetFloat( iter, "height", height );
        GetFloat( iter, "depth", depth );

        if( !GetFloat( iter, "radius", radius ) )
        {
            GetFloat( iter, "diameter", radius );
            radius *= 0.5f;
        }

        GetInt( iter, "rows", rows );
        GetInt( iter, "columns", columns );
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse the input state tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="inputState"> Value to set. </param>
    /// *************************************************************************
    void GetInputState( json::const_iterator iter, CInputState & inputState )
    {
        auto inputIter = iter->find( "input" );
        if( inputIter != iter->end() )
        {
            auto actionIter = inputIter->begin();
            while( actionIter != inputIter->end() )
            {
                string name;
                GetString( actionIter, "name", name );

                CInputMapping mapping;
                GetInputMapping( actionIter, mapping );

                inputState.AddAction( name, mapping );

                ++actionIter;
            }
        }
    }

    
    /// *************************************************************************
    /// <summary> 
    /// Parse the input mapping tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="mapping"> Value to set. </param>
    /// *************************************************************************
    void GetInputMapping( json::const_iterator iter, CInputMapping & mapping )
    {
        auto deviceIter = iter->find( "mouse" );
        if( deviceIter != iter->end() )
        {
            auto mappingIter = deviceIter->begin();
            while( mappingIter != deviceIter->end() )
            {
                mapping.AddInput( EID_MOUSE, 
                                  CInputManager::Instance().GetInputID( 
                                      EID_MOUSE, 
                                      mappingIter->get<string>() ) );

                ++mappingIter;
            }
        }

        deviceIter = iter->find( "keyboard" );
        if( deviceIter != iter->end() )
        {
            auto mappingIter = deviceIter->begin();
            while( mappingIter != deviceIter->end() )
            {
                mapping.AddInput( EID_KEYBOARD,
                                  CInputManager::Instance().GetInputID(
                                      EID_KEYBOARD,
                                      mappingIter->get<string>() ) );

                ++mappingIter;
            }
        }

        deviceIter = iter->find( "gamepad" );
        if( deviceIter != iter->end() )
        {
            auto mappingIter = deviceIter->begin();
            while( mappingIter != deviceIter->end() )
            {
                mapping.AddInput( EID_GAMEPAD, mappingIter->get<int>() );

                ++mappingIter;
            }
        }
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse object data tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="collectionObject"> Value to set. </param>
    /// *************************************************************************
    void GetCollectionObject( json::const_iterator iter, CCollectionObject & collectionObject )
    {
        string name;
        if( GetString( iter, "name", name ) )
        {
            collectionObject.name = name;
            collectionObject.fields.Add( CCollectionObject::NAME );
        }

        CVector3 position;
        if( GetXYZ( iter, "position", position ) )
        {
            collectionObject.position = position;
            collectionObject.fields.Add( CCollectionObject::POSITION );
        }

        CVector3 rotation;
        if( GetXYZ( iter, "rotation", rotation ) )
        {
            collectionObject.rotation = rotation;
            collectionObject.fields.Add( CCollectionObject::ROTATION );
        }

        CVector3 size;
        if( GetWHD( iter, "size", size ) )
        {
            collectionObject.size = size;
            collectionObject.fields.Add( CCollectionObject::SIZE );
        }
        else if( GetFloat( iter, "size", size.d ) )
        {
            collectionObject.size.d = size.d;
            collectionObject.fields.Add( CCollectionObject::TEXT_SIZE );
        }

        CColor color;
        if( GetColor( iter, color ) )
        {
            collectionObject.color = color;
            collectionObject.fields.Add( CCollectionObject::COLOR );
        }

        bool visible = false;
        if( GetBool( iter, "visible", visible ) )
        {
            collectionObject.visible = visible;
            collectionObject.fields.Add( CCollectionObject::VISIBLE );
        }

        CBitmask<uint> alignment;
        if( GetAlignment( iter, "alignment", alignment ) )
        {
            collectionObject.alignment = alignment;
            collectionObject.fields.Add( CCollectionObject::ALIGNMENT );
        }

        string text;
        if( GetString( iter, "text", text ) )
        {
            collectionObject.text = text;
            collectionObject.fields.Add( CCollectionObject::TEXT );
        }

        ETextAlignment textAlignment;
        if( GetTextAlignment( iter, textAlignment ) )
        {
            collectionObject.textAlignment = textAlignment;
            collectionObject.fields.Add( CCollectionObject::TEXT_ALIGNMENT );
        }
    }
}

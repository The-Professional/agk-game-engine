// Physical component dependency
#include "jsonparsehelper.h"

// Game lib dependencies
#include <agk.h>
#include <common\size.h>
#include <common\vector3.h>
#include <common\color.h>
#include <common\bitmask.h>
#include <common\iobject.h>
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


    // .
    /// *************************************************************************
    /// <summary> 
    /// Parse mesh type tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="meshType"> Loaded mesh type. </param>
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
    /// <param name="alignment"> Loaded alignment. </param>
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
    /// <param name="color"> Loaded color. </param>
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
    /// <param name="orientation"> Loaded orientation. </param>
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
    /// <param name="alignment"> Loaded text alignment. </param>
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
    /// <param name="endType"> Loaded script end type. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetScriptEndType( json::const_iterator iter, EAnimationEndType & endType )
    {
        string str;
        if( GetString( iter, "end", str ) )
        {
            endType = CDefs::Instance().GetAnimationEndType( str );
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
    /// <param name="inputState"> Loaded input state. </param>
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
    /// <param name="mapping"> Loaded input mapping. </param>
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
    /// <param name="pObject"> Loaded collection object. </param>
    /// *************************************************************************
    void GetCollectionObject( json::const_iterator iter, iObject * pObject )
    {
        CVector3 pos;
        if( GetXYZ( iter, "position", pos ) )
            pObject->SetPos( pos );

        CVector3 rot;
        if( GetXYZ( iter, "rotation", rot ) )
            pObject->SetRot( rot );

        CVector3 size;
        if( GetWHD( iter, "size", size ) )
            pObject->SetSize( size );

        bool visible = false;
        if( GetBool( iter, "visible", visible ) )
            pObject->SetVisible( visible );

        float textSize = 0;
        if( GetFloat( iter, "textSize", textSize ) )
            pObject->SetTextSize( textSize );

        CColor color;
        if( GetColor( iter, color ) )
            pObject->SetColor( color );

        CBitmask<uint> alignment;
        if( GetAlignment( iter, "alignment", alignment ) )
            pObject->SetAlignment( alignment );

        ETextAlignment textAlignment;
        if( GetTextAlignment( iter, textAlignment ) )
            pObject->SetTextAlignment( textAlignment );
    }
}

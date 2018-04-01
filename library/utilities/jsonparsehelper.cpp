// Physical component dependency
#include "jsonparsehelper.h"

// Game lib dependencies
#include <agk.h>
#include <common\bitmask.h>
#include <common\vector2.h>
#include <common\vector3.h>
#include <common\vector4.h>
#include <common\iobject.h>
#include <common\collectionobject.h>
#include <input\inputstate.h>
#include <input\inputmapping.h>
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
    /// Parse mesh type tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="meshType"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetMeshType( json::const_iterator iter, NDefs::EMeshType & meshType )
    {
        string str;
        if( GetValue( iter, "type", str ) )
        {
            meshType = CDefs::Instance().GetMeshType( str );
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
        if( GetValue( iter, "orientation", str ) )
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
        if( GetValue( iter, "textAlignment", str ) )
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
        if( GetValue( iter, "end", str ) )
        {
            endType = CDefs::Instance().GetEndType( str );
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse animation list tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="tag"> Tag to find. </param>
    /// <param name="fieldType"> Value to set. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetAnimationList( json::const_iterator iter, const string & tag, vector<vector<string>> & animationList )
    {
        auto listIter = iter->find( tag );
        if( listIter != iter->end() )
        {
            for( auto conflictIter = listIter->begin(); conflictIter != listIter->end(); ++conflictIter )
            {
                animationList.push_back( vector<string>() );
                for( auto animIter = conflictIter->begin(); animIter != conflictIter->end(); ++animIter )
                    animationList.back().push_back( animIter->get<string>() );
            }

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
        if( GetValue( iter, tag, str ) )
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
        if( GetValue( iter, tag, str ) )
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
        GetValue( iter, "width", width );
        GetValue( iter, "height", height );
        GetValue( iter, "depth", depth );

        if( !GetValue( iter, "radius", radius ) )
        {
            GetValue( iter, "diameter", radius );
            radius *= 0.5f;
        }

        GetValue( iter, "rows", rows );
        GetValue( iter, "columns", columns );
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
                GetValue( actionIter, "name", name );

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
        string type;
        if( GetValue( iter, "type", type ) )
        {
            collectionObject.type = CDefs::Instance().GetObjectType( type );
            collectionObject.fields.Add( CCollectionObject::TYPE );
        }

        if( GetValue( iter, "name", collectionObject.name ) )
            collectionObject.fields.Add( CCollectionObject::NAME );

        if( GetXYZ( iter, "position", collectionObject.position ) )
            collectionObject.fields.Add( CCollectionObject::POSITION );

        if( GetXYZ( iter, "rotation", collectionObject.rotation ) )
            collectionObject.fields.Add( CCollectionObject::ROTATION );

        if( GetWHD( iter, "size", collectionObject.size ) )
            collectionObject.fields.Add( CCollectionObject::SIZE );
        else if( GetValue( iter, "size", collectionObject.size.d ) )
            collectionObject.fields.Add( CCollectionObject::TEXT_SIZE );

        if( GetColor( iter, collectionObject.color ) )
            collectionObject.fields.Add( CCollectionObject::COLOR );

        if( GetValue( iter, "visible", collectionObject.visible ) )
            collectionObject.fields.Add( CCollectionObject::VISIBLE );

        if( GetAlignment( iter, "alignment", collectionObject.alignment ) )
            collectionObject.fields.Add( CCollectionObject::ALIGNMENT );

        if( GetValue( iter, "text", collectionObject.text ) )
            collectionObject.fields.Add( CCollectionObject::TEXT );

        if( GetTextAlignment( iter, collectionObject.textAlignment ) )
            collectionObject.fields.Add( CCollectionObject::TEXT_ALIGNMENT );
    }
}
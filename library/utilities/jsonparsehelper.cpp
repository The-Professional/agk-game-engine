// Physical component dependency
#include "jsonparsehelper.h"

// Game lib dependencies
#include <agk.h>
#include <common\size.h>
#include <common\vector3.h>
#include <common\color.h>
#include <common\bitmask.h>
#include <managers\inputstate.h>
#include <managers\inputmapping.h>
#include <managers\inputmanager.h>

// Standard lib dependencies
#include <utility>

using namespace nlohmann;
using namespace std;

namespace NParseHelper
{
    /// *************************************************************************
    /// <summary> 
    /// Parse position tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="vec"> Loaded position. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetPosition( json::const_iterator iter, CVector3 & vec )
    {
        auto posIter = iter->find( "position" );
        if( posIter != iter->end() )
        {
            vec = GetXYZ( posIter );
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse rotation tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="vec"> Loaded rotation. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetRotation( json::const_iterator iter, CVector3 & vec)
    {
        auto rotIter = iter->find( "rotation" );
        if( rotIter != iter->end() )
        {
            vec = GetXYZ( rotIter );
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse scale tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="vec"> Loaded scale. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetScale( json::const_iterator iter, CVector3 & vec)
    {
        vec = 1;

        auto scaleIter = iter->find( "scale" );
        if( scaleIter != iter->end() )
        {
            auto uniIter = scaleIter->find( "uniform" );
            if( uniIter != scaleIter->end() )
                vec = uniIter->get<float>();
            else
                vec = GetXYZ( scaleIter );

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse center position tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="vec"> Loaded center position. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetCenterPos( json::const_iterator iter, CVector3 & vec)
    {
        auto centerIter = iter->find( "center" );
        if( centerIter != iter->end() )
        {
            vec = GetXYZ( centerIter );
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse generic x, y, z tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// *************************************************************************
    CVector3 GetXYZ( json::const_iterator iter )
    {
        CVector3 vec;

        auto xyzIter = iter->find( "x" );
        if( xyzIter != iter->end() )
            vec.x = xyzIter->get<float>();
        
        xyzIter = iter->find( "y" );
        if( xyzIter != iter->end() )
            vec.y = xyzIter->get<float>();

        xyzIter = iter->find( "z" );
        if( xyzIter != iter->end() )
            vec.z = xyzIter->get<float>();

        return vec;
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
            auto rgbaIter = colorIter->find( "r" );
            if( rgbaIter != colorIter->end() )
                color.r = rgbaIter->get<int>();

            rgbaIter = colorIter->find( "g" );
            if( rgbaIter != colorIter->end() )
                color.g = rgbaIter->get<int>();

            rgbaIter = colorIter->find( "b" );
            if( rgbaIter != colorIter->end() )
                color.b = rgbaIter->get<int>();

            rgbaIter = colorIter->find( "a" );
            if( rgbaIter != colorIter->end() )
                color.a = rgbaIter->get<int>();

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse size tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="size"> Loaded size. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetSize( json::const_iterator iter, CSize & size)
    {
        auto sizeIter = iter->find( "size" );
        if ( sizeIter != iter->end() )
        {
            auto whIter = sizeIter->find( "w" );
            if( whIter != sizeIter->end() )
                size.w = whIter->get<int>();

            whIter = sizeIter->find( "h" );
            if( whIter != sizeIter->end() )
                size.h = whIter->get<int>();

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse name tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="name"> Loaded name. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetName( json::const_iterator iter, string & name )
    {
        auto nameIter = iter->find( "name" );
        if( nameIter != iter->end() )
        {
            name = nameIter->get<string>();
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse alignment tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="alignment"> Loaded alignment. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetAlignment( json::const_iterator iter, CBitmask<uint> & alignment)
    {
        auto alignmentIter = iter->find( "alignment" );
        if( alignmentIter != iter->end() )
        {
            auto sideIter = alignmentIter->find( "left" );
            if( sideIter != alignmentIter->end() )
                alignment.Add( NDefs::EA_LEFT );

            sideIter = alignmentIter->find( "right" );
            if( sideIter != alignmentIter->end() )
                alignment.Add( NDefs::EA_RIGHT );

            sideIter = alignmentIter->find( "top" );
            if( sideIter != alignmentIter->end() )
                alignment.Add( NDefs::EA_TOP );

            sideIter = alignmentIter->find( "bottom" );
            if( sideIter != alignmentIter->end() )
                alignment.Add( NDefs::EA_BOTTOM );

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse fullscreen tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="fullscreen"> Loaded fullscreen mode. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetFullscreen( json::const_iterator iter, bool & fullscreen)
    {
        auto fullscreenIter = iter->find( "fullscreen" );
        if( fullscreenIter != iter->end() )
        {
            fullscreen = fullscreenIter->get<bool>();
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse fullscreen tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="orientation"> Loaded orientation. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetOrientation( json::const_iterator iter, NDefs::EOrentation & orientation)
    {
        auto orientationIter = iter->find( "orientation" );
        if( orientationIter != iter->end() )
        {
            if( orientationIter->get<string>() == "portrait" )
                orientation = NDefs::EO_PORTRAIT;
            else
                orientation = NDefs::EO_LANDSCAPE;

            return true;
        }

        return false;
    }

    
    /// *************************************************************************
    /// <summary> 
    /// Parse antialias tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="antialias"> Loaded antialias flag. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetAntialias( nlohmann::json::const_iterator iter, bool & antialias )
    {
        auto antialiasIter = iter->find( "antialias" );
        if( antialiasIter != iter->end() )
        {
            antialias = antialiasIter->get<bool>();
            return true;
        }

        return false;
    }

    
    /// *************************************************************************
    /// <summary> 
    /// Parse the mesh tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="mesh"> Loaded mesh name. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetMesh( nlohmann::json::const_iterator iter, std::string & mesh )
    {
        auto meshIter = iter->find( "mesh" );
        if( meshIter != iter->end() )
        {
            mesh = meshIter->get<string>();
            return true;
        }

        return false;
    }

    
    /// *************************************************************************
    /// <summary> 
    /// Parse the texture map tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="image"> Loaded texture map name. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetTextureMap( nlohmann::json::const_iterator iter, std::string & image )
    {
        auto textureMapIter = iter->find( "textureMap" );
        if( textureMapIter != iter->end() )
        {
            image = textureMapIter->get<string>();
            return true;
        }

        return false;
    }

    
    /// *************************************************************************
    /// <summary> 
    /// Parse the normal map tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="image"> Loaded normal map name. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetNormalMap( nlohmann::json::const_iterator iter, std::string & image )
    {
        auto normalMapIter = iter->find( "normalMap" );
        if( normalMapIter != iter->end() )
        {
            image = normalMapIter->get<string>();
            return true;
        }

        return false;
    }

    
    /// *************************************************************************
    /// <summary> 
    /// Parse the specular map tag.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
    /// <param name="image"> Loaded specular map name. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool GetSpecularMap( nlohmann::json::const_iterator iter, std::string & image )
    {
        auto specularMapIter = iter->find( "specularMap" );
        if( specularMapIter != iter->end() )
        {
            image = specularMapIter->get<string>();
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
    void GetDimensions( nlohmann::json::const_iterator iter, float & width, float & height, float & length, float & radius, int & rows, int & columns )
    {
        auto dimIter = iter->find( "width" );
        if( dimIter != iter->end() )
            width = dimIter->get<float>();

        dimIter = iter->find( "height" );
        if( dimIter != iter->end() )
            height = dimIter->get<float>();

        dimIter = iter->find( "length" );
        if( dimIter != iter->end() )
            length = dimIter->get<float>();

        dimIter = iter->find( "radius" );
        if( dimIter != iter->end() )
            radius = dimIter->get<float>();
        else
        {
            dimIter = iter->find( "diameter" );
            if( dimIter != iter->end() )
                radius = dimIter->get<float>() * 0.5f;
        }

        dimIter = iter->find( "rows" );
        if( dimIter != iter->end() )
            rows = dimIter->get<int>();

        dimIter = iter->find( "columns" );
        if( dimIter != iter->end() )
            columns = dimIter->get<int>();
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse the input state tags.
    /// </summary>
    /// <param name="iter"> JSON node to parse. </param>
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
                GetName( actionIter, name );

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
    /// *************************************************************************
    void GetInputMapping( json::const_iterator iter, CInputMapping & mapping )
    {
        auto deviceIter = iter->find( "mouse" );
        if( deviceIter != iter->end() )
        {
            auto mappingIter = deviceIter->begin();
            while( mappingIter != deviceIter->end() )
            {
                mapping.AddInput( NDefs::EID_MOUSE, 
                                  CInputManager::Instance().GetInputID( 
                                      NDefs::EID_MOUSE, 
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
                mapping.AddInput( NDefs::EID_KEYBOARD,
                                  CInputManager::Instance().GetInputID(
                                      NDefs::EID_KEYBOARD,
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
                mapping.AddInput( NDefs::EID_GAMEPAD, mappingIter->get<int>() );

                ++mappingIter;
            }
        }
    }
}

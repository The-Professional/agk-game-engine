// Physical component dependency
#include <utilities/xmlparsehelper.h>

// Standard lib dependency
#include <utility>

namespace NParseHelper
{
    /// *************************************************************************
    /// <summary> 
    /// Parse position tags.
    /// </summary>
    /// <param name="node"> XML node to parse. </param>
    /// <param name="vec"> Loaded position. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool LoadPosition( const XMLNode & node, CVector3 & vec )
    {
        XMLNode positionNode = node.getChildNode( "position" );
        if( !positionNode.isEmpty() )
        {
            vec = LoadXYZ( positionNode );
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse rotation tags.
    /// </summary>
    /// <param name="node"> XML node to parse. </param>
    /// <param name="vec"> Loaded rotation. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool LoadRotation( const XMLNode & node, CVector3 & vec )
    {
        XMLNode rotationNode = node.getChildNode( "rotation" );
        if( !rotationNode.isEmpty() )
        {
            vec = LoadXYZ( rotationNode );
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse scale tags.
    /// </summary>
    /// <param name="node"> XML node to parse. </param>
    /// <param name="vec"> Loaded scale. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool LoadScale( const XMLNode & node, CVector3 & vec )
    {
        vec = 1;

        XMLNode scaleNode = node.getChildNode( "scale" );
        if( !scaleNode.isEmpty() )
        {
            if( scaleNode.isAttributeSet( "uniform" ) )
                vec = (float)std::atof( scaleNode.getAttribute( "uniform" ) );
            else
                vec = LoadXYZ( scaleNode );

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse center position tags.
    /// </summary>
    /// <param name="node"> XML node to parse. </param>
    /// <param name="vec"> Loaded center position. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool LoadCenterPos( const XMLNode & node, CVector3 & vec )
    {
        XMLNode centerNode = node.getChildNode( "center" );
        if( !centerNode.isEmpty() )
        {
            vec = LoadXYZ( centerNode );
            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse color tags.
    /// </summary>
    /// <param name="node"> XML node to parse. </param>
    /// <param name="vec"> Loaded color. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool LoadColor( const XMLNode & node, CColor & color )
    {
        XMLNode colorNode = node.getChildNode( "color" );
        if( !colorNode.isEmpty() )
        {
            if( colorNode.isAttributeSet( "r" ) )
                color.r = std::atoi(colorNode.getAttribute( "r" ));

            if( colorNode.isAttributeSet( "g" ) )
                color.g = std::atoi(colorNode.getAttribute( "g" ));

            if( colorNode.isAttributeSet( "b" ) )
                color.b = std::atoi(colorNode.getAttribute( "b" ));

            if( colorNode.isAttributeSet( "a" ) )
                color.a = std::atoi(colorNode.getAttribute( "a" ));

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse size tags.
    /// </summary>
    /// <param name="node"> XML node to parse. </param>
    /// <param name="vec"> Loaded size. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool LoadSize( const XMLNode & node, CSize & size )
    {
        XMLNode sizeNode = node.getChildNode( "size" );
        if( !sizeNode.isEmpty() )
        {
            if( node.isAttributeSet( "w" ) )
                size.w = std::atoi( node.getAttribute( "w" ) );

            if( node.isAttributeSet( "h" ) )
                size.h = std::atoi( node.getAttribute( "h" ) );

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse alignment tags.
    /// </summary>
    /// <param name="node"> XML node to parse. </param>
    /// <param name="alignment"> Loaded alignment. </param>
    /// <returns> If the tag exists. </returns>
    /// *************************************************************************
    bool LoadAlignment( const XMLNode & node, CBitmask<uint> & alignment )
    {
        XMLNode alignmentNode = node.getChildNode( "alignment" );
        if( !alignmentNode.isEmpty() )
        {
            if( node.isAttributeSet( "left" ) )
                alignment.Add( NDefs::EA_LEFT );

            if( node.isAttributeSet( "right" ) )
                alignment.Add( NDefs::EA_RIGHT );

            if( node.isAttributeSet( "top" ) )
                alignment.Add( NDefs::EA_TOP );

            if( node.isAttributeSet( "bottom" ) )
                alignment.Add( NDefs::EA_BOTTOM );

            return true;
        }

        return false;
    }


    /// *************************************************************************
    /// <summary> 
    /// Parse generic x, y, z tags.
    /// </summary>
    /// <param name="node"> XML node to parse. </param>
    /// *************************************************************************
    CVector3 LoadXYZ( const XMLNode & node )
    {
        CVector3 vec;

        if( node.isAttributeSet( "x" ) )
            vec.x = (float)std::atof( node.getAttribute( "x" ) );

        if( node.isAttributeSet( "y" ) )
            vec.y = (float)std::atof( node.getAttribute( "y" ) );

        if( node.isAttributeSet( "z" ) )
            vec.z = (float)std::atof( node.getAttribute( "z" ) );

        return vec;
    }

}   // NGenFunc

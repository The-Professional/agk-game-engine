// Physical component dependency
#include "script.h"

// Game lib dependencies


/// *************************************************************************
/// <summary>
/// Constructor
/// </summary>
/// *************************************************************************
CScript::CScript()
{
}


/// *************************************************************************
/// <summary> 
/// Constructor
/// </summary>
/// <param name="pData"> Data to initialize the script. </param> 
/// <param name="pObject"> Object to apply the script to. </param> 
/// *************************************************************************
CScript::CScript( CAnimationData * pData, iObject * pObject )
{
    Init( pData, pObject );
}


/// *************************************************************************
/// <summary>
/// Destructor
/// </summary>
/// *************************************************************************
CScript::~CScript()
{
    Clear();
}


/// *************************************************************************
/// <summary>
/// Initialize the script.
/// </summary>
/// <param name="pData"> Data to initialize the script. </param> 
/// <param name="pObject"> Object to apply the script to. </param> 
/// *************************************************************************
void CScript::Init( CAnimationData * pData, iObject * pObject )
{
}
// Physical component dependency
#include "template.h"

// Game lib dependencies
#include <utilities\settings.h>
#include <managers\inputmanager.h>
#include <managers\spritemanager.h>
#include <managers\resourcemanager.h>
#include <managers\scriptmanager.h>
#include <script\scriptglobals.h>
#include <script\scriptcolor.h>
#include <script\scriptvector3.h>
#include <script\animation.h>
#include <3d\sprite3d.h>
#include <2d\sprite2d.h>
#include <2d\textsprite.h>

// AngelScript lib dependencies
#include <scriptstdstring/scriptstdstring.h>
#include <scriptarray/scriptarray.h>

// Standard lib dependencies
#include <vector>

// Namespace
using namespace AGK;
using namespace std;

app App;

CSprite3D * pSprite;
vector<iObject *> pObjectList;

void app::Init()
{
    // Load and apply the settings.
    CSettings::Instance().SetPath( "data/settings.json" );
    CSettings::Instance().LoadSettings();
    CSettings::Instance().ApplySettings();

    // Load the input mapping.
    CInputManager::Instance().SetPath( "data/inputs.json" );
    CInputManager::Instance().LoadInputMap();

    // Load all of our lists.
    CResourceManager::Instance().LoadImageList( "data/images/" );
    CResourceManager::Instance().LoadFontList( "data/fonts/" );
    CSpriteManager::Instance().LoadDataFileList3D( "data/3d/sprites/" );
    CSpriteManager::Instance().LoadDataFileList2D( "data/2d/sprites/" );
    CSpriteManager::Instance().LoadTextDataFileList( "data/2d/text/" );
    CSpriteManager::Instance().LoadCollectionFileList( "data/collections/" );
    CScriptManager::Instance().LoadScriptList( "data/scripts" );
    CScriptManager::Instance().LoadAnimationDataFileList( "data/animations" );

    RegisterStdString( CScriptManager::Instance().GetEnginePtr() );
    RegisterScriptArray( CScriptManager::Instance().GetEnginePtr(), false );
    NScriptGlobals::Register( CScriptManager::Instance().GetEnginePtr() );
    NScriptColor::Register( CScriptManager::Instance().GetEnginePtr() );
    NScriptVector3::Register( CScriptManager::Instance().GetEnginePtr() );

    CAnimation::Register( CScriptManager::Instance().GetEnginePtr() );

    CScriptManager::Instance().LoadScript( "defs" );
    CScriptManager::Instance().LoadScript( "general" );
    CScriptManager::Instance().LoadScript( "controls" );
    CScriptManager::Instance().BuildScript();
}

void app::Begin()
{
    agk::SetErrorMode( 2 );
	agk::SetClearColor( 0, 0, 0 );
	agk::SetSyncRate( 60, 0 );
	agk::SetScissor( 0, 0, 0, 0 );

    pObjectList = CSpriteManager::Instance().CreateCollection( "stage0" );
    pSprite = CSpriteManager::Instance().CreateSprite3D( "ball" );
    pSprite->SetScale( 2 );
    CSpriteManager::Instance().Transform();

    pObjectList[0]->SetParent( pSprite, true );
}

int app::Loop()
{
    // Close the game.
    if( CInputManager::Instance().IsReleased( "menu", "menu back" ) )
        return 1;

    CSettings::Instance().CheckForWindowSizeChange();

    if( CInputManager::Instance().IsReleased( "menu", "menu select" ) )
    {
        /*pSprite->IncPos( 0, 1, 0 );
        pSprite->IncRot( 0, 0, 10 );
        pSprite->IncSize( 1 );*/
        if( pObjectList[2]->IsPlaying() )
            pObjectList[2]->Stop( NDefs::EST_BREAK );
        else
            pObjectList[2]->Play( "color", NDefs::EST_BREAK );
    }

    CSpriteManager::Instance().Update();
    CSpriteManager::Instance().Transform();

	agk::Print( agk::ScreenFPS() );
	agk::Sync();

	return 0; // return 1 to close app
}


void app::End()
{
}

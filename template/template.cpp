// Includes
#include "template.h"

#include <utilities\settings.h>
#include <managers\inputmanager.h>
#include <managers\spritemanager.h>
#include <managers\resourcemanager.h>
#include <3d\sprite3d.h>
#include <2d\sprite2d.h>

// Namespace
using namespace AGK;

app App;

CSprite3D * pSprite;
CSprite2D * pSprite2;

//int test, sub;

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
    CSpriteManager::Instance().LoadCollectionFileList3D( "data/3d/sprites/collections/" );

}

void app::Begin()
{
    agk::SetErrorMode( 2 );
	agk::SetClearColor( 0, 0, 0 );
	agk::SetSyncRate( 0, 0 );
	agk::SetScissor( 0, 0, 0, 0 );

    CSpriteManager::Instance().CreateSpriteCollection3D( "stage0" );
    pSprite = CSpriteManager::Instance().CreateSprite3D( "ball" );
    pSprite->SetScale( 2 );

    pSprite2 = CSpriteManager::Instance().CreateSprite2D( "test" );
}

int app::Loop()
{
    if( CInputManager::Instance().IsReleased("menu", "menu select") )
        pSprite->IncRot( 90.f, 90.f, 0 );

	agk::Print( agk::ScreenFPS() );
	agk::Sync();

	return 0; // return 1 to close app
}


void app::End()
{
}

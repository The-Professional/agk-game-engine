// Includes
#include "template.h"

#include <utilities\settings.h>
#include <managers\spritemanager.h>
#include <managers\resourcemanager.h>
#include <3d\sprite3d.h>

// Namespace
using namespace AGK;

app App;

CSprite3D * pSprite;

void app::Init()
{
    CSettings::Instance().SetFilePath( "data/settings.json" );
    CSettings::Instance().LoadSettings();
    CSettings::Instance().ApplySettings();
}

void app::Begin()
{
    agk::SetErrorMode( 2 );
	agk::SetClearColor( 0, 0, 0 ); // light blue
	agk::SetSyncRate( 0, 0 );
	agk::SetScissor( 0, 0, 0, 0 );

    CResourceManager::Instance().LoadList( NDefs::ERT_IMAGE, "data/3d/lists/imageList.json" );
    CSpriteManager::Instance().LoadDataFileList3D( "data/3d/lists/spriteDataList3d.json" );
    CSpriteManager::Instance().LoadCollectionFileList3D( "data/3d/lists/spriteCollectionList3d.json" );
    CSpriteManager::Instance().CreateSpriteCollection3D( "stage0" );
    pSprite = CSpriteManager::Instance().CreateSprite3D( "ball" );
    pSprite->SetScale( 2 );
}

int app::Loop()
{
    pSprite->IncRot( 0.005f, 0.005f, 0 );

	agk::Print( agk::ScreenFPS() );
	agk::Sync();

	return 0; // return 1 to close app
}


void app::End()
{
}

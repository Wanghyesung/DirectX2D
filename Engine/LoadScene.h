#pragma once
#include "..\Engine_Source\WSceneManger.h"
#include "WPlayScene.h"
#include "WPlayScene.h"
#include "WLeafreScene.h"
#include "WValleyScene.h"
#include "WValleyScene_2.h"
#include "WCaveScene.h"
#include "WTempleScene.h"
#include "WTempleScene_2.h"
#include "WTempleBossScene.h"
#include "WMoveScene.h"
#include "WMoveScene_2.h"
#include "WCaveStartScene.h"
#include "WTempleStartScene.h"

#ifdef _DEBUG
#pragma comment (lib,"..\\x64\\Debug\\Engine.lib")

#else
#pragma comment (lib, "..\\x64\\Release\\Engine.lib")
#endif


namespace W
{
	void InitializeScenes()
	{
		SceneManger::CreateScene<PlayScene>(L"PlayScene");
		SceneManger::CreateScene<LeafreScene>(L"Leafre");
		SceneManger::CreateScene<ValleyScene_2>(L"Valley2");
		SceneManger::CreateScene<CaveStartScene>(L"Start1");
		SceneManger::CreateScene<CaveScene>(L"Cave");
		SceneManger::CreateScene<TempleScene>(L"Temple");
		SceneManger::CreateScene<TempleScene_2>(L"Temple2");
		SceneManger::CreateScene<TempleStartScene>(L"Start2");
		SceneManger::CreateScene<TempleBossScene>(L"TempleBoss");
		SceneManger::CreateScene<MoveScene>(L"Move1");
		SceneManger::CreateScene<MoveScene_2>(L"Move2");
		SceneManger::CreateScene<ValleyScene>(L"Valley");
		//SceneManger::CreateScene<PlayScene>(L"PlayScene");
	}
}
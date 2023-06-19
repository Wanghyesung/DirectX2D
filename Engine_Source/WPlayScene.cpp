#include "WPlayScene.h"
#include "WTransform.h"
#include "WMeshRenderer.h"

namespace W
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		GameObject* pPlayer = new GameObject();
		AddGameObject(eLayerType::Player, pPlayer);
		pPlayer->AddComponent<MeshRenderer>();

		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//player2->AddComponent<MeshRenderer>();
		//
		//pPlayer->GetComponent<Transform>()->SetPosition(0.5f,0.5f,0.f);

	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene::Render()
	{
		Scene::Render();
	}
}

#include "WPlayScene.h"
#include "WTransform.h"
#include "WResources.h"
#include "WMeshRenderer.h"
#include "WMesh.h"
#include "WMaterial.h"
#include "WCameraScript.h"
#include "WCamera.h"
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
		{
			GameObject* pPlayer = new GameObject();
			AddGameObject(eLayerType::Player, pPlayer);
			MeshRenderer* pMeshRender = pPlayer->AddComponent<MeshRenderer>();
			pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			pMeshRender->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			pPlayer->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		}

		{
			GameObject* pPlayer = new GameObject();
			AddGameObject(eLayerType::Player, pPlayer);
			MeshRenderer* pMeshRender = pPlayer->AddComponent<MeshRenderer>();
			pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			pMeshRender->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			pPlayer->GetComponent<Transform>()->SetPosition(2.f,0.f,0.f);
		}

		//camera object
		GameObject* pCamera = new GameObject();
		AddGameObject(eLayerType::Player, pCamera);
		pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
		Camera* pCameraComp = pCamera->AddComponent<Camera>();
		pCamera->AddComponent<CameraScript>();
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

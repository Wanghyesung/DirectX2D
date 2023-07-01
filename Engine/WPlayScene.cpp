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
			GameObject* pPlayer2 = new GameObject();
			AddGameObject(eLayerType::Player, pPlayer2);
			MeshRenderer* pMeshRender2 = pPlayer2->AddComponent<MeshRenderer>();
			pMeshRender2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			pMeshRender2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			pPlayer2->GetComponent<Transform>()->SetPosition(2.f, 0.f, 0.f);


			GameObject* pPlayer = new GameObject();
			AddGameObject(eLayerType::Player, pPlayer);
			MeshRenderer* pMeshRender = pPlayer->AddComponent<MeshRenderer>();
			pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			pMeshRender->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			pPlayer->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.f));
			pPlayer->GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.5f, 0.f));
			//Resources::Find<Material>(L"SpriteMaterial")->SetRenderinMode(eRenderingMode::Transparent);

			pPlayer2->GetComponent<Transform>()->SetParent(pPlayer->GetComponent<Transform>());


			//pPlayer->GetComponent<Transform>()->SetPosition(2.f, 0.f, 0.f);
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

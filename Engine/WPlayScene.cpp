#include "WPlayScene.h"
#include "WTransform.h"
#include "WResources.h"
#include "WMeshRenderer.h"
#include "WMesh.h"
#include "WMaterial.h"
#include "WCameraScript.h"
#include "WCamera.h"
#include "WGridScript.h"
#include "WObject.h"
#include "WRenderer.h"
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
			GameObject* player
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);

			player->SetName(L"Zelda");

			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));

			GameObject* player2 = new GameObject();
			player2->SetName(L"ZeldaChild");
			AddGameObject(eLayerType::Player, player2);
			MeshRenderer* mr2 = player2->AddComponent<MeshRenderer>();
			mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			player2->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 1.0001f));

			player2->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());
			//player->AddComponent<CameraScript>();

			const float pi = 3.141592f;
			float degree = pi / 2.0f;

			player->GetComponent<Transform>()->SetPosition(Vector3(-3.0f, 0.0f, 1.0001f));
			player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));
		}

		{
			GameObject* player = new GameObject();
			player->SetName(L"Smile");
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			//player->AddComponent<CameraScript>();
		}

		{
			GameObject* player = new GameObject();
			player->SetName(L"Smile");
			AddGameObject(eLayerType::UI, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.2f, 0.0f, 0.0f));
			//player->AddComponent<CameraScript>();
		}

		//Main Camera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TrunLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			//renderer::m_vecCameras.push_back(cameraComp);
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TrunLayerMask(eLayerType::Player, false);
			//camera->AddComponent<CameraScript>();
		}

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

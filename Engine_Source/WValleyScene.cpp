#include "WValleyScene.h"
#include "WResources.h"
#include "WShader.h"
#include "WGameObject.h"
#include "WMesh.h"
#include "WMaterial.h"
#include "WMeshRenderer.h"
#include "WTransform.h"
#include "WInput.h"
#include "WSceneManger.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WLadder.h"
#include "WNPC.h"
#include "WCage.h"


namespace W
{
	ValleyScene::ValleyScene()
	{
		std::shared_ptr<Texture> pLadder9 =
			Resources::Load<Texture>(L"Ladder9BaseTex", L"..\\Resources\\Texture\\Object\\ladder\\9_base.png");

		std::shared_ptr<Material> pLadderMater9 = std::make_shared<Material>();
		pLadderMater9->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pLadderMater9->SetTexture(pLadder9);
		Resources::Insert(L"LadderBaseMater9", pLadderMater9);


		std::shared_ptr<Texture> pLadder9_ =
			Resources::Load<Texture>(L"Ladder9Base_Tex", L"..\\Resources\\Texture\\Object\\ladder\\9base.png");

		std::shared_ptr<Material> pLadderMater9_ = std::make_shared<Material>();
		pLadderMater9_->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pLadderMater9_->SetTexture(pLadder9_);
		Resources::Insert(L"LadderBaseMater9_", pLadderMater9_);

		//npc
		std::shared_ptr<Texture> pNPCTex =
			Resources::Load<Texture>(L"NPCTex1", L"..\\Resources\\Texture\\NPC\\npc1.png");

		std::shared_ptr<Material> pNPCMater = std::make_shared<Material>();
		pNPCMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pNPCMater->SetTexture(pNPCTex);
		Resources::Insert(L"NPCMater1", pNPCMater);

	
	}
	ValleyScene::~ValleyScene()
	{

	}
	void ValleyScene::Initialize()
	{
		CreateBackground();
		setobject();

		NPC* pNPC = new NPC();
	 	MeshRenderer* pMeshRenderer = pNPC->AddComponent<MeshRenderer>();
		AddGameObject(eLayerType::NPC, pNPC);
		pMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRenderer->SetMaterial(Resources::Find<Material>(L"NPCMater1"));
		pNPC->GetComponent<Transform>()->SetPosition(2.5f, 7.5f, -0.2f);
		pNPC->GetComponent<Transform>()->SetScale(0.761f, 1.f, 0.f);
		//0.761 : 1


		GameObject* pCamera = new GameObject();
		AddGameObject(eLayerType::Player, pCamera);
		pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
		Camera* pCameraComp = pCamera->AddComponent<Camera>();
		pCamera->AddComponent<CameraScript>();
	}
	void ValleyScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Cave");
		}
	}
	void ValleyScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void ValleyScene::Render()
	{
		Scene::Render();
	}
	void ValleyScene::OnEnter()
	{

	}
	void ValleyScene::OnExit()
	{

	}
	void ValleyScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"dragonValleyMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//035 : 1
		pBackGround->GetComponent<Transform>()->SetScale(25 * 0.35f,  25.f * 1.f, 1.f);
	}

	void ValleyScene::setobject()
	{
		Cage* pCage = new Cage();
		AddGameObject(eLayerType::Object, pCage);
		
		pCage->GetComponent<Transform>()->SetPosition(2.5f, 7.57f, -0.3f);
		pCage->GetComponent<Transform>()->SetScale(0.641f * 2.2f, 1.f * 2.2f, 0.f);
		//0.641 : 1

		Ladder* pLadder0 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder0);
		MeshRenderer* pLadderMeshRender0 = pLadder0->AddComponent<MeshRenderer>();
		pLadderMeshRender0->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender0->SetMaterial(Resources::Find<Material>(L"LadderBaseMater9_"));
		pLadder0->GetComponent<Transform>()->SetPosition(0.f, -4.5f, -0.1f);
		pLadder0->GetComponent<Transform>()->SetScale(1.f * 0.6f, 6.f * 0.6f, 0.f);

		Ladder* pLadder1 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder1);
		MeshRenderer* pLadderMeshRender1 = pLadder1->AddComponent<MeshRenderer>();
		pLadderMeshRender1->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender1->SetMaterial(Resources::Find<Material>(L"LadderBaseMater9_"));
		pLadder1->GetComponent<Transform>()->SetPosition(2.f, 4.2f, -0.1f);
		pLadder1->GetComponent<Transform>()->SetScale(1.f * 0.6f, 6.f * 0.6f, 0.f);

		Ladder* pLadder2 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder2);
		MeshRenderer* pLadderMeshRender2 = pLadder2->AddComponent<MeshRenderer>();
		pLadderMeshRender2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender2->SetMaterial(Resources::Find<Material>(L"LadderBaseMater9"));
		pLadder2->GetComponent<Transform>()->SetPosition(-1.f, -0.7f, -0.1f);
		pLadder2->GetComponent<Transform>()->SetScale(1.f * 0.6f, 5.f * 0.6f, 0.f);

	}
}

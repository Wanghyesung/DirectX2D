#include "guiEditor.h"
#include "WMesh.h"
#include "WResources.h"
#include "WTransform.h"
#include "WMeshRenderer.h"
#include "WMaterial.h"
#include "WGridScript.h"
#include "WRenderer.h"

namespace gui
{
	using namespace W::enums;
	std::vector<Widget*> Editor::m_vecWidgets = {};
	std::vector<EditorObject*> Editor::m_vecEditorObjects = {};
	std::vector<DebugObject*> Editor::m_vecDebugObjects = {};

	void Editor::Initialize()
	{
		//m_vecDebugObjects.resize((UINT)eColliderType::End);
		//
		//std::shared_ptr<W::Mesh> spMesh =
		//	W::Resources::Find<W::Mesh>(L"DebugRect");
		//std::shared_ptr<W::Material> spMaterial =
		//	W::Resources::Find<W::Material>(L"DebugMaterial");;
		//
		//m_vecDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		//m_vecDebugObjects[(UINT)eColliderType::Rect]->AddComponent<W::Transform>();
		//W::MeshRenderer* pMeshRender =
		//	m_vecDebugObjects[(UINT)eColliderType::Rect]->AddComponent<W::MeshRenderer>();
		//pMeshRender->SetMaterial(spMaterial);
		//pMeshRender->SetMesh(spMesh);
		//
		//EditorObject* pGrid = new EditorObject();
		//pGrid->SetName(L"Grid");
		//
		//pMeshRender = pGrid->AddComponent<W::MeshRenderer>();
		//pMeshRender->SetMesh(W::Resources::Find<W::Mesh>(L"RectMesh"));
		//pMeshRender->SetMaterial(W::Resources::Find<W::Material>(L"GridMaterial"));
		//W::GridScript* gridSc = pGrid->AddComponent<W::GridScript>();
		//gridSc->SetCamera(renderer::m_vecCameras[0]);
		//
		//m_vecEditorObjects.push_back(pGrid);
	}
	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void Editor::Update()
	{
		for (EditorObject* obj : m_vecEditorObjects)
		{
			obj->Update();
		}
	}
	void Editor::LateUpdate()
	{
		for (EditorObject* obj : m_vecEditorObjects)
		{
			obj->LateUpdate();
		}
	}
	void Editor::Render()
	{
		for (EditorObject* obj : m_vecEditorObjects)
		{
			obj->Render();
		}

		for (const W::graphics::DebugMesh& mesh :
			renderer::m_vecDebugMeshs)
		{
			DebugRender(mesh);
		}
	}
	void Editor::Release()
	{


	}
	void Editor::DebugRender(const W::graphics::DebugMesh& _mesh)
	{
		DebugObject* pDebugObj = m_vecDebugObjects[(UINT)_mesh.eType];

		pDebugObj->Render();
		
	}
}
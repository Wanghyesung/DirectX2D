#include "WMeshRenderer.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WRenderer.h"

namespace W
{
	MeshRenderer::MeshRenderer():
		Component(eComponentType::MeshRenderer)
	{
	}
	MeshRenderer::~MeshRenderer()
	{
		int a = 10;
	}
	void MeshRenderer::Initialize()
	{

	}
	void MeshRenderer::Update()
	{

	}
	void MeshRenderer::LateUpdate()
	{
	}
	void MeshRenderer::Render()
	{
		//lateupdat�� update���� ������ ���� mesh, shader���� ��ġ���� ���ļ� ����
		Transform* pTransform = GetOwner()->GetComponent<Transform>();
		pTransform->BindConstantBuffer();

		//mMesh->BindBuffer();
		//mShader->Binds();

		m_pMesh->BindBuffer();
		m_pMaterial->Binds();
		m_pMesh->Render();
		//GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
	}
}
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
		Transform* pTransform = GetOwner()->GetComponent<Transform>();
		pTransform->BindConstantBuffer();

		//mMesh->BindBuffer();
		//mShader->Binds();

		renderer::mesh->BindBuffer();
		renderer::shader->Binds();
		GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);

		

	}
}
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
		//lateupdat나 update에서 돌리고 오면 mesh, shader에서 위치값이 겹쳐서 들어옴
		Transform* pTransform = GetOwner()->GetComponent<Transform>();
		pTransform->BindConstantBuffer();

		//mMesh->BindBuffer();
		//mShader->Binds();

		renderer::mesh->BindBuffer();
		renderer::shader->Binds();
		GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);

		

	}
}
#include "WTransform.h"
#include "WRenderer.h"
#include "WConstantBuffer.h"
namespace W
{
	using namespace W::graphics;

	Transform::Transform():
		Component(eComponentType::Transform),
		m_vPosition(Vector3::Zero),
		m_vRotation(Vector3::Zero),
		m_vScale(Vector3::One)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
	}
	void Transform::LateUpdate()
	{
	}
	void Transform::Render()
	{
	}
	void Transform::BindConstantBuffer()
	{
		ConstantBuffer* pConstBuffer = renderer::constantBuffer;
		Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&vPosition);
		pConstBuffer->Bind(eShaderStage::VS);
	}
}
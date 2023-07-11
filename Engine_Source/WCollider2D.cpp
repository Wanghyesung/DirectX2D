#include "WCollider2D.h"
#include "WGameObject.h"

namespace W
{
	Collider2D::Collider2D():
		Component(eComponentType::Collider2D),
		m_pTransform(nullptr),
		m_vSize(Vector2::One),
		m_vCenter(Vector2::Zero)
	{
	}
	Collider2D::~Collider2D()
	{
	}
	void Collider2D::Initialize()
	{
		m_pTransform = GetOwner()->GetComponent<Transform>();
	}
	void Collider2D::Update()
	{
	}
	void Collider2D::LateUpdate()
	{
	}
	void Collider2D::Render()
	{
	}
}
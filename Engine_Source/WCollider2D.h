#pragma once
#include "WComponent.h"
#include "WTransform.h"

namespace W
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		virtual ~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetType(eColliderType _eType) { m_eType = _eType; }
		void SetSize(Vector2 _vSize) { m_vSize = _vSize; }
		void SetCenter(Vector2 _vCenter) { m_vCenter = _vCenter; }

	private:
		eColliderType m_eType;
		Transform* m_pTransform;

		Vector2 m_vSize;
		Vector2 m_vCenter;
	};
}



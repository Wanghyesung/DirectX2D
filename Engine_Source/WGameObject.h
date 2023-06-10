#pragma once

#include "WEntity.h"
#include "WComponent.h"
#include "WConstantBuffer.h"
#include "WMesh.h"
#include "WShader.h"

namespace W
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();


		void SetupState();
		virtual void SetBuffer();
		virtual void SetShader(std::string _strFunName);
		virtual void ConstantBuffer();

		math::Vector3 GetPos() { return m_vPos; }
		void SetPos(math::Vector3 _vPos) { m_vPos = _vPos; }

		float GetColor() { return m_fColor; }

		graphics::ConstantBuffer* GetConstBuffer() { return m_pConstantBuffer; }
		Mesh* GetMesh() { return m_pMesh; }
		Shader* GetShader() { return m_pShader; }

	private:
		eState m_eState;
		//
		math::Vector3 m_vPos;
		float m_fColor;
		graphics::ConstantBuffer* m_pConstantBuffer;
		Mesh* m_pMesh;
		Shader* m_pShader;

	};
}



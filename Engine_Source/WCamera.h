#pragma once
#include "WComponent.h"
#include "WGraphics.h"

namespace W
{
	class Camera : public Component
	{
	public:
		enum class eProjectionType
		{
			Perpectivem,
			OrthoGraphic,
			None,
		};

		Camera();
		virtual ~Camera();

		static Matrix GetViewMatrix() { return m_mView; }
		static Matrix GetProjectionMatrix() { return m_mProjection; }
	
		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType _eType);

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		//월드행렬은 오브젝트마다 다르지만
		//뷰 공간과 투영행렬은 모든 오븍제트들에게 똑같이
		//적용되기 때문에 static으로
		static Matrix m_mView;
		static Matrix m_mProjection;

		eProjectionType m_eType;
		float m_fAspectRatio;//종횡비
		float m_fNear;
		float m_fFal;
		float m_fSize;

	};
}



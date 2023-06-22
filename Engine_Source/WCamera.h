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
		//��������� ������Ʈ���� �ٸ�����
		//�� ������ ��������� ��� ������Ʈ�鿡�� �Ȱ���
		//����Ǳ� ������ static����
		static Matrix m_mView;
		static Matrix m_mProjection;

		eProjectionType m_eType;
		float m_fAspectRatio;//��Ⱦ��
		float m_fNear;
		float m_fFal;
		float m_fSize;

	};
}



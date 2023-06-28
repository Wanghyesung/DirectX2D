#pragma once
#include "WComponent.h"
#include "WGraphics.h"


//UIī�޶�(�̵�X), ĳ���� ī�޶� ����
//renderer render�Լ����� ī�޶� ����ȣ��
//cutoutmode ����, �������������͵��� ����
//Scene, camerascript engine������ �̵�
//opaque ���� cutout �κ� ������ transparnt������ ������ ���� ������ ���� ������� �������
//��������������� ������ ����Ÿ�� ������� ����
//���̾�� ī�޶� ���� ���밡�� 
//SceneMgr -> camera(render)�� ����������� ������

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
		void RegisterCameraInRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		
		void TrunLayerMask(eLayerType _eType, bool _bEnable = true);
		void EnableLayerMask() { m_bitLayerMask.set(); }
		void DisableLayerMasks() { m_bitLayerMask.reset(); }
		
		void SortGameObjects();
		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();

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
	

		//�׸��� ������� ������Ʈ ����
		std::bitset<(UINT)eLayerType::End> m_bitLayerMask;
		std::vector<GameObject*> m_vecOpaqueGameObjects;
		std::vector<GameObject*> m_vecCutOutGameObjects;
		std::vector<GameObject*> m_vecTransparentGameObjects;
 	};
}



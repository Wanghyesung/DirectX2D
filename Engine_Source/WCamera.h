#pragma once
#include "WComponent.h"
#include "WGraphics.h"


//UI카메라(이동X), 캐릭터 카메라 따로
//renderer render함수에서 카메라 렌더호출
//cutoutmode 투명, 투명하지않은것들을 같이
//Scene, camerascript engine쪽으로 이동
//opaque 투명 cutout 부분 부투명 transparnt불투명 순으로 렌더 지금은 먼저 만들어진 순서대로
//렌더렁모드순서대로 정렬후 렌더타입 순서대로 렌더
//레이어마다 카메라를 따로 적용가능 
//SceneMgr -> camera(render)로 렌더순서대로 렌더링

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
	

		//그리는 순서대로 오브젝트 정렬
		std::bitset<(UINT)eLayerType::End> m_bitLayerMask;
		std::vector<GameObject*> m_vecOpaqueGameObjects;
		std::vector<GameObject*> m_vecCutOutGameObjects;
		std::vector<GameObject*> m_vecTransparentGameObjects;
 	};
}



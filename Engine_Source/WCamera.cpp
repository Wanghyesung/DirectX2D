#include "WCamera.h"
#include "WTransform.h"
#include "WGameObject.h"
#include "WApplication.h"

//씬 쪼개기

//메테리얼 바뀔때마다 해당 텍스쳐(shader와 바인딩된) 초기화 
//렌더러에서 메테리얼, 메쉬 그리고 clear

//orthographic 2차원 크기 똑같이
//perpective 뒤로 갈수록 작아지게
//near 절두체 앞(앞부분 짤라서 사용가능)
//far 절두체 뒤(시야)
//카메라는 이동, 회전행렬만
//오브젝트는 카메라의 이동반대방향으로 -pos
//카메라의 기저벡터를 활용해서 회전(오일러각X)
//createlookat함수도 가능 하지만 전자에 비해서 느림
//월드에서는 srt순으로 바꾸어야하지만 view에에서는 tr순서상관이없음 월드행렬은 회전부분행렬이 겹침
//투영행렬전에 종횡비세팅해야함 가로/ 세로
//LH왼손좌표계 앞으로갈수록 -
//perpective는 fov 시야각(라디안) 추가
//만든행렬을 상수버퍼로 shade로
//카메라 이동시 물체 반대편으로

extern W::Application application;

namespace W
{
	Matrix Camera::m_mView = Matrix::Identity;
	Matrix Camera::m_mProjection = Matrix::Identity;

	Camera::Camera():
		Component(eComponentType::Camera),
		m_eType(eProjectionType::OrthoGraphic),
		m_fAspectRatio(1.f),
		m_fNear(1.f),
		m_fFal(1000.f),
		m_fSize(10.f)
	{
	}
	Camera::~Camera()
	{
	}
	
	void Camera::Update()
	{
	}
	void Camera::LateUpdate()
	{
		//lateupdate마다 내 카메라의 뷰행렬, 투영행렬 구하기
		CreateViewMatrix();
		CreateProjectionMatrix(m_eType);
	}
	void Camera::Render()
	{
	}

	bool Camera::CreateViewMatrix()
	{
		Transform* pTr = GetOwner()->GetComponent<Transform>();
		Vector3 vPos = pTr->GetPosition();

		m_mView = Matrix::Identity;
		m_mView *= Matrix::CreateTranslation(-vPos);//카메라의 반대로 물체가 이동
		
		Vector3 up = pTr->Up();
		Vector3 right = pTr->Right();
		Vector3 foward = pTr->Foward();

		//.을 활용하여 행렬 데이터에 접근
		//카메라의 기저벡터를 활용해서 회전(오일러각X)
		//createlookat함수도 가능 하지만 전자에 비해서 느림
		Matrix mViewRotate;
		mViewRotate._11 = right.x;	mViewRotate._12 = up.x;	mViewRotate._13 = foward.x;
		mViewRotate._21 = right.y;	mViewRotate._22 = up.y;	mViewRotate._23 = foward.y;
		mViewRotate._31 = right.z;	mViewRotate._32 = up.z;	mViewRotate._33 = foward.z;
		m_mView *= mViewRotate;

		return true;
	}
	bool Camera::CreateProjectionMatrix(eProjectionType _eType)
	{
		RECT tRect = {};
		GetClientRect(application.GetHwnd(), &tRect);
		float fWidth = tRect.right - tRect.left; //1400
		float fHeight = tRect.bottom - tRect.top; //750
		m_fAspectRatio = fWidth / fHeight; //가로 / 세로

		if (_eType == eProjectionType::OrthoGraphic)
		{
			//orthorgraphic비율
			float fOrthorGraphicRatio = m_fSize / 1000.f;
			fWidth *= fOrthorGraphicRatio;
			fHeight *= fOrthorGraphicRatio;

			//왼손좌표계 투영행렬
			m_mProjection = Matrix::CreateOrthographicLH(fWidth, fHeight, m_fNear, m_fFal);
		}
		else
		{
			m_mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.f, m_fAspectRatio, m_fNear, m_fFal);
		}


		return true;
	}
	void Camera::Initialize()
	{
	}

}

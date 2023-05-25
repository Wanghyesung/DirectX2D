#include "WTime.h"
#include "WApplication.h"

extern W::Application application;

namespace W
{
	double Time::m_dDeltaTime = 0.l;
	double Time::m_dSecond = 0.f;
	LARGE_INTEGER Time::m_lCpuFrequency = {};
	LARGE_INTEGER Time::m_lPrevFrequency = {};
	LARGE_INTEGER Time::m_lCurFrequency = {};

	void Time::Initiailize()
	{
		// CPU 고유 진동수 가져오기
		QueryPerformanceFrequency(&m_lCpuFrequency);

		// 프로그램이 처음 시작할때 진동수
		QueryPerformanceCounter(&m_lPrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&m_lCurFrequency);

		double differnceFrequency = m_lCurFrequency.QuadPart - m_lPrevFrequency.QuadPart;

		m_dDeltaTime = differnceFrequency / m_lCpuFrequency.QuadPart;

		m_lPrevFrequency.QuadPart = m_lCurFrequency.QuadPart;
	}

	void Time::Render()
	{
		m_dSecond += m_dDeltaTime;

		if (m_dSecond > 1.0f)
		{
			HWND hWnd = application.GetHwnd();

			wchar_t szFloat[50] = {};
			float FPS = 1.0f / (float)m_dDeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d", (UINT)FPS);
			//int iLen = wcsnlen_s(szFloat, 50);
			SetWindowText(hWnd, szFloat);

			//TextOut(hdc, 0, 0, szFloat, 20);
			m_dSecond = 0.0f;
		}
	}
}

#include "WApplication.h"

#include "WTime.h"
#include "WInput.h"
#include "WRenderer.h"

namespace W
{
	//0,0의 해상도도 있음
	Application::Application()
		:graphicDevice(nullptr),
		m_hHwnd(NULL),
		m_iWidth(-1),
		m_iHeight(-1)
	{

	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Initialize()
	{
		Time::Initiailize();
		Input::Initialize();

		renderer::Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
	}

	void Application::LateUpdate()
	{
	}

	void Application::Render()
	{
		Time::Render();

		graphicDevice->Draw();
	}

	void Application::SetWindow(HWND _hHwnd, UINT _iWidth, UINT _iHeight)
	{
		//한번만 호출되게
		if (graphicDevice == nullptr)
		{
			m_hHwnd = _hHwnd;
			m_iWidth = _iWidth;
			m_iHeight = _iHeight;
		
			graphicDevice = std::make_unique<W::graphics::GraphicDevice_Dx11>();
			W::graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)_iWidth , (LONG)_iHeight };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(m_hHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(m_hHwnd, true);
		UpdateWindow(m_hHwnd);
	}
}
#include "WApplication.h"

#include "WTime.h"
#include "WInput.h"
#include "WRenderer.h"
#include "WSceneManger.h"
#include "UIManger.h"
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
		SceneManger::Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();

		SceneManger::Update();
		UIManger::Update();
	}

	void Application::LateUpdate()
	{
		SceneManger::LateUpdate();
	}

	void Application::Render()
	{
		Time::Render();

		//graphicDevice->Draw();
		graphicDevice->ClearTarget();
		graphicDevice->UpdateViewPort();

		//SceneManger::Render();
		renderer::Render();
		graphicDevice->Present();
	}

	void Application::Destroy()
	{
		SceneManger::Destroy();
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
			//제일먼저 호출될때 graphicDevice할당
			W::graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)_iWidth , (LONG)_iHeight };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(m_hHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(m_hHwnd, true);
		UpdateWindow(m_hHwnd);
	}
}
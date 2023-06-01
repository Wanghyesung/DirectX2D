// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

//github msdl 참고 딥앱?
//editer 프로잭트
//공유 항목 프로젝트는 어느 플랫폼이여도 사용가능하기 때문에
//빌드 중속성 굳이 하나하나 빌드가 아니라 하나를 돌리면 같이 빌드되게
//engine -> editer
//기존 클래스 복사 -> 기존항복에 추가 
//c++ 버전 20으로

#include "framework.h"
#include "Client.h"
#include "WApplication.h"

//정적라이브러리 추가 1. 소스코드  2. 비주얼스튜디오 옵션
//정적라이브러리에 들어가기 위한 헤더파일 include 

//참조 -> 엔진소수 추가


//정적라이브러리의 commoninclude헤더파일 include해야 알수있음
//#include "..\Client_Source\CommonInclude.h"

////하나하나 전부 해줄 수 없기 때문에
//#include "CommonInclude.h"
//
////디버그일떄 Debug파일에 정적라이브러리를 참조하고 Release일때는 Release파일에 정적라이브럴리 참조
//#ifdef _DEBUG
//#pragma comment ("..\\x64\\Debug\\Client_Source.lib");
//
//#else
//#pragma comment ("..\\x64\\Release\\Client_Source.lib");
//
//#endif

//vertex셰이더에 전달(이동)
//키보드에서 받은(cpu)값을 vertexshader(GPU)로 변수로 입력 gpu에서 처리
//cpu와 gpu에서 데이터 교환할 수 있는 버퍼가 필요함(상수 버퍼) 작은 수 구조체버퍼(상수버퍼들)
//사용량이 많으면 cpu에서 연산하기 때문에 효율이 낮다
//엔진에 따라 다르긴하지만 대부분의 단순값들은 cpu(하복) gpu(물리처리는 피직스?가 대표적)
//게임 개발에 따라 gpu를 어떻게 쓸지
//정점퍼버와(vertex 데이터) 다르게 인덕스 버퍼를 활용하여 그리는순서를 정함(정수 배열)
//서브데이터를 넣을떄 크기만이 아니라, uint2(데이터들의 크기정보) 넣어줌
//정점버퍼의경우는 cpu의 계산에 의한 데이터를 주기 때문에 cpu로 설정해줘야함 (기본값이 아니라)
//상수버퍼 패딩 hlsl은 16바이트 경계를 넘지않아야한다 16바이트만 (vector4만 되는이유)
//4개짜리(rgba, xyzw)와 같이 같은 차원의 수만 곱할 수 있기 때문에 gpu의 경우에는 주로 행렬을 사용하기 떄문
//상수버퍼gpu로 전달 -> 픽셀셰이더로 전달
//cpu에서 만든 서브리소스와 gpu의 서브리소스를 연결 지역변수로만든 서브리소스는 연결해제도 해주어야함
//상수버퍼를 셰이더로 보낼때 어떤 셰이더로 보낼지 무슨데이터인지 , 버퍼주소 
//cvuffer 자료형(상수버퍼) register로 슬롯 구분 상수버퍼크기와 정점셰이더에서 받는 데이터의 크기가 같아야함
//cpu에서 받은 값을 gpu에 전달 후 셰이더로 전달하는 바인드과정을 매 프레임 반복
//그릴때 정점버퍼셋팅했던것처럼 인덱스버퍼도 셋팅
//키보드 좌우상하 삼각형 이동 


W::Application application;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 여기서 게임 로직이 돌아가야한다.
            application.Run();
        }
    }

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 1280, 720, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    application.SetWindow(hWnd, 1400, 750);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    application.Initialize();

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

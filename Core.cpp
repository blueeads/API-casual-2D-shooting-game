#include "Core.h"
#include "SceneManager.h"
#include "Timer.h"
#include "PathManager.h"
#include "ResourcesManager.h"
#include "Texture.h"
#include "Camera.h"
#include "Input.h"
#include "CollisionManager.h"
#include "Mouse.h"

CCore* CCore::m_pInst = NULL;
bool CCore::m_bLoop = true;

DEVMODE dmSaved; // ���� �ػ󵵸� ����.. �ֳ� ���� ������ ������� ������ �ϴϱ�
DEVMODE dmSelected; // ���ϴ� �ػ󵵸� �����ϴ� ����
					// ���� ������ ����


CCore::CCore()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmSaved);
	//_CrtSetBreakAlloc(214);

#ifdef _DEBUG
	//�ܼ�â�� ���������ִ� �Լ��̴�.
	AllocConsole();
#endif
}


CCore::~CCore()
{
	DESTROY_SINGLE(CSceneManager);
	DESTROY_SINGLE(CCollisionManager);
	DESTROY_SINGLE(CInput);
	DESTROY_SINGLE(CCamera);
	DESTROY_SINGLE(CResourcesManager);
	DESTROY_SINGLE(CPathManager);
	DESTROY_SINGLE(CTimer);

	ChangeDisplaySettings(&dmSaved, CDS_RESET);

	ReleaseDC(m_hWnd, m_hDC);

#ifdef _DEBUG
	FreeConsole();
#endif
}

bool CCore::Init(HINSTANCE hInst)
{
	this->m_hInst = hInst;

	MyRegisterClass();

	m_tRS.iW = GetSystemMetrics(SM_CXSCREEN);
	m_tRS.iH = GetSystemMetrics(SM_CYSCREEN);

	Create();

	//ȭ�� DC�� ������ش�.
	m_hDC = GetDC(m_hWnd);

	//Ÿ�̸� �ʱ�ȭ
	if (!GET_SINGLE(CTimer)->Init(m_hWnd))
		return false;

	//��ΰ����� �ʱ�ȭ
	if (!GET_SINGLE(CPathManager)->Init())
		return false;

	// ���ҽ� ������ �ʱ�ȭ
	if (!GET_SINGLE(CResourcesManager)->Init(hInst, m_hDC))
		return false;

	//�Է°����� �ʱ�ȭ
	if (!GET_SINGLE(CInput)->Init(m_hWnd))
		return false;

	//ī�޶� ������ �ʱ�ȭ
	if (!GET_SINGLE(CCamera)->Init(POSITION(0.f, 0.f),
		m_tRS, RESOLUTION(1500, 1200)))
		return false;

	//�������� �ʱ�ȭ
	if (!GET_SINGLE(CSceneManager)->Init())
		return false;

	return true;
}

int CCore::Run()
{
	MSG msg;

	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Logic();
		}
	}
	return (int)msg.wParam;
}

void CCore::Logic()
{
	// Ÿ�̸� ����
	GET_SINGLE(CTimer)->Update();

	float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();

	Input(fDeltaTime);

	if (Update(fDeltaTime) == SC_CHANGE)
		return;

	if (LateUpdate(fDeltaTime) == SC_CHANGE)
		return;

	Collision(fDeltaTime);
	Render(fDeltaTime);
}

void CCore::Input(float fDeltaTime)
{
	GET_SINGLE(CInput)->Update(fDeltaTime);

	GET_SINGLE(CSceneManager)->Input(fDeltaTime);
	GET_SINGLE(CCamera)->Input(fDeltaTime);
}

int CCore::Update(float fDeltaTime)
{
	SCENE_CHANGE sc;
	sc = GET_SINGLE(CSceneManager)->Update(fDeltaTime);
	GET_SINGLE(CCamera)->Update(fDeltaTime);
	return 0;
}

int CCore::LateUpdate(float fDeltaTime)
{
	SCENE_CHANGE sc;
	sc = GET_SINGLE(CSceneManager)->LateUpdate(fDeltaTime);
	return 0;
}

void CCore::Collision(float fDeltaTime)
{
	GET_SINGLE(CSceneManager)->Collision(fDeltaTime);

	GET_SINGLE(CCollisionManager)->Collision(fDeltaTime);
}

void CCore::Render(float fDeltaTime)
{
	//������۸�
	CTexture* pBackBuffer = GET_SINGLE(CResourcesManager)->GetBackBuffer();

	GET_SINGLE(CSceneManager)->Render(pBackBuffer->GetDC(), fDeltaTime);

	//�������� ���콺�׸�
	CMouse* pMouse = GET_SINGLE(CInput)->GetMouse();

	pMouse->Render(pBackBuffer->GetDC(), fDeltaTime);

	BitBlt(m_hDC, 0, 0, m_tRS.iW, m_tRS.iH, pBackBuffer->GetDC(),
		0, 0, SRCCOPY);

	SAFE_RELEASE(pBackBuffer)
}

ATOM CCore::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CCore::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_API);
	wcex.lpszClassName = L"AR13API";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
}

BOOL CCore::Create()
{
	m_hWnd = CreateWindow(L"AR13API", L"AR13API", WS_POPUP,
		0, 0, m_tRS.iW, m_tRS.iH, NULL, NULL, m_hInst, NULL);

	if (!m_hWnd)
	{
		return false;
	}

	RECT rc = { 0,0,m_tRS.iW,m_tRS.iH };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left,
		rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	// ���� �ʱ�ȭ
	memset(&dmSelected, 0, sizeof(dmSelected));
	dmSelected.dmSize = sizeof(dmSelected);
	dmSelected.dmPelsWidth = 1280; // 800
	dmSelected.dmPelsHeight = 720; // 600
	dmSelected.dmBitsPerPel = 32;
	dmSelected.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	if (ChangeDisplaySettings(&dmSelected, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		MessageBox(NULL, L"Program Will Now Close.", L"ERROR", MB_OK | MB_ICONSTOP);
	}

	return true;
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

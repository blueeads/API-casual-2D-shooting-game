#include "Input.h"
#include "Mouse.h"
#include "Animation.h"
#include "Layer.h"
#include "CollisionManager.h"

CInput* CInput::m_pInst = NULL;

CInput::CInput()	:
	m_pCreateKey(NULL),
	m_pMouse(NULL)
{
}


CInput::~CInput()
{
	CObj::EraseObj(m_pMouse);
	SAFE_RELEASE(m_pMouse);
	Safe_Delete_Map(m_mapKey);
}

POSITION CInput::GetMouseClientPos() const
{
	return m_pMouse->GetPos();
}

POSITION CInput::GetMouseWorldPos() const
{
	return m_pMouse->GetWorldPos();
}

POSITION CInput::GetMouseMove() const
{
	return m_pMouse->GetMove();
}

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	AddKey('W', "MoveUp");
	AddKey('S', "MoveDown");
	AddKey('A', "MoveLeft");
	AddKey('D', "MoveRight");
	AddKey("Fire", VK_SPACE);
	AddKey("Item", VK_CONTROL);

	AddKey(VK_UP, "MoveUp2");
	AddKey(VK_DOWN, "MoveDown2");
	AddKey(VK_LEFT, "MoveLeft2");
	AddKey(VK_RIGHT, "MoveRight2");
	AddKey('P', "Fire2");
	AddKey("Item2", 'O');

	AddKey(VK_LBUTTON, "MouseLButton");
	AddKey(VK_RBUTTON, "MouseRButton");
	AddKey(VK_ESCAPE, "SetUp");
	AddKey(VK_CONTROL, "MapEdit", 'M');

	AddKey(VK_SPACE, "Pass");

	//마우스 위치를 얻어오는 함수이다.
	GetCursorPos(&m_tMousePos);

	//마우스 생성
	m_pMouse = CObj::CreateObj<CMouse>("Mouse");

	m_pMouse->SetSize(32, 32);

	CAnimation* pAni = m_pMouse->CreateAnimation("PlayerAnimation");

	vector<wstring> vecFileName;

	for (int i = 1; i <= 2; ++i)
	{
	wchar_t strFileName[MAX_PATH] = {};
	wsprintf(strFileName, L"Mouse%d.bmp", i);
	vecFileName.push_back(strFileName);
	}
	
	m_pMouse->AddAnimationClip("MouseNormal", AT_FRAME, AO_LOOP, 0.3f, 2, 1,
	0, 0, 2, 1, 0.f, "MouseNormal", vecFileName);
	m_pMouse->SetAnimationClipColorKey("MouseNormal", 255, 255, 255);

	SAFE_RELEASE(pAni);

	return true;
}

void CInput::Update(float fDeltaTime)
{
	unordered_map<string, PKEYINFO>::iterator iter;
	unordered_map<string, PKEYINFO>::iterator iterEnd = m_mapKey.end();

	for (iter = m_mapKey.begin(); iter != iterEnd; ++iter)
	{
		int iPushCount = 0;
		for (size_t i = 0; i < iter->second->vecKey.size(); ++i)
		{
			if (GetAsyncKeyState(iter->second->vecKey[i]) & 0x8000)
				++iPushCount;
		}

		if (iPushCount == iter->second->vecKey.size())
		{
			if (!iter->second->bDown && !iter->second->bPress)
			{
				iter->second->bPress = true;
				iter->second->bDown = true;
			}

			else if (iter->second->bDown)
				iter->second->bDown = false;
		}

		else
		{
			if (iter->second->bDown || iter->second->bPress)
			{
				iter->second->bUp = true;
				iter->second->bPress = false;
				iter->second->bDown = false;
			}

			else if (iter->second->bUp)
				iter->second->bUp = false;
		}
	}

	m_pMouse->Update(fDeltaTime);
	m_pMouse->LateUpdate(fDeltaTime);

	GET_SINGLE(CCollisionManager)->AddObject(m_pMouse);
}

bool CInput::KeyDown(const string & strKey) const
{
	PKEYINFO pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bDown;
}

bool CInput::KeyPress(const string & strKey) const
{
	PKEYINFO pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bPress;
}

bool CInput::KeyUp(const string & strKey) const
{
	PKEYINFO pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bUp;
}

PKEYINFO CInput::FindKey(const string & strKey) const
{
	unordered_map<string, PKEYINFO>::const_iterator iter = m_mapKey.find(strKey);

	if (iter == m_mapKey.end())
		return NULL;

	return iter->second;
}

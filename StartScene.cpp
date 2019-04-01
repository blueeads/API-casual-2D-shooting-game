#include "StartScene.h"
#include "UIPanel.h"
#include "UIButton.h"
#include "Layer.h"
#include "Camera.h"
#include "ColliderRect.h"
#include "Core.h"
#include "SceneManager.h"
#include "InGameScene.h"
#include "MapEditScene.h"
#include "CreditScene.h"
#include "HowtoScene.h"
#include "Input.h"

CStartScene::CStartScene()
{
}


CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	//부모 Scene 클래스의 초기화 함수 호출
	if (!CScene::Init())
		return false;

	CLayer* pLayer = FindLayer("UI");


	CUIPanel* pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel",
		pLayer);

	pBackPanel->SetSize(GETRESOLUTION.iW, GETRESOLUTION.iH);
	pBackPanel->SetTexture("StartBack", L"Main.bmp");

	SAFE_RELEASE(pBackPanel);


	//스타트버튼
	CUIButton* pStartBtn = CObj::CreateObj<CUIButton>("StratButton",
		pLayer);

	pStartBtn->SetPos(900.f, 360.f);
	pStartBtn->SetSize(300.f, 100.f);
	pStartBtn->SetTexture("StartButton", L"START.bmp");
	pStartBtn->SetColorKey(255, 0, 255);

	CColliderRect* pRC = (CColliderRect*)pStartBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 300, 100);
	
	SAFE_RELEASE(pRC);

	pStartBtn->SetCallback(this, &CStartScene::StartButtonCallback);

	SAFE_RELEASE(pStartBtn);

	//하우투버튼
	CUIButton* pHowtoBtn = CObj::CreateObj<CUIButton>("HowtoButton",
		pLayer);

	pHowtoBtn->SetPos(900.f,480.f);
	pHowtoBtn->SetSize(300.f, 100.f);
	pHowtoBtn->SetTexture("HowtoButton", L"howto.bmp");
	pHowtoBtn->SetColorKey(255, 0, 255);

	pRC = (CColliderRect*)pHowtoBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 300, 100);

	SAFE_RELEASE(pRC);

	pHowtoBtn->SetCallback(this, &CStartScene::HowtoButtonCallback);

	SAFE_RELEASE(pHowtoBtn);

	//엔드버튼
	CUIButton* pEndBtn = CObj::CreateObj<CUIButton>("EndButton",
		pLayer);

	pEndBtn->SetPos(900.f, 600.f);
	pEndBtn->SetSize(300.f, 100.f);
	pEndBtn->SetTexture("EndButton", L"exit.bmp");
	pEndBtn->SetColorKey(255, 0, 255);

	pRC = (CColliderRect*)pEndBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 300, 100);

	SAFE_RELEASE(pRC);

	pEndBtn->SetCallback(this, &CStartScene::EndButtonCallback);

	SAFE_RELEASE(pEndBtn);

	//크레딧버튼
	CUIButton* pCreditBtn = CObj::CreateObj<CUIButton>("CreditButton",
		pLayer);

	pCreditBtn->SetPos(30.f, 30.f);
	pCreditBtn->SetSize(70.f, 70.f);
	pCreditBtn->SetTexture("CreditButton", L"CreditBtn.bmp");
	pCreditBtn->SetColorKey(255, 0, 255);

	pRC = (CColliderRect*)pCreditBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 70, 70);

	SAFE_RELEASE(pRC);

	pCreditBtn->SetCallback(this, &CStartScene::CreditButtonCallback);

	SAFE_RELEASE(pCreditBtn);

	return true;
}

void CStartScene::Input(float fDeltaTime)
{
	CScene::Input(fDeltaTime);

	if (KEYDOWN("MapEdit")) // 컨트롤 + 'M'
	{
		GET_SINGLE(CSceneManager)->CreateScene<CMapEditScene>(SC_NEXT);
	}
}

void CStartScene::StartButtonCallback(float fTime)
{
	GET_SINGLE(CSceneManager)->CreateScene<CInGameScene>(SC_NEXT);
}

void CStartScene::EndButtonCallback(float fTime)
{
	GET_SINGLE(CCore)->DestroyGame();
}

void CStartScene::CreditButtonCallback(float fTime)
{
	GET_SINGLE(CSceneManager)->CreateScene<CCreditScene>(SC_NEXT);
}

void CStartScene::EditButtonCallback(float fTime)
{
	GET_SINGLE(CSceneManager)->CreateScene<CMapEditScene>(SC_NEXT);
}

void CStartScene::HowtoButtonCallback(float fTime)
{
	GET_SINGLE(CSceneManager)->CreateScene<CHowtoScene>(SC_NEXT);
}
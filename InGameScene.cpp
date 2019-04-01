#include "InGameScene.h"
#include "ColliderPixel.h"
#include "ColliderRect.h"
#include "Stage.h"
#include "Layer.h"
#include "Camera.h"
#include "Minion.h"
#include "Bullet.h"
#include "ColliderRect.h"
#include "Core.h"
#include "SceneManager.h"
#include "StartScene.h"
#include "Input.h"
#include "ResourcesManager.h"
#include "Texture.h"
#include "resource.h"
#include "PathManager.h"
#include "Player.h"
#include "Player2.h"
#include "UIPanel.h"
#include "UIButton.h"
#include "UI.h"
#include "Heart.h"
#include "stack.h"
#include "Item.h"
#include "ColliderSphere.h"

CInGameScene::CInGameScene()
{
	StageNum = First;
	SU = Not;
}


CInGameScene::~CInGameScene()
{
}

bool CInGameScene::Init()
{
	//부모 Scene 클래스의 초기화 함수 호출
	if (!CScene::Init())
		return false;

	CLayer* pLayer = FindLayer("Default");

	//플레이어 2명
	CPlayer* pPlayer = CObj::CreateObj<CPlayer>("Player", pLayer);
	CPlayer2* pPlayer2 = CObj::CreateObj<CPlayer2>("Player2", pLayer);

	SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(pPlayer2);

	//CMinion* pMinion = CObj::CreateObj<CMinion>("Minion", pLayer);
	//SAFE_RELEASE(pMinion); //몬스터

	// 총알 프로토타입을 만들어준다.
	CBullet* pBullet = CScene::CreatePrototype<CBullet>("Bullet",
		m_eSceneType);

	pBullet->SetSize(40.f, 40.f);
	SAFE_RELEASE(pBullet);

	CItem* pItem = CScene::CreatePrototype<CItem>("Item",
		m_eSceneType);

	pItem->SetSize(60, 60);
	SAFE_RELEASE(pItem);

	CHeart* pHeart = CScene::CreatePrototype<CHeart>("Heart", m_eSceneType);

	pHeart->SetSize(50.f, 50.f);
	SAFE_RELEASE(pHeart);

	//////////////////////////////////////////
	CLayer* pStageLayer = FindLayer("Stage");
	
	CStage* m_pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);
	CColliderPixel* pPixelX = m_pStage->AddCollider<CColliderPixel>("NoMove");
	pPixelX->SetPixelInfo("FirstStage.bmp");
	SAFE_RELEASE(pPixelX);
	SAFE_RELEASE(m_pStage);

	//UI
	CLayer* pUi = FindLayer("UI");

	CUIPanel* m_pMap = CObj::CreateObj<CUIPanel>("MapStage", pStageLayer);

	m_pMap->SetSize(1280.f, 620.f);
	m_pMap->SetTexture("StageTile", L"FirstStage.bmp");
	m_pMap->SetPos(0.f, 0.f);
	m_pMap->SetColorKey(255,0,255);
	//타일맵
	SAFE_RELEASE(m_pMap);

	//하단바
	CUIPanel* pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pStageLayer);

	pBackPanel->SetSize(1280.f, 720.f);
	pBackPanel->SetTexture("LBar", L"Lower_Bar.bmp");
	pBackPanel->SetPos(0.f, 0.f);
	pBackPanel->SetColorKey(255, 0, 255);

	SAFE_RELEASE(pBackPanel);

	//환경설정 창
	CUIButton* pSetUpBtn = CObj::CreateObj<CUIButton>("SetButton", pUi);
	CColliderRect* pRC = (CColliderRect*)pSetUpBtn->GetCollider("ButtonBody");

	pSetUpBtn->SetPos(1200.f, 0.f);
	pSetUpBtn->SetSize(70.f, 70.f);
	pSetUpBtn->SetTexture("SetUp", L"Setup.bmp");
	pSetUpBtn->SetColorKey(255, 0, 255);

	pRC = (CColliderRect*)pSetUpBtn->GetCollider("ButtonBody");
	pRC->SetRect(0.f, 0.f, 70.f, 70.f);

	pSetUpBtn->SetCallback(this, &CInGameScene::SetUpButtonCallback);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pSetUpBtn);

	CUIPanel* FirstItemBox = CObj::CreateObj<CUIPanel>("FirstBox", pUi);

	FirstItemBox->SetPos(520.f, 630.f);
	FirstItemBox->SetSize(80.f, 80.f);
	FirstItemBox->SetTexture("FirstBox", L"ItemBox.bmp");
	FirstItemBox->SetColorKey(255, 0, 255);

	SAFE_RELEASE(FirstItemBox);


	CUIPanel* SecondItemBox = CObj::CreateObj<CUIPanel>("SecondBox", pUi);

	SecondItemBox->SetPos(680.f, 630.f);
	SecondItemBox->SetSize(80, 80);
	SecondItemBox->SetTexture("SecondBox", L"ItemBox.bmp");
	SecondItemBox->SetColorKey(255, 0, 255);

	SAFE_RELEASE(SecondItemBox);

	//CHeart* Heart = CObj::CreateObj<CHeart>("Heart", pUi);
	//
	//Heart->SetColorKey(255, 0, 255);
	//SAFE_RELEASE(Heart);

	return true;
}

void CInGameScene::SetUpButtonCallback(float fTime)
{
	CLayer* pUi = FindLayer("UI");
	//Pause창
	CUIPanel* pESC = CObj::CreateObj<CUIPanel>("EscPanel",
		pUi);
	//ReSumeBtn
	CUIButton* pReSumeBtn = CObj::CreateObj<CUIButton>("ReSumeButton",
		pUi);
	//ExitBtn
	CUIButton* pExitBtn = CObj::CreateObj<CUIButton>("ExitButton",
		pUi);

	pESC->SetSize(500.f, 500.f);
	pESC->SetTexture("ESC", L"ESC_Pen.bmp");
	pESC->SetPos(400.f, 50.f);
	pESC->SetColorKey(255, 0, 255);
	pESC->SetDieUI(1);

	SAFE_RELEASE(pESC);

	pReSumeBtn->SetSize(380.f, 140.f);
	pReSumeBtn->SetTexture("ReSumeButton", L"resume.bmp");
	pReSumeBtn->SetPos(460.f, 200.f);
	pReSumeBtn->SetColorKey(255, 0, 255);
	pReSumeBtn->SetDieButton(1);

	CColliderRect* pRC = (CColliderRect*)pReSumeBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 380, 140);

	SAFE_RELEASE(pRC);

	pReSumeBtn->SetCallback(this, &CInGameScene::ReSumeButtonCallback);

	SAFE_RELEASE(pReSumeBtn);

	pExitBtn->SetSize(380.f, 140.f);
	pExitBtn->SetTexture("ExitButton", L"InGameexit.bmp");
	pExitBtn->SetPos(460.f, 350.f);
	pExitBtn->SetColorKey(255, 0, 255);
	pExitBtn->SetDieButton(1);

	pRC = (CColliderRect*)pExitBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 380, 140);

	SAFE_RELEASE(pRC);

	pExitBtn->SetCallback(this, &CInGameScene::ExitButtonCallback);

	SAFE_RELEASE(pExitBtn);

}

void CInGameScene::ReSumeButtonCallback(float fTime)
{
	GET_SINGLE(CSceneManager)->CreateScene<CStartScene>(SC_NEXT);
}

void CInGameScene::ExitButtonCallback(float fTime)
{
	GET_SINGLE(CCore)->DestroyGame();
}

void CInGameScene::ReStartCallBack(float fTime)	
{
	GET_SINGLE(CSceneManager)->CreateScene<CInGameScene>(SC_NEXT);
}

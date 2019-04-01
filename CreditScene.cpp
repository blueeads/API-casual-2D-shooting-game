#include "CreditScene.h"
#include "UIPanel.h"
#include "UIButton.h"
#include "Scenemanager.h"
#include "ColliderRect.h"
#include "StartScene.h"
#include "Layer.h"

CCreditScene::CCreditScene()
{
}


CCreditScene::~CCreditScene()
{
}

bool CCreditScene::Init()
{
	//부모 Scene 클래스의 초기화 함수 호출
	if (!CScene::Init())
		return false;

	CLayer* pUi = FindLayer("UI");

	//뒤에 배경
	/*CUIPanel* pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pUi);

	pBackPanel->SetSize(1280.f, 720.f);
	pBackPanel->SetTexture("LBar", L"Lower_Bar.bmp");
	pBackPanel->SetPos(0.f, 0.f);
	pBackPanel->SetColorKey(255, 0, 255);

	SAFE_RELEASE(pBackPanel);*/

	//하우투 이미지
	CUIPanel* pCredit = CObj::CreateObj<CUIPanel>("Credit", pUi);

	pCredit->SetSize(1280.f, 720.f);
	pCredit->SetTexture("Credit", L"credit.bmp");
	pCredit->SetPos(0.f, 0.f);
	pCredit->SetColorKey(255, 0, 255);

	SAFE_RELEASE(pCredit);

	//돌아가기 버튼
	CUIButton* pMainBtn = CObj::CreateObj<CUIButton>("MainButton", pUi);

	pMainBtn->SetPos(70.f, 55.f);
	pMainBtn->SetSize(70.f, 70.f);
	pMainBtn->SetTexture("MainButton", L"back.bmp");
	pMainBtn->SetColorKey(255, 0, 255);

	CColliderRect* pRC = (CColliderRect*)pMainBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 70.f, 70.f);

	SAFE_RELEASE(pRC);

	pMainBtn->SetCallback(this, &CCreditScene::MainButtonCallback);

	SAFE_RELEASE(pMainBtn);
	return true;
}

void CCreditScene::MainButtonCallback(float fTime)
{
	GET_SINGLE(CSceneManager)->CreateScene<CStartScene>(SC_NEXT);
}

#include "HowtoScene3.h"
#include "HowtoScene4.h"
#include "UIPanel.h"
#include "UIButton.h"
#include "Scenemanager.h"
#include "ColliderRect.h"
#include "StartScene.h"
#include "Layer.h"
#include "InGameScene.h"
#include "Input.h"

CHowtoScene3::CHowtoScene3()
{
}


CHowtoScene3::~CHowtoScene3()
{
}

bool CHowtoScene3::Init()
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
	CUIPanel* pHowto3 = CObj::CreateObj<CUIPanel>("Howto3", pUi);
	pHowto3->SetSize(1280.f, 720.f);
	pHowto3->SetTexture("Howto3", L"howto3.bmp");
	pHowto3->SetPos(0.f, 0.f);
	pHowto3->SetColorKey(255, 0, 255);

	SAFE_RELEASE(pHowto3); 
	return true;
}
void CHowtoScene3::Input(float fTime)
{
	if (KEYDOWN("Pass"))
	{
	//GET_SINGLE(CSceneManager)->CreateScene<CHowtoScene4>(SC_NEXT);
	GET_SINGLE(CSceneManager)->CreateScene<CInGameScene>(SC_NEXT);
	}
}
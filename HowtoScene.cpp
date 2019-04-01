#include "HowtoScene.h"
#include "HowtoScene2.h"
#include "UIPanel.h"
#include "UIButton.h"
#include "Scenemanager.h"
#include "ColliderRect.h"
#include "StartScene.h"
#include "Layer.h"
#include "InGameScene.h"
#include "Input.h"

CHowtoScene::CHowtoScene()
{
}


CHowtoScene::~CHowtoScene()
{
}

bool CHowtoScene::Init()
{
	//�θ� Scene Ŭ������ �ʱ�ȭ �Լ� ȣ��
	if (!CScene::Init())
		return false;

	CLayer* pUi = FindLayer("UI");

	//�ڿ� ���
	/*CUIPanel* pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pUi);

	pBackPanel->SetSize(1280.f, 720.f);
	pBackPanel->SetTexture("LBar", L"Lower_Bar.bmp");
	pBackPanel->SetPos(0.f, 0.f);
	pBackPanel->SetColorKey(255, 0, 255);

	SAFE_RELEASE(pBackPanel);*/

	//�Ͽ��� �̹���
	CUIPanel* pHowto1 = CObj::CreateObj<CUIPanel>("Howto", pUi);
	pHowto1->SetSize(1280.f, 720.f);
	pHowto1->SetTexture("Howto", L"howto1.bmp");
	pHowto1->SetPos(0.f, 0.f);
	pHowto1->SetColorKey(255, 0, 255);

	SAFE_RELEASE(pHowto1);


	return true;
}
void CHowtoScene::Input(float fTime)
{
	if (KEYDOWN("Pass"))
	{
		GET_SINGLE(CSceneManager)->CreateScene<CHowtoScene2>(SC_NEXT);
	}
}



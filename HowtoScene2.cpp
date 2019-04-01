#include "HowtoScene2.h"
#include "HowtoScene3.h"
#include "UIPanel.h"
#include "UIButton.h"
#include "Scenemanager.h"
#include "ColliderRect.h"
#include "StartScene.h"
#include "Layer.h"
#include "InGameScene.h"
#include "Input.h"

CHowtoScene2::CHowtoScene2()
{
}


CHowtoScene2::~CHowtoScene2()
{
}

bool CHowtoScene2::Init()
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
	CUIPanel* pHowto2 = CObj::CreateObj<CUIPanel>("Howto2", pUi);
	pHowto2->SetSize(1280.f, 720.f);
	pHowto2->SetTexture("Howto2", L"howto2.bmp");
	pHowto2->SetPos(0.f, 0.f);
	pHowto2->SetColorKey(255, 0, 255);

	SAFE_RELEASE(pHowto2);

	return true;
}

void CHowtoScene2::Input(float fTime)
{
	if (KEYDOWN("Pass"))
	{
		GET_SINGLE(CSceneManager)->CreateScene<CHowtoScene3>(SC_NEXT);
	}
}

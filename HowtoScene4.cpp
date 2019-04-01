#include "HowtoScene4.h"
#include "UIPanel.h"
#include "UIButton.h"
#include "Scenemanager.h"
#include "ColliderRect.h"
#include "StartScene.h"
#include "Layer.h"
#include "InGameScene.h"
#include "Input.h"

CHowtoScene4::CHowtoScene4()
{
}


CHowtoScene4::~CHowtoScene4()
{
}

bool CHowtoScene4::Init()
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
	CUIPanel* pHowto4 = CObj::CreateObj<CUIPanel>("Howto4", pUi);
	pHowto4->SetSize(1280.f, 720.f);
	pHowto4->SetTexture("Howto4", L"howto4.bmp");
	pHowto4->SetPos(0.f, 0.f);
	pHowto4->SetColorKey(255, 0, 255);

	SAFE_RELEASE(pHowto4); 

	return true;
}
void CHowtoScene4::Input(float fTime)
{
	if (KEYDOWN("Pass"))
	{
	//GET_SINGLE(CSceneManager)->CreateScene<CHowtoScene4>(SC_NEXT);
	GET_SINGLE(CSceneManager)->CreateScene<CInGameScene>(SC_NEXT);
	}
}
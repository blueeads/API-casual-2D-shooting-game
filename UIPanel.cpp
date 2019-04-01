#include "UIPanel.h"
#include "Input.h"

CUIPanel::CUIPanel()
{
}

CUIPanel::CUIPanel(const CUIPanel & ui)	:
	CUI(ui)
{
}


CUIPanel::~CUIPanel()
{
}

bool CUIPanel::Init()
{
	return true;
}

void CUIPanel::Input(float fDeltaTime)
{
	CUI::Input(fDeltaTime);

	if (KEYDOWN("SetUp") && DieUI == 1)
		Die();
}

int CUIPanel::Update(float fDeltaTime)
{
	CUI::Update(fDeltaTime);
	return 0;
}

int CUIPanel::LateUpdate(float fDeltaTime)
{
	CUI::LateUpdate(fDeltaTime);
	return 0;
}

void CUIPanel::Collision(float fDeltaTime)
{
	CUI::Collision(fDeltaTime);
}

void CUIPanel::Render(HDC hDC, float fDeltaTime)
{
	CUI::Render(hDC, fDeltaTime);
}

CUIPanel * CUIPanel::Clone()
{
	return new CUIPanel(*this);
}

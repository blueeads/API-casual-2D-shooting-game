#include "Heart.h"
#include "Texture.h"
#include "Player.h"
#include "MoveObj.h"
#include "Obj.h"

CHeart::CHeart()
{
	HP = 5;
}
CHeart::CHeart(const CHeart & Heart) :
	CMoveObj(Heart)
{

}
CHeart::~CHeart()
{

}

bool CHeart::Init()
{
	SetSpeed(0.f);
	//랜덤박스 리소스
	SetPivot(0.5f, 0.5f);
	SetSize(50.f, 50.f);
	SetTexture("Heart", L"Life.bmp");

	m_pTexture->SetColorKey(RGB(255, 0, 255));

	return true;
}

void CHeart::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);

	Life(hDC);

}

int CHeart::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	return 0;
}

int CHeart::LateUpdate(float fDelaTime)
{
	CMoveObj::LateUpdate(fDelaTime);

	return 0;
}

CHeart * CHeart::Clone()
{
	return new CHeart(*this);
}

void CHeart::Life(HDC hDC)
{

	POSITION pPos;
	pPos.x = 300;
	pPos.y = 400;
	
	for (int i = 0; i < HP; i++)
	{
		BitBlt(hDC, pPos.x, pPos.y, 50, 50, m_pTexture->GetDC(), 0, 0, SRCCOPY);
		pPos.x += 70;
	}
}

void CHeart::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (GetTag() == "PlayerBullet" && pDest->GetTag() == "PlayerBody")
	{
		HP -= 1;
	}

}


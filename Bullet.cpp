#include "Bullet.h"
#include "Texture.h"
#include "ColliderSphere.h"


CBullet::CBullet() :
	m_fDist(0.f),
	m_fLimitDist(1000.f)
{
}

CBullet::CBullet(const CBullet & bullet) :
	CMoveObj(bullet)
{
	m_fLimitDist = bullet.m_fLimitDist;
	m_fDist = bullet.m_fDist;
}


CBullet::~CBullet()
{
}

bool CBullet::Init()
{
	SetSpeed(800.f);
	SetPivot(0.5f, 0.5f);
	SetSize(40.f, 40.f);

	SetTexture("Bullet", L"Bullet.bmp");

	m_pTexture->SetColorKey(RGB(255, 0, 255));
	CColliderSphere* pSphere = AddCollider<CColliderSphere>("BulletBody");

	pSphere->SetSphere(POSITION(0.f, 0.f), 25.f);

	SAFE_RELEASE(pSphere);

	return true;
}

int CBullet::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	MoveAngle(fDeltaTime);

	m_fDist += GetSpeed() * fDeltaTime;

	if (m_fDist >= m_fLimitDist)
		Die();

	return 0;
}

int CBullet::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CBullet::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CBullet::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
}

CBullet * CBullet::Clone()
{
	return new CBullet(*this);
}

void CBullet::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (GetTag() == "PlayerBullet" && pDest->GetTag() == "PlayerBody")
	{
		Die();
	}
	else if (GetTag() == "PlayerBullet" && pDest->GetTag() == "PlayerBody2")
	{
		Die();
	}
}

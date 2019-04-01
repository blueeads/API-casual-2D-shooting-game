#include "Item.h"
#include "Texture.h"
#include "Input.h"
#include "ColliderSphere.h"
#include "StaticObj.h"
#include "Scene.h"

CItem::CItem() :
	m_fFireTime(0.f),
	m_fFireLimitTime(5.f)
{
}

CItem::CItem(const CItem & Item) :
	CMoveObj(Item)
{
	m_fFireTime = Item.m_fFireTime;
	m_fFireLimitTime = Item.m_fFireLimitTime;
}

CItem::~CItem()
{

}

bool CItem::Init()
{
	SetSpeed(0.f);
	//랜덤박스 리소스
	SetPivot(0.5f, 0.5f);
	SetSize(60, 60);

	SetTexture("Item",L"ItemHeart.bmp");

	m_pTexture->SetColorKey(RGB(255, 0, 255));
	CColliderSphere* pSphere = AddCollider<CColliderSphere>("BulletBody");

	pSphere->SetSphere(POSITION(0.f, 0.f), 25.f);

	SAFE_RELEASE(pSphere);

	return true;
}

void CItem::Input(float fTime)
{
	CMoveObj::Input(fTime);

	if (GetAsyncKeyState('1') & 0x8000)
	{

	}

}

int CItem::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	m_fFireTime += fDeltaTime;
	
	if (m_fFireTime >= m_fFireLimitTime)
	{
		m_fFireTime -= m_fFireLimitTime;
		ItemBox();
	}

	return 0;
}

int CItem::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CItem::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CItem::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);

	//Rectangle(hDC, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x,
	//m_tPos.y + m_tSize.y);
}

CItem * CItem::Clone()
{
	return new CItem(*this);
}

void CItem::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (GetTag() == "PlayerItem" && pDest->GetTag() == "PlayerBody")
	{
		Die();
	}
	else if (GetTag() == "PlayerItem" && pDest->GetTag() == "PlayerBody2")
	{
		Die();
	}
}

void CItem::ItemBox()
{
	CObj* pItem = CObj::CreateCloneObj("Item", "ItemBody",
		m_pScene->GetSceneType(), m_pLayer);

	pItem->AddCollisionFunction("ItemBody", CS_ENTER,
		(CItem*)pItem, &CItem::Hit);

	//오른쪽 가운데를 구한다.
	POSITION tPos;

	MoveX(tPos.x);
	MoveY(tPos.y);

	SAFE_RELEASE(pItem);
}
#pragma once
#include "MoveObj.h"

class CItem :
	public CMoveObj
{
private:
	friend class CObj;
	friend class CScene;

private:
	CItem();
	CItem(const CItem& Item);
	~CItem();

private:
	float m_fFireTime;
	float m_fFireLimitTime;
	ITEM_STATE ItemState;

public:
	virtual bool Init();
	void Input(float fTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CItem* Clone();

	void Hit(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);
	void ItemBox();
	void Slot();
};
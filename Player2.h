#pragma once
#include "MoveObj.h"
class CPlayer2 :
	public CMoveObj
{
private:
	friend class CObj;
	friend class CScene;

private:
	CPlayer2();
	CPlayer2(const CPlayer2& player);
	~CPlayer2();

private:
	int check;
	int m_iHP;
	bool m_bAttack;
	int m_iDir;
	float Speed = 200.f;
	int Damage = 1;
	float m_fFireTime;
	float m_fFireLimitTime;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CPlayer2* Clone();
	int GetHP();
public:
	void Hit(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);
	void HitStay(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);
	void Item(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);

private:
	void Fire();
	void ItemBox();
	void m_Heart(int i, int type);
};


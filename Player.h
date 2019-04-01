#pragma once
#include "MoveObj.h"

class CPlayer :
	public CMoveObj
{
private:
	friend class CObj;
	friend class CScene;
	friend class CHeart;

private:
	CPlayer();
	CPlayer(const CPlayer& player);
	~CPlayer();

private:
	int check;
	bool m_bAttack;
	int m_iDir;
	float Speed = 200.f;
	int Damage = 1;
	int SaveHP;
	int m_iHP;
	int m_Win;
	float m_fFireTime;
	float m_fFireLimitTime;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	int GetHP();
	virtual CPlayer* Clone();


public:
	void Hit(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);
	void HitStay(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);	

private:
	void Fire();
	void ItemBox();
	void m_Heart(int i, int type);
};

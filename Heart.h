#pragma once
#include "MoveObj.h"

class CHeart :
	public CMoveObj
{
private:
	CHeart();
	CHeart(const CHeart& Heart);
	~CHeart();

private:
	int HP;
	POSITION pPos;

private:
	friend class CObj; 
	friend class CScene;
	friend class CPlayer;

public:
	virtual bool Init();
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual int Update(float fDelaTime);
	virtual int LateUpdate(float fDelaTime);
	virtual CHeart* Clone();

public:
	virtual void Life(HDC hDC); 
	void Hit(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);
};

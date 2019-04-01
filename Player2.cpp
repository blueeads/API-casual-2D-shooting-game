#include "Player2.h"
#include "Texture.h"
#include "Input.h"
#include "Bullet.h"
#include "ColliderRect.h"
#include "Camera.h"
#include "Animation.h"
#include "Scene.h"
#include "Item.h"
#include "Heart.h"

CPlayer2::CPlayer2() :
	m_fFireTime(0.1f),
	m_fFireLimitTime(10.f)
{
}

CPlayer2::CPlayer2(const CPlayer2 & player) :
	CMoveObj(player)
{
}


CPlayer2::~CPlayer2()
{
}

bool CPlayer2::Init()
{
	SetPos(900.f, 300.f);
	SetSize(80.f, 80.f);
	SetSpeed(Speed);
	SetPivot(0.5f, 0.5f);

	//SetImageOffset(169.f, 122.f);

	//예를 들어 캐릭은 80x80인대 그림의 사이즈가 256x256일때
	//오프셋의 위치를 설정해주어 80x80사이즈가 나오게해준다.
	//SetImageOffset(7.f, 7.f);

	/*SetTexture("Player", L"HOS.bmp");
	SetColorKey(255, 255, 255);*/

	CColliderRect* pRC = AddCollider<CColliderRect>("PlayerBody2");

	//RC->SetRect(-72.f, -60.f, 72.f, 60.f);
	//pRC->SetRect(-60.f, -60.f, 60.f, 60.f);
	pRC->AddCollisionFunction(CS_ENTER, this,
		&CPlayer2::Hit);
	pRC->AddCollisionFunction(CS_STAY, this,
		&CPlayer2::HitStay);

	SAFE_RELEASE(pRC)

		m_iHP = 5;

	//중력을 적용한다.
	SetPhysics(false);

	//점프힘 설정
	SetForce(200.f);

	CAnimation* pAni = CreateAnimation("PlayerAnimation2");

	AddAnimationClip("IdleRight2", AT_ATLAS, AO_LOOP, 0.8f, 4, 4,
		0, 2, 1, 1, 0.f, "PlayerIdleRight2", L"Player2_Move.bmp");
	SetAnimationClipColorKey("IdleRight2", 255, 0, 255);

	AddAnimationClip("IdleLeft2", AT_ATLAS, AO_LOOP, 0.8f, 4, 4,
		0, 1, 1, 1, 0.f, "PlayerIdleLeft2", L"Player2_Move.bmp");
	SetAnimationClipColorKey("IdleLeft2", 255, 0, 255);

	AddAnimationClip("IdleUp2", AT_ATLAS, AO_LOOP, 0.8f, 4, 4,
		0, 3, 1, 1, 0.f, "PlayerIdleUp2", L"Player2_Move.bmp");
	SetAnimationClipColorKey("IdleUp2", 255, 0, 255);

	AddAnimationClip("IdleDown2", AT_ATLAS, AO_LOOP, 0.8f, 4, 4,
		0, 0, 1, 1, 0.f, "PlayerIdleDown2", L"Player2_Move.bmp");
	SetAnimationClipColorKey("IdleDown2", 255, 0, 255);

	///////////////////////////////////////////////////////////////////////
	AddAnimationClip("RunRight2", AT_ATLAS, AO_ONCE_RETURN, 0.8f, 4, 4,
		0, 2, 4, 1, 0.f, "PlayerRunRight2", L"Player2_Move.bmp");
	SetAnimationClipColorKey("RunRight2", 255, 0, 255);

	AddAnimationClip("RunLeft2", AT_ATLAS, AO_ONCE_RETURN, 0.8f, 4, 4,
		0, 1, 4, 1, 0.f, "PlayerRunLeft2", L"Player2_Move.bmp");
	SetAnimationClipColorKey("RunLeft2", 255, 0, 255);

	AddAnimationClip("RunUp2", AT_ATLAS, AO_ONCE_RETURN, 0.8f, 4, 4,
		0, 3, 4, 1, 0.f, "PlayerRunUp2", L"Player2_Move.bmp");
	SetAnimationClipColorKey("RunUp2", 255, 0, 255);

	AddAnimationClip("RunDown2", AT_ATLAS, AO_ONCE_RETURN, 0.8f, 4, 4,
		0, 0, 4, 1, 0.f, "PlayerRunDown2", L"Player2_Move.bmp");
	SetAnimationClipColorKey("RunDown2", 255, 0, 255);

	AddAnimationClip("AttackRight2", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 4, 4,
		0, 2, 4, 1, 0.f, "PlayerAttackRight2", L"Player2_Move.bmp");
	SetAnimationClipColorKey("AttackRight2", 255, 0, 255);

	AddAnimationClip("AttackLeft2", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 4, 4,
		0, 1, 4, 1, 0.f, "PlayerAttackLeft2", L"Player2_Move.bmp");
	SetAnimationClipColorKey("AttackLeft2", 255, 0, 255);

	AddAnimationClip("Attacked2", AT_ATLAS, AO_ONCE_RETURN, 2.0f, 4, 4,
		0, 1, 4, 1, 0.f, "PlayerAttacked2", L"Player2_Move.bmp");
	SetAnimationClipColorKey("Attacked2", 255, 0, 255);

	AddAnimationClip("Die2", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 4, 4,
		0, 1, 4, 1, 0.f, "PlayerDie2", L"Player2_Move.bmp");
	SetAnimationClipColorKey("Die2", 255, 0, 255);
	/*
	AddAnimationClip("RunRight", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 5, 7,
	0, 2, 5, 1, 0.f, "PlayerRunRight", L"Idle1.bmp");
	SetAnimationClipColorKey("RunRight", 255, 255, 255);

	AddAnimationClip("RunLeft", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 5, 7,
	0, 2, 5, 1, 0.f, "PlayerRunLeft", L"Idle.bmp");
	SetAnimationClipColorKey("RunLeft", 255, 255, 255);


	*/

	check = 0;

	//Frame 애니메이션
	//한장 한장 애니메이션쓰는방법
	vector<wstring> vecFileName;

	/*for (int i = 1; i <= 7; ++i)
	{
	wchar_t strFileName[MAX_PATH] = {};
	wsprintf(strFileName, L"%d.bmp", i);
	vecFileName.push_back(strFileName);
	}

	AddAnimationClip("AttackLeft", AT_FRAME, AO_LOOP, 0.3f, 4, 1,
	0, 0, 4, 1, 0.f, "PlayerAttackLeft", vecFileName);
	SetAnimationClipColorKey("AttackLeft", 255, 255, 255);*/

	SAFE_RELEASE(pAni);

	m_iDir = 1;

	return true;
}

void CPlayer2::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	if (KEYPRESS("MoveUp2"))
	{
		//Jump();
		MoveYFromSpeed(fDeltaTime, MD_BACK);
		m_pAnimation->ChangeClip("RunUp2");
		m_iDir = 1;
	}
	if (KEYPRESS("MoveDown2"))
	{
		MoveYFromSpeed(fDeltaTime, MD_FRONT);
		m_pAnimation->ChangeClip("RunDown2");
		m_iDir = -1;
	}
	if (KEYPRESS("MoveLeft2"))
	{
		MoveXFromSpeed(fDeltaTime, MD_BACK);
		m_pAnimation->ChangeClip("RunLeft2");
		m_iDir = -1;
	}
	if (KEYPRESS("MoveRight2"))
	{
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
		m_pAnimation->ChangeClip("RunRight2");
		m_iDir = 1;
	}
	if (KEYUP("MoveUp2"))
	{
		m_pAnimation->SetDefaultClip("IdleUp2");
	}
	if (KEYUP("MoveDown2"))
	{
		m_pAnimation->SetDefaultClip("IdleDown2");
	}
	if (KEYUP("MoveLeft2"))
	{
		m_pAnimation->SetDefaultClip("IdleLeft2");
	}
	if (KEYUP("MoveRight2"))
	{
		m_pAnimation->SetDefaultClip("IdleRight2");
	}


	if (KEYDOWN("Fire2"))
	{
		Fire();

		if (m_iDir == -1)
			m_pAnimation->ChangeClip("AttackLeft2");

		else
			m_pAnimation->ChangeClip("AttackRight2");
	}

	//if (KEYDOWN("Item2"))
	//{
	//	MessageBox(NULL, L"아이템효과", L"Item", MB_OK);
	//}
}

int CPlayer2::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	if (m_bAttack && m_pAnimation->GetMotionEnd())
		m_bAttack = false;

	if (!m_bMove && !m_bAttack)
		m_pAnimation->ReturnClip();

	return 0;
}

int CPlayer2::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CPlayer2::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CPlayer2::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);

	//Rectangle(hDC, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x,
	//m_tPos.y + m_tSize.y);

	// HP 기능 참고하도록
	// 아이템 같은경우는 태그를 이용하여 구분 GetTag() 함수있음.

	m_fFireTime += fDeltaTime;

	if (m_fFireTime >= m_fFireLimitTime)
	{
		m_fFireTime -= m_fFireLimitTime;
		ItemBox();
	}

	if (check == 0)
	{
		for (int i = 0; i < m_iHP; i++)
			m_Heart(i, 0);
	}

	check = 1;

	//wchar_t strHP[32] = {};
	//wsprintf(strHP, L"HP : %d", m_iHP);
	//POSITION tPos = m_tPos - m_tSize * m_tPivot;
	//tPos -= GET_SINGLE(CCamera)->GetPos();
	//TextOut(hDC, tPos.x, tPos.y , strHP, lstrlen(strHP));
}

CPlayer2 * CPlayer2::Clone()
{
	return new CPlayer2(*this);
}

int CPlayer2::GetHP()
{
	return m_iHP;
}

void CPlayer2::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (pDest->GetObj()->GetTag() == "PlayerBullet")
	{
		m_iHP -= Damage;
		m_pAnimation->ChangeClip("Attacked2");

		if (m_iHP <= 0)
		{
			m_pAnimation->ChangeClip("Die2");
			Die();
		}

		for (int i = 0; i < m_iHP; i++)
			m_Heart(i, 0);

		for (int i = 0; i < 5 - m_iHP; i++)
			m_Heart(i, 1);
	}

	else if (pDest->GetObj()->GetTag() == "PlayerItem")
	{
		if (m_iHP <= 4)	m_iHP += 1;

		for (int i = 0; i < m_iHP; i++)
			m_Heart(i, 0);

		for (int i = 0; i < 5 - m_iHP; i++)
			m_Heart(i, 1);
	}

	else if (pDest->GetTag() == "StageColl")
	{
		ClearGravity();
		JumpEnd();
	}
}

void CPlayer2::HitStay(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "StageColl")
	{
		ClearGravity();
		JumpEnd();
		m_tPos.y = pSrc->GetHitPoint().y - m_tPivot.y * m_tSize.y;
	}

	if (pDest->GetTag() == "NoMove")
	{
		if (m_iDir == 1)
			m_tPos.x = pSrc->GetHitPoint().x - m_tPivot.x * m_tSize.x + 48;

		else
			m_tPos.x = pSrc->GetHitPoint().x - m_tPivot.x * m_tSize.x + 52;
	}

	else if (pDest->GetTag() == "Snowman")
	{
		m_tPos.x = pSrc->GetHitPoint().x - m_tPivot.x * m_tSize.x;
	}
}

void CPlayer2::Fire()
{
	m_bAttack = true;

	CObj* pBullet = CObj::CreateCloneObj("Bullet", "PlayerBullet",
		m_pScene->GetSceneType(), m_pLayer);

	pBullet->AddCollisionFunction("BulletBody", CS_ENTER,
		(CBullet*)pBullet, &CBullet::Hit);

	//오른쪽 가운데를 구한다.
	POSITION tPos;

	if (m_iDir == -1)
		tPos.x = GetLeft() - pBullet->GetSize().x * (1.f - pBullet->GetPivot().x);

	else
		tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.y = GetCenter().y;

	pBullet->SetPos(tPos);

	if (m_iDir == -1)
		((CMoveObj*)pBullet)->SetAngle(Pl);

	SAFE_RELEASE(pBullet);
}

void CPlayer2::ItemBox()
{
	CObj* pItem = CObj::CreateCloneObj("Item", "PlayerItem",
		m_pScene->GetSceneType(), m_pLayer);

	pItem->AddCollisionFunction("BulletBody", CS_ENTER,
		(CItem*)pItem, &CItem::Hit);

	//오른쪽 가운데를 구한다.
	POSITION tPos;

	tPos.x = (rand() % 1100) + 850;
	tPos.y = (rand() % 480) + 100;

	pItem->SetPos(tPos);

	if (m_iDir == -1)
		((CMoveObj*)pItem)->SetAngle(Pl);

	SAFE_RELEASE(pItem);
}

void CPlayer2::m_Heart(int i, int type)
{
	CObj* pHeart = CObj::CreateCloneObj("Heart", "PlayerHeart",
		m_pScene->GetSceneType(), m_pLayer);
	if (type == 1)
	{
		pHeart->SetTexture("DieHeart", L"Die.bmp");
		pHeart->SetColorKey(255, 0, 255);
		pHeart->SetPos(1180.f - 70.f * i, 670.f);
	}
	else
	{
		pHeart->SetPos(900.f + 70.f * i, 670.f);
	}
	SAFE_RELEASE(pHeart);
}
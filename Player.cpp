#include "Player.h"
#include "Texture.h"
#include "Input.h"
#include "Bullet.h"
#include "ColliderRect.h"
#include "Camera.h"
#include "Animation.h"
#include "Scene.h"
#include "Item.h"
#include "Heart.h"

CPlayer::CPlayer() :
	m_fFireTime(0.f),
	m_fFireLimitTime(10.f)
{
}

CPlayer::CPlayer(const CPlayer & player) :
	CMoveObj(player)
{
}


CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	SetPos(300.f, 300.f);
	SetSize(80.f, 80.f);
	SetSpeed(Speed);
	SetPivot(0.5f, 0.5f);

	//SetImageOffset(169.f, 122.f);

	//예를 들어 캐릭은 80x80인대 그림의 사이즈가 256x256일때
	//오프셋의 위치를 설정해주어 80x80사이즈가 나오게해준다.
	//SetImageOffset(7.f, 7.f);

	/*SetTexture("Player", L"HOS.bmp");
	SetColorKey(255, 255, 255);*/

	CColliderRect* pRC = AddCollider<CColliderRect>("PlayerBody");

	//RC->SetRect(-72.f, -60.f, 72.f, 60.f);
	//pRC->SetRect(-60.f, -60.f, 60.f, 60.f);
	pRC->AddCollisionFunction(CS_ENTER, this,
		&CPlayer::Hit);
	pRC->AddCollisionFunction(CS_STAY, this,
		&CPlayer::HitStay);

	SAFE_RELEASE(pRC)

	m_iHP = 5;
	check = 0;
	//중력을 적용한다.
	SetPhysics(false);

	//점프힘 설정
	SetForce(200.f);

	CAnimation* pAni = CreateAnimation("PlayerAnimation");

	AddAnimationClip("IdleLeft", AT_ATLAS, AO_LOOP, 0.8f, 4, 4,
		0, 1, 1, 1, 0.f, "PlayerIdleLeft", L"Player_Move.bmp");
	SetAnimationClipColorKey("IdleLeft", 255, 0, 255);

	AddAnimationClip("IdleRight", AT_ATLAS, AO_LOOP, 0.8f, 4, 4,
		0, 2, 1, 1, 0.f, "PlayerIdleRight", L"Player_Move.bmp");
	SetAnimationClipColorKey("IdleRight", 255, 0, 255);

	AddAnimationClip("IdleUp", AT_ATLAS, AO_LOOP, 0.8f, 4, 4,
		0, 3, 1, 1, 0.f, "PlayerIdleUp", L"Player_Move.bmp");
	SetAnimationClipColorKey("IdleUp", 255, 0, 255);

	AddAnimationClip("IdleDown", AT_ATLAS, AO_LOOP, 0.8f, 4, 4,
		0, 0, 1, 1, 0.f, "PlayerIdleDown", L"Player_Move.bmp");
	SetAnimationClipColorKey("IdleDown", 255, 0, 255);

	///////////////////////////////////////////////////////////////////////
	AddAnimationClip("RunRight", AT_ATLAS, AO_ONCE_RETURN, 0.8f, 4, 4,
		0, 2, 4, 1, 0.f, "PlayerRunRight", L"Player_Move.bmp");
	SetAnimationClipColorKey("RunRight", 255, 0, 255);

	AddAnimationClip("RunLeft", AT_ATLAS, AO_ONCE_RETURN, 0.8f, 4, 4,
		0, 1, 4, 1, 0.f, "PlayerRunLeft", L"Player_Move.bmp");
	SetAnimationClipColorKey("RunLeft", 255, 0, 255);

	AddAnimationClip("RunUp", AT_ATLAS, AO_ONCE_RETURN, 0.8f, 4, 4,
		0, 3, 4, 1, 0.f, "PlayerRunUp", L"Player_Move.bmp");
	SetAnimationClipColorKey("RunUp", 255, 0, 255);

	AddAnimationClip("RunDown", AT_ATLAS, AO_ONCE_RETURN, 0.8f, 4, 4,
		0, 0, 4, 1, 0.f, "PlayerRunDown", L"Player_Move.bmp");
	SetAnimationClipColorKey("RunDown", 255, 0, 255);

	AddAnimationClip("AttackRight", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 4, 4,
		0, 2, 4, 1, 0.f, "PlayerAttackRight", L"Player_Move.bmp");
	SetAnimationClipColorKey("AttackRight", 255, 0, 255);

	AddAnimationClip("AttackLeft", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 4, 4,
		0, 1, 4, 1, 0.f, "PlayerAttackLeft", L"Player_Move.bmp");
	SetAnimationClipColorKey("AttackLeft", 255, 0, 255);

	AddAnimationClip("Attacked", AT_ATLAS, AO_ONCE_RETURN, 0.3f, 3, 4,
		0, 1, 3, 1, 0.f, "PlayerAttacked", L"Player_Attacked.bmp");
	SetAnimationClipColorKey("Attacked", 255, 0, 255);

	AddAnimationClip("Die", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 4, 4,
		0, 0, 3, 0, 0.f, "PlayerDie", L"Player_Die.bmp");
	SetAnimationClipColorKey("Die", 255, 0, 255);
	/*
	AddAnimationClip("RunRight", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 5, 7,
	0, 2, 5, 1, 0.f, "PlayerRunRight", L"Idle1.bmp");
	SetAnimationClipColorKey("RunRight", 255, 255, 255);

	AddAnimationClip("RunLeft", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 5, 7,
	0, 2, 5, 1, 0.f, "PlayerRunLeft", L"Idle.bmp");
	SetAnimationClipColorKey("RunLeft", 255, 255, 255);


	*/

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

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	if (KEYPRESS("MoveUp"))
	{
		//Jump();
		MoveYFromSpeed(fDeltaTime, MD_BACK);
		m_pAnimation->ChangeClip("RunUp");
		m_iDir = 1;
	}
	if (KEYPRESS("MoveDown"))
	{
		MoveYFromSpeed(fDeltaTime, MD_FRONT);
		m_pAnimation->ChangeClip("RunDown");
		m_iDir = -1;
	}
	if (KEYPRESS("MoveLeft"))
	{
		MoveXFromSpeed(fDeltaTime, MD_BACK);
		m_pAnimation->ChangeClip("RunLeft");
		m_iDir = -1;
	}
	if (KEYPRESS("MoveRight"))
	{
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
		m_pAnimation->ChangeClip("RunRight");
		m_iDir = 1;
	}
	if (KEYUP("MoveUp"))
	{
		m_pAnimation->SetDefaultClip("IdleUp");
	}
	if (KEYUP("MoveDown"))
	{
		m_pAnimation->SetDefaultClip("IdleDown");
	}
	if (KEYUP("MoveLeft"))
	{
		m_pAnimation->SetDefaultClip("IdleLeft");
	}
	if (KEYUP("MoveRight"))
	{
		m_pAnimation->SetDefaultClip("IdleRight");
	}


	if (KEYDOWN("Fire"))
	{
		Fire();

		if (m_iDir == -1)
			m_pAnimation->ChangeClip("AttackLeft");

		else
			m_pAnimation->ChangeClip("AttackRight");
	}

	//if (KEYDOWN("Item"))
	//{
	//	MessageBox(NULL, L"아이템효과", L"Item", MB_OK);
	//}
}

int CPlayer::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	if (m_bAttack && m_pAnimation->GetMotionEnd())
		m_bAttack = false;

	if (!m_bMove && !m_bAttack)
		m_pAnimation->ReturnClip();

	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CPlayer::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
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

	wchar_t strHP[32] = {};
	wsprintf(strHP, L"HP : %d", m_iHP);
	POSITION tPos = m_tPos - m_tSize * m_tPivot;
	tPos -= GET_SINGLE(CCamera)->GetPos();
	TextOut(hDC, tPos.x, tPos.y , strHP, lstrlen(strHP));
}

CPlayer * CPlayer::Clone()
{
	return new CPlayer(*this);
}

int CPlayer::GetHP()
{
	return m_iHP;
}

void CPlayer::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (pDest->GetObj()->GetTag() == "PlayerBullet")
	{
		m_iHP -= Damage;

		if (m_iHP <= 0)
		{
			m_pAnimation->ChangeClip("Die");
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

void CPlayer::HitStay(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
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

void CPlayer::Fire()
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

void CPlayer::ItemBox()
{
	CObj* pItem = CObj::CreateCloneObj("Item", "PlayerItem",
		m_pScene->GetSceneType(), m_pLayer);

	pItem->AddCollisionFunction("BulletBody", CS_ENTER,
		(CItem*)pItem, &CItem::Hit);

	//오른쪽 가운데를 구한다.
	POSITION tPos;

	tPos.x = (rand() % 680) + 310;
	tPos.y = (rand() % 480) + 100;

	pItem->SetPos(tPos);

	if (m_iDir == -1)
		((CMoveObj*)pItem)->SetAngle(Pl);

	SAFE_RELEASE(pItem);
}

void CPlayer::m_Heart(int i, int type)
{
	CObj* pHeart = CObj::CreateCloneObj("Heart", "PlayerHeart",
		m_pScene->GetSceneType(), m_pLayer);
	if (type == 1)
	{
		pHeart->SetTexture("DieHeart", L"Die.bmp");
		pHeart->SetColorKey(255, 0, 255);
		pHeart->SetPos(380.f - 70.f * i, 670.f);
	}
	else
	{
		pHeart->SetPos(100.f + 70.f * i, 670.f);
	}

	SAFE_RELEASE(pHeart);
}

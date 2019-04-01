#pragma once
#include "Scene.h"
class CStartScene :
	public CScene
{
private:
	friend class CSceneManager;

private:
	CStartScene();
	~CStartScene();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);

public:
	void StartButtonCallback(float fTime);
	void HowtoButtonCallback(float fTime);
	void EndButtonCallback(float fTime);
	void CreditButtonCallback(float fTime);
	void EditButtonCallback(float fTime);
};


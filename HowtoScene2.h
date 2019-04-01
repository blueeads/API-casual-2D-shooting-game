#pragma once
#include "Scene.h"

class CHowtoScene2 :
	public CScene
{
private:
	friend class CSceneManager;

private:
	CHowtoScene2();
	~CHowtoScene2();

private:
	int SCeneN;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);

};


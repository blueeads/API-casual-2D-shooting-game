#pragma once
#include "Scene.h"

class CHowtoScene :
	public CScene
{
private:
	friend class CSceneManager;

private:
	CHowtoScene();
	~CHowtoScene();

private:
	int SCeneN;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);

};


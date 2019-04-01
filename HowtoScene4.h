#pragma once
#include "Scene.h"

class CHowtoScene4 :
	public CScene
{
private:
	friend class CSceneManager;

private:
	CHowtoScene4();
	~CHowtoScene4();

private:
	int SCeneN;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);

};


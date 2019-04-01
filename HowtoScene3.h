#pragma once
#include "Scene.h"

class CHowtoScene3 :
	public CScene
{
private:
	friend class CSceneManager;

private:
	CHowtoScene3();
	~CHowtoScene3();

private:
	int SCeneN;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);

};


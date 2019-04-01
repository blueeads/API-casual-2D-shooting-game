#pragma once
#include "Scene.h"

class CCreditScene :
	public CScene
{
private:
	friend class CSceneManager;

private:
	CCreditScene();
	~CCreditScene();

private:
	Stage_NumBer StageNum;

public:
	virtual bool Init();
	void MainButtonCallback(float fTime);

};


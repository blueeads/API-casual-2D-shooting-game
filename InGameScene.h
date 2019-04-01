#pragma once
#include "Scene.h"

class CInGameScene :
	public CScene
{
private:
	friend class CSceneManager;

private:
	CInGameScene();
	~CInGameScene();
protected:
	SetUP SU;
private:
	class CStage* m_pStage;
	static wchar_t m_strText[MAX_PATH];
	Stage_NumBer StageNum;
	float fTime;
public:
	virtual bool Init();
	void SetUpButtonCallback(float fTime);
	void ReSumeButtonCallback(float fTime);
	void ExitButtonCallback(float fTime);
	void ReStartCallBack(float fTime);

	void TimeAndHeart();

};


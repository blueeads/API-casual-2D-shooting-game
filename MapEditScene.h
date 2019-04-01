#pragma once
#include "Scene.h"

class CMapEditScene :
	public CScene
{
private:
	friend class CSceneManager;

private:
	CMapEditScene();
	~CMapEditScene();

private:
	TILE_EDIT_MODE m_eTem;
	TILE_OPTION m_eEditOption;
	vector<class CTexture*> m_vecTileTex;
	int m_iEditTileTex;
	class CStage* m_pStage;

private:
	static wchar_t m_strText[MAX_PATH];

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);

public:
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};


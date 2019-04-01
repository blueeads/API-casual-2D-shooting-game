#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_

#include <windows.h>

typedef struct tagMenu
{
	char* options[3];
	int optionSpawns[3];
	int x, y;
	int w, h;
	COLORREF color;

}MENU;

MENU InitMenu(RECT rt, COLORREF color, 
			  char* option1, int spawn1, 
			  char* option2, int spawn2, 
			  char* option3, int spawn3);
void DrawMenu(HDC hdc, MENU Menu);


#endif
#include "GameMenu.h"

MENU InitMenu(RECT rt, COLORREF color,
	char* option1, int spawn1,
	char* option2, int spawn2,
	char* option3, int spawn3)
{
	MENU temp;

	temp.options[0] = option1;
	temp.optionSpawns[0] = spawn1;
	temp.options[1] = option2;
	temp.optionSpawns[1] = spawn2;
	temp.options[2] = option3;
	temp.optionSpawns[2] = spawn3;
	temp.x = rt.left;
	temp.y = rt.top;
	temp.w = rt.right - rt.left;
	temp.h = rt.bottom - rt.top;
	temp.color = color;

	return temp;
}

void DrawMenu(HDC hdc, MENU Menu)
{
	HBRUSH hbrMenu, hbrOld;
	hbrMenu = CreateSolidBrush(Menu.color);
	COLORREF OldBk, OldText;

	int x1, y1, x2, y2;
	x1 = Menu.x;
	y1 = Menu.y;
	x2 = x1 + Menu.w;
	y2 = y1 + Menu.h;

	hbrOld = (HBRUSH)SelectObject(hdc, hbrMenu);
	Rectangle(hdc, x1, y1, x2, y2);

	OldBk = SetBkColor(hdc, Menu.color);
	COLORREF textcolor = !(Menu.color);
	OldText = SetTextColor(hdc, textcolor);

	for (int i = 0; i < 3; i++)
	{
		//if (Menu.options[i] != 0)
		//{
			//TextOut(hdc, x1 + 30, y1 + (i * 20) + 20,
			//	Menu.options[i], strlen(Menu.options[i]));
		//}
	}

	SetBkColor(hdc, OldBk);
	SetTextColor(hdc, OldText);
	DeleteObject(hbrOld);
	DeleteObject(hbrMenu);
}


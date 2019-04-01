#ifndef _STACK_H_
#define _STACK_H_

#include "GameMenu.h"

#define MAX 3

typedef struct tagStack
{
	MENU data[MAX];
	int top;

}STACK;

STACK InitStack(void);
bool Empty(STACK stack);
bool Full(STACK stack);
bool Push(STACK* stack, MENU data);
MENU Pop(STACK* stack);
MENU Top(STACK stack);

#endif
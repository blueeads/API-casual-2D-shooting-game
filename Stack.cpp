#include "Stack.h"

STACK InitStack(void)
{
	STACK temp;

	temp.top = -1;

	return temp;
}

bool Empty(STACK stack)
{
	if (stack.top < 0) { return true; }
	else { return false; }
}

bool Full(STACK stack)
{
	if (stack.top == (MAX - 1)) { return true; }
	else { return false; }
}

bool Push(STACK* stack, MENU data)
{
	if (Full(*stack)) return false;

	stack->top++;

	stack->data[stack->top] = data;

	return true;
}

MENU Pop(STACK* stack)
{
	MENU temp;

	temp = stack->data[stack->top];
	stack->top--;

	return temp;
}

MENU Top(STACK stack)
{
	return stack.data[stack.top];
}


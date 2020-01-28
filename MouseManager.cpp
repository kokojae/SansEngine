#include "DXUT.h"
#include "MouseManager.h"


MouseManager::MouseManager()
{
}


MouseManager::~MouseManager()
{
}

void MouseManager::SetMouseState(UINT msg, LPARAM lPa)
{
	uMsg = msg;
	lParam = lPa;
	xPos = LOWORD(lPa);
	yPos = HIWORD(lPa);
}

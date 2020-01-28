#pragma once
class MouseManager
{
private:
	UINT uMsg;
	LPARAM lParam;
	int xPos;
	int yPos;

public:
	MouseManager();
	~MouseManager();

	// 싱글턴 반환 함수
	static MouseManager& Instance()
	{
		static MouseManager *instance = new MouseManager;
		return *instance;
	}

	void SetMouseState(UINT msg, LPARAM lPa);

	UINT GetMsg() { return uMsg; }
	int GetXPos() { return xPos; }
	int GetYPos() { return yPos; }
};


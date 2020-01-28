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

	// �̱��� ��ȯ �Լ�
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


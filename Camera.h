#pragma once
class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Release();

	void MoveCamera();
	void ResetCamera();

private:
	D3DXVECTOR3 vHighPos;
	D3DXVECTOR2 vCamera;
};


#include "DXUT.h"
#include "Camera.h"
#include "ObjectManager.h"
#include "GameManager.h"

Camera::Camera()
{
	Init();
}


Camera::~Camera()
{
	Release();
}

void Camera::Init()
{
	vHighPos = { 400, 0, 0 };
	vCamera = { 0, 0 };
}

void Camera::Release()
{
}

void Camera::MoveCamera()
{
	vCamera.x = vHighPos.x - (GameManager::Instance().GetPlayer().GetPos()).x;
	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, vCamera.x, 0, 0);
	ObjectManager::Instance().GetObjectSprite()->SetTransform(&mat);
}

void Camera::ResetCamera()
{
	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, 0, 0, 0);
	ObjectManager::Instance().GetObjectSprite()->SetTransform(&mat);
}

//--------------------------------------------------------------------------------------
// File: SansEngine.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "DXUT.h"
#include "resource.h"
#include "SansEngine.h"


//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
// false�� ��ȯ�Ͽ� �ۿ� �������� ���� D3D9 ��⸦ �ź��մϴ�.
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
    // Typically want to skip back buffer formats that don't support alpha blending
	// �Ϲ������� ���� ������ �������� �ʴ� ���� ������ �ǳ� �ٷ����մϴ�.
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// Before a device is created, modify the device settings as needed
// ��ġ�� ����� ���� �ʿ信 ���� ��ġ ������ �����Ͻʽÿ�
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
// ��ġ �缳�� (D3DPOOL_MANAGED)�� ���� �۵��ϰ�
// �� ���� ũ�⿡ ������ ���� D3D9 ���ҽ��� ����ϴ�.
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
	// �ʱ�ȭ
	ObjectManager::Instance().Init();
	SoundManager::Instance().Init();
	GameManager::Instance().Init();
	FontManager::Instance().Init();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
// ��ġ �缳�� (D3DPOOL_DEFAULT)�� ���� �۵����� �ʰų�
// �� ���� ũ�⿡ ����� D3D9 ���ҽ��� ����ϴ�.
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
// ��� ������Ʈ�� ó���մϴ�. ���Ǵ� D3D API�� ������� ȣ��˴ϴ�
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
	// ������Ʈ
	GameManager::Instance().Update();
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
// D3D9 ��ġ�� ����Ͽ� ����� ������
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    // Clear the render target and the zbuffer 
    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );

    // Render the scene
	if (SUCCEEDED(pd3dDevice->BeginScene()))
	{
		GameManager::Instance().Render();

        V( pd3dDevice->EndScene() );
    }
}


//--------------------------------------------------------------------------------------
// Handle messages to the application 
// ���� ���α׷��� ���� �޽��� ó��
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
	MouseManager::Instance().SetMouseState(uMsg, lParam);

    return 0;
}

//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9ResetDevice callback 
// OnD3D9ResetDevice �ݹ鿡�� ���� �� D3D9 ���ҽ� ������
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
// OnD3D9CreateDevice �ݹ鿡�� ���� �� D3D9 ���ҽ� ������
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
	// ����
	FontManager::Instance().Release();
	GameManager::Instance().Release();
	SoundManager::Instance().Release();
	ObjectManager::Instance().Release();
}


//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
// ��� ���� �ʱ�ȭ�ϰ� ���� ������ �̵�
//--------------------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
{
    // Enable run-time memory check for debug builds.
	// ����� ���忡 ���� ��Ÿ�� �޸� �˻縦 Ȱ��ȭ�Ͻʽÿ�.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // Set the callback functions
	// �ݹ� �Լ� ����
    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackFrameMove( OnFrameMove );

    // TODO: Perform any application-level initialization here
	// TODO : ��� ���ø����̼� ���� �ʱ�ȭ�� �����Ͻʽÿ�.

    // Initialize DXUT and create the desired Win32 window and Direct3D device for the application
	// DXUT�� �ʱ�ȭ�ϰ� ���� ���α׷��� ���� ���ϴ� Win32 â�� Direct3D ��ġ�� ����ϴ�.
    DXUTInit( true, true ); // Parse the command line and show msgboxes, ��� ���� ���� �м��ϰ� msgboxes�� ǥ���Ͻʽÿ�.
    DXUTSetHotkeyHandling( true, true, true );  // handle the default hotkeys, �⺻ ����Ű�� ó��
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen, ��ü ȭ�� �� �� Ŀ�� ǥ�� �� Ŭ��
    DXUTCreateWindow( L"SansEngine" );
    DXUTCreateDevice( true, 1920, 1080);

    // Start the render loop
	// ���� ���� ����
    DXUTMainLoop();

    // TODO: Perform any application-level cleanup here
	// TODO : ��� ���ø����̼� ���� ������ �����Ͻʽÿ�.

    return DXUTGetExitCode();
}



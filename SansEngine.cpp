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
// false를 반환하여 앱에 적합하지 않은 D3D9 기기를 거부합니다.
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
    // Typically want to skip back buffer formats that don't support alpha blending
	// 일반적으로 알파 블렌딩을 지원하지 않는 버퍼 형식을 건너 뛰려고합니다.
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// Before a device is created, modify the device settings as needed
// 장치를 만들기 전에 필요에 따라 장치 설정을 수정하십시오
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
// 장치 재설정 (D3DPOOL_MANAGED)을 통해 작동하고
// 백 버퍼 크기에 묶이지 않은 D3D9 리소스를 만듭니다.
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
	// 초기화
	ObjectManager::Instance().Init();
	SoundManager::Instance().Init();
	GameManager::Instance().Init();
	FontManager::Instance().Init();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
// 장치 재설정 (D3DPOOL_DEFAULT)을 통해 작동하지 않거나
// 백 버퍼 크기에 연결된 D3D9 리소스를 만듭니다.
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
// 장면 업데이트를 처리합니다. 사용되는 D3D API에 관계없이 호출됩니다
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
	// 업데이트
	GameManager::Instance().Update();
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
// D3D9 장치를 사용하여 장면을 렌더링
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
// 응용 프로그램에 대한 메시지 처리
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
	MouseManager::Instance().SetMouseState(uMsg, lParam);

    return 0;
}

//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9ResetDevice callback 
// OnD3D9ResetDevice 콜백에서 생성 된 D3D9 리소스 릴리스
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
// OnD3D9CreateDevice 콜백에서 생성 된 D3D9 리소스 릴리스
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
	// 해제
	FontManager::Instance().Release();
	GameManager::Instance().Release();
	SoundManager::Instance().Release();
	ObjectManager::Instance().Release();
}


//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
// 모든 것을 초기화하고 렌더 루프로 이동
//--------------------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
{
    // Enable run-time memory check for debug builds.
	// 디버그 빌드에 대해 런타임 메모리 검사를 활성화하십시오.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // Set the callback functions
	// 콜백 함수 설정
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
	// TODO : 모든 애플리케이션 레벨 초기화를 수행하십시오.

    // Initialize DXUT and create the desired Win32 window and Direct3D device for the application
	// DXUT를 초기화하고 응용 프로그램에 대한 원하는 Win32 창과 Direct3D 장치를 만듭니다.
    DXUTInit( true, true ); // Parse the command line and show msgboxes, 명령 행을 구문 분석하고 msgboxes를 표시하십시오.
    DXUTSetHotkeyHandling( true, true, true );  // handle the default hotkeys, 기본 단축키를 처리
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen, 전체 화면 일 때 커서 표시 및 클립
    DXUTCreateWindow( L"SansEngine" );
    DXUTCreateDevice( true, 1920, 1080);

    // Start the render loop
	// 렌더 루프 시작
    DXUTMainLoop();

    // TODO: Perform any application-level cleanup here
	// TODO : 모든 애플리케이션 레벨 정리를 수행하십시오.

    return DXUTGetExitCode();
}



#pragma once
class TextureInfo
{
public:
	TextureInfo();
	~TextureInfo();

	D3DXVECTOR2 size = D3DXVECTOR2(100, 100);
	float index = 0;
	D3DXVECTOR2 center = D3DXVECTOR2(0,0);
	D3DXVECTOR2 scale = D3DXVECTOR2(1, 1);
	float rotation = 0;
	D3DXCOLOR uiColor = D3DCOLOR_ARGB(255,255,255,255);
	bool camera_on = true;

	wchar_t * ConverCtoWC(char * str);
};
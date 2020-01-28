#include "DXUT.h"
#include "TextureInfo.h"


TextureInfo::TextureInfo()
{
}


TextureInfo::~TextureInfo()
{
}

wchar_t * TextureInfo::ConverCtoWC(char * str)
{
	//wchar_t형 변수 선언
	wchar_t* pStr;

	//멀티 바이트 크기 계산 길이 반환
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);

	//wchar_t 메모리 할당
	pStr = new WCHAR[strSize];

	//형 변환
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);

	return pStr;
}

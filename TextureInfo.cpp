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
	//wchar_t�� ���� ����
	wchar_t* pStr;

	//��Ƽ ����Ʈ ũ�� ��� ���� ��ȯ
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);

	//wchar_t �޸� �Ҵ�
	pStr = new WCHAR[strSize];

	//�� ��ȯ
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);

	return pStr;
}

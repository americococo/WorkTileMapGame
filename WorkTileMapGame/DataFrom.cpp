#include <Windows.h>

wchar_t* ConverCtoWC(char* str)
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

char * ConvertWCtoC(wchar_t* str)

{

	//��ȯ�� char* ���� ����

	char* pStr;



	//�Է¹��� wchar_t ������ ���̸� ����

	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	//char* �޸� �Ҵ�

	pStr = new char[strSize];



	//�� ��ȯ 

	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);

	return pStr;
}
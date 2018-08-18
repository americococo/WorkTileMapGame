#include <Windows.h>

wchar_t* ConverCtoWC(char* str)
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

char * ConvertWCtoC(wchar_t* str)

{

	//반환할 char* 변수 선언

	char* pStr;



	//입력받은 wchar_t 변수의 길이를 구함

	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	//char* 메모리 할당

	pStr = new char[strSize];



	//형 변환 

	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);

	return pStr;
}
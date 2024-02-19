#include "helpers.h"


namespace obvl
{
	LPWSTR CharToLPWSTR(const char* charArray)
	{
		LPWSTR lpwszStr = new wchar_t[strlen(charArray) + 1];
		MultiByteToWideChar(CP_ACP, 0, charArray, -1, lpwszStr, strlen(charArray) + 1);
		return lpwszStr;
	}

	char* LPWSTRToChar(LPWSTR lpwszStr)
	{
		char* charArray = new char[wcslen(lpwszStr) + 1];
		WideCharToMultiByte(CP_ACP, 0, lpwszStr, -1, charArray, wcslen(lpwszStr) + 1, 0, 0);
		return charArray;
	}

	std::string LPWSTRToString(LPWSTR lpwszStr)
	{
		std::string str = std::string(LPWSTRToChar(lpwszStr));
		return str;
	}

	LPWSTR StringToLPWSTR(std::string str)
	{
		LPWSTR lpwszStr = CharToLPWSTR(str.c_str());
		return lpwszStr;
	}
}
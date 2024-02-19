#pragma once
#include "Windows.h"
#include <string>


namespace obvl
{
	LPWSTR CharToLPWSTR(const char* charArray);

	char* LPWSTRToChar(LPWSTR lpwszStr);
	
	std::string LPWSTRToString(LPWSTR lpwszStr);

	LPWSTR StringToLPWSTR(std::string str);
	
}
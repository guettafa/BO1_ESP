#include "pch.h"
#include "client.h"

MODULEINFO Client::GetModuleInfo(const wchar_t* moduleName)
{
	MODULEINFO moduleInfo;

	HMODULE hModule  = GetModuleHandle(moduleName);
	HANDLE  hProcess = GetCurrentProcess();

	GetModuleInformation(hProcess, hModule, &moduleInfo, sizeof(MODULEINFO));
	
	return moduleInfo;
}

uintptr_t Client::FindPattern(const wchar_t* moduleName, const char* pattern, int patternLength)
{
	MODULEINFO moduleInfo        = GetModuleInfo(moduleName);
	DWORD      imageSize         = moduleInfo.SizeOfImage;

	uintptr_t  moduleBaseAddress = reinterpret_cast<uintptr_t>(moduleInfo.lpBaseOfDll);

	for (size_t i = 0; i < imageSize; i++)
	{
		bool isPatternFound = true;

		// Go through each byte in instruction
		for (size_t j = 0; j < patternLength; j++)
		{
			if (pattern[j] != *reinterpret_cast<char*>(moduleBaseAddress + i + j))
			{
				isPatternFound = false;
			}
		}
		if (isPatternFound) // return adress of the instruction
			return moduleBaseAddress + i; 
	}
	return std::string::npos;
}

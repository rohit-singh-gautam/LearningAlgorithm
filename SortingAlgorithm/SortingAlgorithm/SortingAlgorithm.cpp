#include "pch.h"
#include "SortHelper.h"
#include "SortTest.h"
#include <Windows.h>
#include <iostream>

int main()
{
	const int count = 1;
	const int arraycount = 10000;
	const int arraysize = 768;
	HANDLE process = GetCurrentProcess();
	DWORD_PTR processAffinityMask = 0x2;

	if (!SetProcessAffinityMask(process, processAffinityMask)) {
		std::cout << "Unable to set priority mask" << std::endl;
	}

	if (!SetPriorityClass(process, HIGH_PRIORITY_CLASS)) {
		std::cout << "Making priority highest" << std::endl;
	}

	SortAllTest(count, arraycount, arraysize);
}
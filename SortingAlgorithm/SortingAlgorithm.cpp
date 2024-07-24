#include "SortHelper.h"
#include "TestClassContainer.h"
#include <iostream>

int main()
{
	const int count = 1;
	const int arraycount = 10000;
	const int arraysize = 768;

#ifdef WIN32
	HANDLE process = GetCurrentProcess();
	DWORD_PTR processAffinityMask = 0x2;

	if (!SetProcessAffinityMask(process, processAffinityMask)) {
		std::cout << "Unable to set priority mask" << std::endl;
	}

	if (!SetPriorityClass(process, HIGH_PRIORITY_CLASS)) {
		std::cout << "Making priority highest" << std::endl;
	}
#endif

	SortAllTest(count, arraycount, arraysize);

	return 0;
}
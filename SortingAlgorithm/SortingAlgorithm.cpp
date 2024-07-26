#include "SortHelper.h"
#include "TestClassContainer.h"
#include <iostream>
#include <unordered_set>

int main()
{
	const int NumberOfArrayToSortAtOnce = 1;
	const int arraycount = 10000;
	const int arraysize = 4064;

	const std::unordered_set<std::pair<std::string_view, size_t>> skiptestlist {
		{"Bubble Sort", TestProperties { TestProperties::N_Square, TestProperties::Iterative }},
		{"Selection Sort", TestProperties { TestProperties::N_Square, TestProperties::Iterative }},
		{"QuickSort Sort", TestProperties { TestProperties::N_LogN, TestProperties::Iterative, TestProperties::Randomize }},
		{"QuickSort Sort", TestProperties { TestProperties::N_LogN, TestProperties::Recursive, TestProperties::Randomize }}
	};

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

	TestClassContainer::TestAllSortingAlgorigthmAllOrders(arraycount, arraysize, NumberOfArrayToSortAtOnce, skiptestlist);

	return 0;
}
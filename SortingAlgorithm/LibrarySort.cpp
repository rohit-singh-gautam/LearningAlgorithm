#include "SortHelper.h"
#include "SortTest.h"
#include <chrono>
#include <algorithm>
#include <iostream>

TestLibrarySortClass::TestLibrarySortClass(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "Library Sort";
}

void TestLibrarySortClass::SortAlgorithm(std::vector<int> &a) {
	std::sort(a.begin(), a.end());
}
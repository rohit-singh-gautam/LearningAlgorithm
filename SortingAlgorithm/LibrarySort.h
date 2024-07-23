#include "SortHelper.h"
#include "SortTest.h"
#include <chrono>
#include <algorithm>
#include <iostream>

class TestLibrarySortClass : public TestClass {
public:
	TestLibrarySortClass(std::vector<std::vector<int>> &inarrays) : TestClass { inarrays, "Library Sort" } { }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		std::sort(a.begin(), a.end());
	}
};

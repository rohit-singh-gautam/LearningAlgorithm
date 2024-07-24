#pragma once

#include "SortHelper.h"
#include "TestClassContainer.h"
#include <chrono>
#include <algorithm>
#include <iostream>

class TestLibrarySortClass : public TestClass {
	static constexpr const std::string_view name { "LibrarySort" };
public:
	TestLibrarySortClass(std::vector<std::vector<int>> &inarrays) : TestClass { inarrays, NONE } { }

	const std::string_view &GetBaseName() const override { return name; }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		std::sort(a.begin(), a.end());
	}
};

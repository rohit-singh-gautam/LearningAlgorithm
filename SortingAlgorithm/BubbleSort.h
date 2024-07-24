#pragma once

#include "SortHelper.h"
#include "TestClassContainer.h"

class TestBubbleSortClass : public TestClass {
	static constexpr const std::string_view name { "Bubble Sort" };
public:
	TestBubbleSortClass(std::vector<std::vector<int>> &inarrays) :
		TestClass { inarrays, TestClass::N_Square } { }

	const std::string_view &GetBaseName() const override { return name; }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		auto n = a.size();
		bool bSorted = false;
		for (auto i = n - 1; i >= 1 && !bSorted; --i) {
			bSorted = true;
			for (size_t j = 0; j < i; j++) {
				if (a[j + 1] < a[j]) {
					std::swap(a[j], a[j + 1]);
					bSorted = false;
				}
			}
		}
	}
};

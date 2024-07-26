#pragma once

#include "TestClass.h"
class BubbleSortTester : public TestClass {
public:
	static constexpr const std::string_view name { "Bubble Sort" };
	using TestClass::TestClass;

	const std::string_view &GetBaseName() const override { return name; }

	static void BubbleSortAlgorithm(std::vector<int> &a) {
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

	static const std::vector<size_t> AllSortProperties;
	static auto &GetAllSortProperties() { return AllSortProperties; }

private:
	static const std::unordered_map<size_t, SortingFunction> sortmaps;
	const std::unordered_map<size_t, SortingFunction> &GetSortMapping() const override { return sortmaps; }
};


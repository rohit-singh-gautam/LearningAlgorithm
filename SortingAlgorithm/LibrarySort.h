#pragma once

#include "SortHelper.h"
#include <chrono>
#include <algorithm>
#include <iostream>

class LibrarySortTester : public TestClass {
public:
	static constexpr const std::string_view name { "Library Sort" };

	using TestClass::TestClass;

	const std::string_view &GetBaseName() const override { return name; }

	static const std::vector<size_t> AllSortProperties;
	static auto &GetAllSortProperties() { return AllSortProperties; }

	static void LibrarySortAlgorithm(std::vector<int> &a) {
		std::sort(a.begin(), a.end());
	}

private:

	static const std::unordered_map<size_t, SortingFunction> sortmaps;
	const std::unordered_map<size_t, SortingFunction> &GetSortMapping() const override { return sortmaps; }
};

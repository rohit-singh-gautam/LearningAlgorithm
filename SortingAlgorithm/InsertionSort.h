#pragma once

#include "SortHelper.h"

using namespace std;

inline void InsertionSort(std::vector<int> &a, size_t start, size_t end) {
	auto first = a[start];
	for (std::size_t i = 1; i <= end; ++i) {
		auto j = i;
		auto pivot = a[j];
		if (pivot < first) {
			while (j > start) {
				--j;
				a[j + 1] = a[j];
			}
			first = a[start] = pivot;
		}
		else {
			while (pivot < a[j - 1]) {
				a[j] = a[j - 1];
				j--;
			}
			a[j] = pivot;
		}
	}
}

inline void InsertionSort(std::vector<int> &a) {
	auto n = a.size();
	for (std::size_t i = 1; i < n; i++) {
		auto j = i;
		auto pivot = a[j];
		if (pivot < a[0]) {
			while (j-- > 0) {
				a[j + 1] = a[j];
			}
			a[0] = pivot;
		}
		else {
			while (pivot < a[j - 1]) {
				a[j] = a[j - 1];
				j--;
			}
			a[j] = pivot;
		}
	}
}

inline void InsertionSort(int *first, int *last) {
	for (auto next = first; ++next != last;) {
		auto next1 = next;
		auto pivot = *next;
		if (pivot < *first) {
			while (next1 != first) {
				auto next2 = next1;
				 *next2 = *(--next1);
			}
			*first = pivot;
		}
		else {
			for (auto first1 = next1; pivot < *(--first1); next1 = first1)
				*next1 = *first1;
			*next1 = pivot;
		}
	}
}
inline void InsertionSortPointer(std::vector<int> &inarrays) {
	int *first = &inarrays.front();
	int *last = &inarrays.back();
	InsertionSort(first, last);
}

class InsertionSortTester : public TestClass {
public:
	static constexpr const std::string_view name { "Insertion Sort" };
	using TestClass::TestClass;

	const std::string_view &GetBaseName() const override { return name; }

	static const std::vector<size_t> AllSortProperties;
	static auto &GetAllSortProperties() { return AllSortProperties; }

private:
	static const std::unordered_map<size_t, SortingFunction> sortmaps;
	const std::unordered_map<size_t, SortingFunction> &GetSortMapping() const override { return sortmaps; }
};


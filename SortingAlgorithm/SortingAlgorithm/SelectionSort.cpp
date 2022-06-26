#include "pch.h"
#include "SortHelper.h"
#include "SortTest.h"

using namespace std;

void SelectionSortRange(std::vector<int> &a, size_t start, size_t end) {
	if (start >= end) return;

	for (size_t i = start; i <= end - 1; i++) {
		size_t lowest = i;
		for (size_t j = i + 1; j <= end; j++) {
			if (a[j] < a[lowest]) lowest = j;
		}

		swap(a[i], a[lowest]);
	}
}

void SelectionSort(std::vector<int> &a) {
	SelectionSortRange(a, 0, a.size() - 1);
}

TestSelectionSortClass::TestSelectionSortClass(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "Selection Sort";
}

void TestSelectionSortClass::SortAlgorithm(std::vector<int> &a) {
	SelectionSort(a);
}
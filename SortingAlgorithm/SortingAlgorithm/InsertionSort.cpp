#include "pch.h"
#include "SortHelper.h"
#include "SortTest.h"

using namespace std;

void InsertionSort(std::vector<int> &a, int start, int end) {
	auto first = a[start];
	for (std::size_t i = 1; i <= end; i++) {
		auto j = i;
		auto pivot = a[j];
		if (pivot < first) {
			while (--j >= start) {
				a[j + 1] = a[j];
			}
			first = a[start] = a[j];
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

void InsertionSort(std::vector<int> &a) {
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

void InsertionSort(int *first, int *last) {
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



TestInsertionSortClass::TestInsertionSortClass(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "Insertion Sort";
}

void TestInsertionSortClass::SortAlgorithm(std::vector<int> &a) {
	InsertionSort(a);
}

TestInsertionSortClass1::TestInsertionSortClass1(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "Insertion Sort Pointer";
}

void TestInsertionSortClass1::SortAlgorithm(std::vector<int> &a) {
	int *first = &a.front();
	int *last = &a.back();
	InsertionSort(first, last);
}
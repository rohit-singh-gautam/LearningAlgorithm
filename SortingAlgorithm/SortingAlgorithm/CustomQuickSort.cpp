#include "pch.h"
#include "SortHelper.h"
#include "SortTest.h"
#include <chrono>
#include <iostream>

size_t CustomPartitionAlgorithm(std::vector<int> &a, size_t start, size_t end) {
	int pivot;

	register auto i = start;
	register auto j = end;
		
	// Probably reverse sorted lets try to swap first and last till we can
	while (i < j && a[i] > a[j]) {
		std::swap(a[i++], a[j--]);
	}

	// Taking care of forward sorted case
	while (start < end && a[start] <= a[start + 1]) start++;
	if (start == end) return 0; //Already sorted.

	i = start + 1;
	j = end;
		
	pivot = a[start];
 

	while (i <= end && a[i] <= pivot) i++;
	while (a[j] > pivot) j--; // a[start] is val where j is going to stop anyway
	if (i < j) {
		std::swap(a[i], a[j]);

		// In second iteration
		while (true) {
			while (a[i] <= pivot) i++;
			while (a[j] > pivot) j--; // a[start] is val where j is going to stop anyway
			if (i >= j) break;
			std::swap(a[i], a[j]);
		}
	}

	std::swap(a[start], a[j]);
	return j;
}

size_t CustomPartitionAlgorithmInsertion(std::vector<int> &a, size_t start, size_t end) {
	int pivot;

	if (end < start + 32) {
		int *first = &a[start];
		int *last = &a[end]; last++;
		InsertionSort(first, last);
		return 0;
	}

	register auto i = start;
	register auto j = end;

	// Probably reverse sorted lets try to swap first and last till we can
	while (i < j && a[i] > a[j]) {
		std::swap(a[i++], a[j--]);
	}

	// Taking care of forward sorted case
	while (start < end && a[start] <= a[start + 1]) start++;
	if (start == end) return 0; //Already sorted.

	i = start + 1;
	j = end;

	pivot = a[start];


	while (i <= end && a[i] <= pivot) i++;
	while (a[j] > pivot) j--; // a[start] is val where j is going to stop anyway
	if (i < j) {
		std::swap(a[i], a[j]);

		// In second iteration
		while (true) {
			while (a[i] <= pivot) i++;
			while (a[j] > pivot) j--; // a[start] is val where j is going to stop anyway
			if (i >= j) break;
			std::swap(a[i], a[j]);
		}
	}

	std::swap(a[start], a[j]);
	return j;
}

void CustomQuickSortRecursiveHelper(std::vector<int> &a, const size_t start, const size_t end) {
	register auto part = CustomPartitionAlgorithm(a, start, end);
	if (part == 0) return;
	if (start < part - 1) CustomQuickSortRecursiveHelper(a, start, part - 1);
	if (part + 1 < end) CustomQuickSortRecursiveHelper(a, part + 1, end);
}

void CustomQuickSortRecursiveTailHelper(std::vector<int> &a, size_t start, size_t end) {
	while (true) {
		auto part = CustomPartitionAlgorithm(a, start, end);
		if (part == 0) return;

		auto choice = (start + 1 < part) + ((part + 1 < end) << 1);

		switch (choice)
		{
		case 1:
			end = part - 1;
			break;

		case 2:
			start = part + 1;
			break;

		case 3:
			if (part - start < end - part) {
				CustomQuickSortRecursiveHelper(a, start, part - 1);
				start = part + 1;
			}
			else {
				CustomQuickSortRecursiveHelper(a, part + 1, end);
				end = part - 1;
			}
			break;

		default:
			return;
		}
	}
}

void CustomQuickSortRecursiveTailInsertionHelper(std::vector<int> &a, size_t start, size_t end) {
	while (true) {
		auto part = CustomPartitionAlgorithmInsertion(a, start, end);
		if (part == 0) return;

		auto choice = (start + 1 < part) + ((part + 1 < end) << 1);

		switch (choice)
		{
		case 1:
			end = part - 1;
			break;

		case 2:
			start = part + 1;
			break;

		case 3:
			if (part - start < end - part) {
				CustomQuickSortRecursiveTailInsertionHelper(a, start, part - 1);
				start = part + 1;
			}
			else {
				CustomQuickSortRecursiveTailInsertionHelper(a, part + 1, end);
				end = part - 1;
			}
			break;

		default:
			return;
		}
	}
}

TestCustomQuickSortClass::TestCustomQuickSortClass(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "Custom QuickSort";
}

void TestCustomQuickSortClass::SortAlgorithm(std::vector<int> &a) {
	CustomQuickSortRecursiveHelper(a, 0, a.size() - 1);
}

TestCustomQuickSortTailClass::TestCustomQuickSortTailClass(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "Custom QuickSort Tail";
}

void TestCustomQuickSortTailClass::SortAlgorithm(std::vector<int> &a) {
	CustomQuickSortRecursiveHelper(a, 0, a.size() - 1);
}

TestCustomQuickSortTailInsertionClass::TestCustomQuickSortTailInsertionClass(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "Custom QuickSort Insertion Tail";
}

void TestCustomQuickSortTailInsertionClass::SortAlgorithm(std::vector<int> &a) {
	CustomQuickSortRecursiveTailInsertionHelper(a, 0, a.size() - 1);
}
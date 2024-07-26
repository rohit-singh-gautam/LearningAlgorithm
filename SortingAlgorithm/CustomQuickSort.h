#pragma once

#include "SortHelper.h"
#include "InsertionSort.h"
#include "HeapSort.h"
#include <chrono>
#include <iostream>

inline size_t CustomPartitionAlgorithm(std::vector<int> &a, size_t start, size_t end) {
	int pivot;

	auto i = start;
	auto j = end;
		
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

inline size_t CustomPartitionAlgorithmInsertion(std::vector<int> &a, size_t start, size_t end) {
	int pivot;

	if (start + 128 > end) {
		int *first = &a[start];
		int *last = &a[end]; last++;
		InsertionSort(first, last);
		return 0;
	}

	auto i = start;
	auto j = end;

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

inline void CustomQuickSortRecursiveHelper(std::vector<int> &a, const size_t start, const size_t end) {
	auto part = CustomPartitionAlgorithm(a, start, end);
	if (part == 0) return;
	if (start < part - 1) CustomQuickSortRecursiveHelper(a, start, part - 1);
	if (part + 1 < end) CustomQuickSortRecursiveHelper(a, part + 1, end);
}

inline void CustomQuickSortRecursiveHelper(std::vector<int> &a) { CustomQuickSortRecursiveHelper(a, 0, a.size() - 1); }

inline void CustomQuickSortRecursiveTailHelper(std::vector<int> &a, size_t start, size_t end) {
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
				CustomQuickSortRecursiveTailHelper(a, start, part - 1);
				start = part + 1;
			}
			else {
				CustomQuickSortRecursiveTailHelper(a, part + 1, end);
				end = part - 1;
			}
			break;

		default:
			return;
		}
	}
}

inline void CustomQuickSortRecursiveTailHelper(std::vector<int> &a) { CustomQuickSortRecursiveTailHelper(a, 0, a.size() - 1); }

inline void CustomQuickSortRecursiveTailInsertionHelper(std::vector<int> &a, size_t start, size_t end) {
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

inline void CustomQuickSortRecursiveTailInsertionHelper(std::vector<int> &a) { CustomQuickSortRecursiveTailInsertionHelper(a, 0, a.size() - 1); }

inline void CustomQuickSortRecursiveTailInsertionHeapHelper(std::vector<int> &a) {
	CreateHeap<int,testgreater<int>>(a);
	CustomQuickSortRecursiveTailInsertionHelper(a, 0, a.size() - 1);
}

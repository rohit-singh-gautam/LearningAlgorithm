#include "SortHelper.h"
#include "SortTest.h"
#include <stack>
#include <chrono>
#include <iostream>

using namespace std;


size_t PartitionAlgorithm(std::vector<int> &a, const size_t start, const size_t end) {
	auto pivot = a[start];
	auto i = start + 1;
	auto j = end;

	while (true) {
		while (i <= end && a[i] <= pivot) i++;
		while (a[j] > pivot) j--; // a[start] is val where j is going to stop anyway
		if (i >= j) break;
		swap(a[i], a[j]);
	}

	swap(a[start], a[j]);
	return j;
}

size_t PartitionAlgorithmRand(std::vector<int> &a, const size_t start, const size_t end) {
	auto rnd = (rand() % (end - start + 1)) + start;
	swap(a[start], a[rnd]);

	auto pivot = a[start];
	auto i = start + 1;
	auto j = end;

	while (true) {
		while (i <= end && a[i] <= pivot) i++;
		while (a[j] > pivot) j--; // a[start] is val where j is going to stop anyway
		if (i >= j) break;
		swap(a[i], a[j]);
	}

	swap(a[start], a[j]);
	return j;
}

size_t PartitionAlgorithm2(std::vector<int> &a, const size_t start, const size_t end) {
	const auto pivot = a[end];
	auto i = start - 1;

	for (auto j = start; j <= end - 1; j++) {
		if (a[j] < pivot) {
			i++;
			swap(a[i], a[j]);
		}
	}

	swap(a[i+1], a[end]);
	return i + 1;
}

size_t PartitionAlgorithmRand2(std::vector<int> &a, const size_t start, const size_t end) {
	auto rnd = (rand() % (end - start + 1)) + start;
	swap(a[end], a[rnd]);

	auto pivot = a[end];
	auto i = start - 1;

	for (auto j = start; j <= end - 1; j++) {
		if (a[j] < pivot) {
			i++;
			swap(a[i], a[j]);
		}
	}

	swap(a[i + 1], a[end]);
	return i + 1;
}

void QuickSortRecursiveHelper1(std::vector<int> &a, size_t start, size_t end) {

	while (true) {
		auto part = PartitionAlgorithm(a, start, end);
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
				QuickSortRecursiveHelper1(a, start, part - 1);
				start = part + 1;
			}
			else {
				QuickSortRecursiveHelper1(a, part + 1, end);
				end = part - 1;
			}
			break;

		default:
			return;
		}
	}
}

void QuickSortRecursiveHelper2(std::vector<int> &a, const size_t start, const size_t end) {
	auto part = PartitionAlgorithm2(a, start, end);

	if (start + 1 < part) QuickSortRecursiveHelper2(a, start, part - 1);
	if (part + 1 < end) QuickSortRecursiveHelper2(a, part + 1, end);
}

void QuickSortRecursiveHelperRand(std::vector<int> &a, const size_t start, const size_t end) {
	auto part = PartitionAlgorithmRand(a, start, end);

	if (start + 1 < part) QuickSortRecursiveHelperRand(a, start, part - 1);
	if (part + 1 < end) QuickSortRecursiveHelperRand(a, part + 1, end);
}

void QuickSortRecursiveHelperRand2(std::vector<int> &a, const size_t start, const size_t end) {
	auto part = PartitionAlgorithmRand2(a, start, end);

	if (start + 1 < part) QuickSortRecursiveHelperRand2(a, start, part - 1);
	if (part + 1 < end) QuickSortRecursiveHelperRand2(a, part + 1, end);
}

void QuickSortIterative(std::vector<int> &a) {
	if (a.size() <= 1) return;
	stack<pair<size_t, size_t>> st;
	st.push(make_pair(0, a.size() - 1));
	while (!st.empty()) {
		auto top = st.top(); st.pop();
		auto start = top.first; auto end = top.second;
		auto part = PartitionAlgorithm(a, start, end);
		if (start + 1 < part) st.push(make_pair(start, part - 1));
		if (part + 1 < end) st.push(make_pair(part + 1, end));
	}
}

void QuickSortIterativeRand(std::vector<int> &a) {
	if (a.size() <= 1) return;
	stack<pair<size_t, size_t>> st;
	st.push(make_pair(0, a.size() - 1));
	while (!st.empty()) {
		auto top = st.top(); st.pop();
		auto start = top.first; auto end = top.second;
		auto part = PartitionAlgorithmRand(a, start, end);
		if (start + 1 < part) st.push(make_pair(start, part - 1));
		if (part + 1 < end) st.push(make_pair(part + 1, end));
	}
}

void QuickSortIterative2(std::vector<int> &a) {
	if (a.size() <= 1) return;
	stack<pair<size_t, size_t>> st;
	st.push(make_pair(0, a.size() - 1));
	while (!st.empty()) {
		auto top = st.top(); st.pop();
		auto start = top.first; auto end = top.second;
		auto part = PartitionAlgorithm2(a, start, end);
		if (start + 1 < part) st.push(make_pair(start, part - 1));
		if (part + 1 < end) st.push(make_pair(part + 1, end));
	}
}

void QuickSortIterativeRand2(std::vector<int> &a) {
	if (a.size() <= 1) return;
	stack<pair<size_t, size_t>> st;
	st.push(make_pair(0, a.size() - 1));
	while (!st.empty()) {
		auto top = st.top(); st.pop();
		auto start = top.first; auto end = top.second;
		auto part = PartitionAlgorithmRand2(a, start, end);
		if (start + 1 < part) st.push(make_pair(start, part - 1));
		if (part + 1 < end) st.push(make_pair(part + 1, end));
	}
}

TestQuickSortClass1::TestQuickSortClass1(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "QuickSort 1";
}

void TestQuickSortClass1::SortAlgorithm(std::vector<int> &a) {
	QuickSortIterative(a);
}

TestQuickSortClass2::TestQuickSortClass2(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "QuickSort 2";
}

void TestQuickSortClass2::SortAlgorithm(std::vector<int> &a) {
	QuickSortIterative2(a);
}

TestQuickSortClassRand1::TestQuickSortClassRand1(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "QuickSort Rand 1";
}

void TestQuickSortClassRand1::SortAlgorithm(std::vector<int> &a) {
	QuickSortIterativeRand(a);
}

TestQuickSortClassRand2::TestQuickSortClassRand2(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "QuickSort Rand 2";
}

void TestQuickSortClassRand2::SortAlgorithm(std::vector<int> &a) {
	QuickSortIterativeRand2(a);
}

TestQuickSortRecursiveClass1::TestQuickSortRecursiveClass1(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "QuickSort Recursive 1";
}

void TestQuickSortRecursiveClass1::SortAlgorithm(std::vector<int> &a) {
	QuickSortRecursiveHelper1(a, 0, a.size() - 1);
}

TestQuickSortRecursiveClass2::TestQuickSortRecursiveClass2(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "QuickSort Recursive 2";
}

void TestQuickSortRecursiveClass2::SortAlgorithm(std::vector<int> &a) {
	QuickSortRecursiveHelper2(a, 0, a.size() - 1);
}

TestQuickSortRecursiveClassRand1::TestQuickSortRecursiveClassRand1(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "QuickSort Recursive Rand 1";
}

void TestQuickSortRecursiveClassRand1::SortAlgorithm(std::vector<int> &a) {
	QuickSortRecursiveHelperRand(a, 0, a.size() - 1);
}

TestQuickSortRecursiveClassRand2::TestQuickSortRecursiveClassRand2(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "QuickSort Recursive Rand 2";
}

void TestQuickSortRecursiveClassRand2::SortAlgorithm(std::vector<int> &a) {
	QuickSortRecursiveHelperRand2(a, 0, a.size() - 1);
}
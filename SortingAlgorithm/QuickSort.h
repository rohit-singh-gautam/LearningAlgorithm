#pragma once

#include "SortHelper.h"
#include "TestClassContainer.h"
#include <stack>
#include <chrono>
#include <iostream>

using namespace std;


inline size_t PartitionAlgorithm(std::vector<int> &a, const size_t start, const size_t end) {
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

inline size_t PartitionAlgorithmRand(std::vector<int> &a, const size_t start, const size_t end) {
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

inline size_t PartitionAlgorithmLeftOptimized(std::vector<int> &a, const size_t start, const size_t end) {
	const auto pivot = a[start];
	auto i = start;

	for (auto j = start + 1; j <= end; j++) {
		if (a[j] < pivot) {
			i++;
			swap(a[i], a[j]);
		}
	}

	swap(a[i], a[start]);
	return i;
}

inline size_t PartitionAlgorithmRandLeftOptimized(std::vector<int> &a, const size_t start, const size_t end) {
	auto rnd = (rand() % (end - start + 1)) + start;
	swap(a[end], a[rnd]);

	auto pivot = a[start];
	auto i = start;

	for (auto j = start; j <= end; j++) {
		if (a[j] < pivot) {
			i++;
			swap(a[i], a[j]);
		}
	}

	swap(a[i], a[start]);
	return i;
}

inline void QuickSortTailRecursiveHelper(std::vector<int> &a, size_t start, size_t end) {

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
				QuickSortTailRecursiveHelper(a, start, part - 1);
				start = part + 1;
			}
			else {
				QuickSortTailRecursiveHelper(a, part + 1, end);
				end = part - 1;
			}
			break;

		default:
			return;
		}
	}
}

inline void QuickSortTailRecursiveLeftOptimizedHelper(std::vector<int> &a, size_t start, size_t end) {

	while (true) {
		auto part = PartitionAlgorithmLeftOptimized(a, start, end);
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
				QuickSortTailRecursiveLeftOptimizedHelper(a, start, part - 1);
				start = part + 1;
			}
			else {
				QuickSortTailRecursiveLeftOptimizedHelper(a, part + 1, end);
				end = part - 1;
			}
			break;

		default:
			return;
		}
	}
}

inline void QuickSortRecursiveHelperLeftOptimized(std::vector<int> &a, const size_t start, const size_t end) {
	auto part = PartitionAlgorithmLeftOptimized(a, start, end);

	if (start + 1 < part) QuickSortRecursiveHelperLeftOptimized(a, start, part - 1);
	if (part + 1 < end) QuickSortRecursiveHelperLeftOptimized(a, part + 1, end);
}

inline void QuickSortRecursiveHelperRand(std::vector<int> &a, const size_t start, const size_t end) {
	auto part = PartitionAlgorithmRand(a, start, end);

	if (start + 1 < part) QuickSortRecursiveHelperRand(a, start, part - 1);
	if (part + 1 < end) QuickSortRecursiveHelperRand(a, part + 1, end);
}

inline void QuickSortRecursiveHelperRandLeftOptimized(std::vector<int> &a, const size_t start, const size_t end) {
	auto part = PartitionAlgorithmRandLeftOptimized(a, start, end);

	if (start + 1 < part) QuickSortRecursiveHelperRandLeftOptimized(a, start, part - 1);
	if (part + 1 < end) QuickSortRecursiveHelperRandLeftOptimized(a, part + 1, end);
}

inline void QuickSortIterative(std::vector<int> &a) {
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

inline void QuickSortIterativeRand(std::vector<int> &a) {
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

inline void QuickSortIterativeLeftOptimized(std::vector<int> &a) {
	if (a.size() <= 1) return;
	stack<pair<size_t, size_t>> st;
	st.push(make_pair(0, a.size() - 1));
	while (!st.empty()) {
		auto top = st.top(); st.pop();
		auto start = top.first; auto end = top.second;
		auto part = PartitionAlgorithmLeftOptimized(a, start, end);
		if (start + 1 < part) st.push(make_pair(start, part - 1));
		if (part + 1 < end) st.push(make_pair(part + 1, end));
	}
}

inline void QuickSortIterativeRandLeftOptimized(std::vector<int> &a) {
	if (a.size() <= 1) return;
	stack<pair<size_t, size_t>> st;
	st.push(make_pair(0, a.size() - 1));
	while (!st.empty()) {
		auto top = st.top(); st.pop();
		auto start = top.first; auto end = top.second;
		auto part = PartitionAlgorithmRandLeftOptimized(a, start, end);
		if (start + 1 < part) st.push(make_pair(start, part - 1));
		if (part + 1 < end) st.push(make_pair(part + 1, end));
	}
}

class TestQuickSortClass1 : public TestClass {
	static constexpr const std::string_view name { "QuickSort" };

public:
	TestQuickSortClass1(std::vector<std::vector<int>> &inarrays) : TestClass {inarrays, N_LogN, Iterative} { }

	const std::string_view &GetBaseName() const override { return name; }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		QuickSortIterative(a);
	}
};

class TestQuickSortClass2 : public TestClass {
	static constexpr const std::string_view name { "QuickSort" };

public:
	TestQuickSortClass2(std::vector<std::vector<int>> &inarrays) : TestClass { inarrays, N_LogN, Iterative, OptimizeLeft } { }

	const std::string_view &GetBaseName() const override { return name; }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		QuickSortIterativeLeftOptimized(a);
	}
};

class TestQuickSortClassRand1 : public TestClass {
	static constexpr const std::string_view name { "QuickSort" };

public:
	TestQuickSortClassRand1(std::vector<std::vector<int>> &inarrays) : TestClass { inarrays,  N_LogN, Iterative, Randomize } { }

	const std::string_view &GetBaseName() const override { return name; }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		QuickSortIterativeRand(a);
	}
};

class TestQuickSortClassRand2 : public TestClass {
	static constexpr const std::string_view name { "QuickSort" };

public:
	TestQuickSortClassRand2(std::vector<std::vector<int>> &inarrays) : TestClass { inarrays,  N_LogN, Iterative, Randomize, OptimizeLeft } { }

	const std::string_view &GetBaseName() const override { return name; }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		QuickSortIterativeRandLeftOptimized(a);
	}
};

class TestQuickSortRecursiveClass1 : public TestClass {
	static constexpr const std::string_view name { "QuickSort" };

public:
	TestQuickSortRecursiveClass1(std::vector<std::vector<int>> &inarrays) : TestClass { inarrays, N_LogN, TailRecursive } { }

	const std::string_view &GetBaseName() const override { return name; }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		QuickSortTailRecursiveHelper(a, 0, a.size() - 1);
	}
};


class TestQuickSortTailRecursiveLeftOptimizedClass : public TestClass {
	static constexpr const std::string_view name { "QuickSort" };

public:
	TestQuickSortTailRecursiveLeftOptimizedClass(std::vector<std::vector<int>> &inarrays) : TestClass { inarrays, N_LogN, TailRecursive, OptimizeLeft } { }

	const std::string_view &GetBaseName() const override { return name; }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		QuickSortTailRecursiveLeftOptimizedHelper(a, 0, a.size() - 1);
	}
};

class TestQuickSortRecursiveClass2 : public TestClass {
	static constexpr const std::string_view name { "QuickSort" };

public:
	TestQuickSortRecursiveClass2(std::vector<std::vector<int>> &inarrays) : TestClass { inarrays, N_LogN, Recursive, OptimizeLeft } { }

	const std::string_view &GetBaseName() const override { return name; }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		QuickSortRecursiveHelperLeftOptimized(a, 0, a.size() - 1);
	}
};

class TestQuickSortRecursiveClassRand1 : public TestClass {
	static constexpr const std::string_view name { "QuickSort" };

public:
	TestQuickSortRecursiveClassRand1(std::vector<std::vector<int>> &inarrays) : TestClass { inarrays,  N_LogN, Recursive, Randomize } { }

	const std::string_view &GetBaseName() const override { return name; }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		QuickSortRecursiveHelperRand(a, 0, a.size() - 1);
	}
};

class TestQuickSortRecursiveClassRand2 : public TestClass {
	static constexpr const std::string_view name { "QuickSort" };

public:
	TestQuickSortRecursiveClassRand2(std::vector<std::vector<int>> &inarrays) : TestClass { inarrays, N_LogN, Recursive, Randomize, OptimizeLeft } { }

	const std::string_view &GetBaseName() const override { return name; }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		QuickSortRecursiveHelperRandLeftOptimized(a, 0, a.size() - 1);
	}
};

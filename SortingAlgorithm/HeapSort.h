#include "SortHelper.h"
#include "SortTest.h"
#include <algorithm>
#include <iostream>
#include <chrono>

using namespace std;

inline size_t LeafSize(const size_t size) {
	if (size == 0) return 0;
	size_t temp = size;
	while ((temp - 1) & temp) {
		temp = (temp - 1) & temp;
	}

	return temp;
}

inline size_t ToWidth(const int val) {
	string str = ToString(val);
	return str.size();
}

inline size_t findMaxWidth(std::vector<int> &a) {
	size_t maxwidth = 0;
	for (auto &v : a) {
		size_t width = ToWidth(v);
		maxwidth = max(maxwidth, width);
	}
	return maxwidth;
}

inline void DisplayHeap(std::vector<int> &a) {
	size_t n = a.size();
	size_t width = findMaxWidth(a) + 2;
	size_t leafsize = LeafSize(n);
	size_t currwidth = width * leafsize;
	int currcount = 1;
	int i = 0;

	DisplayString(string("Heap Tree"), currwidth);
	cout << endl;
	while (i < n) {
		for (int j = 0; j < currcount && i < n; j++, i++) {
			DisplayString(a[i], currwidth);
		}
		cout << endl;
		currcount <<= 1;
		currwidth >>= 1;
	}
}



inline void Heapify(std::vector<int> &a, const size_t root, const size_t last) {
	size_t parent = root;
	int val = a[root];
	size_t leftchild = parent * 2 + 1;

	while (leftchild <= last) {
		const size_t rightchild = leftchild + 1;
		const size_t selected = leftchild == last || a[leftchild] > a[rightchild] ?
			leftchild : rightchild;
		if (val >= a[selected]) break;
		a[parent] = a[selected];
		parent = selected;
		leftchild = parent * 2 + 1;
	}

	a[parent] = val;
}

inline void CreateHeap(std::vector<int> &a) {
	size_t last = a.size() - 1;
	for (size_t i = (last / 2) + 1; i > 0; i--) {
		Heapify(a, i - 1, last);
	}
}

inline void HeapSort(std::vector<int> &a, bool bDisplayHeap) {
	size_t n = a.size();
	CreateHeap(a);
	if (bDisplayHeap) {
		Display(a, "Heap array", false);
		DisplayHeap(a);
	}
	for (size_t i = n - 1; i > 0; i--) {
		swap(a[0], a[i]);
		Heapify(a, 0, i - 1);
	}
}

inline void TestHeapSort(std::vector<vector<int>> manyarray) {
	vector<int> a{ 3, 4, 6, 9, 20, 88, 34, 5, 56, 32, 33, 83, 74, 17, 27, 7, 1, 2, 93, 31, 16, 43, 63, 68 };

	auto start = std::chrono::high_resolution_clock::now();

	/*Display(a, "Original");
	HeapSort(a);
	Display(a, "After HeapSort"); */
	for (auto arr : manyarray) {
		HeapSort(arr);
	}

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;

	std::cout << "HeapSort Elapsed time: " << elapsed.count() << " s\n";
}

class TestHeapSortClass : public TestClass {
public:
	TestHeapSortClass(std::vector<std::vector<int>> &inarrays) : TestClass { inarrays, "HeapSort" } { }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		HeapSort(a);
	}
};

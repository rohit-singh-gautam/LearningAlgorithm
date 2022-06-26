#include "pch.h"
#include "SortHelper.h"
#include "SortTest.h"

using namespace std;

vector<int> buffer;

// Merge from start to mid and mid + 1 to end

void Merge(std::vector<int> &a, const size_t start, const size_t mid, const size_t end) {
	size_t n = end - start + 1; size_t n1 = mid - start + 1; size_t n2 = end - mid;
	size_t i = 0; size_t i1 = 0; size_t i2 = 0;
	
	while (i < n && i1 < n1 && i2 < n2) {
		int val1 = a[i1 + start];
		int val2 = a[i2 + mid + 1];
		if (val1 < val2) {
			buffer[i] = val1;
			i1++;
		}
		else {
			buffer[i] = val2;
			i2++;
		}
		i++;
	}

	while (i1 < n1) {
		int val1 = a[i1 + start];
		buffer[i] = val1;
		i1++;
		i++;
	}

	while (i2 < n2) {
		int val2 = a[i2 + mid + 1];
		buffer[i] = val2;
		i2++;
		i++;
	}

	for (int i = 0; i < n; i++) {
		a[start + i] = buffer[i];
	}

	return;
}

void MergeSortHelper(std::vector<int> &a, size_t start, size_t end) {
	size_t mid = start + (end - start) / 2;
	if (start < mid) MergeSortHelper(a, start, mid);
	if (mid + 1 < end) MergeSortHelper(a, mid + 1, end);
	Merge(a, start, mid, end);
}

void MergeSort(std::vector<int> &a) {
	if (a.size() <= 1) return;
	if (buffer.size() < a.size()) {
		buffer.resize(a.size());
	}
	MergeSortHelper(a, 0, a.size() - 1);
}

TestMergeSortClass::TestMergeSortClass(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "Merge Sort";
}

void TestMergeSortClass::SortAlgorithm(std::vector<int> &a) {
	MergeSort(a);
}
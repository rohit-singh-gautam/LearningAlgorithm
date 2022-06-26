#include "pch.h"
#include "SortHelper.h"
#include "SortTest.h"

using namespace std;

void BubbleSort(std::vector<int> &a) {
	size_t n = a.size();
	bool bSorted = false;
	for (size_t i = 1; i < n && !bSorted; i++) {
		bSorted = true;
		for (size_t j = 0; j < n - i; j++) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
				bSorted = false;
			}
		}
	}
}


TestBubbleSortClass::TestBubbleSortClass(std::vector<std::vector<int>> &inarrays) : TestClass(inarrays) {
	Name = "Bubble Sort";
}

void TestBubbleSortClass::SortAlgorithm(std::vector<int> &a) {
	BubbleSort(a);
}
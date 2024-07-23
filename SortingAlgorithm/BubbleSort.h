#include "SortHelper.h"
#include "SortTest.h"

using namespace std;

inline void BubbleSort(std::vector<int> &a) {
	auto n = a.size();
	bool bSorted = false;
	for (auto i = n - 1; i >= 1 && !bSorted; --i) {
		bSorted = true;
		for (size_t j = 0; j < i; j++) {
			if (a[j + 1] < a[j]) {
				swap(a[j], a[j + 1]);
				bSorted = false;
			}
		}
	}
}


class TestBubbleSortClass : public TestClass {
public:
	TestBubbleSortClass(std::vector<std::vector<int>> &inarrays) :
		TestClass { inarrays, "Bubble Sort" } { }

private:
	void SortAlgorithm(std::vector<int> &a) override {
		BubbleSort(a);
	}
};

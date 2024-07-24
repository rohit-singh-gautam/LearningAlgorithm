#include "SortHelper.h"
#include "TestClassContainer.h"
#include "BubbleSort.h"
#include "QuickSort.h"
#include "SelectionSort.h"
#include "CustomQuickSort.h"
#include "InsertionSort.h"
#include "HeapSort.h"
#include "LibrarySort.h"
#include "MergeSort.h"
#include <iostream>
#include <sstream>
#include <random>
#include <algorithm>

using namespace std;

void SortTestAddAllQuick(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	vector<vector<int>> *manyarray2 = new vector<vector<int>>(manyarray);
	vector<vector<int>> *manyarray3 = new vector<vector<int>>(manyarray);
	vector<vector<int>> *manyarray4 = new vector<vector<int>>(manyarray);
	vector<vector<int>> *manyarray5 = new vector<vector<int>>(manyarray);
	vector<vector<int>> *manyarray6 = new vector<vector<int>>(manyarray);
	vector<vector<int>> *manyarray7 = new vector<vector<int>>(manyarray);
	vector<vector<int>> *manyarray8 = new vector<vector<int>>(manyarray);

	AllTest.push_back(new TestQuickSortClass1(*manyarray1));
	AllTest.push_back(new TestQuickSortRecursiveClass1(*manyarray2));
	AllTest.push_back(new TestQuickSortClass2(*manyarray3));
	AllTest.push_back(new TestQuickSortRecursiveClass2(*manyarray4));
	AllTest.push_back(new TestQuickSortClassRand1(*manyarray5));
	AllTest.push_back(new TestQuickSortRecursiveClassRand1(*manyarray6));
	AllTest.push_back(new TestQuickSortClassRand2(*manyarray7));
	AllTest.push_back(new TestQuickSortRecursiveClassRand2(*manyarray8));
}

void SortTestAddAllNoRandQuick(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	vector<vector<int>> *manyarray2 = new vector<vector<int>>(manyarray);
	vector<vector<int>> *manyarray3 = new vector<vector<int>>(manyarray);
	vector<vector<int>> *manyarray4 = new vector<vector<int>>(manyarray);

	AllTest.push_back(new TestQuickSortClass1(*manyarray1));
	AllTest.push_back(new TestQuickSortRecursiveClass1(*manyarray2));
	AllTest.push_back(new TestQuickSortClass2(*manyarray3));
	AllTest.push_back(new TestQuickSortRecursiveClass2(*manyarray4));
}

void SortTestAddAllQuickIterRecur(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	vector<vector<int>> *manyarray2 = new vector<vector<int>>(manyarray);

	AllTest.push_back(new TestQuickSortClass1(*manyarray1));
	AllTest.push_back(new TestQuickSortRecursiveClass1(*manyarray2));
}

void SortTestAddQuick(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	AllTest.push_back(new TestQuickSortRecursiveClass1(*manyarray1));
}

void SortTestAddCustomQuick(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	AllTest.push_back(new TestCustomQuickSortClass(*manyarray1));
}

void SortTestAddCustomQuickTail(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	AllTest.push_back(new TestCustomQuickSortTailClass(*manyarray1));
}

void SortTestAddCustomQuickTailInsertion(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	AllTest.push_back(new TestCustomQuickSortTailInsertionClass(*manyarray1));
}

void SortTestAddCustomQuickTailInsertionHeap(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	AllTest.push_back(new TestCustomQuickSortTailInsertionHeapClass(*manyarray1));
}

void SortTestAddHeap(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	AllTest.push_back(new TestHeapSortClass(*manyarray1));
}

void SortTestAddInsertion(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	AllTest.push_back(new TestInsertionSortClass(*manyarray1));
}

void SortTestAddInsertion1(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	AllTest.push_back(new TestInsertionSortClass1(*manyarray1));
}

void SortTestAddSelection(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	AllTest.push_back(new TestSelectionSortClass(*manyarray1));
}

void SortTestAddBubble(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	AllTest.push_back(new TestBubbleSortClass(*manyarray1));
}


void SortTestAddMerge(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	AllTest.push_back(new TestMergeSortClass(*manyarray1));
}

void SortTestAddLibrary(vector<vector<int>> &manyarray, vector<TestClass *> &AllTest) {
	vector<vector<int>> *manyarray1 = new vector<vector<int>>(manyarray);
	AllTest.push_back(new TestLibrarySortClass(*manyarray1));
}

void SortTestAddAllSorted(const int arraycount, const int arraysize, vector<TestClass *> &AllTest) {
	vector<vector<int>> manyarray = TestClass::GenerateManyArray(arraycount, arraysize, 0, 1000000);
	//Pre sorting:
	for (auto &arr : manyarray) {
		std::sort(arr.begin(), arr.end());
	}

	SortTestAddCustomQuick(manyarray, AllTest);
	SortTestAddQuick(manyarray, AllTest);
	SortTestAddHeap(manyarray, AllTest);
	SortTestAddMerge(manyarray, AllTest);
	SortTestAddLibrary(manyarray, AllTest);
	//SortTestAddBubble(manyarray, AllTest);
	//SortTestAddSelection(manyarray, AllTest);
	//SortTestAddInsertion(manyarray, AllTest);
}

void SortTestAddAllReverseSorted(const int arraycount, const int arraysize, vector<TestClass *> &AllTest) {
	vector<vector<int>> manyarray = TestClass::GenerateManyArray(arraycount, arraysize, 0, 1000000);
	//Pre sorting:
	for (auto &arr : manyarray) {
		std::sort(arr.begin(), arr.end(), std::greater<>());
	}

	SortTestAddCustomQuick(manyarray, AllTest);
	SortTestAddQuick(manyarray, AllTest);
	SortTestAddHeap(manyarray, AllTest);
	SortTestAddMerge(manyarray, AllTest);
	SortTestAddLibrary(manyarray, AllTest);
	//SortTestAddBubble(manyarray, AllTest);
	//SortTestAddSelection(manyarray, AllTest);
	//SortTestAddInsertion(manyarray, AllTest);
}


void SortTestAddAllInsertion(const int arraycount, const int arraysize, vector<TestClass *> &AllTest) {
	vector<vector<int>> manyarray = TestClass::GenerateManyArray(arraycount, arraysize, 0, 1000000);
	SortTestAddInsertion(manyarray, AllTest);
	SortTestAddInsertion1(manyarray, AllTest);
	SortTestAddQuick(manyarray, AllTest);
	SortTestAddCustomQuickTailInsertion(manyarray, AllTest);
	SortTestAddLibrary(manyarray, AllTest);
}


void SortTestAddAll(const int arraycount, const int arraysize, vector<TestClass *> &AllTest) {
	vector<vector<int>> manyarray = TestClass::GenerateManyArray(arraycount, arraysize, 0, 1000000);
	SortTestAddInsertion(manyarray, AllTest);
	SortTestAddCustomQuick(manyarray, AllTest);
	SortTestAddCustomQuickTail(manyarray, AllTest);
	SortTestAddCustomQuickTailInsertion(manyarray, AllTest);
	SortTestAddCustomQuickTailInsertionHeap(manyarray, AllTest);
	SortTestAddInsertion1(manyarray, AllTest);
	SortTestAddQuick(manyarray, AllTest);
	SortTestAddHeap(manyarray, AllTest);
	SortTestAddMerge(manyarray, AllTest);
	SortTestAddLibrary(manyarray, AllTest);
	// SSortTestAddBubble(manyarray, AllTest);
	// SortTestAddSelection(manyarray, AllTest);
	// SortTestAddInsertion(manyarray, AllTest);
	// SortTestAddCustomQuickTailInsertion(manyarray, AllTest);
	// SortTestAddCustomQuickTail(manyarray, AllTest);
	// SortTestAddInsertion1(manyarray, AllTest);
	// SortTestAddLibrary(manyarray, AllTest);
	// SortTestAddCustomQuick(manyarray, AllTest);
}

void SortAllTest(const int count, const int arraycount, const int arraysize) {
	cout << "Initializing ..." << endl;

	//Less important paarameter
	const int DisplayPeriod = 10;

	//Adding Test
	vector<TestClass *> AllTest;
	//SortTestAddAllInsertion(arraycount, arraysize, AllTest);
	SortTestAddAll(arraycount, arraysize, AllTest);

	cout << "Sorting ..." << endl;
	int current = 0;
	auto begin_time = std::chrono::high_resolution_clock::now();
	auto prev_time = begin_time - begin_time;
	while (current + count <= arraycount) {
		auto seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(AllTest.begin(), AllTest.end(), std::default_random_engine(seed));
		
		for (auto test : AllTest) {
			test->Sort(count);
		}
		current += count;
		auto current_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = current_time - begin_time;
		if (elapsed_time.count() - prev_time.count() > DisplayPeriod) {
			cout << "completed: " << current << " in " << elapsed_time.count() << "s" << endl;
			prev_time = elapsed_time;
		}
	}

	std::sort(AllTest.begin(), AllTest.end(),
				[](TestClass *l, TestClass *r) 
					{ return l->getElapsedTime() < r->getElapsedTime(); } );

	for (auto test : AllTest) {
		test->FindSorted();
		test->DisplayResult();
	}
}
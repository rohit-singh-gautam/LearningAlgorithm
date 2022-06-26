#include "pch.h"
#include "SortHelper.h"
#include "SortTest.h"
#include <iostream>
#include <sstream>
#include <random>
#include <algorithm>

using namespace std;

std::vector<int> GenerateRandomArray(size_t size, int min_val, int max_val) {
	vector<int> ret(size);
	for (size_t i = 0; i < size; i++) {
		int rnd = (rand() % (max_val - min_val + 1)) + min_val;
		ret[i] = rnd;
	}
	return ret;
}

std::vector<std::vector<int>> GenerateManyArray(int count, int size, int min_val, int max_val) {
	vector<vector<int>> arrays(count, vector<int>(size));
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < size; j++) {
			int rnd = (rand() % (max_val - min_val + 1)) + min_val;
			arrays[i][j] = rnd;
		}
	}
	return arrays;
}

TestClass::TestClass(std::vector<std::vector<int>> &inarrays)
	: arrays(inarrays), current(0), elapsed_time(0), InitialSortedAsc(0), InitialSortedDesc(0), SortedAfterExecutionAsc(-1), SortedAfterExecutionDesc(-1) {
	for (auto &inarray : inarrays) {
		auto srtpr = IsSorted(inarray);
		if (srtpr.first) InitialSortedAsc++;
		if (srtpr.second) InitialSortedDesc++;
	}
}

void TestClass::Sort(size_t count) {
	if (current + count > arrays.size()) return;
	begin_time = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < count; i++) {
		SortAlgorithm(arrays[current + i]);
	}

	end_time = std::chrono::high_resolution_clock::now();

	current += count;
	elapsed_time += end_time - begin_time;
}

void TestClass::FindSorted() {
	SortedAfterExecutionAsc = 0;
	SortedAfterExecutionDesc = 0;
	for (auto &array : arrays) {
		auto srtpr = IsSorted(array);
		if (srtpr.first) SortedAfterExecutionAsc++;
		if (srtpr.second) SortedAfterExecutionDesc++;
	}
}

void DisplaySorted(string pre,  size_t count, size_t Asc, size_t Desc) {
	cout << pre << " Sorted: " << count;
	cout << "(";
	if (Asc == 0 && Desc == 0) {
		cout << "unsorted";
	}
	else if (Asc > 0 && Desc > 0) {
		cout << "asc:" << Asc << ",desc:" << Desc;
	}
	else if (Asc > 0) {
		cout << "asc";
		if (Asc < count) cout << ":" << Asc;
	}
	else if (Desc > 0) {
		cout << "desc:" << Desc;
		if (Desc < count) cout << ":" << Desc;
	}
	cout << ")";
}

void TestClass::DisplayResult() const {
	cout << Name << ": " << elapsed_time.count() << " s; ";
	DisplaySorted("Initial", arrays.size(), InitialSortedAsc, InitialSortedDesc);
	cout << "; ";
	DisplaySorted("Final", arrays.size(), SortedAfterExecutionAsc, SortedAfterExecutionDesc);
	cout << endl;
}

double TestClass::getElapsedTime() const {
	return elapsed_time.count();
}

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
	vector<vector<int>> manyarray = GenerateManyArray(arraycount, arraysize, 0, 1000000);
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
	vector<vector<int>> manyarray = GenerateManyArray(arraycount, arraysize, 0, 1000000);
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
	vector<vector<int>> manyarray = GenerateManyArray(arraycount, arraysize, 0, 1000000);
	SortTestAddInsertion(manyarray, AllTest);
	SortTestAddInsertion1(manyarray, AllTest);
	SortTestAddQuick(manyarray, AllTest);
	SortTestAddCustomQuickTailInsertion(manyarray, AllTest);
	SortTestAddLibrary(manyarray, AllTest);
}


void SortTestAddAll(const int arraycount, const int arraysize, vector<TestClass *> &AllTest) {
	vector<vector<int>> manyarray = GenerateManyArray(arraycount, arraysize, 0, 1000000);
	SortTestAddInsertion(manyarray, AllTest);
	SortTestAddCustomQuick(manyarray, AllTest);
	SortTestAddCustomQuickTail(manyarray, AllTest);
	SortTestAddCustomQuickTailInsertion(manyarray, AllTest);
	SortTestAddInsertion1(manyarray, AllTest);
	SortTestAddQuick(manyarray, AllTest);
	SortTestAddHeap(manyarray, AllTest);
	SortTestAddMerge(manyarray, AllTest);
	SortTestAddLibrary(manyarray, AllTest);
	//SSortTestAddBubble(manyarray, AllTest);
	//SortTestAddSelection(manyarray, AllTest);
	SortTestAddInsertion(manyarray, AllTest);
	SortTestAddCustomQuickTailInsertion(manyarray, AllTest);
	SortTestAddCustomQuickTail(manyarray, AllTest);
	SortTestAddInsertion1(manyarray, AllTest);
	SortTestAddLibrary(manyarray, AllTest);
	SortTestAddCustomQuick(manyarray, AllTest);
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
	std::chrono::steady_clock::time_point begin_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> prev_time = begin_time - begin_time;
	while (current + count <= arraycount) {
		auto seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(AllTest.begin(), AllTest.end(), std::default_random_engine(seed));
		
		for (auto test : AllTest) {
			test->Sort(count);
		}
		current += count;
		std::chrono::steady_clock::time_point current_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed_time = current_time - begin_time;
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
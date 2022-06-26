#pragma once
#include "SortHelper.h"
#include <chrono>
#include <string>

class TestClass {
private:
	size_t current;
	std::chrono::steady_clock::time_point begin_time;
	std::chrono::steady_clock::time_point end_time;
	std::chrono::duration<double> elapsed_time;
	std::vector<std::vector<int>> &arrays;
	size_t InitialSortedAsc;
	size_t InitialSortedDesc;
	size_t SortedAfterExecutionAsc;
	size_t SortedAfterExecutionDesc;
protected:
	std::string Name;
	virtual void SortAlgorithm(std::vector<int> &a) = 0;

public:
	TestClass(std::vector<std::vector<int>> &inarrays);
	void Sort(size_t count);
	void FindSorted();
	void DisplayResult() const;
	double getElapsedTime() const;
};

class TestHeapSortClass : public TestClass {
public:
	TestHeapSortClass(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestQuickSortClass1 : public TestClass {
public:
	TestQuickSortClass1(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestQuickSortClass2 : public TestClass {
public:
	TestQuickSortClass2(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestQuickSortClassRand1 : public TestClass {
public:
	TestQuickSortClassRand1(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestQuickSortClassRand2 : public TestClass {
public:
	TestQuickSortClassRand2(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestQuickSortRecursiveClass1 : public TestClass {
public:
	TestQuickSortRecursiveClass1(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestCustomQuickSortClass : public TestClass {
public:
	TestCustomQuickSortClass(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestCustomQuickSortTailClass : public TestClass {
public:
	TestCustomQuickSortTailClass(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestCustomQuickSortTailInsertionClass : public TestClass {
public:
	TestCustomQuickSortTailInsertionClass(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestQuickSortRecursiveClass2 : public TestClass {
public:
	TestQuickSortRecursiveClass2(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestQuickSortRecursiveClassRand1 : public TestClass {
public:
	TestQuickSortRecursiveClassRand1(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestQuickSortRecursiveClassRand2 : public TestClass {
public:
	TestQuickSortRecursiveClassRand2(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestInsertionSortClass : public TestClass {
public:
	TestInsertionSortClass(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestInsertionSortClass1 : public TestClass {
public:
	TestInsertionSortClass1(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestLibrarySortClass : public TestClass {
public:
	TestLibrarySortClass(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestMergeSortClass : public TestClass {
public:
	TestMergeSortClass(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestSelectionSortClass : public TestClass {
public:
	TestSelectionSortClass(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

class TestBubbleSortClass : public TestClass {
public:
	TestBubbleSortClass(std::vector<std::vector<int>> &inarrays);

private:
	void SortAlgorithm(std::vector<int> &a) override;
};

void SortAllTest(const int count, const int arraycount, const int arraysize);

std::vector<int> GenerateRandomArray(size_t size, int min_val = 0, int max_val = INT_MAX);
std::vector<std::vector<int>> GenerateManyArray(int count, int size, int min_val = 0, int max_val = INT_MAX);
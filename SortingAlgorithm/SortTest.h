#pragma once
#include "SortHelper.h"
#include <chrono>
#include <string>
#include <limits>

class TestClass {
private:
	size_t current;
	decltype(std::chrono::high_resolution_clock::now()) begin_time;
	decltype(std::chrono::high_resolution_clock::now()) end_time;
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
	TestClass(std::vector<std::vector<int>> &inarrays, std::string Name);
	void Sort(size_t count);
	void FindSorted();
	void DisplayResult() const;
	double getElapsedTime() const;
};


void SortAllTest(const int count, const int arraycount, const int arraysize);

std::vector<int> GenerateRandomArray(size_t size, int min_val = 0, int max_val = std::numeric_limits<int>::max());
std::vector<std::vector<int>> GenerateManyArray(int count, int size, int min_val = 0, int max_val = std::numeric_limits<int>::max());
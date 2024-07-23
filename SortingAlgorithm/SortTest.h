#pragma once
#include "SortHelper.h"
#include <chrono>
#include <string>
#include <limits>
#include <vector>

class TestClass {
private:
	size_t NumberOfArraySorted;
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
	void Sort(size_t NumberOfArrayToSort);
	void FindSorted();
	void DisplayResult() const;
	double getElapsedTime() const;


	template <typename IntType = int>
	static std::vector<IntType> GenerateRandomArray(size_t size, IntType min_val, IntType max_val = std::numeric_limits<IntType>::max()) {
		std::vector<IntType> ret(size);
		for (size_t i = 0; i < size; i++) {
			IntType rnd = (rand() % (max_val - min_val + 1)) + min_val;
			ret[i] = rnd;
		}
		return ret;
	}

	template <typename IntType = int>
	static std::vector<std::vector<IntType>> GenerateManyArray(int count, int size, IntType min_val, IntType max_val = std::numeric_limits<IntType>::max()) {
		std::vector<std::vector<IntType>> arrays(count, std::vector<IntType>(size));
		for (size_t i = 0; i < count; i++) {
			for (size_t j = 0; j < size; j++) {
				IntType rnd = (rand() % (max_val - min_val + 1)) + min_val;
				arrays[i][j] = rnd;
			}
		}
		return arrays;
	}
};


void SortAllTest(const int count, const int arraycount, const int arraysize);

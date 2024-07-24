#pragma once
#include <vector>
#include <string>
#include <iostream>

std::pair<bool, bool> IsSorted(std::vector<int> &a);
void HeapSort(std::vector<int> &a, bool bDisplayHeap = false);
void CreateHeap(std::vector<int> &a);
void Heapify(std::vector<int> &a, const size_t root, const size_t last);
void InsertionSort(std::vector<int> &a, int start, int end);
void InsertionSort(int *first, int *last);

std::string ToString(const int val);

enum DisplayAlignment {
	DisplayCenter,
	DisplayLeft,
	DisplayRight
};

void DisplayString(const std::string &str, const size_t size, const DisplayAlignment alignment = DisplayCenter);
void DisplayString(const int val, const size_t size, const DisplayAlignment alignment = DisplayCenter);
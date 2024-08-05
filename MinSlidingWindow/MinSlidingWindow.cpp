// MinSlingingWindows.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <vector>
#include <deque>
#include <functional>
#include <concepts>
#include <ranges>


template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& arr) {
	auto itr = arr.begin();
	if (itr != arr.end()) {
		o << *itr++;
	}
	for (; itr != arr.end(); itr = std::next(itr)) {
		o << " " << *itr;
	}

	return o;
}

template <typename T, typename comparator = std::less<T>>
	requires std::totally_ordered<T>
void SlidingWindow(const std::vector<T> & arr, size_t windowSize) {
	if (windowSize == 0 || arr.size() < windowSize)
	{
		return;
	}

	if (windowSize == 1) {
		std::cout << arr;
	}

	std::deque<size_t> deq;
	size_t i = 0;
	for (; i < windowSize; i++) {
		auto val = arr[i];
		while (!deq.empty() && !comparator{} (arr[deq.back()], val)) {
			deq.pop_back();
		}
		deq.push_back(i);
	}

	for (; i < arr.size(); i++) {
		std::cout << arr[deq.front()] << " ";
		if (deq.front() < i - windowSize + 1) {
			deq.pop_front();
		}
		auto val = arr[i];
		while (!deq.empty() && !comparator{} (arr[deq.back()], val)) {
			deq.pop_back();
		}
		deq.push_back(i);
	}
	std::cout << arr[deq.front()];
}



template <typename T, typename comparator = std::less<T>>
	requires std::totally_ordered<T>
std::vector<T> SlidingWindow1(const std::vector<T> &arr, size_t windowSize) {
	std::vector<T> ans { };
	if (arr.size() < windowSize) { 
		auto minvalue = std::ranges::min(arr, comparator { });
		ans.push_back(minvalue);
	} else if (windowSize == 1) {
		ans.insert(std::begin(ans), std::begin(arr), std::end(arr));
	} else {
		std::deque<size_t> MinWindowQueue { };

		MinWindowQueue.push_back(0);
		size_t index { 1 };
		for(; index < windowSize; ++index) {
			if(arr[index] < arr[MinWindowQueue.front()]) {
				MinWindowQueue.front() = index;
			}
		}

		do {
			ans.push_back(arr[MinWindowQueue.front()]);
			if (MinWindowQueue.front() + windowSize <= index ) {
				MinWindowQueue.pop_front();
			}

			while(!MinWindowQueue.empty() && arr[index] <= arr[MinWindowQueue.back()]) MinWindowQueue.pop_back();
			MinWindowQueue.push_back(index++);
		} while(index < arr.size());
		ans.push_back(arr[MinWindowQueue.front()]);
	}

	return ans;
}

int main()
{
	const std::vector<std::pair<size_t, std::vector<int>>> tests = {
		{3, {4, 3, 7, 2, 9, 1, 2, 4, 7, 2}},
		{4, {4, 3, 1, 9, 1, 2, 4, 7, 2, 2}},
	};

	for (const auto& test : tests) {
		std::cout << "Array: " << test.second << std::endl;
		auto ans = SlidingWindow1(test.second, test.first);
		std::cout << "Windows (" << test.first << "): " << ans << std::endl;
	}
    return 0;
}


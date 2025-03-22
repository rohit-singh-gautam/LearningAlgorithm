// CombinationSum.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class CombinationSum {
	vector<vector<int>> ans { };
	vector<int> res { };
	vector<int> a;
	const size_t sum;
	size_t csum { 0 };

	void Calculate(size_t start) {
		if (start >= a.size()) {
			return;
		}
		res.push_back(a[start]);
		csum += a[start];
		if (csum == sum) {
			ans.push_back(res);
		}
		else if (csum < sum) {
			Calculate(start);
		}
		csum -= a[start];
		res.pop_back();

		if (csum + a[start] < sum) {
			Calculate(start + 1);
		}
	}

	void CalculateUnique(size_t start) {
		if (csum + a[start] <= sum) {
			res.push_back(a[start]);
			csum += a[start];

			if (csum == sum) {
				ans.push_back(res);
			}
			else if (start + (size_t)1 < a.size()) {
				CalculateUnique(start + 1);
			}

			csum -= a[start];
			res.pop_back();

			size_t add = 1;
			while (start + add < a.size() && a[start] == a[start + add]) add++;

			if (start + add < a.size()) {
				CalculateUnique(start + add);
			}
		}
	}

public:
	CombinationSum(const vector<int>& input, int sum) : a(input), sum(sum) {
		sort(a.begin(), a.end());
	};

	void Calculate() { Calculate(0); }
	void CalculateUnique() { CalculateUnique(0); }

	vector<vector<int>> GetAns() {
		return ans;
	}

};

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& a) {
	auto itr = a.begin();

	o << *itr;
	itr = std::next(itr);

	for (; itr != a.end(); itr = std::next(itr)) {
		o << " " << *itr;
	}

	return o;
}


template <typename T>
std::ostream& operator<<(std::ostream & o, const std::vector<std::vector<T>> & alist) {
	auto itr = alist.begin();
	if (itr == alist.end()) {
		return o << "empty";
	}

	o << '{' << *itr << '}';
	itr = std::next(itr);
	for (; itr != alist.end(); itr = std::next(itr)) {
		o << " {" << *itr << '}';
	}

	return o;
}



int main()
{
	std::vector<std::pair<std::vector<int>,int>> tests = {
		{ { 2, 3, 6, 7 }, 7 },
		{ { 2, 3, 6, 7 }, 8 },
		{ { 2, 3, 6, 7 }, 9 },
		{ { 2, 3, 6, 7 }, 10 },
		{ { 2, 3, 6, 7 }, 11 },
		{ { 2, 3, 6, 7 }, 12 },
		{ { 2, 3, 6, 7 }, 13 },
		{ { 2, 3, 6, 7 }, 14 },
		{ { 2, 3, 6, 7 }, 15 },
		{ { 2, 3, 6, 7 }, 16 },
		{ { 2, 3, 6, 7 }, 17 },
		{ { 2, 3, 6, 7 }, 18 },
		{ { 2, 3, 6, 7 }, 19 },
		{ { 10,1,2,7,6,1,5 }, 1 },
		{ { 10,1,2,7,6,1,5 }, 2 },
		{ { 10,1,2,7,6,1,5 }, 3 },
		{ { 10,1,2,7,6,1,5 }, 4 },
		{ { 10,1,2,7,6,1,5 }, 5 },
		{ { 10,1,2,7,6,1,5 }, 6 },
		{ { 10,1,2,7,6,1,5 }, 7 },
		{ { 10,1,2,7,6,1,5 }, 8 },
		{ { 10,1,2,7,6,1,5 }, 9 },
		{ { 10,1,2,7,6,1,5 }, 10 },
		{ { 10,1,2,7,6,1,5 }, 11 },
		{ { 10,1,2,7,6,1,5 }, 12 },
		{ { 10,1,2,7,6,1,5 }, 13 },
		{ { 10,1,2,7,6,1,5 }, 14 },
		{ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 5 },
	};

	for (auto &[array, sum]: tests) {
		std::cout << "Test: " << array << " Sum: " << sum << std::endl;
		CombinationSum cmbsum(array, sum);
		cmbsum.CalculateUnique();
		vector<vector<int>> ans = cmbsum.GetAns();
		std::cout << "Ans: " << ans << std::endl;
		for(const auto &oneans: ans) {
			auto total = std::accumulate(std::begin(oneans), std::end(oneans), 0);
			if (total != sum) {
				std::cout << "Failed for Array: " << oneans << "; got: " << total << ", expected: " << sum << std::endl;
				return 0;
			}
		}
	}

    return 0;
}


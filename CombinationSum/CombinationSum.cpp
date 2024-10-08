// CombinationSum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class CombinationSum {
	vector<vector<int>> ans;
	vector<int> res;
	vector<int> a;
	const size_t sum;
	size_t csum = 0;
public:
	CombinationSum(const vector<int>& input, int sum) : a(input), sum(sum) {
		sort(a.begin(), a.end());
	};

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

		if (csum + a[start] < sum)
			Calculate(start + 1);
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
	vector<int> a = { 2, 3, 6, 7 };
	vector<int> b = { 10,1,2,7,6,1,5 };
	int sum = 7;
	int sumb = 8;

	std::cout << "Sum: " << sumb << "; Array: " << b << std::endl;
	CombinationSum cmbsum(b, sumb);

	cmbsum.CalculateUnique(0);

	vector<vector<int>> ans = cmbsum.GetAns();

	std::cout << "Ans: " << ans << std::endl;

    return 0;
}


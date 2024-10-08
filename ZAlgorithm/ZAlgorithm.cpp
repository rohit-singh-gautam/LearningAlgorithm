// ZAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

vector<int> ZAlgorithm(string hay, string needle) {
	string tosearch = needle + '$' + hay;
	int size = tosearch.size();
	vector<int> zcnt(size);
	zcnt[0] = 0;

	int left = 0;
	int right = 0;

	for(int k = 1; k < size; k++) {
		if (k > right) {
			left = right = k;
			while (right <= size && tosearch[right] == tosearch[right - left]) {
				right++;
			}
			zcnt[k] = right - left;
			right--;
		}
		else {
			int k1 = k - left;
			if (zcnt[k1] < right - k + 1) {
				zcnt[k] = zcnt[k1];
			}
			else {
				left = k;
				while (right <= size && tosearch[right] == tosearch[right - left]) {
					right++;
				}
				zcnt[k] = right - left;
				right--;
			}
		}
	}

	vector<int> ans;
	for (int i = needle.size()+1; i < size; i++) {
		if (zcnt[i] >= needle.size()) {
			ans.push_back(i - needle.size() - 1);
		}
	}

	return ans;
}


int main()
{
	string needle = "abcabcx";
	string hay = "asabcabcxstneababcacdabcabcx";

	vector<int> ans = ZAlgorithm(hay, needle);

	for (int &v : ans) {
		string temp = hay.substr(v, needle.size());
		cout << temp << endl;
	}

    return 0;
}


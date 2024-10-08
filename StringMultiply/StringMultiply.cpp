// StringMultiply.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

string MultipleString(string s1, string s2) {
	int n1 = s1.size();
	int n2 = s2.size();
	if (!n1 || !n2) return "0";
	vector<int> res(n1 + n2);
	int carrier;

	for (int i1 = n1 - 1; i1 >= 0; i1--) {
		int m1 = s1[i1] - '0';
		carrier = 0;

		for (int i2 = n2 - 1; i2 >= 0; i2--) {
			int m2 = s2[i2] - '0';
			int indx = n1 + n2 - i1 - i2 - 2;

			int sum = res[indx] + m1 * m2 + carrier;

			res[indx] = sum % 10;
			carrier = sum / 10;
		}

		if (carrier) {
			res[n1 + n2 - i1 - 1] = carrier;
		}
	}

	int i = n1 + n2 - 1;
	while (i > 0 && !res[i]) i--;

	string s = "";
	while (i >= 0) s += res[i--] + '0';

	return s;
}

int main()
{
	string s1 = "55";
	string s2 = "60";

	string ans = MultipleString(s1, s2);

	cout << ans;

    return 0;
}


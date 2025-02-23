// StringMultiply.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>

std::string MultipleString(std::string s1, std::string s2) {
	auto n1 = s1.size();
	auto n2 = s2.size();
	if (!n1 || !n2) return "0";
	std::vector<char> res(n1 + n2);
	size_t carrier;

	for (auto i1 = n1; i1 > 0; i1--) {
		int m1 = s1[i1 - 1] - '0';
		carrier = 0;

		for (auto i2 = n2; i2 > 0; i2--) {
			auto m2 = s2[i2 - 1] - '0';
			auto indx = n1 + n2 - i1 - i2;

			auto sum = res[indx] + m1 * m2 + carrier;

			res[indx] = sum % 10;
			carrier = sum / 10;
		}

		if (carrier) {
			res[n1 + n2 - i1] = static_cast<char>(carrier);
		}
	}

	auto i = n1 + n2;
	while (i > 1 && !res[i - 1]) i--;

	std::string s = "";
	while (i > 0) s += res[--i] + '0';

	return s;
}

auto test(const std::string &s1, const std::string &s2) {
	auto val1 = std::stoll(s1);
	auto val2 = std::stoll(s2);
	std::string ans = MultipleString(s1, s2);
	auto valans = std::stoll(ans);

	std::cout << "s1: " << s1 << " * s2: " << s2 << " = " << ans << " Expected: " << valans << std::endl;

	return val1 * val2 == valans;
}

int main()
{
	const std::vector<std::pair<std::string, std::string>> testlist {
		{"55", "60"},
		{"1", "2"},
		{"0", "0"},
		{"0", "1"},
		{"1", "0"},
		{"1", "1"},
		{"22", "99"},
		{"33", "88"},
		{"9999999", "9999999"},
		{"999999999", "999999999"},
	};


	for(const auto &[s1, s2]: testlist) {
		auto result = test(s1, s2);
		if (!result) {
			std::cout << "Test failed for s1: " << s1 << ", s2: " << s2 << std::endl;
			break;
		}
	}

    return 0;
}


#include <iostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& arr) {
	const auto len = arr.size();
	size_t index = 0;
	for (; index < len - 1; index++) {
		o << arr[index] << " ";
	}

	o << arr.back();
	return o;
}

bool findmatch(const std::string &text, const std::string &wld) {
	size_t n = text.size();
	size_t m = wld.size();
	std::vector<std::vector<bool>> seq(n+1, std::vector<bool>(m+1, false));

	seq[0][0] = true;
	for (size_t i = 1; i <= m; i++) {
		if (wld[i - 1] == '*') {
			seq[0][i] = seq[0][i - 1];
		}
		else {
			break;
		}
	}

	for (size_t i = 1; i <= n; i++) {
		for (size_t j = 1; j <= m; j++) {
			if (text[i - 1] == wld[j - 1] || wld[j - 1] == '.') {
				seq[i][j] = seq[i - 1][j - 1];
			}
			else if (wld[j - 1] == '*') {
				seq[i][j] = seq[i - 1][j] || seq[i][j - 1];
			}
		}
	}
	
	return seq[n][m];
}

bool findmatchrecursive(const std::string &text, const std::string &wld, int textindex, int wldindex) {
	if (textindex == -1 || wldindex == -1) return textindex == -1 && wldindex == -1;
	if (wld[wldindex] == '.') return findmatchrecursive(text, wld, textindex - 1, wldindex - 1);
	if (wld[wldindex] == '*') return findmatchrecursive(text, wld, textindex - 1, wldindex) || findmatchrecursive(text, wld, textindex - 1, wldindex - 1);
	if (text[textindex] == wld[wldindex]) return findmatchrecursive(text, wld, textindex - 1, wldindex - 1);
	return false;
}

bool findmatchrecursive(const std::string &text, const std::string &wld) {
	return findmatchrecursive(text, wld, text.size() - 1, wld.size() - 1);
}


//NOT WORKING
bool findmatchfast(const std::string &text, const std::string &wld) {
	const size_t n = text.size();
	const size_t m = wld.size();

	size_t start = -1;

	size_t i = 0;
	size_t j = 0;

	while(j < n) {
		const char &v = text[j];
		if (wld[i] == '.' || wld[i] == v) {
			i++;
			j++;
		}
		else if (wld[i] == '*') {
			if (i == m - 1) {
				return true;
			}
			i++;
			start = i;
		}
		else if (start == -1) {
			return false;
		}
		else {
			i = start;
			j++;
		}
	}

	return i == m;
}



int main()
{
	const std::vector < std::pair<std::string, std::vector<std::string>>> tests = {
		{"This is a test for Apoorv Rohit Singh", {"*t.st*", "*ohit", "*ohit*"}},
		{"This is a test for abcabcd Apoorv Rohit Singh", {"*abcd*", "*ohit", "*ohit*"}}
	};

	for (const auto& test : tests) {
		std::cout << "TEXT: " << test.first << std::endl;

		for (const auto& srch : test.second) {
			const auto ret = findmatchrecursive(test.first, srch) ? "true" : "false";
			const auto ret1 = findmatch(test.first, srch) ? "true" : "false";
			std::cout << "\tRESULT: Recursive: " << ret << ", Iterative: " << ret1 << "; SEARCH: " << srch << std::endl;
		}

		std::cout << std::endl;
	}
	
    return 0;
}


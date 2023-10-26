#include <iostream>
#include <vector>

namespace algo {
void print_arr(const std::vector<int>& v, int start_idx=0, int adjustment=0) {
	for (size_t i = start_idx; i < v.size(); ++i) {
		std::cout << v[i] + adjustment << ' ';
	}
	std::cout << '\n';
}

std::vector<int> zfunc(std::string& s) {
	std::vector<int> z(s.size(), 0);

	// Maintain precalculated part of zfunc array
	int l = 0;
	int r = 0;

	for (int i = 0; i < (int)s.size(); ++i) {
		// we have big repeated prefix with len (r-l)
		// and if we now that suffix of (r-l) string also
		// repeats in the beginning of the string so we can start
		// calculating with it's len of prefix (r-l) prefix.
		z[i] = std::max(0, std::min(r - i, z[i - l]));

		while (i + z[i] < (int)s.size() && s[i + z[i]] == s[z[i]]) {
			++z[i];
		}

		if (i + z[i] > r) {
			l = i;
			r = i + z[i];
		}
	}

	return z;
}
};


int main() {
	std::string str("abacaba");
	std::vector<int> ans = algo::zfunc(str);

	algo::print_arr(ans);

	return 0;
}
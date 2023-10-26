#include <iostream>
#include <vector>

namespace algo {
void print_arr(const std::vector<int>& v, int start_idx=0, int adjustment=0) {
	for (size_t i = start_idx; i < v.size(); ++i) {
		std::cout << v[i] + adjustment << ' ';
	}
	std::cout << '\n';
}

std::vector<int> pfunc(std::string& s) {
	std::vector<int> p(s.size(), 0);

	p[0] = 0;
	for (int i = 1; i < (int)s.size(); ++i) {
		int j = p[i - 1];

		while (j > 0 && s[j] != s[i]) {
			j = p[j - 1];
		}

		if (s[j] == s[i]) {
			++j;
		}

		p[i] = j;
	}

	return p;
}
};

int main() {
	std::string str("abacaba");
	std::vector<int> ans = algo::pfunc(str);

	algo::print_arr(ans);
	
	return 0;
}
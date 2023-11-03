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

int kpm(std::string p, std::string t) {
	std::string s = p + "#" + t;

	std::vector<int> pfunc_arr = pfunc(s);
	for (int i = 0; i < (int)pfunc_arr.size(); ++i) {
		if (pfunc_arr[i] == p.size()) {
			return i;
		}
	}

	print_arr(pfunc_arr);

	return -1;
}

};

int main() {
	std::string str("l;jl;kjlkoMishajlkjl;jl;j");
	int ans = algo::kpm(std::string("Misha"), str);
	std::cout << ans << '\n';

	return 0;
}
#include <iostream>

#include <vector>

namespace algo {
void print_arr(const std::vector<int>& v, int start_idx=0, int adjustment=0) {
	for (size_t i = start_idx; i < v.size(); ++i) {
		std::cout << v[i] + adjustment << ' ';
	}
	std::cout << '\n';
}

static constexpr size_t kCapacity = 1000;

std::vector<int> count_sort(std::vector<int>& v) {
	std::vector<int> ans(v.size(), 0);
	std::vector<int> shuffle(kCapacity);

	for (int i = 0; i < (int)v.size(); ++i) {
		++shuffle[v[i]];
	}
	for (int i = 1; i < kCapacity; ++i) {
		shuffle[i] += shuffle[i - 1];
	}
	for (int i = 0; i < (int)v.size(); ++i) {
		--shuffle[v[i]];
		ans[shuffle[v[i]]] = v[i];
	}

	return ans;
}

};

int main() {
	std::vector<int> to_sort({9,2,5,1,4,8,8,7,6});
	std::vector<int> ans = algo::count_sort(to_sort);

	algo::print_arr(ans);

	return 0;
}
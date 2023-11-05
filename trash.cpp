#include <iostream>
#include <limits>

#include <vector>

namespace algo {
void print_arr(const std::vector<int>& v, int start_idx=0, int adjustment=0) {
	for (size_t i = start_idx; i < v.size(); ++i) {
		std::cout << v[i] + adjustment << ' ';
	}
	std::cout << '\n';
}

static constexpr int kCapacity = 10;

int maxPowCap(std::vector<int>& v) {
	int max_num = std::numeric_limits<int>::min();
	for (auto num : v) {
		max_num = std::max(num, max_num);
	}
	int pow = 1;
	while (pow <= max_num) {
		pow *= kCapacity;
	}
	return pow / kCapacity;
}

std::vector<int> radix_sort(std::vector<int>& v) {
	std::vector<int> res(v);
	int max_pow = maxPowCap(v);

	std::vector<int> shuffle[kCapacity];
	int cur_pow = 1;
	while (cur_pow <= max_pow) {
		for (int i = 0; i < (int)res.size(); ++i) {
			shuffle[(res[i] / cur_pow) % kCapacity].push_back(res[i]);
		}
		int k = 0;
		for (int i = 0; i < kCapacity; ++i) {
			for (int j = 0; j < (int)shuffle[i].size(); ++j) {
				res[k++] = shuffle[i][j];
			}
			shuffle[i].clear();
		}
		cur_pow *= kCapacity;
	}

	return res;
}
};

int main() {
	std::vector<int> to_sort({29, 24, 121, 1016, 18});
	std::vector<int> sorted = algo::radix_sort(to_sort);
	algo::print_arr(sorted);

	return 0;
}
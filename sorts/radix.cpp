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
	for (int i = 0; i < (int)v.size(); ++i) {
		max_num = std::max(max_num, v[i]);
	}

	int ten_pow = 1;
	while (ten_pow < max_num) {
		ten_pow *= kCapacity;
	}
	return ten_pow / kCapacity;
}

std::vector<int> radix_sort(std::vector<int>& v) {
	std::vector<int> sorted(v.begin(), v.end());

	std::vector<int> shuffle[kCapacity];
	for (int i = 0; i < (int)sorted.size(); ++i) {
		shuffle[sorted[i] % kCapacity].push_back(sorted[i]);
	}
	int k = 0;
	for (int i = 0; i < kCapacity; ++i) {
		for (int j = 0; j < (int)shuffle[i].size(); ++j) {
			sorted[k++] = shuffle[i][j];
		}
		shuffle[i].clear();
	}

	print_arr(sorted);

	int pow = maxPowCap(v);
	int cur_pow = kCapacity;
	while (cur_pow <= pow) {
		for (int i = 0; i < (int)sorted.size(); ++i) {
			shuffle[(sorted[i] / cur_pow) % kCapacity].push_back(sorted[i]);
		}
		int k = 0;
		for (int i = 0; i < kCapacity; ++i) {
			for (int j = 0; j < (int)shuffle[i].size(); ++j) {
				sorted[k++] = shuffle[i][j];
			}
			shuffle[i].clear();
		}
		print_arr(sorted);
		cur_pow *= kCapacity;
	}

	return sorted;
}

};

int main() {
	std::vector<int> to_sort({29, 121, 1016, 18});
	std::vector<int> sorted = algo::radix_sort(to_sort);

	algo::print_arr(sorted);

	return 0;
}
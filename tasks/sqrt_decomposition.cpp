/*
дан массив размера nn целых чисел от 11 до nn,
и требуется отвечать на qq заранее известных запросов:
количество различных чисел на отрезке [l_i, r_i]
*/
#include <iostream>

#include <vector>
#include <cmath>

namespace algo {
struct pair {
	pair(int a, int b) : first(a), second(b) {}

	int first{0};
	int second{0};
};

void print_arr(const std::vector<int>& v, int start_idx=0, int adjustment=0) {
	for (size_t i = start_idx; i < v.size(); ++i) {
		std::cout << v[i] + adjustment << ' ';
	}
	std::cout << '\n';
}

int sqrt_decomposition(std::vector<int>& v, std::vector<pair>& q) {
	int k = (int)std::ceil(sqrt((float)v.size()));
	std::vector<int> blocks(k, 0);

	int blck_sz = (int)std::floor(sqrt((float)v.size()));

	int cur_sum = 0;
	int idx = -1;
	for (int i = 0; i < (int)v.size(); ++i) {
		if (i % blck_sz == 0) {
			++idx;
		}
		blocks[idx] += v[i];
	}

	print_arr(blocks);
	print_arr(v);

	int res = 0;
	for (int i = (int)std::ceil((float)q[0].first / blck_sz); i < (int)std::floor((float)q[0].second / blck_sz); ++i) {
		res += blocks[i];
	}
	for (int i = q[0].first; i % blck_sz != 0; ++i) {
		res += v[i];
	}
	for (int i = (int)std::floor((float)q[0].second / blck_sz) * blck_sz; i < q[0].second; ++i) {
		res += v[i];
	}

	int sum = 0;
	for (int i = q[0].first; i < q[0].second; ++i){
		sum += v[i];
	}
	std::cout << sum << '\n';

	return res;
}

};

int main() {
	std::vector<int> arr({1,2,3,4,5,6,7,8,9,18,2});
	std::vector<algo::pair> q(1, algo::pair(0, 6));

	int res = sqrt_decomposition(arr, q);
	std::cout << res << '\n';

	return 0;
}

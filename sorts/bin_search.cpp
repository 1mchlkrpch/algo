#include <iostream>

#include <vector>

namespace algo {

static constexpr int kNotFound = -1;

int bin_search(std::vector<int>& nums, int target) {
	int l = 0;
	int r = (int)nums.size() - 1;

	while (l < r) {
		int m = (l + r) / 2;

		if (nums[m] == target) {
			return m;
		}

		if (nums[m] > target) {
			r = m - 1;
		}

		if (nums[m] < target) {
			l = m + 1;
		}
	}

	return (target == nums[(l + r) / 2])? (l + r) / 2 : kNotFound;
}

};

int main() {
	std::vector<int> v({1,2,3,4,5,6,7,8,9});
	int pos = algo::bin_search(v, 16);

	std::cout << pos << '\n';

	return 0;
}
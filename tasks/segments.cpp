/*
Дан набор из nn отрезков на прямой,
заданных координатами начал и концов [l_i, r_i].
Требуется найти любую точку на прямой,
покрытую наибольшим количеством отрезков.
 */
/*
3
1 5
2 7
9 11
2

4
0 5
2 7
3 4
9 11
3

4
1 5
2 7
3 4
9 11
*/

#include <iostream>
#include <limits>

#include <algorithm>

#include <vector>

struct pair {
	pair(int a, int b) : first(a), second(b) {}

	int first{0};
	int second{0};
};

int scanline(std::vector<pair>& s) {
	std::vector<pair> events;
	for (int i = 0; i < (int)s.size(); ++i) {
		events.push_back(pair(s[i].first,   1));
		events.push_back(pair(s[i].second, -1));
	}

	std::sort(events.begin(), events.end(), [](pair& a, pair& b){
		return a.first < b.first;
	});

	int cnt = 0;
	int res = std::numeric_limits<int>::min();

	for (int i = 0; i < (int)events.size(); ++i) {
		cnt += events[i].second;
		res = std::max(res, cnt);
	}

	return res;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n_segms = 0;
	std::cin >> n_segms;

	std::vector<pair> segments;
	for (int i = 0; i < n_segms; ++i) {
		pair p(0,0);
		std::cin >> p.first >> p.second;
		segments.push_back(p);
	}

	int pos = scanline(segments);
	std::cout << pos << '\n';

	return 0;
}
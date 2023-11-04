/*
Есть два принтера.
Один печатает лист раз в x минут,
другой раз в yy минут.
За сколько минут они напечатают nn листов?
*/

#include <iostream>

/*
60 10 6
*/

namespace algo {

bool check(int t, int x, int y, int n) {
	return (
		(int)(
			  (float)t / x
			+ (float)t / y
		) >= n);
}

int solve(int n, int x, int y) {
	int l = 1;
	int r = x * n;

	while (r - l > 1) {
		int m = (l + r) / 2;
		if (check(m, x, y, n)) {
			r = m;
		} else {
			l = m;
		}
	}

	return r;
}

};

int main() {
	int n = 0;
	int x = 0;
	int y = 0;

	std::cin >> n >> x >> y;

	int ans = algo::solve(n, x, y);
	std::cout << ans << '\n';

	return 0;
}
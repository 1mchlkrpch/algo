#include <iostream>

#include <vector>

namespace algo {

void print_arr(const std::vector<int>& v, int start_idx=0, int adjustment=0) {
	for (size_t i = start_idx; i < v.size(); ++i) {
		std::cout << v[i] + adjustment << ' ';
	}
	std::cout << '\n';
}

template <typename Tp, size_t N, int (*Cmp)(Tp&, Tp&)>
class dheap {
	static const int kNotFound = -1;
	
	static const int kLess    = -1;
	static const int kEqual   =  0;
	static const int kGreater =  1;

 public:
	dheap(std::vector<Tp>& v) : data_(v) {
		static_assert(N > 1);
		heapify();
		hsort();

		print_arr(data_);
		debug();
	}

	void hsort() {
		std::vector<Tp> ans(data_.size(), 0);
		int sz = (int)data_.size();

		for (int i = 0; i < sz; ++i) {
			std::swap(data_[0], data_[data_.size() - 1]);
			ans[i] = data_[data_.size() - 1];
			data_.pop_back();
			sift_down(0);
		}

		std::swap(data_, ans);
	}

	void insert(Tp& el) {
		if (find(el) == kNotFound) {
			data_.push_back(el);
			sift_up();
		}
	}

	void heapify() {
		for (int i = 0; i < (int)data_.size(); ++i) {
			sift_up(i);
		}
	}

	void sift_up(int idx = -1) {
		if (idx == -1) {
			idx = (int)data_.size() - 1;
		}

		while (idx != 0 && Ls(data_[(idx - 1) / N], data_[idx])) {
			std::swap(data_[(idx - 1) / N], data_[idx]);
			idx = (idx - 1) / N;
		}
	}

	void sift_down(int idx = 0) {
		while (true) {
			int lrg_child_idx = idx;

			for (int ch = 1; ch <= (int)N; ++ch) {
				int child_idx = idx * (int)N + ch;

				if (child_idx >= (int)data_.size()) {
					break;
				}

				if (Ls(data_[lrg_child_idx], data_[child_idx])) {
					lrg_child_idx = child_idx;
				}
			}

			if (lrg_child_idx == idx) {
				break;
			}

			std::swap(data_[idx], data_[lrg_child_idx]);
			idx = lrg_child_idx;
		}
	}

	int find(Tp& el, int idx = 0) {
		if (data_.size() == 0 || Gr(el, data_[idx])) {
			return kNotFound;
		}
		if (Eq(el, data_[idx])) {
			return idx;
		}

		int res = kNotFound;
		for (int i = 1; i <= (int)N; ++i) {
			int child_idx = idx * N + i;
			if (child_idx >= (int)data_.size()) {
				break;
			}
			res = find(el, child_idx);
			if (res != kNotFound) {
				break;
			}
		}
		return res;
	}

	void debug() {
		FILE *f = fopen("graph.dot", "w");
		fprintf(f, "digraph G {\n");

		for (int i = 0; i < (int)data_.size(); ++i) {
			for (int ch = 1; ch <= (int)N; ++ch) {
				if (i * (int)N + ch < (int)data_.size()) {
					fprintf(f, "\t%d->%d\n", data_[i], data_[i * N + ch]);
				}
			}
		}

		fprintf(f, "}\n");

		fclose(f);
		system("dot -Tpng graph.dot -o graph.png");
	}

	bool Gr(Tp& a, Tp& b) { return Cmp(a,b) == kGreater; }
	bool Eq(Tp& a, Tp& b) { return Cmp(a,b) == kEqual; }
	bool Ls(Tp& a, Tp& b) { return Cmp(a,b) == kLess; }

 private:
	std::vector<Tp> data_{};
	int sz_{0};
};

};

int cmp(int& a, int& b) {
	if (a > b) {
		return 1;
	}
	return (a == b)? 0 : -1;
}

static constexpr size_t kCapacity = 17;

int main() {
	std::vector<int> data;
	std::vector<int> v;
	for (size_t i = 1; i < kCapacity; ++i) {
		data.push_back(i * 3237 % kCapacity);
	}

	algo::dheap<int,3,cmp> dh(data);

	dh.debug();

	return 0;
}
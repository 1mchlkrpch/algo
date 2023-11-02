#include <iostream>
#include <limits>

#include <vector>

namespace algo {

class graph {
 public:
	graph(std::vector<std::vector<int>>& tr, int n_vtx)
			: mtx_(n_vtx, std::vector<int>(n_vtx, -1)) {
		for (int i = 0; i < (int)tr.size(); ++i) {
			mtx_[tr[i][0]][tr[i][1]] = tr[i][2];
		}
	}

	void debug() {
		FILE *f = fopen("graph.dot", "w");

		fprintf(f, "digraph G {\n");
		for (int i = 0; i < (int)mtx_.size(); ++i) {
			for (int j = 0; j < (int)mtx_[0].size(); ++j) {
				if (mtx_[i][j] != -1) {
					fprintf(f, "\t%d->%d [label=%d]\n", i, j, mtx_[i][j]);
				}
			}
		}
		fprintf(f, "}\n");
		fclose(f);
		system("dot -Tpng graph.dot -o graph.png");
	}

	std::vector<int> dijkstra(int start_idx) {
		int sz = (int)mtx_.size();

		std::vector<bool> used(sz, false);
		std::vector<int> d(sz, std::numeric_limits<int>::max());
		d[start_idx] = 0;

		for (int i = 0; i < sz; ++i) {
			int v = -1;
			for (int u = 0; u < sz; ++u) {
				if (!used[u] && (v == -1 || d[u] < d[v])) {
					v = u;
				}
			}

			used[v] = true;
			for (int j = 0; j < sz; ++j) {
				if (mtx_[v][j] != -1) {
					d[j] = std::min(d[j], d[v] + mtx_[v][j]);
				}
			}
		}

		return d;
	}

	void print() {
		for (int i = 0; i < (int)mtx_.size(); ++i) {
			for (int j = 0; j < (int)mtx_.size(); ++j) {
				printf("%d ", mtx_[i][j]);
			}
			printf("\n");
		}
	}

 private:
 	std::vector<std::vector<int>> mtx_{};
};

void print_arr(const std::vector<int>& v, int start_idx=0, int adjustment=0) {
	for (size_t i = start_idx; i < v.size(); ++i) {
		std::cout << v[i] + adjustment << ' ';
	}
	std::cout << '\n';
}

};

int main() {
	std::vector<std::vector<int>> tr = {
		{0, 1, 7},
		{0, 2, 8},
		{0, 3, 9},
		{1, 4, 10},
		{3, 4, 1}
	};

	algo::graph g(tr, 5);
	g.debug();

	std::vector<int> d = g.dijkstra(0);

	algo::print_arr(d);

	return 0;
}
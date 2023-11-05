#include <iostream>
#include <memory>

#include <queue>
#include <vector>

namespace algo {

struct pair {
	pair(int a, int b) : first(a), second(b) {}
	
	int first{0};
	int second{0};
};

class ahocorasick {
	static constexpr int  kAlphCap   =  26;
	static constexpr char kFirstChar = 'a';
 public:
	struct node {
		node(int v=-1)
			: val(v), ch(std::vector<node*>(kAlphCap, nullptr)),
			  to(kAlphCap, nullptr), link(nullptr) {}
		int val{-1};

		std::vector<int> palindrome_indexes{};

		uint64_t id{};
		std::vector<node*> ch;

		node *link{nullptr};
		std::vector<node*> to{};

		node *transition(int i) {
		  return (ch[i] != nullptr) ? ch[i] : to[i];
		}
	};

	node *root_{nullptr};
	int sz_{0};

 public:
	ahocorasick() : root_(new node()), sz_(0) { root_->id = (uint64_t)root_; }
	void insert(std::string& s) {
		node *n = root_;
		for (int i = 0; i < (int)s.size(); ++i) {
			if (n->ch[s[i] - kFirstChar] == nullptr) {
				n->ch[s[i] - kFirstChar] = new node();
				n->ch[s[i] - kFirstChar]->id = (uint64_t)n->ch[s[i] - kFirstChar];
			}
			n = n->ch[s[i] - kFirstChar];
		}
		n->val = sz_++;
	}
	void debug() {
		FILE *f = fopen("graph.dot", "w");
		fprintf(f, "digraph G{\n");
		std::queue<node*> q;
		q.push(root_);
		fprintf(f, "\t%ld[shape=circle label=_]\n",
			root_->id);
		while (!q.empty()) {
			node *n = q.front();
			q.pop();
			for (int i = 0; i < kAlphCap; ++i) {
				node *child = n->ch[i];
				if (child != nullptr) {
					if (child->val != -1) {
						fprintf(f, "\t%ld[shape=circle color=red label=%d]\n",
							child->id, child->val);
					} else {
						fprintf(f, "\t%ld[shape=circle label=_]\n",
							child->id);
					}
					fprintf(f, "\t%ld->%ld [label=%c]\n",
						n->id, child->id, kFirstChar + i);
					q.push(child);
				}
			}
			if (n->link != nullptr && n != root_) {
				fprintf(f, "\t%ld->%ld [color=green]\n",
					n->id, n->link->id);
			}
		}
		fprintf(f, "}\n");
		fclose(f);
		system("dot -Tpng graph.dot -o graph.png");
	}
	node *get_root() { return root_; }

	void recalc() {
		recalc_root();

		std::queue<node*> q;
		q.push(get_root());

		while (!q.empty()) {
			node *v = q.front();
			q.pop();

			for (int i = 0; i < kAlphCap; ++i) {
				if (v->ch[i] != nullptr) {
					auto child = v->ch[i];
					child->link = (v == root_) ? root_ : v->link->transition(i);
					
					for (int j = 0; j < kAlphCap; ++j) {
						if (child->ch[j] != nullptr) {
							child->to[j] = child->link->transition(j);
						}
					}
					q.push(child);
				}
			}
		}
	}

	void recalc_root() {
		if (root_ == nullptr) {
			return;
		}
		root_->link = root_;
		for (int i = 0; i < kAlphCap; ++i) {
			if (root_->ch[i] == nullptr) {
				get_root()->to[i] = root_;
			}
		}
	}
};

};

int main() {
	int n_seq = 0;
	std::cin >> n_seq;
	std::string s;

	algo::ahocorasick ac;
	for (int i = 0; i < n_seq; ++i) {
		std::cin >> s;
		ac.insert(s);
	}
	ac.recalc();
	ac.debug();

	return 0;
}
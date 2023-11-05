#include <iostream>
#include <algorithm>
#include <memory>

#include <vector>
#include <queue>

namespace algo {

void print_arr(const std::vector<bool>& v, int start_idx=0, int adjustment=0) {
	for (size_t i = start_idx; i < v.size(); ++i) {
		std::cout << v[i] + adjustment << ' ';
	}
	std::cout << '\n';
}

std::vector<int> zfunc(std::string& s) {
	std::vector<int> z(s.size(), 0);
	int l = 0;
	int r = 0;
	int sz = (int)s.size();
	for (int i = 0; i < sz; ++i) {
		z[i] = std::max(0, std::min(z[i - l], r - i));
		while (z[i] + i < sz && s[z[i]] == s[i + z[i]]) {
			++z[i];
		}
		if (r < z[i] + i) {
			r = z[i] + i;
			l = i;
		}
	}
	return z;
}

// returns vector of bools
// ans[i] = true if s[i:sz] can to be a center of palindrome.
// for ex: abbaa : abb|aa|, "aa" is also palindrome so we  write "bba" after "abbaa" for example
// also abba|a|, "a" is also palindrome, we can write "abba" after "abbaa" to get palindrome.
std::vector<bool> sfunc(std::string s, char delimiter='#') {
	std::vector<bool> ans(s.size(), false);

	std::string combined = s;
	std::reverse(combined.begin(), combined.end());

	combined += delimiter;
	combined += s;

	int sz = (int)s.size();
	std::vector<int> z = zfunc(combined);
	for (int i = 0; i < sz; ++i) {
		if (z[sz + 1 + i] >= sz - i - 1) {
			ans[i] = true;
		}
	}

	return ans;
}

static constexpr int kAlphCap = 26;
static constexpr char kFirstChar = 'a';

struct node {
	node(int v=-1) : val(v), ch(std::vector<node*>(kAlphCap, nullptr)) {}
	int val{-1};

	std::vector<int> palindrome_indexes{};

	uint64_t id{};
	std::vector<node*> ch;
};

struct pair {
	pair(int a, int b) : first(a), second(b) {}
	
	int first{0};
	int second{0};
};

class trie {
 public:
	trie() : root_(new node()), sz_(0) {
		root_->id = (uint64_t)root_;
	}

	void insert(std::string& s, int idx) {
		node *n = root_;
		std::vector<bool> suffix_palindromes = sfunc(s);
		for (int i = 0; i < (int)s.size(); ++i) {
			if (n->ch[s[i] - kFirstChar] == nullptr) {
				n->ch[s[i] - kFirstChar] = new node();
				n->ch[s[i] - kFirstChar]->id = (uint64_t)n->ch[s[i] - kFirstChar];
			}
			n = n->ch[s[i] - kFirstChar];
			if (i < (int)s.size() - 1 && suffix_palindromes[i + 1]) {
				n->palindrome_indexes.push_back(idx);
			}
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
		}

		fprintf(f, "}\n");
		fclose(f);
		system("dot -Tpng graph.dot -o graph.png");
	}

	std::vector<pair> find_paly(std::string str, int id) {
		std::vector<pair> ans;
		std::vector<bool> can_be_centered = sfunc(str);

		node *n = root_;
		for (int i = 0; i < (int)str.size(); ++i) {
			if (n->ch[str[i] - kFirstChar] == nullptr) {
				return ans;
			}

			n = n->ch[str[i] - kFirstChar];
			if (n->val != -1 && can_be_centered[i + 1]) {
				ans.push_back(pair(id, n->val));
			}
		}

		for (auto idx : n->palindrome_indexes) {
			if (id != idx) {
				ans.push_back(pair(id, idx));
			}
		}

		return ans;
	}

 private:
	node *root_{nullptr};
	int sz_{0};
};

};

int main() {
	int n_words = 0;
	std::cin >> n_words;
	
	algo::trie t;
	std::string word = "";

	for (int i = 0; i < n_words; ++i) {
		std::cin >> word;
		std::reverse(word.begin(), word.end());
		t.insert(word, i);
	}
	t.debug();

	std::vector<algo::pair> ans = t.find_paly(std::string("a"), 0);
	for (auto [f,s] : ans) {
		std::cout << f << ' ' << s << '\n';
	}
	std::cout << '\n';

	return 0;
}

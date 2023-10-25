#include <iostream>

#include <vector>

namespace algo {
void print_arr(const std::vector<int>& v, int start_idx=0, int adjustment=0) {
	for (size_t i = start_idx; i < v.size(); ++i) {
		std::cout << v[i] + adjustment << ' ';
	}
	std::cout << '\n';
}

template<int Cap, char First>
class sfxarr {
 public:
	sfxarr(std::string& str)
			: str_(str + First), sfxarr_(str_.size()), lcp_(str.size()) {
		build_arr();
		build_lcp();
	}

	void print(std::vector<int>& v) {
		for (int i = 0; i < (int)v.size(); ++i) {
			for (int j = v[i]; j < (int)str_.size(); ++j) {
				std::cout << str_[j];
			}
			std::cout << '\n';
		}
		printf("\n\n");
	}

	void print_out() {
		print(sfxarr_);
		print_arr(sfxarr_, 1, 1);
	}

	void print_lcp() {
		print_arr(lcp_);
	}

 private:
	void build_arr() {
		int sz = (int)str_.size();

		// Prepare part.
		// Comb[i] is number of 'str[j]' that equal or less (LG-order)
		// than this str[i] (or 2^k class in main part).
		std::vector<int> comb(Cap, 0);
		for (int i = 0; i < sz; ++i) {
			++comb[str_[i] - First];
		}
		for (int i = 1; i < Cap; ++i) {
			comb[i] += comb[i - 1];
		}
		for (int i = 0; i < sz; ++i) {
			--comb[str_[i] - First];
			sfxarr_[comb[str_[i] - First]] = i;
		}

		// Create int-equivalent string for all
		// classes of equivalence.
		// the bigger (LG-order) letter 'str_[sfxarr_[i]]'
		// the bigger int_eqv[sfxarr_[i]]
		std::vector<int> int_eqv(sz, 0);
		for (int i = 1; i < sz; ++i) {
			int_eqv[sfxarr_[i]] += int_eqv[sfxarr_[i - 1]];
			if (str_[sfxarr_[i]] != str_[sfxarr_[i - 1]]) {
				++int_eqv[sfxarr_[i]];
			}
		}

		// Main part.
		// shifted_indeces[i] = sfxarr_[i] - 2^k
		std::vector<int> shifted_indeces(sz,0);
		// Number equivalent for classes with length=2^{k+1}.
		std::vector<int> next_int_eqv(sz, 0);
		for (int shift = 0; (1 << shift) < sz; ++shift) {
			for (int i = 0; i < sz; ++i) {
				shifted_indeces[i] = sfxarr_[i] - (1 << shift);
				if (shifted_indeces[i] < 0) {
					shifted_indeces[i] += sz;
				}
			}

			for (int i = 0; i < Cap; ++i) {
				comb[i] = 0;
			}
			for (int i = 0; i < sz; ++i) {
				++comb[int_eqv[i]];
			}
			for (int i = 1; i < Cap; ++i) {
				comb[i] += comb[i - 1];
			}

			// the less i the less shifted_indeces[i] (LG-order)
			// So we put firstly shifted_indeces[i] with bigger i
			// on bigger 'comb[int_eqv[shifted_indeces[i]]]' indeces.
			for (int i = sz - 1; i >= 0; --i) {
				--comb[int_eqv[shifted_indeces[i]]];
				sfxarr_[comb[int_eqv[shifted_indeces[i]]]] = shifted_indeces[i];
			}

			// We we do new class if they differ by the first part
			// or the second.
			next_int_eqv[sfxarr_[0]] = 0;
			for (int i = 0; i < sz; ++i) {
				next_int_eqv[sfxarr_[i]] = next_int_eqv[sfxarr_[i - 1]];
				if (int_eqv[sfxarr_[i]] != int_eqv[sfxarr_[i - 1]]) {
					++next_int_eqv[sfxarr_[i]];
				} else {
					if (int_eqv[sfxarr_[i] + (1 << shift)] != int_eqv[sfxarr_[i - 1] + (1 << shift)]) {
						++next_int_eqv[sfxarr_[i]];
					}
				}
			}

			int_eqv = next_int_eqv;
		}
	}

	void build_lcp() {
		int sz = (int)str_.size();
		// inv_sfxarr[i]: i-th symbol in str_.
		std::vector<int> inv_sfxarr(str_.size());
		for (int i = 0; i < sz; ++i) {
			inv_sfxarr[sfxarr_[i]] = i;
		}

		int start_len = 0;
		for (int i = 0; i < (int)lcp_.size(); ++i) {
			// Get index(in sfxarr_), largest (length) sfx.
			// inv_sfxarr[i] is index in sfxarr_ that it starts with
			// i-th symbol in str.
			// https://www.cs.helsinki.fi/u/tpkarkka/opetus/12s/spa/lecture10.pdf
			int sa_pos = inv_sfxarr[i];
			if (sa_pos == 0) {
				continue;
			}

			// prev index in (lg) order.
			int sa_prev_suffix = sfxarr_[sa_pos - 1];			
			int pfx_len = start_len;
			while ( pfx_len < sz - i &&
					pfx_len < sz - sa_prev_suffix &&
					str_[sa_prev_suffix + pfx_len] == str_[i + pfx_len]) {
				++pfx_len;
			}

			lcp_[sa_pos - 1] = pfx_len;

			start_len = (pfx_len == 0)? 0 : pfx_len - 1;
		}
	}

 private:
	std::string str_{""};
	std::vector<int> sfxarr_{};
	std::vector<int> lcp_{};
};
};

int main() {
	std::string str("abacaba");
	algo::sfxarr<200,(char)0> sfxarr(str);
	sfxarr.print_out();
	sfxarr.print_lcp();

	return 0;
}
#include "Automate.hpp"
#include <iostream>

bool Automate::is_operator(char c) {
  return c == '.' or c == '*' or c == '+';
}

Automate::Automate(int k) : k(k), lengths(std::vector<int>(k, cmax)) {}

Automate Automate::Concatenate(const Automate& a1, const Automate& a2) {
  Automate res(a1.k);
  //res.lengths = std::vector<int>(k, cmax);
  for (auto w1 : a1.lengths) {
    for (auto  w2: a2.lengths) {
      int index = (w1 + w2) % a1.k;
      res.lengths[index] = std::min(w1 + w2, res.lengths[index]);
    }
  }
  return res;
}

Automate Automate::UnionLang(const Automate &a1, const Automate &a2) {
  Automate res = a1;
  for (int i = 0; i < res.lengths.size(); ++i) {
    res.lengths[i] = std::min(res.lengths[i], a2.lengths[i]);
  }
  return res;
}

Automate Automate::KleeneStar(const Automate& a1) {
  Automate result(a1.k);
  std::vector<int> dp(a1.k, cmax);
  for (int i = 0; i < a1.k; ++i) {
    dp[i] = a1.lengths[i];
  }
  for (int t = 1; t <= a1.k; ++t) {
    std::vector<int> new_dp(a1.k, cmax);
    for (int i = 0; i < a1.k; ++i) {
      if (dp[i] == cmax) continue;
      for (int j = 0; j < a1.k; ++j) {
        if (a1.lengths[j] == cmax) continue;
        int new_length = dp[i] + a1.lengths[j];
        int new_remainder = new_length % a1.k;
        new_dp[new_remainder] = std::min(new_dp[new_remainder], new_length);
      }
    }
    for (int i = 0; i < a1.k; ++i) {
      dp[i] = std::min(dp[i], new_dp[i]);
    }
  }
  for (int i = 0; i < a1.k; ++i) {
    result.lengths[i] = dp[i];
  }
  result.lengths[0] = 0;
  //for (auto i : result.lengths) std::cout << i << "\n";
  return result;
}

Automate::Automate(const std::string &regexp, int k) {
  std::stack<Automate> st;
  for (char c : regexp) {
    if (c == '1') {
      Automate a(k);
      a.lengths[0] = 0;
      st.push(a);
    } else if (!is_operator(c) and c != ' ') {
      Automate a(k);
      a.lengths[1] = 1;
      st.push(a);
    } else if (c == '.') {
      if (st.size() < 2) {
        throw std::runtime_error("Invalid reverse Polish notation:"
                                 " not enough operands for concatenation.");
      }
      Automate a2 = st.top(); st.pop();
      Automate a1 = st.top(); st.pop();
      st.push(Concatenate(a1, a2));
    } else if (c == '+') {
      if (st.size() < 2) {
        throw std::runtime_error("Invalid reverse Polish notation:"
                                 " not enough operands for union.");
      }
      Automate a2 = st.top(); st.pop();
      Automate a1 = st.top(); st.pop();
      st.push(UnionLang(a1, a2));
    } else if (c == '*') {
      if (st.empty()) {
        throw std::runtime_error("Invalid reverse Polish notation:"
                                 " not enough operands for Kleene star.");
      }
      Automate a = st.top(); st.pop();
      st.push(KleeneStar(a));
    }
  }
  if (st.size() != 1) throw std::runtime_error("Invalid reverse Polish notation:"
                                               " too many operands.");
  lengths = st.top().lengths;
}

int find_min_length(const Automate &a, int l) {
  return a.lengths[l] == cmax ? -1 : a.lengths[l];
}


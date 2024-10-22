#ifndef FORMAL_TASKS_AUTOMATE_HPP
#define FORMAL_TASKS_AUTOMATE_HPP

#include <stack>
#include <unordered_set>
#include <vector>
#include <string>

const int cmax = 10000;

class Automate {
 public:
  int k;
  std::vector<int> lengths;
  bool is_operator(char c);
  Automate Concatenate(const Automate& a1, const Automate& a2);
  Automate UnionLang(const Automate& a1, const Automate& a2);
  Automate KleeneStar(const Automate& a1);
  Automate(int k) : k(k), lengths(std::vector<int>(k, cmax)) {};
  Automate(const std::string& regexp, int k);
};




#endif

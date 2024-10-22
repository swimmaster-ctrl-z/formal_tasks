#include "Automate.hpp"

#include <iostream>

int find_min_length(const Automate &a, int l) {
  return a.lengths[l] == cmax ? -1 : a.lengths[l];
}

int main() {
  try {
    std::string regex;
    int k, l;
    std::getline(std::cin, regex);
    std::cin >> k >> l;

    if (l < 0 || l >= k) {
      throw std::invalid_argument("Invalid value of l or k");
    }

    Automate automate(regex, k);
    int result = find_min_length(automate, l);

    if (result == -1) {
      std::cout << "INF" << std::endl;
    } else {
      std::cout << result << std::endl;
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
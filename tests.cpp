#include "Automate.hpp"
#include <gtest/gtest.h>

TEST(BuildAutomatonTest, ValidRegex) {
  std::string regex = "ab+c.aba.*.bac.+.+*";
  int k = 3;
  int l = 1;
  Automate automaton = Automate(regex, k);
  EXPECT_EQ(find_min_length(automaton, l), 4);
}


TEST(BuildAutomatonTest, InvalidRegexTooManyOperands) {
  std::string regex = "ab+c.aba.*+";
  int k = 3;
  EXPECT_THROW(Automate(regex, k), std::runtime_error);
}


TEST(BuildAutomatonTest, InvalidRegexTooFewOperandsForConcatenation) {
  std::string regex = "a.";
  int k = 3;
  EXPECT_THROW(Automate(regex, k), std::runtime_error);
}

TEST(ConcatenateTest, ConcatenateAutomatons) {
  int k = 3;
  Automate a1("ab.b.", k);
  EXPECT_EQ(find_min_length(a1, 0), 3);
  EXPECT_EQ(find_min_length(a1, 1), -1);
}


TEST(UnionOpTest, UnionAutomatons) {
  int k = 3;
  Automate a1("ab+b+b+c+", k);
  EXPECT_EQ(find_min_length(a1, 1), 1);
  EXPECT_EQ(find_min_length(a1, 0), -1);
}

TEST(KleeneStarTest, KleeneStarAutomaton) {
  int k = 3;
  Automate a1("a*", k);
  EXPECT_EQ(find_min_length(a1, 1), 1);
  EXPECT_EQ(find_min_length(a1, 0), 0);
}

TEST(KleeneStarTest, KleeneStarAutomatonHard) {
  int k = 4;
  Automate a1("ab.*", k);
  EXPECT_EQ(find_min_length(a1, 1), -1);
  EXPECT_EQ(find_min_length(a1, 0), 0);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
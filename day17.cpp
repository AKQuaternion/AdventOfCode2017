//
// Created by Chris Hartman on 11/25/19.
//
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using std::abs;
using std::ceil;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::istringstream;
using std::map;
using std::max;
using std::max_element;
using std::min;
using std::pair;
using std::set;
using std::sqrt;
using std::string;
using std::swap;
using std::vector;

void day17() {
  auto star1 = 0;
  auto star2 = 0;

  auto input = 301;
  vector<int> v(1);
  for (int i = 1; i <= 2017; ++i) {
    auto pos = input % v.size();
    rotate(v.begin(), v.begin() + pos, v.end());
    v.push_back(i);
  }

  auto big = find(v.begin(), v.end(), 2017);
  ++big;
  if (big == v.end())
    big = v.begin();
  star1 = *big;
  cout << "Day 17 star 1 = " << star1 << "\n";

  auto pos = 0;
  for (int i = 1; i <= 50'000'000; ++i) {
    pos += input;
    pos %= i;
    if (pos == 0)
      star2 = i;
    ++pos;
  }
  cout << "Day 17 star 2 = " << star2 << "\n";
}
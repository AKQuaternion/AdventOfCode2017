//
// Created by Chris Hartman on 11/24/19.
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
using std::ostringstream;
using std::pair;
using std::set;
using std::sqrt;
using std::string;
using std::swap;
using std::vector;

void day15() {
  auto star1 = 0;
  auto star2 = 0;

  const auto mulA = 16807ul;
  const auto mulB = 48271ul;
  const auto div = 2147483647ul;
  //  auto a = 65ul;
  //  auto b = 8921ul;
  auto a = 591ul;
  auto b = 393ul;
  for (auto i = 0u; i < 40e6; ++i) {
    a = a * mulA % div;
    b = b * mulB % div;
    if ((a & 0xffff) == (b & 0xffff))
      ++star1;
    //    cout << star1 << " " << a << "\t" << b << endl;
  }
  a = 591ul;
  b = 393ul;

  for (auto i = 0u; i < 5e6; ++i) {
    do
      a = a * mulA % div;
    while ((a % 4) != 0);

    do
      b = b * mulB % div;
    while ((b % 8) != 0);

    if ((a & 0xffff) == (b & 0xffff))
      ++star2;
  }
  cout << "Day 14 star 1 = " << star1 << "\n";
  cout << "Day 14 star 2 = " << star2 << "\n";
}
//
// Created by Chris Hartman on 11/20/19.
//
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using std::ceil;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::map;
using std::max;
using std::min;
using std::pair;
using std::sqrt;
using std::string;
using std::vector;

pair<int, int> coords(int n) {
  int ring = ceil((sqrt(n) + 1) / 2) - 1;
  n -= (2 * ring - 1) * (2 * ring - 1);
  auto x = ring;
  auto y = -ring;
  auto step = 2 * ring;
  auto up = min(step, n);
  n -= up;
  auto left = min(step, n);
  n -= left;
  auto down = min(step, n);
  n -= down;
  auto right = min(step, n);
  n -= right;
  assert(n == 0);
  return {x + right - left, y + up - down};
}

void day3() {
  auto [x, y] = coords(265149);
  cout << "Day 3 star 1 = " << abs(x) + abs(y) << endl;
  map<pair<int, int>, int> v;
  v[{0, 0}] = 1;
  int i = 2;
  while (true) {
    auto [lx, ly] = coords(i);
    auto sum = v[{lx - 1, ly - 1}] + v[{lx, ly - 1}] + v[{lx + 1, ly - 1}] +
               v[{lx - 1, ly}] + +v[{lx + 1, ly}] + v[{lx - 1, ly + 1}] +
               v[{lx, ly + 1}] + v[{lx + 1, ly + 1}];
    v[{lx, ly}] = sum;
    if (sum > 265149) {
      cout << "Day 3 star 2 = " << sum << endl;
      break;
    }
    ++i;
  }
}
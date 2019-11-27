//
// Created by Chris Hartman on 11/26/19.
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

void day19() {
  string star1;
  auto star2 = 1;
  ifstream ifile("../day19.txt");
  string line;
  vector<string> p;
  while (getline(ifile, line)) {
    p.push_back(line);
  }
  auto startX = std::find(p[0].begin(), p[0].end(), '|');

  auto dx = 0;
  auto dy = 1;
  auto x = startX - p[0].begin();
  auto y = 0;
  while (true) {
    while (p[y + dy][x + dx] != ' ') {
      y += dy;
      x += dx;
      ++star2;
      if (isalpha(p[y][x]))
        star1 += p[y][x];
    }
    if (dy != 0) { // moving vertically
      dy = 0;
      if (p[y][x - 1] != ' ')
        dx = -1;
      else if (p[y][x + 1] != ' ')
        dx = 1;
      else
        break;
    } else { // moving horizontally
      dx = 0;
      if (p[y - 1][x] != ' ')
        dy = -1;
      else if (p[y + 1][x] != ' ')
        dy = 1;
      else
        break;
    }
  }

  cout << "Day 19 star 1 = " << star1 << "\n";
  cout << "Day 19 star 2 = " << star2 << "\n";
}
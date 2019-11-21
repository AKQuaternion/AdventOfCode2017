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

void day4() {
  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day4.txt");
  while (true) {
    string line;
    getline(ifile, line);
    if (!ifile)
      break;
    istringstream iss(line);
    string s;
    map<string, int> m1;
    map<string, int> m2;
    while (iss >> s) {
      m1[s]++;
      auto c{s};
      sort(c.begin(), c.end());
      m2[c]++;
    }
    if (std::all_of(m1.begin(), m1.end(), [](auto e) { return e.second == 1; }))
      ++star1;
    if (std::all_of(m2.begin(), m2.end(), [](auto e) { return e.second == 1; }))
      ++star2;
  }
  cout << "Day 4 star 1 = " << star1 << "\n";
  cout << "Day 4 star 2 = " << star2 << "\n";
}
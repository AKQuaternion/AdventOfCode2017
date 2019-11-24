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
using std::pair;
using std::set;
using std::sqrt;
using std::string;
using std::swap;
using std::vector;

void day11() {
  map<string, vector<int>> coords{{"n", {0, -1, 1}},  {"ne", {1, -1, 0}},
                                  {"se", {1, 0, -1}}, {"s", {0, 1, -1}},
                                  {"sw", {-1, 1, 0}}, {"nw", {-1, 0, 1}}};

  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day11.txt");
  string line;
  getline(ifile, line);
  istringstream in(line);
  //  istringstream in("se,sw,se,sw,sw");
  string dir;
  vector<int> pos{0, 0, 0};
  auto count = 0;
  while (getline(in, dir, ',')) {
    if (dir.back() == '\n')
      dir.pop_back();
    //    cout << dir << " ";
    for (int i = 0; i < 3; ++i)
      pos[i] += coords[dir][i];
    star2 = max(star2, max(abs(pos[0]), max(abs(pos[1]), abs(pos[2]))));
  }
  star1 = max(abs(pos[0]), max(abs(pos[1]), abs(pos[2])));
  cout << "Day 11 star 1 = " << star1 << "\n";
  cout << "Day 11 star 2 = " << star2 << "\n";
}
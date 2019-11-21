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

void day5() {
  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day5.txt");
  vector<int> v;
  int num;
  while (ifile >> num)
    v.push_back(num);

  auto v2{v};
  int pc = 0;
  while (pc >= 0 && pc < v.size()) {
    ++star1;
    pc += v[pc]++;
  }
  pc = 0;
  while (pc >= 0 && pc < v2.size()) {
    ++star2;
    auto offset = v2[pc];
    if (offset >= 3)
      --v2[pc];
    else
      ++v2[pc];
    pc += offset;
  }
  cout << "Day 4 star 1 = " << star1 << "\n";
  cout << "Day 4 star 2 = " << star2 << "\n";
}
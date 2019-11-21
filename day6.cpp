//
// Created by Chris Hartman on 11/20/19.
//
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
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
using std::max_element;
using std::min;
using std::pair;
using std::set;
using std::sqrt;
using std::string;
using std::vector;

void day6() {
  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day6.txt");
  vector<int> v;
  int num;
  while (ifile >> num)
    v.push_back(num);

  map<vector<int>, int> seen;
  while (true) {
    //    for(auto i:v) cout << i << " ";
    //    cout << endl;
    seen[v] = star1;
    auto largest = max_element(v.begin(), v.end()) - v.begin();
    auto num = v[largest];
    v[largest] = 0;
    for (int i = 1; i <= num; ++i)
      ++v[(largest + i) % v.size()];
    ++star1;
    if (seen.count(v))
      break;
  }
  cout << "Day 6 star 1 = " << star1 << "\n";
  cout << "Day 6 star 2 = " << star1 - seen[v] << "\n";
}
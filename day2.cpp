//
// Created by Chris Hartman on 11/20/19.
//
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::max;
using std::min;
using std::string;
using std::vector;

int findDivisible(const vector<int> &v) {
  for (int i = 0; i < v.size(); ++i)
    for (int j = i + 1; j < v.size(); ++j)
      if (v[j] % v[i] == 0)
        return v[j] / v[i];
  throw(0);
}

void day2() {
  ifstream ifile("../day2.txt");
  auto star1 = 0;
  auto star2 = 0;
  while (true) {
    string line;
    getline(ifile, line);
    if (!ifile)
      break;
    istringstream iss(line);
    int num;
    vector<int> v;
    while (iss >> num)
      v.push_back(num);
    std::sort(v.begin(), v.end());
    star1 += v.back() - v.front();
    star2 += findDivisible(v);
  }
  cout << "Day 2 star 1 = " << star1 << "\n";
  cout << "Day 2 star 2 = " << star2 << "\n";
}

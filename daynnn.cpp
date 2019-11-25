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

void daynnn() {
  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../daynnn.txt");
  string line;
  while (getline(ifile, line)) {
    istringstream iline(line);
  }
  cout << "Day nnn star 1 = " << star1 << "\n";
  cout << "Day nnn star 2 = " << star2 << "\n";
}
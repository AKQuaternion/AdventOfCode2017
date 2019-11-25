//
// Created by Chris Hartman on 11/24/19.
//
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

void day13() {
  map<int, int> scanners;
  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day13.txt");
  //  istringstream ifile("0: 3\n"
  //                      "1: 2\n"
  //                      "4: 4\n"
  //                      "6: 4");
  string line;
  while (getline(ifile, line)) {
    string _s;
    char _c;
    istringstream iline(line);
    int layer, range;
    iline >> layer >> _c >> range;
    scanners[layer] = range;
    //    cout << layer << " " << range << endl;
  }

  auto initialScanners = scanners;

  for (const auto [l, r] : scanners)
    if (l % (2 * (r - 1)) == 0)
      star1 += l * r;

  bool caught = (star1 != 0);
  while (caught) {
    ++star2;
    caught = false;
    for (const auto [l, r] : scanners)
      caught |= ((l + star2) % (2 * (r - 1)) == 0);
  }
  cout << "Day 13 star 1 = " << star1 << "\n";
  cout << "Day 13 star 2 = " << star2 << "\n";
}
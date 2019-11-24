//
// Created by Chris Hartman on 11/23/19.
//
//
// Created by Chris Hartman on 11/22/19.
//
#include <algorithm>
#include <cmath>
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
using std::ceil;
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
using std::vector;

void day10() {
  auto skip = 0;
  auto pos = 0;
  vector<int> v(256);
  std::iota(v.begin(), v.end(), 0);
  string _s;
  char _c;
  int _i;
  double _d;

  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day10.txt");
  while (true) {
    int length;
    ifile >> length;
    if (!ifile)
      break;
    ifile >> _c;
    for (auto i = 0; i < length / 2; ++i)
      swap(v[(pos + i) % 256], v[(pos + length - 1 - i) % 256]);
    pos += skip + length;
    ++skip;
  }
  star1 = v[0] * v[1];

  skip = 0;
  pos = 0;
  std::iota(v.begin(), v.end(), 0);

  ifile.close();
  ifile.open("../day10.txt");
  vector<int> lengths;
  while (true) {
    ifile >> _c;
    if (!ifile)
      break;
    lengths.push_back(int(_c));
  }

  vector<int> s{17, 31, 73, 47, 23};
  lengths.insert(lengths.end(), s.begin(), s.end());
  for (int i = 0; i < 64; ++i)
    for (auto length : lengths) {
      for (auto i = 0; i < length / 2; ++i)
        swap(v[(pos + i) % 256], v[(pos + length - 1 - i) % 256]);
      pos += skip + length;
      ++skip;
    }

  vector<int> hashes;
  for (int i = 0; i < 16; ++i) {
    auto blocksum = 0u;
    for (int j = 0; j < 16; ++j)
      blocksum ^= v[16 * i + j];
    hashes.push_back(blocksum);
  }

  cout << "Day 10 star 1 = " << std::dec << star1 << "\n";
  cout << "Day 10 star 2 = ";
  for (auto i : hashes)
    cout << std::hex << (i < 10 ? "0" : "") << i;
  cout << std::dec << endl;
}
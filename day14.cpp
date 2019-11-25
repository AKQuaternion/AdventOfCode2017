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
using std::ostringstream;
using std::pair;
using std::set;
using std::sqrt;
using std::string;
using std::swap;
using std::vector;

void floodfill(vector<vector<char>> &b, int i, int j) {
  if (i < 0 || i >= 128 || j < 0 || j >= 128)
    return;
  if (b[i][j] == '.')
    return;
  b[i][j] = '.';
  floodfill(b, i - 1, j);
  floodfill(b, i + 1, j);
  floodfill(b, i, j - 1);
  floodfill(b, i, j + 1);
}

void day14() {
  map<int, int> scanners;
  auto star1 = 0;
  auto star2 = 0;
  string input("ugkiagan");
  //  string input = "flqrgnkx";

  vector<vector<char>> bits(128);
  for (int i = 0; i < 128; ++i) {
    int skip = 0;
    int pos = 0;
    vector<int> v(256);
    std::iota(v.begin(), v.end(), 0);

    vector<int> lengths;
    ostringstream out;
    out << input << "-" << i;
    cout << out.str() << endl;
    for (auto c : out.str())
      lengths.push_back(int(c));

    vector<int> s{17, 31, 73, 47, 23};
    lengths.insert(lengths.end(), s.begin(), s.end());

    for (int i = 0; i < 64; ++i)
      for (auto length : lengths) {
        for (auto i = 0; i < length / 2; ++i)
          swap(v[(pos + i) % 256], v[(pos + length - 1 - i) % 256]);
        pos += skip + length;
        ++skip;
      }

    vector<unsigned int> hashes;
    for (int i = 0; i < 16; ++i) {
      auto blocksum = 0u;
      for (int j = 0; j < 16; ++j)
        blocksum ^= v[16 * i + j];
      hashes.push_back(blocksum);
    }
    cout << std::hex << hashes[0] << endl;
    for (auto h : hashes)
      for (auto col = 0u; col < 8; ++col)
        if (1 << (7 - col) & h) {
          ++star1;
          bits[i].push_back('#');
        } else
          bits[i].push_back('.');
  }

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j)
      cout << bits[i][j];
    cout << endl;
  }
  cout << std::dec;

  for (int i = 0; i < 128; ++i)
    for (int j = 0; j < 128; ++j)
      if (bits[i][j] == '#') {
        ++star2;
        floodfill(bits, i, j);
      }
  cout << "Day 14 star 1 = " << star1 << "\n";
  cout << "Day 14 star 2 = " << star2 << "\n";
}
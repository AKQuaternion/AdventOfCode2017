//
// Created by Chris Hartman on 11/27/19.
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
#include <tuple>
#include <utility>
#include <vector>
using std::abs;
using std::ceil;
using std::cout;
using std::endl;
using std::forward_as_tuple;
using std::ifstream;
using std::istream;
using std::istringstream;
using std::map;
using std::max;
using std::max_element;
using std::min;
using std::ostream;
using std::pair;
using std::set;
using std::sqrt;
using std::string;
using std::swap;
using std::tie;
using std::tuple;
using std::vector;

struct Pattern {
  Pattern(const string &input, const string &output) {
    istringstream iline(input);
    string s;
    while (getline(iline, s, '/'))
      in.push_back(s);
    istringstream ioline(output);
    while (getline(ioline, s, '/'))
      out.push_back(s);
  }

  vector<string> in;
  vector<string> out;
};

ostream &operator<<(ostream &os, const Pattern &p) {
  for (const auto &s : p.in)
    os << s << endl;
  return os;
}

bool operator<(const Pattern &x, const Pattern &y) { return x.in < y.in; }
bool operator==(const Pattern &x, const Pattern &y) { return x.in == y.in; }
bool operator==(const Pattern &x, const vector<string> &y) { return x.in == y; }

void day21() {
  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day21.txt");
  string line;
  vector<Pattern> s2;

  while (getline(ifile, line)) {
    string _s;
    string input;
    string output;
    istringstream iline(line);
    iline >> input >> _s >> output;
    Pattern p(input, output);

    vector<Pattern> newOnes(8, p);
    int size = p.in.size();
    for (int transform = 1; transform < 8; ++transform) {
      for (int x = 0; x < size; ++x)
        for (int y = 0; y < size; ++y) {
          auto nx = (transform & 1) ? x : size - 1 - x;
          auto ny = (transform & 2) ? y : size - 1 - y;
          if (transform & 4)
            swap(nx, ny);
          newOnes[transform].in[ny][nx] = p.in[y][x];
        }
    }
    s2.insert(s2.end(), newOnes.begin(), newOnes.end());
  }

  sort(s2.begin(), s2.end());
  s2.erase(unique(s2.begin(), s2.end()), s2.end());

  vector<string> it{".#.", "..#", "###"};

  for (int iter = 0; iter < 18; ++iter) {
    auto chunk = (it.size() % 2 == 0) ? 2 : 3;
    auto chp = chunk + 1;
    assert(it.size() % chunk == 0);
    auto pieces = it.size() / chunk;
    vector<string> itOut(pieces * chp, string(pieces * chp, ' '));
    for (int up = 0; up < pieces; ++up)
      for (int left = 0; left < pieces; ++left) {
        vector<string> patch(chunk, string(chunk, ' '));
        for (int y = 0; y < chunk; ++y)
          for (int x = 0; x < chunk; ++x)
            patch[y][x] = it[up * chunk + y][left * chunk + x];

        auto match = std::find(s2.begin(), s2.end(), patch);
        assert(match != s2.end());
        for (int y = 0; y < chp; ++y)
          for (int x = 0; x < chp; ++x)
            itOut[up * chp + y][left * chp + x] = match->out[y][x];
      }
    it = itOut;

    auto on = 0ul;
    for (const auto s : it)
      on += std::count(s.begin(), s.end(), '#');
    if (iter == 4)
      star1 = on;
    cout << "After iter " << iter << " size is " << it.size()
         << " with #: " << on << endl;
  }
  for (const auto s : it)
    star2 += std::count(s.begin(), s.end(), '#');

  cout << "Day 21 star 1 = " << star1 << "\n";
  cout << "Day 21 star 2 = " << star2 << "\n";
}
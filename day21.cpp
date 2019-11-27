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
bool operator==(const Pattern &x, const vector<string> &y) {return x.in == y;}

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

    Pattern fx{p};
    Pattern fy{p};
    Pattern fxy{p};
    Pattern s{p};
    Pattern sx{p};
    Pattern sy{p};
    Pattern sxy{p};
    int size = p.in.size();
    for (int x = 0; x < size; ++x)
      for (int y = 0; y < size; ++y) {
        fx.in[y][size - 1 - x] = p.in[y][x];
        fxy.in[size - 1 - y][size - 1 - x] = p.in[y][x];
        fy.in[size - 1 - y][x] = p.in[y][x];
      }
    for (int x = 0; x < size; ++x)
      for (int y = 0; y < size; ++y) {
        s.in[x][y] = p.in[y][x];
        sx.in[x][y] = fx.in[y][x];
        sy.in[x][y] = fy.in[y][x];
        sxy.in[x][y] = fxy.in[y][x];
      }
    vector<Pattern> newOnes;
    newOnes.push_back(p);
    newOnes.push_back(fx);
    newOnes.push_back(fxy);
    newOnes.push_back(fy);
    newOnes.push_back(s);
    newOnes.push_back(sx);
    newOnes.push_back(sy);
    newOnes.push_back(sxy);
    sort(newOnes.begin(), newOnes.end());
    newOnes.erase(unique(newOnes.begin(), newOnes.end()), newOnes.end());
    s2.insert(s2.end(), newOnes.begin(), newOnes.end());
  }

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

        auto match =
            std::find(s2.begin(), s2.end(),patch);
        assert(match != patterns.end());
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
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
using std::tuple;
using std::forward_as_tuple;
using std::tie;
using std::swap;
using std::vector;

struct Particle {
  Particle(const string &s, int id) : id(id) {
    // p=<-717,-4557,2578>, v=<153,21,30>, a=<-8,8,-7>
    char _c;
    istringstream iline(s);
    iline >> _c >> _c >> _c >> x >> _c >> y >> _c >> z >> _c >> _c;
    iline >> _c >> _c >> _c >> dx >> _c >> dy >> _c >> dz >> _c >> _c;
    iline >> _c >> _c >> _c >> ax >> _c >> ay >> _c >> az >> _c;
  }
  void update() {
    dx += ax;
    dy += ay;
    dz += az;
    x += dx;
    y += dy;
    z += dz;
  }
  [[nodiscard]] long long distance() const { return abs(x) + abs(y) + abs(z); }
  [[nodiscard]] tuple<long long, long long, long long> pos() const {
    return forward_as_tuple(x, y, z);
  }
  int id;
  long long x, y, z, dx, dy, dz, ax, ay, az;
};
void day20() {
  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day20.txt");
  string line;
  vector<Particle> ps;
  while (getline(ifile, line)) {
    ps.emplace_back(line, ps.size());
  }

  auto star1ps{ps};
  for (int i = 0; i < 1e3; ++i)
    for (auto &p : star1ps)
      p.update();

  for (int i = 0; i < star1ps.size(); ++i) {
    if (star1ps[i].distance() < star1ps[star1].distance())
      star1 = i;
  }
  cout << "Day 20 star 1 = " << ps[star1].id << "\n";

  for (int i = 0; i < 1e3; ++i) {
    sort(ps.begin(), ps.end(),
         [](auto a, auto b) { return a.pos() < b.pos(); });
    vector<Particle> qs;
    int j = 0;
    while (j < ps.size()) {
      if (j < ps.size() - 1 && ps[j].pos() == ps[j + 1].pos()) {
        auto k = j + 1;
        while (k < ps.size() && ps[k].pos() == ps[j].pos())
          ++k;
        j = k; // skip these
      } else {
        qs.push_back(ps[j]);
        ++j;
      }
    }
    ps = qs;
    for (auto &p : ps)
      p.update();
  }

  cout << "Day 20 star 2 = " << ps.size() << "\n";
}
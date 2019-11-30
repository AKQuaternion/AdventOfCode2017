//
// Created by Chris Hartman on 11/29/19.
//
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
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
using std::queue;
using std::sqrt;
using std::string;
using std::forward_as_tuple;
using std::tie;
using std::tuple;
using std::swap;
using std::vector;

static auto star1 = 0;
static pair<int,int> star2 = {0,0};
static map<pair<int,int>,int> comps;
static int mn=0;

void dfs(int s,pair <int,int> inVal) {
  for(int ii=0;ii<=mn;++ii) {
    if(comps[{s,ii}] > 0) {
      --comps[{s,ii}];
      --comps[{ii,s}];
      star1 = max(star1, inVal.second+s+ii);
      star2 = max(star2, {inVal.first+1,inVal.second+s+ii});
      dfs(ii,{inVal.first+1,inVal.second+s+ii});
      ++comps[{s,ii}];
      ++comps[{ii,s}];
    }
  }
}

void day24() {
  ifstream ifile("../day24.txt");
  string line;

  while (getline(ifile, line)) {
    int n1, n2;
    char _c;
    istringstream iline(line);
    iline >> n1 >> _c >> n2;
    mn = max(n1, max(n2, mn));
    comps[{n1, n2}]++;
    comps[{n2, n1}]++;
  }

  dfs(0, {0, 0});
  cout << "Day 24 star 1 = " << star1 << "\n";
  cout << "Day 24 star 2 = " << star2.second << "\n";
}
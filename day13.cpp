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

map<int, vector<int>> edges;

namespace { // internal linkage
}

int dfs(int vertex, vector<int> &visited) {
  if (!visited[vertex])
    ++star2;
  for (auto i : edges[vertex]) {
    if (!visited[i]) {
      visited[i] = 1;
      dfs(i, visited);
    }
  }
  return (std::count(visited.begin(), visited.end(), 1));
}

void day13() {
  map<int, int> m;
  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day13.txt");
  string line;
  while (getline(ifile, line)) {
    string _s;
    char _c;
    istringstream iline(line);
    int layer, range;
    iline >> layer >> _c >> range;
    cout << layer << " " << range << endl;
  }
  //    cout << endl;
}
cout << "Day 13 star 1 = " << star1 << "\n";
cout << "Day 13 star 2 = " << star2 << "\n";
}
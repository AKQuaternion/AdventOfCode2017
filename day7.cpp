//
// Created by Chris Hartman on 11/20/19.
//
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using std::ceil;
using std::cout;
using std::endl;
using std::ifstream;
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

map<string, vector<string>> children;
map<string, int> weights;
map<string, string> parent;
map<string, int> carries;

void calcCarry(const string &node) {
  if (children[node].empty()) {
    cout << node << " -> " << weights[node] << endl;
    carries[node] = weights[node];
  } else {
    auto total = weights[node];
    for (const auto &c : children[node]) {
      calcCarry(c);
      total += carries[c];
    }
    carries[node] = total;
    cout << node << " " << carries[node] << " -> ";
    for (const auto &c : children[node]) {
      cout << c << " " << weights[c] << " " << carries[c] << ", ";
    }
    cout << endl;
  }
}

int checkCarry(const string &node) {
  if (children[node].empty()) {
    return -1;
  } else {
    vector<int> v;
    for (const auto &c : children[node]) {
      if (auto res = checkCarry(c); res >= 0)
        return res;
      v.push_back(carries[c]);
    }
    sort(v.begin(), v.end());
    if (v.size() < 3)
      return -1;
    if (v[0] != v[1]) {
      for (const auto &c : children[node]) {
        if (carries[c] == v[0]) {
          cout << v[1] - v[0] + weights[c] << endl;
          return v[1] - v[0] + weights[c];
        }
      }
    }
    if (v[v.size() - 1] != v[v.size() - 2])
      for (const auto &c : children[node]) {
        if (carries[c] == v[v.size() - 1]) {
          cout << c << " " << v[v.size() - 2] - v[v.size() - 1] + weights[c]
               << endl;
          return v[v.size() - 2] - v[v.size() - 1] + weights[c];
        }
      }
    return -1;
  }
}

void day7() {
  string star1;
  auto star2 = 0;
  ifstream ifile("../day7.txt");
  string line;
  while (getline(ifile, line)) {
    istringstream iline(line);
    string s;
    string base;
    iline >> base;
    parent[base];
    vector<string> onit;
    char c;
    iline >> c;
    int n;
    iline >> n; // weight
    weights[base] = n;
    iline >> c;
    assert(c == ')');
    iline >> s; // ->
    while (iline >> s) {
      if (s.back() == ',')
        s.pop_back();
      onit.push_back(s);
      parent[s] = base;
    }
    children[base] = onit;
  }
  for (auto [child, parent] : parent)
    if (parent == "")
      star1 = child;
  calcCarry(star1);
  star2 = checkCarry(star1);
  //  for(auto [s,i]:carries)
  //    cout << s << " carries " << i << endl;
  cout << "Day 7 star 1 = " << star1 << "\n"; // 9:41
  cout << "Day 7 star 2 = " << star2 << "\n";
}
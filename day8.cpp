//
// Created by Chris Hartman on 11/21/19.
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

map<string, int> regs;

void day8() {
  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day8.txt");
  string line;
  while (getline(ifile, line)) {
    istringstream iline(line);
    // b inc 5 if a > 1
    string target;
    string updown;
    int amount;
    string _s;
    string source;
    string op;
    int cmpval;
    iline >> target >> updown >> amount >> _s >> source >> op >> cmpval;
    if (updown == "dec")
      amount *= -1;
    if (op == "==") {
      if (regs[source] == cmpval)
        regs[target] += amount;
    }
    if (op == "!=") {
      if (regs[source] != cmpval)
        regs[target] += amount;
    }
    if (op == "<") {
      if (regs[source] < cmpval)
        regs[target] += amount;
    }
    if (op == ">") {
      if (regs[source] > cmpval)
        regs[target] += amount;
    }
    if (op == "<=") {
      if (regs[source] <= cmpval)
        regs[target] += amount;
    }
    if (op == ">=") {
      if (regs[source] >= cmpval)
        regs[target] += amount;
    }
    for (const auto &[rname, rval] : regs)
      if (rval > star2)
        star2 = rval;
  }
  for (const auto &[rname, rval] : regs)
    if (rval > star1)
      star1 = rval;

  cout << "Day 8 star 1 = " << star1 << "\n";
  cout << "Day 8 star 2 = " << star2 << "\n";
}
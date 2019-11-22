//
// Created by Chris Hartman on 11/22/19.
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

string _s;
char _c;
int _i;
double _d;
auto star2 = 0;

void readGarbage(istream &in) {
  char c;
  while (in >> c) {
    if (c == '>')
      return;
    if (c == '!')
      in >> c;
    else
      ++star2;
  }
}

int readGroup(istream &in, int level) {
  int score = level;
  char c;
  while (in >> c) {
    if (c == '}')
      return score;
    if (c == '<')
      readGarbage(in);
    if (c == '{')
      score += readGroup(in, level + 1);
  }
  throw 0;
}

void day9() {
  auto star1 = 0;
  ifstream ifile("../day9.txt");
  //  istringstream ifile("{{<ab>},{<ab>},{<ab>},{<ab>}}");
  ifile >> _c;
  star1 = readGroup(ifile, 1);

  cout << "Day 8 star 1 = " << star1 << "\n";
  cout << "Day 8 star 2 = " << star2 << "\n";
}
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

void printLine(const vector<int> &line, const vector<int> &exchanges) {
  vector<int> inverse(exchanges.size());
  for (int i = 0; i < exchanges.size(); ++i)
    inverse[exchanges[i]] = i;
  for (auto i : line)
    cout << char('a' + inverse[i]);
  cout << "\n";
}

vector<int> applyPerm(const vector<int> &orig, const vector<int> &perm) {
  vector<int> res(orig.size());
  for (int i = 0; i < res.size(); ++i)
    res[i] = orig[perm[i]];
  return res;
}

void day16() {
  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day16.txt");
  //  istringstream ifile("s1,x3/4,pe/b");
  string line;
  getline(ifile, line);
  const int size = 16;
  vector<int> exchanges(size);
  vector<int> programLine(size);
  iota(exchanges.begin(), exchanges.end(), 0);
  iota(programLine.begin(), programLine.end(), 0);
  istringstream in(line);
  string danceMove;
  while (getline(in, danceMove, ',')) {
    //    cout << line << endl;
    istringstream move(danceMove);
    char c;
    move >> c;
    switch (c) {
    case 'x':
      int p1, p2;
      move >> p1 >> c >> p2;
      //      cout << "x" << p1 << "/" << p2 << ": \t";
      swap(programLine[p1], programLine[p2]);
      break;
    case 'p':
      char n1, n2;
      move >> n1 >> c >> n2;
      n1 -= 'a';
      n2 -= 'a';
      swap(exchanges[n1], exchanges[n2]);
      //      cout << "p" << n1 << "/" << n2 << ": \t";
      break;
    case 's':
      int spin;
      move >> spin;
      //      cout << "s" << spin << ": \t";
      rotate(programLine.begin(), programLine.end() - spin, programLine.end());
      break;
    default:
      throw 1;
    }
  }
  cout << "Day 16 star 1 = ";
  printLine(programLine, exchanges);

  vector<int> exchangesMany(size);
  vector<int> programLineMany(size);
  iota(exchangesMany.begin(), exchangesMany.end(), 0);
  iota(programLineMany.begin(), programLineMany.end(), 0);
  for (auto time = 0ull; time < 1000; ++time) {
    programLineMany = applyPerm(programLineMany, programLine);
    exchangesMany = applyPerm(exchangesMany, exchanges);
  }
  auto pl1000{programLineMany};
  auto ex1000{exchangesMany};
  for (auto time = 1ull; time < 1000'000; ++time) { // note start at 1
    programLineMany = applyPerm(programLineMany, pl1000);
    exchangesMany = applyPerm(exchangesMany, ex1000);
  }

  cout << "Day 16 star 2 = ";
  printLine(programLineMany, exchangesMany);
}

//    Day 16 star 1 = fgmobeaijhdpkcln first 10 repeats
//    Day 16 star 1 = hjbagmnplkcfiedo
//    Day 16 star 1 = chadeplfgojnmikb
//    Day 16 star 1 = lgmknhfibepodacj
//    Day 16 star 1 = kbgadmpcelnfohji
//    Day 16 star 1 = dhjecfignbapmokl
//    Day 16 star 1 = aimfhncebglokjdp
//    Day 16 star 1 = ekbilmpoghdacnjf
//    Day 16 star 1 = daejgpflnikbmcho
//    Day 16 star 1 = knmlbicfogjhdepa
//    Day 16 star 1 = elgknmjpdbhcaiof
//    Day 16 star 2 = lgmkacfjbopednhi
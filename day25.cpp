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

struct Instr {
  int write;
  int move;
  char next;
};

struct State {
  Instr instrs[2];
};

map<char,State> tm = {
    {'A',{Instr{1,1,'B'},Instr{0,-1,'B'}}},
    {'B',{Instr{0,1,'C'},Instr{1,-1,'B'}}},
    {'C',{Instr{1,1,'D'},Instr{0,-1,'A'}}},
    {'D',{Instr{1,-1,'E'},Instr{1,-1,'F'}}},
    {'E',{Instr{1,-1,'A'},Instr{0,-1,'D'}}},
    {'F',{Instr{1,1,'A'},Instr{1,-1,'E'}}},
};

map<int,int> tape;

void day25() {
  int pos=0;
  char state = 'A';
  for(int i=0;i<12629077;++i) {
    auto in = tm[state].instrs[tape[pos]];
    tape[pos]=in.write;
    pos += in.move;
    state = in.next;
  } //41.11

  auto star1 = count_if(tape.begin(),tape.end(),[](auto p){return p.second==1;});
  auto star2 = 0;
  cout << "Day 25 star 1 = " << star1 << "\n";
  cout << "Day 25 star 2 = " << star2 << "\n";
}
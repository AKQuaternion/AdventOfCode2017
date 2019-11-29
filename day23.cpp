//
// Created by Chris Hartman on 11/28/19.
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
using std::pair;
using std::set;
using std::sqrt;
using std::string;
using std::swap;
using std::tie;
using std::tuple;
using std::vector;

struct Instr {
  string _op;
  string _r1;
  string _r2;
};

auto star1 = 0;
static auto star2 = 0;

class Computer2 {
public:
  enum Reason { SEND, RECEIVE, END };

private:
  long long val(const string &r) const {
    if (r[0] >= 'a' && r[0] <= 'z')
      return _reg.at(r[0]);
    else {
      istringstream i(r);
      long long n;
      i >> n;
      return n;
    }
  };
  /*
   * set X Y sets register X to the value of Y.
 sub X Y decreases register X by the value of Y.
 mul X Y sets register X to the result of multiplying the value contained in
 register X by the value of Y. jnz X Y jumps with an offset of the value of Y,
 but only if the value of X is not zero. (An offset of 2 skips the next
 instruction, an offset of -1 jumps to the previous instruction, and so on.)
   */
public:
  Computer2(vector<Instr> v, int id) : _program(move(v)), _reg{{'a', 0}} {}
  long long getLastSent() { return _lastSent; }
  Reason run() {
    while (_pc < _program.size()) {
      const auto &i = _program[_pc];
      ++_pc;
      cout << _pc - 1 << ":\t " << i._op << " " << i._r1 << " " << i._r2
           << " | ";
      //      if (i._op == "snd") {
      //        _lastSent = val(i._r1);
      //        return SEND;
      //      }
      if (i._op == "set") {
        _reg[i._r1[0]] = val(i._r2);
      }
      if (i._op == "sub") {
        _reg[i._r1[0]] -= val(i._r2);
      }
      if (i._op == "mul") {
        ++star1;
        _reg[i._r1[0]] *= val(i._r2);
      }
      if (i._op == "mod") {
        _reg[i._r1[0]] %= val(i._r2);
      }
      //      if (i._op == "rcv") {
      //        if (_received.empty()) {
      //          --_pc;
      //          return RECEIVE;
      //        }
      //        _reg[i._r1[0]] = _received.front();
      //        _received.pop();
      //      }
      if (i._op == "jnz") {
        if (val(i._r1) != 0)
          _pc += val(i._r2) - 1;
      }
      for (auto [reg, val] : _reg)
        cout << reg << "=" << val << " ";
      cout << endl;
    }
    return END;
  }

  void compile() const {
    cout << "  int count=0;\n"
            "  int a=0;\n"
            "  int b=0;\n"
            "  int c=0;\n"
            "  int d=0;\n"
            "  int e=0;\n"
            "  int f=0;\n"
            "  int g=0;\n"
            "  int h=0;\n";
    for (auto pc = 0; pc < _program.size(); ++pc) {
      const auto &i = _program[pc];
      cout << "label" << pc << ":\t";
      if (i._op == "set") {
        cout << i._r1[0] << " = " << i._r2 << ";\n";
      }
      if (i._op == "sub") {
        if (i._r2[0] == '-')
          cout << i._r1[0] << " += " << i._r2.substr(1) << ";\n";
        else
          cout << i._r1[0] << " -= " << i._r2 << ";\n";
      }
      if (i._op == "mul") {
        cout << "++count;\n";
        cout << i._r1[0] << " *= " << i._r2 << ";\n";
      }
      if (i._op == "mod") {
        cout << i._r1[0] << " %= " << i._r2 << ";\n";
      }
      if (i._op == "jnz") {
        cout << "if (" << i._r1 << " != 0) goto label" << pc + val(i._r2)
             << ";\n";
      }
    }
    cout << "label" << _program.size() << ":\n";
    cout << "return count;\n";
  }

private:
  vector<Instr> _program;
  map<char, long long> _reg;
  int _pc = 0;
  long long _lastSent = 0;
};

long long theProgram() {
  long long count = 0;
  bool debug = false;
  long long b = 0;
  long long c = 0;
  long long d = 0;
  long long f = 0;
  long long g = 0;
  long long h = 0;

  if (debug) {
    c = b = 79;
  } else {
    ++count;
    b = 107900;
    c = b + 17000;
  }

  while (true) {
    f = 1;
    d = 2;
  label10:
    do {
      count += b-2;
//      for (auto e=2; e<b/2; ++e) {
//        if (d * e == b)
//          f = 0;
//      }
      if (b%d==0)
        f=0;
      ++d;
      g = d;
      g -= b;
    } while (g != 0);
    if (f == 0)
      ++h;
    g = b - c;
    if (g == 0)
      return h;
    b += 17;
  }
} // 13586198529905

void day23() {

  ifstream ifile("../day23.txt");

  string line;
  vector<Instr> program;
  while (getline(ifile, line)) {
    istringstream iline(line);
    Instr i;
    iline >> i._op >> i._r1 >> i._r2;
    cout << i._op << i._r1 << i._r2 << endl;
    program.push_back(i);
  }

  Computer2 box(program, 0);
      while (box.run() == Computer2::SEND)
    ;
//  box.compile();
  //    while (box.run() == Computer2::SEND)
  //      ;
  //      star1 = box.getLastSent();

    cout << "Day 23 star 1 = " << star1 << "\n";
  cout << "Day 23 star 2 = " << theProgram() << "\n";
} // 11:!7
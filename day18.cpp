//
// Created by Chris Hartman on 11/25/19.
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
using std::move;
using std::pair;
using std::queue;
using std::set;
using std::sqrt;
using std::string;
using std::swap;
using std::vector;

struct Instr {
  string _op;
  string _r1;
  string _r2;
};

class Computer {
public:
  enum Reason { SEND, RECEIVE, END };

private:
  long long val(const string &r) {
    if (r[0] >= 'a' && r[0] <= 'z')
      return _reg[r[0]];
    else {
      istringstream i(r);
      long long n;
      i >> n;
      return n;
    }
  };

public:
  Computer(vector<Instr> v, int id) : _program(move(v)), _reg{{'p', id}} {}
  long long getLastSent() { return _lastSent; }
  void receive(long long r) { _received.push(r); }
  Reason run() {
    while (_pc < _program.size()) {
      const auto &i = _program[_pc];
      ++_pc;
      //      cout << _pc-1 << ":\t " << i._op << " " << i._r1 << " " << i._r2
      //      << " | ";
      if (i._op == "snd") {
        _lastSent = val(i._r1);
        return SEND;
      }
      if (i._op == "set") {
        _reg[i._r1[0]] = val(i._r2);
      }
      if (i._op == "add") {
        _reg[i._r1[0]] += val(i._r2);
      }
      if (i._op == "mul") {
        _reg[i._r1[0]] *= val(i._r2);
      }
      if (i._op == "mod") {
        _reg[i._r1[0]] %= val(i._r2);
      }
      if (i._op == "rcv") {
        if (_received.empty()) {
          --_pc;
          return RECEIVE;
        }
        _reg[i._r1[0]] = _received.front();
        _received.pop();
      }
      if (i._op == "jgz") {
        if (val(i._r1) > 0)
          _pc += val(i._r2) - 1;
      }
      //      for(auto [reg,val]:_reg)
      //        cout << reg << "=" << val << " ";
      //      cout << endl;
    }
    return END;
  }

private:
  vector<Instr> _program;
  map<char, long long> _reg;
  int _pc = 0;
  long long _lastSent = 0;
  queue<long long> _received;
};

void day18() {
  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day18.txt");
  //  istringstream ifile {"set a 1\n"
  //                      "add a 2\n"
  //                      "mul a a\n"
  //                      "mod a 5\n"
  //                      "snd a\n"
  //                      "set a 0\n"
  //                      "rcv a\n"
  //                      "jgz a -1\n"
  //                      "set a 1\n"
  //                      "jgz a -2\n"};
  //  istringstream ifile("snd 1\n"
  //                      "snd 2\n"
  //                      "snd p\n"
  //                      "rcv a\n"
  //                      "rcv b\n"
  //                      "rcv c\n"
  //                      "rcv d\n");
  string line;

  vector<Instr> program;
  while (getline(ifile, line)) {
    istringstream iline(line);
    Instr i;
    iline >> i._op >> i._r1 >> i._r2;
    //    cout << i._op << i._r1 << i._r2 << endl;
    program.push_back(i);
  }

  Computer box(program, 0);
  while (box.run() == Computer::SEND)
    star1 = box.getLastSent();
  cout << "Day 18 star 1 = " << star1 << "\n";

  vector<Computer> boxes{{program, 0}, {program, 1}};
  int which = 0;
  bool canRun[2] = {true, true};
  while (canRun[0] || canRun[1]) {
    switch (boxes[which].run()) {
    case Computer::SEND:
      if (which == 1)
        ++star2;
      boxes[1 - which].receive(boxes[which].getLastSent());
      canRun[1 - which] = true;
      break;
    case Computer::RECEIVE:
      canRun[which] = false;
      which = 1 - which;
      break;
    case Computer::END:
      throw 1;
      break;
    }
  }
  cout << "Day 18 star 2 = " << star2 << "\n";
}
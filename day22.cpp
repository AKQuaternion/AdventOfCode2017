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
using std::forward_as_tuple;
using std::tie;
using std::tuple;
using std::swap;
using std::vector;

void day22() {
  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day22.txt");
  string line;
  int row=0;
  map<pair<int,int>,int> grid;
  while (getline(ifile, line)) {
    for(int i=0;i<line.size();++i)
      grid[{i,row}]=line[i]=='#'?2:0;
    ++row;
  }

  pair<int,int> dirs[4] {{-1,0},{0,-1},{1,0},{0,1}};
  auto dir = 1u;
  auto x=row/2;
  auto y=row/2;

  auto grid2 = grid;
  /*
   * If the current node is infected, it turns to its right. Otherwise, it turns to its left. (Turning is done in-place; the current node does not change.)
If the current node is clean, it becomes infected. Otherwise, it becomes cleaned. (This is done after the node is considered for the purposes of changing direction.)
The virus carrier moves forward one node in the direction it is facing.
   */
  for(int burst=0;burst<10000;++burst) {
    if(grid[{x,y}] == 2) {
      dir = (dir + 1) % 4;
      grid[{x,y}] ='.';
    }
    else {
      dir = (dir + 3) % 4;
      grid[{x,y}] =2;
      ++star1;
    }
    x += dirs[dir].first;
    y += dirs[dir].second;
  }

  cout << "Day 22 star 1 = " << star1 << "\n";
//  Clean nodes become weakened.
//      Weakened nodes become infected.
//      Infected nodes become flagged.
//      Flagged nodes become clean.
//      Every node is always in exactly one of the above states.
//
//      The virus carrier still functions in a similar way, but now uses the following logic during its bursts of action:
//
//  Decide which way to turn based on the current node:
//  If it is clean, it turns left.
//      If it is weakened, it does not turn, and will continue moving in the same direction.
//      If it is infected, it turns right.
//      If it is flagged, it reverses direction, and will go back the way it came.
//      Modify the state of the current node, as described above.
//      The virus carrier moves forward one node in the direction it is facing.
   dir = 1u;
   x=row/2;
   y=row/2;
  for(int burst=0;burst<10000000;++burst) {
    if(grid2[{x,y}] == 0) { //clean
      dir = (dir + 3) % 4;
      grid2[{x,y}] =1;
    }
    else if (grid2[{x,y}] == 1){//weakened
//      dir = (dir + 3) % 4;
      grid2[{x,y}] =2;
      ++star2;
    }
    else if (grid2[{x,y}] == 2){//infected
      dir = (dir + 1) % 4;
      grid2[{x,y}] =3;
    }
    else if (grid2[{x,y}] == 3){//flagged
      dir = (dir + 2) % 4;
      grid2[{x,y}] =0;
    }
    x += dirs[dir].first;
    y += dirs[dir].second;
  }

  cout << "Day 22 star 2 = " << star2 << "\n";
}
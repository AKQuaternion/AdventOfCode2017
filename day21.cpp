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
using std::forward_as_tuple;
using std::ifstream;
using std::istream;
using std::istringstream;
using std::map;
using std::max;
using std::max_element;
using std::min;
using std::ostream;
using std::pair;
using std::set;
using std::sqrt;
using std::string;
using std::swap;
using std::tie;
using std::tuple;
using std::vector;

struct Pattern {
  Pattern(const string &line) {
    string s;
    string input;
    string output;
    istringstream iline(line);
    iline >> input >> s >> output;
    iline.clear();
    iline.str(input);
    while (getline(iline, s, '/'))
      in.push_back(s);
    iline.clear();
    iline.str(output);
    while (getline(iline, s, '/'))
      out.push_back(s);
  }

  vector<string> in;
  vector<string> out;
};

bool operator<(const Pattern &x, const Pattern &y) { return x.in < y.in; }
bool operator==(const Pattern &x, const Pattern &y) { return x.in == y.in; }
bool operator<(const Pattern &x, const vector<string> &y) { return x.in < y; }

void day21() {
  auto star1 = 0;
  auto star2 = 0;
  ifstream ifile("../day21.txt");
  string line;
  vector<Pattern> patterns;

  while (getline(ifile, line)) {
    Pattern p(line);

    vector<Pattern> newOnes(8, p);
    int size = p.in.size();
    for (int transform = 1; transform < 8; ++transform) {
      for (int x = 0; x < size; ++x)
        for (int y = 0; y < size; ++y) {
          auto nx = (transform & 1) ? x : size - 1 - x;
          auto ny = (transform & 2) ? y : size - 1 - y;
          if (transform & 4)
            swap(nx, ny);
          newOnes[transform].in[ny][nx] = p.in[y][x];
        }
    }
    patterns.insert(patterns.end(), newOnes.begin(), newOnes.end());
  }

  sort(patterns.begin(), patterns.end());
  patterns.erase(unique(patterns.begin(), patterns.end()), patterns.end());

  vector<string> image{".#.", "..#", "###"};

  for (int iter = 0; iter < 18; ++iter) {
    auto inChunkSize = (image.size() % 2 == 0) ? 2 : 3;
    auto outChunkSize = inChunkSize + 1;
    auto chunks = image.size() / inChunkSize;
    vector<string> newImage(chunks * outChunkSize,
                         string(chunks * outChunkSize, ' '));
    for (int chunkY = 0; chunkY < chunks; ++chunkY)
      for (int chunkX = 0; chunkX < chunks; ++chunkX) {
        vector<string> patch(inChunkSize, string(inChunkSize, ' '));
        for (int y = 0; y < inChunkSize; ++y)
          for (int x = 0; x < inChunkSize; ++x)
            patch[y][x] =
                image[chunkY * inChunkSize + y][chunkX * inChunkSize + x];

        auto match = std::lower_bound(patterns.begin(), patterns.end(), patch);
        assert(match != patterns.end());

        for (int y = 0; y < outChunkSize; ++y)
          for (int x = 0; x < outChunkSize; ++x)
            newImage[chunkY * outChunkSize + y][chunkX * outChunkSize + x] =
                match->out[y][x];
      }
    image = newImage;

    if (iter == 4)
      for (const auto s : image)
        star1 += std::count(s.begin(), s.end(), '#');
  }
  for (const auto s : image)
    star2 += std::count(s.begin(), s.end(), '#');

  cout << "Day 21 star 1 = " << star1 << "\n";
  cout << "Day 21 star 2 = " << star2 << "\n";
}
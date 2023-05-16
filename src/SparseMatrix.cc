#include "SparseMatrix.hh"

#include <random>
#include <fstream>
#include <cassert>
#include <tuple>

SparseMatrix::SparseMatrix(int m, int n): _m(m), _n(n) {
  static default_random_engine e;
  bernoulli_distribution b(.01);
  uniform_real_distribution<float> u(0, 1);
  vector<float> row;
  for (int i = 0; i < m; ++i) {
    row.clear();
    for (int j = 0; j < n; ++j) {
      row.push_back(b(e) ? u(e) : 0);
    }
    _matrix.push_back(row);
  }
}

SparseMatrix::SparseMatrix(string &filename) {
  ifstream in(filename, ios::in | ios::binary);
  assert(in);
  int m, n;
  in.read(reinterpret_cast<char *>(&m), sizeof(int));
  in.read(reinterpret_cast<char *>(&n), sizeof(int));
  _m = m;
  _n = n;
  vector<float> row;
  for (int i = 0; i < m; ++i) {
    row.clear();
    for (int j = 0; j < n; ++j) {
      float num;
      in.read(reinterpret_cast<char *>(&num), sizeof(float));
      row.push_back(num);
    }
    _matrix.push_back(row);
  }
  in.close();
}

tuple<int, int> SparseMatrix::size() {
  return make_tuple(_m, _n);
}
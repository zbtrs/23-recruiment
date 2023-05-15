#include "SparseMatrix.hh"

#include <random>

SparseMatrix::SparseMatrix(int m, int n) {
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

}
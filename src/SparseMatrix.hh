#pragma once
#include <vector>
#include <string>
#include <tuple>
using namespace std;

struct SparseMatrix {
  vector<vector<float>> _matrix;
  int _m, _n;

  SparseMatrix() = default;
  // generate random data
  SparseMatrix(int m, int n);
  // import data from file
  SparseMatrix(string &filename);
  SparseMatrix(const vector<vector<float>> &m) : _matrix(m), _m(m.size()), _n(m[0].size()) {}
  
  tuple<int, int> size();
};

vector<float> operator*(const vector<float> &vec, const SparseMatrix &matrix);
vector<vector<float>> operator*(const vector<vector<float>> &A, const SparseMatrix &B);

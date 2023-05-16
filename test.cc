#include "SparseMatrix.hh"
#include <cassert>
#include <random>
#include <string>
#include <tuple>
#include <vector>
#include <iostream>

using namespace std;

void random_vec(vector<float> &vec, int size) {
  static default_random_engine e;
  uniform_real_distribution<float> u(-100, 100);
  for (int i =  0; i < size; ++i) {
    vec.push_back(u(e));
  }
  return;
}

vector<vector<float>> create_matrix(int size) {
  static default_random_engine e;
  uniform_real_distribution<float> u(-100, 100);
  vector<float> row;
  vector<vector<float>> matrix;
  for (int i = 0; i < size; ++i) {
    row.clear();
    for (int j = 0; j < size; ++j) {
      row.push_back(u(e));
    }
    matrix.push_back(row);
  }
  return matrix;
}

int main(int argc, char *argv[]) {
  assert(argc > 1);
// read from file
  cout << "test0: " << endl;
  string filename(argv[1]);
  SparseMatrix test0(filename);
  vector<float> vec, res;
  int m, n;
  std::tie(m, n) = test0.size();
  random_vec(vec, n);
  res = vec * test0;
  cout << endl;
// SpMV
  int size = 1024;
  cout << "test1: " << endl;
  SparseMatrix test1(size, size);
  random_vec(vec, size);
  res = vec * test1;
  cout << endl;
// SpMM
  cout << "test2" << endl;
  SparseMatrix test2(size, size);
  vector<vector<float>> A(create_matrix(size));
  vector<vector<float>> C(A * test2);
  cout << endl;
  return 0;
}
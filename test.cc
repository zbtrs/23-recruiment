#include "SparseMatrix.hh"
#include <random>
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

int main() {
// SpMV
  int size = 1024;
  cout << "test1: " << endl;
  vector<float> vec, res;
  SparseMatrix test1(size, size);
  random_vec(vec, size);
  res = vec * test1;
  cout << endl;
// SpMSp
  cout << "test2" << endl;
  SparseMatrix test2(size, size);
  vector<vector<float>> A(create_matrix(size));
  vector<vector<float>> C(A * test2);
  cout << endl;
  return 0;
}
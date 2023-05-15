// optimize function SpMV & SpMSp


#include "SparseMatrix.hh"
#include "timer.hh"
#include <iostream>
#include <chrono>

using namespace chrono;

vector<float> SpMV(const vector<float> &vec, const SparseMatrix &m) {
  if (m._matrix.size() == 0 || m._matrix[0].size() != vec.size()) return vector<float>();
  vector<float> res;
  for (int i = 0; i < m._matrix.size(); ++i) {
    float sum = 0;
    for (int j = 0; j < m._matrix[0].size(); ++j) {
      sum += m._matrix[i][j] * vec[j];
    }
    res.push_back(sum);
  }
  return res;
}

//optmized version
vector<float> SpMV_opt(const vector<float> &vec, const SparseMatrix &m) {
//data format transform
  if (m._matrix.size() == 0 || m._matrix[0].size() != vec.size()) return vector<float>();
  // val: value of non-zero element
  // off: column index of non-zero element in the row
  // idx: the index of first non-zero element in the row
  vector<float> val, res;
  vector<int> idx, off;
  {
    // ScopeTimer timer("data format transform");
    int cnt = 0;
    idx.push_back(cnt);
    for (int i = 0; i < m._matrix.size(); ++i) {
      for (int j = 0; j < m._matrix[0].size(); ++j) {
        if (m._matrix[i][j] != 0) {
          val.push_back(m._matrix[i][j]);
          off.push_back(j);
          ++cnt;
        }
      }
      idx.push_back(cnt);
    }
  }
// calc
  for (int i = 0; i < idx.size() - 1; ++i) {
    float sum = 0;
    for (int j = idx[i]; j < idx[i+1]; ++j) {
      sum += val[j] * vec[off[j]];
    }
    res.push_back(sum);
  }
  return res;
}

// vector<float> operator*(const vector<int> &vec, const Spar)
vector<float> operator*(const vector<float> &vec, const SparseMatrix &m) {
  vector<float> res, res_opt;
  {
    ScopeTimer timer("spmv");
    res = SpMV(vec, m);
  }
  {
    ScopeTimer timer("spmv_opt");
    res_opt = SpMV_opt(vec, m);
  }
  if (res != res_opt) {
    cout << "results not match" << endl;
    return vector<float>();
  }
  return res;
}


vector<vector<float>> SpMM(const vector<vector<float>> &A, const SparseMatrix &B) {
  if (B._matrix.size() == 0 || B._matrix[0].size() != A[0].size()) return vector<vector<float>>();
  vector<vector<float>> C;
  vector<float> row;
  for (int i = 0; i < A.size(); ++i) {
    row.clear();
    for (int j = 0; j < B._matrix.size(); ++j) {
      float sum = 0;
      for (int k = 0; k < B._matrix[0].size(); ++k) {
        sum += A[i][k] * B._matrix[j][k];
      }
      row.push_back(sum);
    }
    C.push_back(row);
  }
  return C;
}

//optimized version
vector<vector<float>> SpMM_opt(const vector<vector<float>> &A, const SparseMatrix &B) {
  if (B._matrix.size() == 0 || B._matrix[0].size() != A[0].size()) return vector<vector<float>>();
  // C: result matrix 
  vector<vector<float>> C;
  vector<float> val;
  vector<int> idx, off;
  {
    // ScopeTimer timer("data format transform");
    int cnt = 0;
    idx.push_back(cnt);
    for (int i = 0; i < B._matrix.size(); ++i) {
      for (int j = 0; j < B._matrix[0].size(); ++j) {
        if (B._matrix[i][j] != 0) {
          val.push_back(B._matrix[i][j]);
          off.push_back(j);
          ++cnt;
        }
      }
      idx.push_back(cnt);
    }
  }
  //calc
  {
    // ScopeTimer timer("calc");
    vector<float> row;
    for (int row_A = 0; row_A < A.size(); ++row_A) {
      row.clear();
      for (int row_B = 0; row_B < idx.size() - 1; ++row_B) {
        float sum = 0;
        for (int j = idx[row_B]; j < idx[row_B+1]; ++j) {
          sum += val[j] * A[row_A][off[j]];
        }
        row.push_back(sum);
      }
      C.push_back(row);
    }
  }
  return C;
}

vector<vector<float>> operator*(const vector<vector<float>> &A, const SparseMatrix &B) {
  vector<vector<float>> C, C_opt;
  {
    ScopeTimer timer("SpMM");
    C = SpMM(A, B);
  }
  {
    ScopeTimer timer("SpMM_opt");
    C_opt = SpMM_opt(A, B);
  }
  if (C != C_opt) {
    cout << "test2 results not match" << endl;
    return vector<vector<float>>();
  }
  return C;
}
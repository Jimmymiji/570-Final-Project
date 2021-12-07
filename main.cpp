#include <unordered_map>
#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
#include <algorithm>

#include "stringGenerator.h"

using namespace std;

const unordered_map<char, unordered_map<char, int>> costTable = {
    {'A', {{'A', 0}, {'C', 110}, {'G', 48}, {'T', 94}}},
    {'C', {{'A', 110}, {'C', 0}, {'G', 118}, {'T', 48}}},
    {'G', {{'A', 48}, {'C', 118}, {'G', 0}, {'T', 110}}},
    {'T', {{'A', 94}, {'C', 48}, {'G', 110}, {'T', 0}}}};
const int gapPenalty = 30;

int basicAlignment(const string& str1, const string& str2, string& newStr1,
                   string& newStr2) {
  int m = str1.size();
  int n = str2.size();
  vector<vector<int>> DP = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
  for (int i = 1; i <= m; i++) {
    DP[i][0] = i * gapPenalty;
  }
  for (int i = 1; i <= n; i++) {
    DP[0][i] = i * gapPenalty;
  }

  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      int tmp1 = costTable.at(str1[i - 1]).at(str2[j - 1]) + DP[i - 1][j - 1];
      int tmp2 = gapPenalty + DP[i - 1][j];
      int tmp3 = gapPenalty + DP[i][j - 1];
      if (tmp1 <= tmp2 && tmp1 <= tmp3) {
        DP[i][j] = tmp1;
        continue;
      }
      if (tmp2 <= tmp1 && tmp2 <= tmp3) {
        DP[i][j] = tmp2;
        continue;
      }
      if (tmp3 <= tmp1 && tmp3 <= tmp2) {
        DP[i][j] = tmp3;
        continue;
      }
    }
  }

  int l = m + n;
  newStr1.resize(l);
  newStr2.resize(l);
  int idx1 = l - 1;
  int idx2 = l - 1;
  int i = m;
  int j = n;
  while (i != 0 && j != 0) {
    if (DP[i - 1][j - 1] + costTable.at(str1[i - 1]).at(str2[j - 1]) ==
        DP[i][j]) {
      newStr1[idx1--] = str1[i - 1];
      newStr2[idx2--] = str2[j - 1];
      i--;
      j--;
    } else if (DP[i][j - 1] + gapPenalty == DP[i][j]) {
      newStr1[idx1--] = '_';
      newStr2[idx2--] = str2[j - 1];
      j--;
    } else {
      newStr1[idx1--] = str1[i - 1];
      newStr2[idx2--] = '_';
      i--;
    }
  }
  while (idx1) {
    newStr1[idx1--] = (i > 0) ? str1[i - 1] : '_';
    i--;
  }
  while (idx2) {
    newStr2[idx2--] = (j > 0) ? str2[j - 1] : '_';
    j--;
  }
  int start = 1;
  while (newStr1[start] == '_' && newStr2[start] == '_') {
    start++;
  }
  newStr1 = newStr1.substr(start);
  newStr2 = newStr2.substr(start);

  return DP[m][n];
}

vector<int> sapceEfficientAlignment(const string& str1, const string& str2) {
  int m = str1.size();
  int n = str2.size();
  vector<vector<int>> DP = vector<vector<int>>(2, vector<int>(m + 1, 0));
  for (int i = 0; i <= m; i++) {
    DP[0][i] = i * gapPenalty;
  }

  for (int j = 1; j <= n; j++) {
    DP[1][0] = j * gapPenalty;
    for (int i = 1; i <= m; i++) {
      int tmp1 = DP[0][i - 1] +
                 costTable.at(str1[i - 1]).at(str2[j -1]);
      int tmp2 = DP[0][i] + gapPenalty;
      int tmp3 = DP[1][i - 1] + gapPenalty;
      if (tmp1 <= tmp2 && tmp1 <= tmp3) {
        DP[1][i] = tmp1;
        continue;
      }
      if (tmp2 <= tmp1 && tmp2 <= tmp3) {
        DP[1][i] = tmp2;
        continue;
      }
      if (tmp3 <= tmp1 && tmp3 <= tmp2) {
        DP[1][i] = tmp3;
        continue;
      }
    }
    DP[0] = DP[1];
  }
  return DP[1];
}

int helper(const string& str1, const string& str2,
                              int start1, int end1, int start2, int end2,
                              vector<vector<int>>& P) {
  int m = end1 - start1 + 1;
  int n = end2 - start2 + 1;

  // Small problem solved with basic alignment algorithm
  if (m < 3 || n < 3) {
    vector<vector<int>> DP = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
      DP[i][0] = i * gapPenalty;
    }
    for (int i = 1; i <= n; i++) {
      DP[0][i] = i * gapPenalty;
    }
    for (int i =  1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        int tmp1 = costTable.at(str1[i + start1 - 1]).at(str2[j + start2 - 1]) +
                   DP[i-1][j-1];
        int tmp2 = gapPenalty + DP[i - 1][j];
        int tmp3 = gapPenalty + DP[i][j - 1];
        if (tmp1 <= tmp2 && tmp1 <= tmp3) {
          DP[i - 1][j - 1] = tmp1;
          continue;
        }
        if (tmp2 <= tmp1 && tmp2 <= tmp3) {
          DP[i - 1][j] = tmp2;
          continue;
        }
        if (tmp3 <= tmp1 && tmp3 <= tmp2) {
          DP[i][j - 1] = tmp3;
          continue;
        }
      }
    }

    int l = m + n;
    int idx1 = l - 1;
    int idx2 = l - 1;
    int i = m;
    int j = n;
    P.push_back({end1, end2});
    while (i != 0 && j != 0) {
      if (DP[i - 1][j - 1] +
              costTable.at(str1[i + start1 - 1]).at(str2[j + start2 - 1]) ==
          DP[i][j]) {
        i--;
        j--;
      } else if (DP[i - start1][j - start2 - 1] + gapPenalty ==
                 DP[i - start1][j - start2]) {
        j--;
      } else {
        i--;
      }
      P.push_back({i + start1 - 1, j + start2 - 1});
    }
    return DP[m][n];
  }
  
  vector<int> forwardCost = sapceEfficientAlignment(str1, str2.substr(start2, n/2));

  string tmp1 = str1.substr(start1, m);
  string tmp2 = str2.substr(start2, n);
  reverse(tmp1.begin(), tmp1.end());
  reverse(tmp2.begin(), tmp2.end());
  vector<int> backwardCost = sapceEfficientAlignment(tmp1, tmp2);

  int q = -1;
  int minCost = INT16_MAX; 
  for (int i = 1; i <= m; i++) {
    if (forwardCost[i] + backwardCost[i] < minCost) {
      minCost = forwardCost[i] + backwardCost[i];
      q = i;
    }
  }
  q = q + start1 - 1;

  return minCost +
         helper(str1, str2, start1, start1 + q, start2, start2 + n / 2, P) +
         helper(str1, str2, start1 + q + 1, end1, start2 + n / 2 + 1, end2, P);
}

int devideAndConquerAlignment(const string& str1, const string& str2,
                              string& newStr1, string& newStr2) {
  int m = str1.size();
  int n = str2.size();
  vector<vector<int>> path;
  int cost = helper(str1, str2, 0, m - 1, 0, n - 1, path);

  // costtruct new string from path

  return cost;
}

int checkAlignment(const string& str1, const string& str2) {
  int ans = 0;
  int s = str1.size() < str2.size() ? str1.size() : str2.size();
  for (int i = 0; i < s; i++) {
    if (str1[i] == '_' || str2[i] == '_') {
      ans = ans + gapPenalty;
    } else {
      ans = ans + costTable.at(str1[i]).at(str2[i]);
    }
  }
  ans = ans + (str1.size() - s + str2.size() - s) * gapPenalty;
  return ans;
}

int main() {
  stringGenerator sg1("BaseTestcases_CS570FinalProject/input1.txt");
  stringGenerator sg2("BaseTestcases_CS570FinalProject/input2.txt");

  string new1, new2, newa, newb;

  string str1 = sg1.getFirstString();
  string str2 = sg1.getSecondString();
  int ans1 = devideAndConquerAlignment(str1, str2, new1, new2);
  cout << "Ans1: " << ans1 << endl;
  cout << "new1: " << new1 << endl;
  cout << "new2: " << new2 << endl;
  cout << "checkAlignment(new1, new2): " << checkAlignment(new1, new2) << endl;

  string stra = sg2.getFirstString();
  string strb = sg2.getSecondString();
  int ans2 = devideAndConquerAlignment(stra, strb, newa, newb);
  cout << "Ans2: " << ans2 << endl;
  cout << "newa: " << newa << endl;
  cout << "newb: " << newb << endl;
  cout << "checkAlignment(newa, newb): " << checkAlignment(newa, newb) << endl;

  return 0;
}
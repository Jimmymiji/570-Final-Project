#include <stdio.h>
#include <unistd.h>
#include <ios>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <ctime>


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

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Please secify input file" << endl;
    return 0;
  }

  string filename = argv[1];

  stringGenerator sg(filename);

  string str1 = sg.getFirstString();
  string str2 = sg.getSecondString();
  string new1, new2;

  double time_elapsed_ms = 0;
  int ans = 0;
  
  
  // clock_t c_start = std::clock();
  ans = basicAlignment(str1, str2, new1, new2);
  // clock_t c_end = std::clock();
  // time_elapsed_ms = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
  // cout << "Cost: " << ans << endl;
  // cout << "new1: " << new1 << endl;
  // cout << "new2: " << new2 << endl;
  // cout << "checkAlignment(new1, new2): " << checkAlignment(new1, new2)
  //       << endl;
  // std::cout << "CPU time used: " << time_elapsed_ms << " ms\n";

  // Write to file
  ofstream myfile;
  // string outFileName = filename.substr(0, filename.size() - 4) + "_output.txt";
  myfile.open ("data/output_basic.txt");
  if(new1.size() <= 50){
    myfile << new1 << " " << new1 << "\n";
  } else {
    myfile << new1.substr(0, 50) << " " << new1.substr(new1.size() - 50, 50) << "\n";
  }
  if(new2.size() <= 50){
    myfile << new2 << " " << new2 << "\n";
  } else {
    myfile << new2.substr(0, 50) << " " << new2.substr(new2.size() - 50, 50) << "\n";
  }
  myfile << ans * 1.0 << "\n";
  // myfile << time_elapsed_ms / 1000.0 << "\n";
  myfile.close();

  return 0;
}
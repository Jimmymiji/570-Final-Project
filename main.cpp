#include "stringGenerator.h"
#include <unordered_map>

const unordered_map<char, unordered_map<char, int>> costTable = {{'A', {{'A', 0}, {'C', 110}, {'G', 48}, {'T', 94}}},
                                                                {'C', {{'A', 110}, {'C', 0}, {'G', 118}, {'T', 48}}}
                                                                {'G', {{'A', 48}, {'C', 118}, {'G', 0}, {'T', 110}}}
                                                                {'T', {{'A', 94}, {'C', 48}, {'G', 110}, {'T', 0}}}};
const int gapPenalty = 30;

int basicAlignment(const string& str1, const string& str2, vector<vector<int>>& M){
    int m = str1.size();
    int n = str2.size();
    vector<vector<int>> DP = vector<vector<int>>(m+1, vector<int>(n+1,0));
    for(int i = 0; i <= m; i++){
        DP[i][0] = i * gapPenalty;
    }
    for(int i = 0; i <= n; i++){
        DP[0][i] = i * gapPenalty;
    }

    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= n; j++){
            int tmp1 = costTable[str1[i]][str2[j]] + DP[i-1][j-1];
            int tmp2 = gapPenalty + DP[i-1][j];
            int tmp3 = gapPenalty + DP[i][j-1];
        }
    }

}

int main(){
    stringGenerator sg("BaseTestcases_CS570FinalProject/input1.txt");
    return 0;
}
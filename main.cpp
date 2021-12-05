#include "stringGenerator.h"
#include <unordered_map>

const unordered_map<char, unordered_map<char, int>> costTable = {
    {'A', {{'A', 0}, {'C', 110}, {'G', 48}, {'T', 94}}},
    {'C', {{'A', 110}, {'C', 0}, {'G', 118}, {'T', 48}}},
    {'G', {{'A', 48}, {'C', 118}, {'G', 0}, {'T', 110}}},
    {'T', {{'A', 94}, {'C', 48}, {'G', 110}, {'T', 0}}}
    };
const int gapPenalty = 30;

int basicAlignment(const string& str1, const string& str2, string& newStr1, string& newStr2){
    int m = str1.size();
    int n = str2.size();
    vector<vector<int>> DP = vector<vector<int>>(m+1, vector<int>(n+1,0));
    for(int i = 1; i <= m; i++){
        DP[i][0] = i * gapPenalty;
    }
    for(int i = 1; i <= n; i++){
        DP[0][i] = i * gapPenalty;
    }

    for(int i = 1; i <= m; i++){    
        for(int j = 1; j <= n; j++){
            int tmp1 = costTable.at(str1[i-1]).at(str2[j-1]) + DP[i-1][j-1];
            int tmp2 = gapPenalty + DP[i-1][j];
            int tmp3 = gapPenalty + DP[i][j-1];
            if(tmp1 <= tmp2 && tmp1 <= tmp3){
                DP[i][j] = tmp1;
                continue;
            }
            if(tmp2 <= tmp1 && tmp2 <= tmp3){
                DP[i][j] = tmp2;
                continue;
            }
            if(tmp3 <= tmp1 && tmp3 <= tmp2){
                DP[i][j] = tmp3;
                continue;
            }
        }
    }

    int l = m + n;
    newStr1.resize(l);
    newStr2.resize(l);
    int idx1 = l;
    int idx2 = l;
    int i = m;
    int j = n;
    while( i!= 0 && j != 0){ 
        if(DP[i-1][j-1] + costTable.at(str1[i-1]).at(str2[j-1]) == DP[i][j]){
            newStr1[idx1--] = str1[i--];
            newStr2[idx2--] = str2[j--];
        } else if (DP[i-1][j] + gapPenalty == DP[i][j]){
            newStr1[idx1--] = str1[i--];
            newStr2[idx2--] = '_';
        } else {
            newStr1[idx1--] = '_';
            newStr2[idx2--] = str2[j--];
        }
    }
    while(idx1){
        newStr1[idx1--] = i > 0 ? str1[i--] : '_';
    }
    while(idx2){
        newStr2[idx2--] = j > 0 ? str2[j--] : '_';
    }
    int start = 0;
    while(start < l && newStr1[start] == '_' && newStr2[start] == '_'){
        start++;
    }

    newStr1 = newStr1.substr(start);
    newStr2 = newStr2.substr(start);
    
    return DP[m][n];
}

int main(){
    stringGenerator sg1("BaseTestcases_CS570FinalProject/input1.txt");
    stringGenerator sg2("BaseTestcases_CS570FinalProject/input2.txt");

    string new1, new2, newa, newb;
    
    string str1 = sg1.getFirstString();
    string str2 = sg1.getSecondString();
    int ans1 = basicAlignment(str1, str2, new1, new2);
    cout << "Ans1: " << ans1 << endl;
    cout << "new1: " << new1 << endl;
    cout << "new1f:" << new1.substr(0,50) << endl;
    cout << "      "<<"ACACACTGAC_TACTGACTGGTG_ACTACTG_ACT_G_GACTGAC_TACT" << endl;
    cout << "new1l:" << new1.substr(new1.size() - 50,50) << endl;
    cout << "      "<<"TAT_TA_TTATACG_CTA_TTATACG_CGACGCGGACGC_G_T_ATACG_" << endl;
    cout << "new2: " << new2 << endl;
    cout << "new2f:" << new2.substr(0,50) << endl;
    cout << "      "<<"CTACTG_ACT_G_GACTGAC_TACTGACTGGTG_ACTACTG_ACT_G_G_" << endl;
    cout << "new2l:" << new2.substr(new2.size() - 50,50) << endl;
    cout << "      "<<"G_CGACGCGGACGC_G_T_ATACG_CTA_TTATACG_CGACGCGGACGCG" << endl;

   
    string stra = sg2.getFirstString();
    string strb = sg2.getSecondString();
    int ans2 = basicAlignment(stra, strb, newa, newb);
    cout << "Ans2: " << ans2 << endl;
    cout << "newa: " << newa << endl;
    
    cout << "newb: " << newb << endl;
    // for(auto& a : M){
    //     for(auto b : a){
    //         cout << b << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}
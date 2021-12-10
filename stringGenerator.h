#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include <fstream>

using namespace std;

class stringGenerator{
    private:
    string str1, str2;
    vector<int> jumpIdx1 = {}, jumpIdx2 = {};
    
    public:
    stringGenerator(string filename){
        ifstream infile(filename);
        for( string line; getline( infile, line ); )
        {
            if(line[line.size() - 1] == 13){
                line = line.substr(0, line.size()-1);
            }
            if(jumpIdx1.empty() && str1 == ""){
                str1 = line;      
                continue;
            }
            if(isdigit(line[0]) && str2 == ""){
                jumpIdx1.push_back(stoi(line));
                continue;
            }
            if(!isdigit(line[0])){
                str2 = line;
                continue;
            }
            jumpIdx2.push_back(stoi(line));
        }

        for(int a : jumpIdx1){
            string tmp = str1;
            str1 = tmp.substr(0, a+1) + tmp + tmp.substr(a+1);
        }


        for(int a : jumpIdx2){
            string tmp = str2;
            str2 = tmp.substr(0, a+1) + tmp + tmp.substr(a+1);
        }

    }

    string getFirstString(){
        return str1;
    }

    string getSecondString(){
        return str2;
    }   

};
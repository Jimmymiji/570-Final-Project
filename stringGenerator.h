#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include <fstream>

using namespace std;

class stringGenerator{
    private:
    string str1, str2;
    vector<int> jumpIdx1, jumpIdx2;
    
    public:
    stringGenerator(string filename){
        string line;
        ifstream infile(filename);
        while (getline(infile, line))
        {
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

        cout << "string 1 is: " << str1 << endl;
        for(int a : jumpIdx1){
            cout << a << " ";
        }
        cout << endl;
        cout << "string 2 is: " << str2 << endl;
        for(int a : jumpIdx2){
            cout << a << " ";
        }
        cout << endl;

        for(int a : jumpIdx1){
            string tmp = str1;
            str1 = tmp.substr(0, a+1) + tmp + tmp.substr(a+1);
            break;
        }
        cout << str1 << endl;

        for(int a : jumpIdx2){
            string tmp = str2;
            str2 = tmp.substr(0, a+1) + tmp + tmp.substr(a+1);
            break;
        }
        cout << str2 << endl;
    }

    string getFirstString(){
        return str1;
    }

    string getSecondString(){
        return str1;
    }   

};
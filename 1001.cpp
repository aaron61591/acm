/*************************************************************************
    > File Name: 1001.cpp
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2013年10月16日 星期三 09时09分20秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class power {

    friend istream& operator >> (istream &ln, power &r);
    public:
        string operator () (int n);
    private:
        vector<int> s;
        int dot;
}

istream& operator >> (istream &ln, power &r) {

    string tmp;
    ln>>tmp;
    for(int i = 0; i != 6; ++i) {
        if(tmp[i] == '.') {
            r.dot = 6-i-1;
        }
    }
    r.s.clear();
    for(int i = 5; i >= 0; --i){
        if(tmp[i] != '.') {
            r.s.push_back(tmp[i] - '0');
        }
    }
    return(ln);
}

string power::operator () (int n) {

    vector<int> answer(n * 5);
    answer[0] = 1;
    for(int i = 0; i != n; ++i) {
        vector<int> tmp(answer);
        for(int j = 0; j != n * 5; ++j) {
            answer[j] = 0;
        }
        for(int j = 0; j != n * 5; ++;) {
            for(int k = 0; k != 5;)
        }
    }
}

int main (){

    power s;
    int n;
    while(cin>>s>>n)cout<<s(n)<<endl;
}

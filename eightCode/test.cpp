/*************************************************************************
    > File Name: test.cpp
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2013年11月06日 星期三 10时25分40秒
 ************************************************************************/

#include <iostream>
#include <stdlib.h>

using namespace std;

int& iniInt(int a) {
    int* p = new int;
    cout<<"new address: "<<p<<endl;
    *p = a;
    return *p;
}

int main () {
    int a = iniInt(2);
    cout<<"var address: "<<&a<<endl;
    int& b = a;
    cout<<sizeof(b)<<endl;
    int c = b;
    cout<<&c<<endl;
}

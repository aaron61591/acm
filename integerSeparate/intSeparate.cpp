/*************************************************************************
    > File Name: intSeparate.cpp
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2013年10月17日 星期四 18时31分39秒
 ************************************************************************/

#include <iostream>

using namespace std;

int sepInt (int n, int m) {

    if (n < 0)
       throw n;
    else if (n == 1 || m == 1)
        return 1;
    else if (n == m)
        return sepInt(n, m - 1) + 1;
    else if (n > m)
        return sepInt(n, m - 1) + sepInt(n - m, m);
    else if (n < m)
        return sepInt(n, n);
}

int main () {

    int n;
    while (cin>>n){
        try {
            cout<<sepInt(n, n)<<endl;
        } catch (int e) {
            cerr<<"Are you kidding me?"<<e<<" is not ok"<<endl;
        }
    }
    return 0;
}

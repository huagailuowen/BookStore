#include<bits/stdc++.h>
#include <shared_mutex>
#include <thread>
// #include"M"
using namespace std;
    shared_mutex s_m;
int f(int n)
{
    s_m.lock_shared();
    cerr<<n<<'\n';
    // s_m.unlock();
    return (n<2)?n:f(n-1)+f(n-2);
}
int main()
{
    // s_m.lock_shared();
    
    int a=0;
    const int &b=a;
    a+=1;
    cout<<b;
    f(a);
    return 0;
}
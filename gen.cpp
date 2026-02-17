#include<bits/stdc++.h>
#include "./lib/random.h"
#define ll long long
#define loop(i,s,n) for(ll i = s; i < n; ++i)


using namespace std;

#define random uniform

string random_string(int n){
    string res = "";
    res.reserve(n+1);
    for(int i = 0; i < n; ++i){
        res.push_back('a'+random(0,26));
    }
    return res;
}

int main(){
    // freopen("in.txt", "w", stdout);
    int t = 1;
    ll n = random(5,10);
    cout << t << ' ' << n;
    loop(i,0,n)
        cout << random(1,20) << ' ';
    cout << '\n';

}

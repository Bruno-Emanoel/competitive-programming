#include<bits/stdc++.h>
#include "./lib/random.h"
#define ll long long
#define loop(i,s,n) for(ll i = s; i < n; ++i)


using namespace std;

#define random uniform

string random_string(int n){
    string res = "";
    res.reserve(n+1);
    char cc[]={'.','.','K'};
    for(int i = 0; i < n; ++i){
        res.push_back(cc[random(0, 2)]);
    }
    return res;
}

int main(){
    // freopen("in.txt", "w", stdout);
    int t = 1;
    ll n = random(5,6);
    loop(i,0,n)
        cout << random_string(n)<<endl;

}

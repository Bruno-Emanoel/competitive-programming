#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <algorithm>
#include <climits>
#include <math.h>
#include <map>
#include <chrono>
#include <numeric>

using namespace std;

#define ll long long
#define vll vector<ll>
#define vpll vector<pll>
#define v vector
#define matrix v<v<ll>>
#define pq priority_queue
#define pll pair<ll,ll>
#define Tree v<list<int>>
#define loop(i,s,n) for(ll i = s; i < n; i++)
#define downto(i,s,n) for(ll i = s; i >= n; i--)
#define foreach(i,v) for(auto &i:v)
#define full(a) a.begin(), a.end()
#define populate(vec) for(auto &i:vec) cin >> i;
#define getBit(x,i) ((1<<i)&x)
#define ssort stable_sort
#define INF LLONG_MAX
#define NINF LLONG_MIN
#define unmap unordered_map
#define unset unordered_set
#define ispot2(x) ((1<<lg(x))==x)
#define getPot(x)  (((ll)1)<<x)
#define dobdiv(a,b) ((double)a/(double)b)
#define mset multiset
#define mmap multimap

#ifdef LOCAL
#include "debug/debug.h"
#else
#define debug(...) {}
#endif


template <typename T>
void print(v<T> &vec) {
  for(size_t i = 0; i < vec.size(); ++i) {
    cout << vec[i] << " \n"[i==vec.size()-1];
  }
}

ll f(ll b, ll x) {
  ll res = 0;
  while(x%b==0)
  ++res,x/=b;
  return res;
}

void solve() {
  #define CANT { cout << "NO\n"; return; }
  ll x, y; cin >> x >>y;
  vll vec(x);vec[0]=1;
  ll best=0;
  ll n = x,m=y;
  v<vll> dp(n,vll(m+1,0));
  loop(i,1,n) {
    loop(j,i+1,m-(n-1-i)+1){
      best=max(best,
      dp[i][j]=max(dp[i][j-1],dp[i-1][j-1]+f(i+1,j))
      );
    }
  } 
  cout << best << '\n';
  //print(save);
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(nullptr);
  int t=1;
  
  cin >> t;
  
  while(t--) {
    solve();
  }
  return 0;
}

// 4+3+2+1+2+0+1
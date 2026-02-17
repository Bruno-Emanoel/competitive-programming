#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <set>
#include <unordered_map>
#include <cstring>
#include <numeric>
#include <queue>
#include <numbers>
#include <bit>
#include <queue>
#include <chrono>
#include <math.h>
#include <iterator>
#include <list>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

#define ll long long 
#define ull unsigned long long 
#define pll pair<ll,ll>
#define vll vector<ll>
#define vpll vector<pll>
#define v vector
#define loop(i,s,n) for(ll i = s; i < n; ++i)
#define downto(i,s,n) for(ll i = s; i >= n; --i)
#define foreach(i,v) for(auto &i:v)
#define full(a) a.begin(), a.end()
#define getBit(x,i) ((1LL<<i)&(x))
#define ispot2(x) ((1LL<<lg(x))==(x))
#define getPot(x)  ((1LL)<<(x))
#define INF LLONG_MAX
#define NINF LLONG_MIN
//#define PI std::numbers::pi
#define unmap unordered_map
#define unset unordered_set
#define mset multiset
#define mmap multimap
//#define ordered_set __gnu_pbds::tree<ll, __gnu_pbds::null_type, less<ll>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>
//#define ordered_multiset __gnu_pbds::tree<ll, __gnu_pbds::null_type, less_equal<ll>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>
//#define ordered_map __gnu_pbds::tree<ll, ll, less<ll>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>



#ifdef LOCAL
//#include "lib/random.h"
//#include "lib/mymath.h"
//#include "lib/geo.h"
//#include "lib/segtree.h"
//#include "lib/custom_addons.h"
//#include "lib/mystrings.h"
#include "debug/debug.h"
#else
#define debug(...) {}
#endif

// UTIL 
constexpr inline int lg(ull i) {
  return __bit_width(i) - 1;
}

template <typename T>
bool sign(T x) {
  return x&NINF;
}

// READING
template <typename T>
inline void getall(v<T> &a) {
  for(auto&i:a)
    i.read();
}

inline void getall(vll &a) { for(auto&i:a)cin>>i;}
inline void getall(vpll &a) { for(auto&i:a)cin>>i.first>>i.second;}

// PRINTING
template <typename T>
void print(const v<T> &vec) {
  for(size_t i = 0; i < vec.size(); ++i) {
    cout << vec[i] << " \n"[i==vec.size()-1];
  }
}
void print(const vpll &vec) {
  for(const auto &[a,b]:vec)
    cout << a << ' ' << b << '\n';
}

// CODE BELOW HERE
 
constexpr ll MAXN = 2e5;
vpll t[MAXN];

struct cmp{
  bool operator()(pll &a, pll &b) {return a.second>b.second;}
};

struct mng {
  ll n; mng(ll n):n{n}{}
  ~mng(){
    loop(i,0,n)
      t[i].clear();
  }
};

void solve() {
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(nullptr);
  int t=1;
  cin >> t;
  while(t--)
    solve();
  return 0;
}

// 1 8 40
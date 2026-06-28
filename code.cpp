/*  CODE.CPP  */
#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")

using ldouble = long double;
using ll = long long int;
using ull = unsigned long long int;
using pll = pair<ll,ll>;
using vll = vector<ll>;
using vpll = vector<pll>;
template <typename T>
using v = vector<T>;

#define loop(i,s,n) for(ll i = s; i < (ll)n; ++i)
#define downto(i,s,n) for(ll i = s; i >= (ll)n; --i)
#define foreach(i,v) for(auto &i:v)

#define full(a) a.begin(), a.end()

constexpr ll INF = LLONG_MAX;
constexpr ll NINF = LLONG_MIN;
//constexpr ldouble PI  = numbers::pi;

#ifdef LOCAL
#include "debug/debug.h"
#else
#define debug(...) {}
#endif

constexpr inline unsigned lg(ull x)     { return __bit_width(x)-1; }
constexpr inline ll getBit(ll x, ll i)  { return (1LL<<i) & x; }
constexpr inline ll ispot2(ll x)        { return (1LL<<lg(x)) == x; }
constexpr inline ll getPot(ll x)        { return 1ULL<<x; }
constexpr inline ll getMsb(ll x)        { return getPot(lg(x)); }

constexpr inline pll mkpll(ll a, ll b) { return make_pair(a,b); }

// READING
inline void getall(vll &a) { for(auto&i:a)cin>>i;}
inline void getall(vpll &a) { for(auto&i:a)cin>>i.first>>i.second;}
inline void getalt(vpll &a) { for(auto&i:a)cin>>i.first;for(auto&i:a)cin>>i.second;}
// PRINTING
template <typename T>
void print(const v<T> &vec, char sep = ' ') {
  char sepp[] = {sep, '\n'};
  for(size_t i = 0; i < vec.size(); ++i)
    cout << vec[i] << sepp[i==vec.size()-1];
}
void print(const vpll &vec) {
  for(const auto &[a,b]:vec)
    cout << a << ' ' << b << '\n';
}
// CODE BELOW HERE

void solve() {
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr);
  cerr.tie(nullptr);
  int t=1; 
  cin >> t; 
  while(t--)
    solve();
  return 0;
}

/*  CODE.CPP  */
#include <bits/stdc++.h>
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

#define double long double
#define ll long long 
#define pll pair<ll,ll>
#define vll vector<ll>
#define vpll vector<pll>
#define v vector

#define loop(i,s,n) for(ll i = s; i < (ll)n; ++i)
#define downto(i,s,n) for(ll i = s; i >= (ll)n; --i)
#define foreach(i,v) for(auto &i:v)

#define full(a) a.begin(), a.end()
#define getBit(x,i) ((1LL<<i)&(x))
#define ispot2(x) ((1LL<<lg(x))==(x))
#define getPot(x)  ((1ULL)<<(x))
#define getMsb(x) getPot(lg(x))

#define INF LLONG_MAX
#define NINF LLONG_MIN
#define PI acos(-1)

// template <typename T = ll, typename Cmp = greater_equal<ll>>
// using ordered_multiset = __gnu_pbds::tree<T, __gnu_pbds::null_type, Cmp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

//typedef gp_hash_table<ll, ll, hash<ll>, equal_to<ll>, direct_mod_range_hashing<ll>, linear_probe_fn<>,
//                      hash_standard_resize_policy<hash_prime_size_policy, hash_load_check_resize_trigger<true>, true>>
//    hashT;


#ifdef LOCAL
#include "debug/debug.h"
#else
#define debug(...) {}
#endif

constexpr unsigned ll lg(ll x) {
  return __bit_width(x)-1;
}

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

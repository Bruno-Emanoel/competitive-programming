#include <bits/stdc++.h>
#include "mymath.h"
using namespace std;
#define ll long long
#define ull unsigned ll
#define v vector
#define full(a) a.begin(), a.end()
#define loop(i,s,n) for(ll i = s; i < n; ++i)
#define getPot(i) ((1ULL)<<(i))

// Bitset used for subset sum optimization
class BitSet {
  public:
  ll n, sz;
  v<ull> vec;
  ll best=-1;
  BitSet(ll n): n{n}, sz{n/64+1}, vec(sz) {}
  void limit() {
    if(this->n%64==63)
      *vec.rbegin()&=0ULL-1;
    else
      *vec.rbegin()&=getPot(this->n%64+1)-1;
  }
  void set(ll i) {
    vec[i/64]|=getPot(i%64);
    best=max(best,i);
  }
  BitSet& operator<<=(ll n) {
    ll i = (best/64);
    while(i>=0) {
      if(vec[i]==0){--i;continue;}
      if(i+n/64<sz) {
        if(n%64&&i+(n+63)/64<sz) {
          ll ind = i+(n+63)/64;
          vec[ind]|=vec[i]>>(64-(n%64));
          if(ind==sz-1)
            limit();
          if(vec[ind])
            best=max<ll>(best,64*ind+lg(vec[ind]));
        }
        ll ind = i+n/64;
        vec[ind]|=vec[i]<<(n%64);
        if(ind==sz-1) 
          limit();

        if(vec[ind])
          best=max<ll>(best,64*ind+lg(vec[ind]));
      }
      i--;
    }
    return *this;
  }
};

// Solve subset sum for x with elements of vec
// if vec has sum C, solves in O(C*sqrt(C)/64)
// For small x can be faster and bounded by O(nlogn)
ll subsetSum(v<ll> &vec, ll x, bool isSort=false) {
  if(!isSort)
    sort(full(vec));
  vec.emplace_back(1e18);
  v<ll> a;
  ll las = 1;
  loop(i,1,(ll)vec.size()) {
    if(vec[i]!=vec[las]) {
      ll x = i-las, j = 0;
      if(x%vec[las]==0&&x/vec[las]<=x) // If only need one elm is needed and has right amount
        return x;
      while(x>=getPot(j)) {
        x-=getPot(j);
        a.emplace_back(vec[las]*getPot(j++));
      }
      if(x)
        a.emplace_back(vec[las]*x);
      las=i;
    }
    if(vec[i]>x) break;
  }
  BitSet can(x);
  can.set(0);
  for(auto num:a) 
    can<<=num;
  return can.best;
}
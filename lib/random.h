#ifndef ll
#include<bits/stdc++.h>
#define ll long long
using namespace std;
#endif

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();

int uniform(int l, int r) { return uniform_int_distribution<int>(l, r)(rng); }
double genReal() { return uniform_real_distribution(0.0,1.0)(rng); }

vector<vector<int>> randGraph(int n, double chance) {
  vector<vector<int>> g(n);

  for(int i = 0; i < n; ++i) {
    for(int j = i+1; j<n; ++j) {
      if(genReal()<=chance) {
        g[i].emplace_back(j);
        g[j].emplace_back(i);
      }
    }
  }

  return g;
}


ll find(ll a, vector<ll> &p) {
  if(p[a]==a) return a;
  return p[a] = find(p[a],p);
}
void unite(ll a, ll b, vector<ll> &p) {
  a = find(a,p), b = find(b,p);
  if(a!=b){
    p[a] = b;
  }
}
vector<pair<ll,ll>> randTree(ll n){
  vector<pair<ll,ll>> tree;
  vector<ll> p(n);
  for(int i = 0; i < n; i++)
    p[i] = i;
  for(int i = 1; i < n; i++) {
    ll origin;
    ll next;
    do {
      origin = uniform((ll)0,n-1), next = uniform((ll)0,n-1);
    } while(find(origin,p)==find(next,p)||origin==next);
    tree.emplace_back(origin, next);
    unite(origin,next,p);
  }
  return tree;
}
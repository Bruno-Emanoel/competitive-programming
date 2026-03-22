#ifdef LOCAL
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define ll long long 
#endif

class KMP {
  public:
  size_t n;
  string P;
  vector<int> neighbor;
  KMP(string p): n{p.size()}, P(p), neighbor(n+1) {
    for(int i = 1; i < n; ++i)
      neighbor[i+1]=nxt(i,P[i]); // proximo estado ativo ao memso tempo que i+1 é o ultimo que avançou com char P[i]
  }
  int nxt(int st, char c) {
    while(st=neighbor[st]) { // avança nos estados até que chegue no estado inicial
      if(P[st]==c) return st+1; // se achou um estado que avança com c, é ele
    }
    return P[0]==c; // vai ficar no estado 0 ou então consegue avançar pro 1
  }
  int match(string &T) {
    size_t count=0,st=0;
    auto f = [&count](int ind) { ++count; }; // Se precisar processar um match muda aqui
    for(size_t i = 0; i < T.size(); ++i) {
      if(T[i]==P[st])st++;  // Lider avança
      else st=nxt(st,T[i]); // Busca proximo estado
      if(st==n){
        f(i);st=neighbor[st]; // processa o match e passa a ohlar pro proximo estado ativo
      }
    }
    return count;
  }
};

// Calculate z(s), the Z-function of string s
// z[i] = max { x : s[0..x-1] == s[i..i+x-1] }
ll z[];
void calcZ(string &s) {
  ll n = s.size();
  z[0] = 0;
  ll l = 0, r = 1; // we keep [l, r), the latest interval that had a match (with largest r or largest size in case of draw)
  for(ll i = 1; i < n; ++i) {
    z[i] = (i < r)*min(r - i, z[i - l]); // if i < r, the partial value is known 
    while(i + z[i] < n && s[z[i]] == s[i + z[i]]) // try matching
      ++z[i];
    if(i + z[i] > r) { // update last biggest interval with match
      l = i;
      r = i + z[i];
    }
  }
  z[0] = n;
}
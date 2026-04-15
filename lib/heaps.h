/*  HEAPS.H   */

namespace RefHeap {
  #define ll long long
  #define pll pair<ll,ll>
  #define loop(i,s,n) for(ll i = s; i <n;++i)
  #include <algorithm>
  #include <vector>
  using namespace std;
  constexpr ll MAXN = 1e4;
  ll n, hn;
  ll whe[MAXN];
  pll heap[MAXN];
  void heapfy() {
    hn = n;
    loop(i,0,n) {
      whe[i]=i;
      heap[i]={0,i};
    }
  }
  void troca(ll i, ll j) {
    swap(whe[heap[i].second],whe[heap[j].second]);
    swap(heap[i],heap[j]);
  }
  void down(ll i) {
    if(2*i+1>=hn) return;
    if(heap[i].first<heap[2*i+1].first) {
      if(2*i+2>=hn||heap[2*i+1].first>=heap[2*i+2].first){
        troca(i,2*i+1);
        down(2*i+1);
      }else if(2*i+2<hn) {
        troca(i,2*i+2);
        down(2*i+2);
      }
    }else if(2*i+2<hn&&heap[i].first<heap[2*i+2].first){
      troca(i,2*i+2);
      down(2*i+2);
    }
  }
  void up(ll i) {
    if(i==0) return;
    ll upind = i/2-(i%2==0);
    if(heap[i].first>heap[upind].first) {
      troca(i,upind);
      up(upind);
    }
  }
  void remove(ll i) {
    if(i<hn-1) {
      troca(i,hn-1);
      down(i);
      up(i);
    } 
    hn--;
  }
}
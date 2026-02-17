#ifndef ll
#include <vector>
#define ll long long
#define INF (ll)1e9
using namespace std;
#endif

struct node {
  ll val=0;
  bool prop=false;
  node() = default;
  node(ll a): val{a} {};
  node operator+(const node&a) {
    node ret;
    ret.val = val+a.val;
    return ret;
  }
  node clear() {
    val = 0;
    prop = true;
    return *this;
  }
};

class Seg {
  public:
  size_t n, size;
  vector<node> nodes;
  Seg(const vector<ll> &data): n{data.size()}, size{2*n}, nodes(size)  {
    build(0,0,n-1,data);
  }
  node build(ll i, ll l, ll r, const vector<ll> &data) {
    if(l==r) return nodes[i] = node(data[l]);
    ll mid = l+(r-l)/2;
    return nodes[i] = build(i+1,l,mid,data)+build(i+(mid-l+1)*2,mid+1,r,data);
  }
  node query(ll i, ll lef, ll rig, ll l, ll r) {
    if(r<lef||rig<l) return node();
    if(lef<=l&&r<=rig) return nodes[i];
    ll mid = l+(r-l)/2;
    return query(i+1,lef,rig,l,mid)+query(i+2*(mid-l+1),lef,rig,mid+1,r);
  }
  node operator()(ll l, ll r) {
    return query(0,l,r,0,n-1);
  }
  node update(ll i, ll ind, ll val, ll l, ll r) {
    if(l==r&&l==ind) return nodes[i] = node(val);
    ll mid = l+(r-l)/2;
    if(ind<=mid) 
      return nodes[i] = update(i+1,ind,val,l,mid)+nodes[i+2*(mid-l+1)];
    return nodes[i]= nodes[i+1]+update(i+2*(mid-l+1),ind,val,mid+1,r);
  }
  // Modificar de acordo com o tipo de passeio que se deseja fazer
  // Tira a necessidade de uma busca binária em alguns casos
  ll ans,curr;
  void walk(ll i, ll lef, ll rig, ll l, ll r) {
    if(r<lef||rig<l||ans!=INF||curr<l-lef) return; // Fora do range ou valor encontrado
    ll mid = l+(r-l)/2;
    if(lef<=l&&r<=rig) { // intervalo incluso
      if(min(curr,nodes[i].val)>=r-lef) { // Resposta está exatamente no fim desse intervalo ou depois
        curr = min(curr,nodes[i].val); // Pega o valor total do intervalo
        if(curr==r-lef) ans = curr; // Se estiver no fim do intervalo salva
        return;
      }else if(l==r) { // A resposta não está depois e o intervalo é unitário
        curr = min(curr,nodes[i].val);
      }
      
    }
    // Desce a seg
    walk(i+1,lef,rig,l,mid); 
    walk(i+2*(mid-l+1),lef,rig,mid+1,r);
  }
  ll startWalk(ll l, ll r) {
    ans = INF, curr = INF;
    walk(0,l,r,0,n-1);
    return ans;
  }
  void upd(ll ind, ll val) {
    update(0,ind,val,0,n-1);
  }
};

class SegProp {
  public:
  ll n, size;
  vector<node> nodes;
  SegProp(ll n): n{n}, size{2*n}, nodes(size) {}

  node query(ll i, ll lef, ll rig, ll l, ll r) {
    if(r<lef||rig<l||nodes[i].prop) return node();
    if(lef<=l&&r<=rig) return nodes[i];
    ll mid = l+(r-l)/2;
    return query(i+1,lef,rig,l,mid)+query(i+2*(mid-l+1),lef,rig,mid+1,r);
  }
  node operator()(ll l, ll r) {
    return query(0,l,r,0,n-1);
  }
  node update(ll i, ll ind, ll val, ll l, ll r) {
    if(l==r&&l==ind) return nodes[i] = nodes[i]+node(val);
    ll mid = l+(r-l)/2;
    if(nodes[i].prop) {
      nodes[i+1].clear();
      nodes[i+2*(mid-l+1)].clear();
    }
    if(ind<=mid) 
      return nodes[i] = update(i+1,ind,val,l,mid)+nodes[i+2*(mid-l+1)];
    return nodes[i] = nodes[i+1]+update(i+2*(mid-l+1),ind,val,mid+1,r);
  }
  void upd(ll i, ll x) {
    update(0,i,x,0,n-1);
  }

  node erase(ll i, ll lef, ll rig, ll l, ll r) {
    if(r<lef||rig<l||nodes[i].prop) return nodes[i];
    if(lef<=l&&r<=rig) return nodes[i].clear();
    ll mid = l+(r-l)/2;
    return nodes[i] = erase(i+1,lef,rig,l,mid)+erase(i+2*(mid-l+1),lef,rig,mid+1,r);
  }
  void ers(ll l, ll r) {
    erase(0,l,r,0,n-1);
  }
};


/*
struct node {
  ll x=LLONG_MAX;
  ll dec=0;
  bool prop=false;
  node() = default;
  node(ll x):x{x} {}
  node operator+(const node &a) {
    return node(min(x,a.x));
  }
  node sub(ll a=1) {
    x-=a;
    dec+=a;
    prop=true;
    return *this;
  }
};

constexpr ll MAXN = 1e5;
node nodes[2*MAXN];
pll mins[MAXN];
ll arr[MAXN];

class SegProp {
  public:
  ll n, size;
  SegProp(ll n): n{n}, size{2*n} {
    build(0,0,n-1);
  }

  node build(ll i, ll l, ll r) {
    if(l==r) return nodes[i]=node(arr[l]);
    ll mid = l + (r-l)/2;
    return nodes[i]=build(i+1,l,mid)+build(i+2*(mid-l+1),mid+1,r);
  }
  node query(ll i, ll lef, ll rig, ll l, ll r) {
    if(r<lef||rig<l) return node();
    if(lef<=l&&r<=rig) return nodes[i];
    ll mid = l+(r-l)/2;
    if(nodes[i].prop) {
      nodes[i]=nodes[i+1].sub(nodes[i].dec)+nodes[i+2*(mid-l+1)].sub(nodes[i].dec);
    }
    return query(i+1,lef,rig,l,mid)+query(i+2*(mid-l+1),lef,rig,mid+1,r);
  }
  ll operator()(ll l, ll r) {
    return query(0,l,r,0,n-1).x;
  }

  node update(ll i, ll lef, ll rig, ll l, ll r) {
    if(r<lef||rig<l) return nodes[i];
    if(lef<=l&&r<=rig) return nodes[i].sub();
    ll mid = l+(r-l)/2;
    if(nodes[i].prop) {
      nodes[i]=nodes[i+1].sub(nodes[i].dec)+nodes[i+2*(mid-l+1)].sub(nodes[i].dec);
    }
    return nodes[i] = update(i+1,lef,rig,l,mid)+update(i+2*(mid-l+1),lef,rig,mid+1,r);
  }
  void upd(ll l, ll r) {
    update(0,l,r,0,n-1);
  }
};
*/
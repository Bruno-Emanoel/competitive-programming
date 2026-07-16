#include "code.cpp"
constexpr ll MAXN = 2e5, LOGN = lg(MAXN);
vll t[MAXN];
ll up[MAXN][LOGN+1], depth[MAXN];
ll now = 0;

/* 
  Below is a segtree class that can be used for each path.
  This is more efficient because instead of querying in a big tree for every path
  we now only need smaler trees which are still contiguous in memory.
  Now for the full path queries only one function call is needed  (range [0,n-1] which is the root)
  and for the mid path queries (two final in each query) we make a segment query in a tree with smaller height
node node_arr[2*MAXN];
ll NSZ = 0;
class Seg {
  public:
  size_t n = 0, size;
  ll st;
  node *nodes;
  Seg() = default;
  Seg(ull n, ll st): n{n}, size{2*n}, st(st), nodes(node_arr+NSZ) {
    NSZ+=size;
    build(0,st,st+n-1);
  }
  ...
}
Seg segs[MAXN];
*/

namespace HLD {
ll pos[MAXN], head[MAXN], heavy[MAXN], val[MAXN], conv[MAXN];


ll dfs(ll u = 0, ll p = 0) {
  ll sz = 1, msz = 0; heavy[u] = -1;
  depth[u] = depth[p]+1;
  up[u][0] = p;
  loop(i,1,LOGN+1)
  up[u][i] = up[up[u][i-1]][i-1]; 
  foreach(w,t[u]) if(w!=p) {
    ll nsz = dfs(w,u);
    sz+=nsz;
    if(nsz>msz)
    msz = nsz, heavy[u] = w;
  }
  return sz;
}

void compose(ll u, ll w, ll p = -1) {
  head[u] = w, pos[u] = now++, conv[pos[u]] = val[u];
  if(heavy[u]!=-1)
  compose(heavy[u],w,u);
  else
  segs[w] = Seg(pos[u]-pos[w]+1,conv+pos[w]);
  foreach(x,t[u]) if(x!=p&&x!=heavy[u])
  compose(x,x,u);
}

// LCA em O(logn) com HLD
// Sobe os caminhos pesados até que ambos estejam no mesmo caminho pesado
// Sobe o que está mais fundo de cada vez
ll lca(ll u, ll w) {
  while(head[u]!=head[w]) {
    if(depth[u]<depth[w])
      swap(u,w);
    u = par[head[u]];
  }
  return depth[u]<depth[w] ? u : w;
}

void updup(ll u, ll v, bool inclusive = true) {
  while(head[u]!=head[v])
    segs[head[u]].upd(0,pos[u]-pos[head[u]]), u = par[head[u]];
  if(inclusive) {
    if(u!=v)
      segs[head[u]].upd(pos[v]-pos[head[v]]+1,pos[u]-pos[head[u]]);
  }else
    segs[head[u]].upd(pos[v]-pos[head[v]],pos[u]-pos[head[u]]);
} 

void upd(ll u, ll v) {
  if(depth[u]<depth[v])
    swap(u,v);
  ll lc = lca(u,v);
  if(lc==v)
    return updup(u,v);
  updup(u,lc);
  updup(v,lc,false);
}
}

ll jump(ll u, ll x) {
  while(x) {
    u = up[u][lg(x)];
    x^=getMsb(x);
  }
  return u;
}

// This lca implementation may return lca and a child of the lca in one of the paths
// This is useful when the query is on a non-idempotent operation
pll lca(ll a, ll b) {
  a = jump(a,depth[a]-depth[b]);
  if(a==b)
    return {a,b};
  downto(i,LOGN,0)
    if(up[a][i]!=up[b][i])
      a=up[a][i], b = up[b][i];
  return {up[a][0], b};
}

namespace Centroid {
vll t[MAXN];
vpll centree[MAXN];
ll ans[MAXN], sz[MAXN];
bitset<MAXN> removed;

ll get_sz(ll u, ll p) {
  sz[u] = 1;
  for(auto w:t[u]) if(w!=p&&!removed[w])
    sz[u] += get_sz(w,u);
  return sz[u];
}

ll get_centroid(ll u, ll p, ll n) {
  for(auto w:t[u])
    if(w!=p&&!removed[w]&&sz[w]*2>n)
      return get_centroid(w,u,n);
  return u;
}

void next_level(ll u, ll p, ll cent, ll d = 1) {
  centree[u].emplace_back(cent,d);
  for(auto w:t[u]) if(w!=p&&!removed[w])
    next_level(w,u,cent,d+1);
}

void decompose(ll u) {
  get_sz(u,u);
  ll centroid = get_centroid(u,u,sz[u]);
  removed[centroid] = true;
  for(auto w:t[centroid])
    if(!removed[w]) {
      next_level(w,centroid,centroid);
      decompose(w);
    }
}
};
/*  GRAPHS.H   */

constexpr ll MAXN = 10;
vll g[MAXN];
vpll bridges;
ll tin[MAXN], low[MAXN];
bool vis[MAXN];
ll now = 0;

// Find bridges of the graph in O(N+M) in the dfs
// Bridges are edges that when removed will increase the number of connected components
void find_bridges(ll u = 0, ll p = -1) {
  vis[u] = true;
  tin[u] = low[u] = now++;
  foreach(w,g[u]) if(w!=p) {
    if(vis[w]) {
      low[u]= min(low[u],tin[w]);
    }else {
      find_bridges(w,u);
      low[u]=min(low[u],low[w]);
      if(low[w]>tin[u])
        bridges.emplace_back(u,w);
    }
  }
}

vll articulation;

// Find Articulation points of the graph in O(N+M) in the dfs
// Articulation points are vertices that when removed will increase the number of connected components
void find_articulation(ll u = 0, ll p = -1) {
  vis[u] = true;
  tin[u] = low[u] = now++;
  int child = 0;
  foreach(w,g[u]) if(w!=p) {
    if(vis[w]) {
      low[u]= min(low[u],tin[w]);
    }else {
      find_articulation(w,u);
      low[u]=min(low[u],low[w]);
      if(low[w]>=tin[u]&&p!=-1)
        articulation.emplace_back(u);
      child++;
    }
  }
  if(p==-1&&child>1)
    articulation.emplace_back(u);
}

// Shortest path with negative edges and cycles
// Same complexity as bellman ford O(NM) but in average faster
struct Edge {
  ll to, w;
};
v<Edge> graph[MAXN];
vll FSPA(ll n, ll st = 0) {
  queue<pll> q;
  vll dist(n), relax(n);
  dist[st] = 0, relax[st] = 0;
  q.emplace(0,0);
  bool negCycle = false;
  while(q.size()) {
    auto [u,w] = q.front(); q.pop();
    if(dist[u]<w) continue;
    foreach(edg,graph[u]) {
      if(dist[u] + edg.w < dist[edg.to]) {
        relax[edg.to]++;
        if(relax[edg.to]>=n) {
          negCycle = true;break;
        }
        dist[edg.to] = dist[u]+edg.w;
        q.emplace(edg.to,dist[edg.to]);
      }
    }
  }
  return dist;
}

// Shortest path without negative vertices O((n+m)logn)
vll dijikstra(ll n, ll st = 0) {
  vll dist(n,LLONG_MAX);
  dist[st]=0;
  priority_queue<pll> pq;
  pq.emplace(0,st);
  while(pq.size()) {
    auto [w,now] = pq.top();pq.pop();
    if(w<dist[now]) continue;
    foreach(u,graph[now]) if(w+u.w<dist[u.to]) {
      dist[u.to] = w+u.w;
      pq.emplace(dist[u.to], u.to);
    }
  }
}

namespace max_match {
  constexpr ll MAXN = 2e4+1;
  ll n, m, now = 0, match[MAXN], when[MAXN], dist[MAXN];
  vll g[MAXN];
  #define NUL n+m

  bool bfs() {
    ++now;
    static queue<ll> q;
    loop(i,0,n) if(match[i]==NUL)
      dist[i] = 0, when[i] = now, q.emplace(i);
    dist[NUL] = INF;
    while(q.size()) {
      ll u = q.front(); q.pop();
      if(dist[u]<dist[NUL]) 
        foreach(w,g[u]) if(when[match[w]]<now) {
          dist[match[w]] = dist[u]+1;
          when[match[w]] = now;
          q.emplace(match[w]);
        }
    }
    return dist[NUL] != INF;
  }

  bool dfs(ll u) {
    if(u==NUL)
      return true;
    foreach(w,g[u]) if(dist[match[w]] == dist[u] + 1) 
      if(dfs(match[w])) {
        match[w] = u;
        match[u] = w;
        return true;
      }
    dist[u] = INF;
    return false;
  }

  /**
   *  return the size of the maximum size edge set for bipartite graph 
   *  Hopcroft-Karp algorithm
  **/
  ll max_match() {
    ll ans = 0;
    while(bfs()) {
      ll oans = ans;
      loop(i,0,n) if(match[i]==NUL&&dfs(i))
        ++ans;
      if(oans==ans)
        break;
    }
    return ans;
  }
}

namespace SCC {
  ll p[1],sz[1],act[1],vis[1];
  ll find(ll x);
  void unite(ll a, ll b);
  void dfs(ll u) {
    act[u] = 1;
    vis[u] = 1;
    for(auto w:g[u]) {
      if(vis[w]==0) {
        dfs(w);
      }
      if(act[find(w)])
        unite(u,w);
    }
    vis[u] = 2;
    --act[find(u)];
  }
  set<ll> find_scs(ll n) {
    for(ll i = 0; i < n; ++i)
      p[i] = i, sz[i] = 1, vis[i] = 0, act[i] = 0;
    for(ll i = 0; i < n; ++i) if(!vis[i])
      dfs(i);
    set<ll> res;
    for(ll i = 0; i < n; ++i)
      res.emplace(find(i));
    return res;
  }
}

namespace Flow {
struct Edge {
  ll to, ind;
  ll flow, cap;
};
v<Edge> g[MAXN];
vll hs[MAXN<<1];
ll ec[MAXN], height[MAXN];
Edge *cur[MAXN];

struct PushRelabel {
  ll n;
  PushRelabel(ll n): n{n} {
    loop(i,0,n)
      ec[i] = 0, height[i] = 0, cur[i] = nullptr;
  }
  void addEdge(ll u, ll w, ll x, ll rx = 0) {
    g[u].emplace_back(w,g[w].size(),0,x);
    g[w].emplace_back(u,g[u].size()-1,0,rx);
  }
  void addFlow(Edge&e, ll f) {
    if(!ec[e.ind] && f) hs[height[e.ind]].emplace_back(e.ind);
    Edge &back = g[e.to][e.ind];
    e.flow += f, e.cap -= f, ec[e.to] += f;
    back.flow -= f, back.cap +=f, ec[back.to] -=f;
  }
  ll calc(ll s, ll t) {
    height[s] = n, ec[t] = 1;
    vll cnt(2*n); cnt[0] = n-1;
    loop(i,0,n) cur[i] = g[i].data();
    foreach(e,g[s]) addFlow(e,e.cap);
    ll hi = 0;
    while(true) {
      while(hs[hi].empty()) if(!hi--) return -ec[s];
      ll u = hs[hi].back(); hs[hi].pop_back();
      while(ec[u] > 0) 
        if(cur[u] == g[u].data() + g[u].size()) {
          height[u] = 1e9;
          foreach(e,g[u]) if(e.cap && height[u] > height[e.to] + 1)
            height[u] = height[e.to] + 1, cur[u] = &e;
          if(++cnt[height[u]], !--cnt[hi] && hi < n) 
            loop(i,0,n) if(hi < height[i] && height[i] < n)
              --cnt[height[i]], height[i] = n+1;
          hi = height[u];
        }else if(cur[u]->cap && height[u] == height[cur[u]->to] + 1)
          addFlow(*cur[u], min(ec[u],cur[u]->cap));
        else
          ++cur[u];
    }
  }
};
  
}
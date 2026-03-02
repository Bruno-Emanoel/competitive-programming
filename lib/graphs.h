#include "code.cpp"
#include <bits/stdc++.h>

constexpr ll MAXN;
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
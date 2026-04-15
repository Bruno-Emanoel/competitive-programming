/*  TREAP.H   */
#include "random.h"
#define ll long long

struct node {
  ll i, x;
  node *l = nullptr, *r = nullptr;
  node() = default;
  node(ll i): i{i}, x{uniform(1,1e9)} {}
  node(ll i, ll x): i{i}, x{x} {}
};
typedef node* pnode;

ll constexpr MAXN = 1e5;
node arena[MAXN*4];
ll sz = 0;

class Treap {
  public:
  pnode root = nullptr;
  ~Treap() { sz = 0; }
  void split(pnode t, ll i, pnode &l, pnode &r) {
    if(!t)
      l = r = nullptr;
    else if(t->i <= i)
      split(t->r, i, t->r, r), l = t;
    else
      split(t->l, i, l, t->l), r = t;
  }
  void merge(pnode &t, pnode l, pnode r) {
    if(!l || !r)
      t = l ? l : r;
    else if(l->x > r->x)
      merge(l->r, l->r, r), t = l;
    else
      merge(r->l, l, r->l), t = r;
  }
  void insert(pnode &t, pnode item) {
    if(!t)
      t = item;
    else if(item->x > t->x)
      split(t, item->i, item->l, item->r), t = item;
    else if(item->i < t->i)
      insert(t->l, item);
    else
      insert(t->r, item);
  }
  void emplace(ll i) {
    insert(root, &(arena[sz++] = node(i)));
  }
  void emplace(ll i, ll x) {
    insert(root, &(arena[sz++] = node(i, x)));
  }
  void post_order(pnode t, function<void(pnode)> f) {
    if(!t)
      return;
    post_order(t->l,f);
    post_order(t->r,f);
    f(t);
  }
  bool not_found;
  void remove(pnode &t, ll i) {
    if(!t)
      not_found = true;
    else if(t->i == i) 
      // pnode todel = t; 
      not_found = false, merge(t, t->l, t->r);
      // delete todel
    else if(i < t->i)
      remove(t->l, i);
    else
      remove(t->r, i);
  }
  pnode unite(pnode l, pnode r) {
    if(!l || !r)
      return l ? l : r;
    if(l->x < r->x) swap(l, r);
    pnode lt, rt;
    split(r, l->i, lt, rt);
    l->l = unite(l->l, lt);
    l->r = unite(l->r, rt);
    return l;
  }
};

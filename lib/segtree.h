/*  SEGTREE.H   */

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
  void upd(ll ind, ll val) {
    update(0,ind,val,0,n-1);
  }
};

struct BIT {
	ll n;
	vll bit;

	BIT(ll n): n(n), bit(n) {
		loop(i,0,n)
			bit[i] = 0;
	}

	node sum(ll r) {
		node ret = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			ret = ret + bit[r];
		return ret;
	}

	ll operator()(ll l, ll r) {
		return sum(r).val - sum(l - 1).val;
	}

	void upd(ll idx) {
		for (; idx < n; idx = idx | (idx + 1))
			++bit[idx].val;
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



struct customHash {
  static unsigned ll splitmix64(unsigned ll x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(unsigned ll x) const {
    static const unsigned ll FIXED_RANDOM =
      chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

namespace std {
  template<>
  struct hash<pll> {
    size_t operator()(const pll &a) const {
      return customHash()(a.first+ (((ll)a.second)<<31));
    }
  };
};

template <typename T>
inline bool operator==(const pair<T,T>&a,const pair<T,T>&b) {
  return  a.first==b.first&&a.second==b.second;
}

template <typename T>
inline pair<T,T> operator+(const pair<T,T>&a,const pair<T,T>&b) {
  return {a.first+b.first,a.second+b.second};
}
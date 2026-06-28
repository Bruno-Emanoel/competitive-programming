/*  CUSTOM_ADDONS.H   */
struct customHash {
  static unsigned ll splitmix64(unsigned ll x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(unsigned ll x) const {
    static const unsigned ll FIXED_RANDOM =
      chrono::steady_clock::now().time_since_epoch().count()
      ^ (ull)(std::make_unique<char>().get());
    return splitmix64(x ^ FIXED_RANDOM);
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

constexpr int MAXN = 1e6*sizeof(int);
char arena[MAXN];
int sz = 0;

template <typename T>
struct Alloc {
	using value_type = T;
	Alloc() noexcept {};
	T* allocate(size_t n) {
		sz += n*sizeof(T);
		return (T*)&arena[sz-n*sizeof(T)];
	}
	void deallocate([[maybe_unused]]T*p, [[maybe_unused]]size_t n) {}
};


// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using ordered_multiset = __gnu_pbds::tree<ll, __gnu_pbds::null_type, greater_equal<ll>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
//#define pbds __gnu_pbds
//typedef pbds::gp_hash_table<ll, ll, hash<ll>, equal_to<ll>, pbds::direct_mod_range_hashing<ll>, pbds::quadratic_probe_fn<>,
//                      pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy, pbds::hash_load_check_resize_trigger<true>, true>>
//    hashT;
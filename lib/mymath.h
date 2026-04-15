/*  mymath.h  */

constexpr inline int lg(unsigned long i) {
  return __bit_width(i) - 1;
}

inline ll binexpo(ll a, ll e) {
  ll ans = 1;
  a %=mod;
  e %=mod-1;
  while(e) {
    if(e&1)
      ans =(ans*a)%mod;
    a = (a*a)%mod;
    e>>=1;
  }
  return ans;
}

void sieve() {
  primes.reserve(MAXN/10);
  vector<bool> isC(MAXN+1);
  primes.emplace_back(2);
  for(ll i = 4; i <=MAXN; i+=2)
    isC[i]=true;

  for(ll i = 3; i<=MAXN; i+=2)
    if(isC[i])continue;
    else {
      primes.emplace_back(i);
      for(ll j = i*i; j<=MAXN; j+=2*i)
        isC[j]=true;
    }
}

namespace contsieve {
  constexpr ll MAXN = 1e16;
  constexpr ll PRIMES_CNT = 10000;

  constexpr auto sieve() {
    array<ll,PRIMES_CNT> primes = {};
    ll sz = 0;
    bitset<1001> isC;
    for(ll i = 4; i*i <=MAXN; i+=2) {
      isC[i]=true;
    }
    primes[sz++] = 2;

    for(ll i = 3; i*i<=MAXN; i+=2)
      if(isC[i])continue;
      else {
        primes[sz++] = i;
        for(ll j = i*i; j*j<=MAXN; j+=2*i)
          isC[j]=true;
      }
    return primes;
  }

  auto primes = sieve();
}

// Calculate factorial and its inverse
void calcfato() {
  fat[0]=1;
  for(ll i = 1; i < MAXN; ++i) 
    fat[i]=(fat[i-1]*i)%mod;

  inv[MAXN-1]=binexpo(fat[MAXN-1],mod-2);
  for(ll i = MAXN-2; i>=0; --i) {
    inv[i]=(inv[i+1]*(i+1))%mod;
  }
}

// Calculate factorial with choose[i][j]
ll MAXFAT;
void calccfato() {
  fat[0]=1;
  vector<vector<ll>> choose;
  for(ll i = 1; i < MAXFAT; ++i) 
    fat[i]=(fat[i-1]*i)%mod;

  inv[MAXFAT-1]=binexpo(fat[MAXFAT-1],mod-2);
  for(ll i = MAXFAT-2; i>=0; --i) {
    inv[i]=(inv[i+1]*(i+1))%mod;
  }

  // i escolhe j
  choose[0][0] = 1;
  for(ll i = 1; i < MAXFAT; ++i){
    choose[i][0]=1;
    for(ll j = 1; j < min(i,MAXN-1); ++j)
      choose[i][j]= (choose[i-1][j-1]+choose[i-1][j])%mod;
    if(i==min(i,MAXN-1))
      choose[i][i]=1;
    else{
      choose[i][MAXN-1] = (fat[i]*inv[MAXN-1])%mod;
      choose[i][MAXN-1] = (choose[i][MAXN-1]*inv[i-(MAXN-1)])%mod;
    }
  }

  // i escolhe pelo menos j
  for(ll i = 1; i < MAXFAT; ++i){
    if(i==min(i,MAXN-1))
      for(ll j = i-1; j>=0; --j) 
        choose[i][j]=(choose[i][j]+choose[i][j+1])%mod;
    else {
      ll accum = 0;
      ll tot = binexpo(2,i);
      for(ll j = 0; j < MAXN; ++j) {
        ll aux = choose[i][j];
        choose[i][j]=(((tot-accum)%mod)+mod)%mod;
        accum = (accum+aux)%mod;
      }
    }
  }

}

// "normalize" the factor of a number
void reduce_div(ll &c, map<ll,ll> &fac, ll up, ll low) {
  vector<ll> toers;
  for(auto &[a,b]:fac) {
    ll aux=a;
    while(aux<=up&&b>0) {
      ll cnt = up/aux - low/aux;
      c/=binexpo(a,min(cnt,b));
      b-=cnt;
      aux*=a;
    }

    if(b<=0) toers.emplace_back(a);
  }
  for(auto ers:toers)
    fac.erase(ers);
}

// Template for modular arithmetic
struct Mint {
  ll x=0;
  Mint() = default;
  Mint(ll a): x{((a%mod)+mod)%mod} {}
  Mint(ll p, ll q): Mint((((p%mod)+mod)%mod)*binexpo(q,mod-2)) {}
  Mint operator+(const Mint &a) const { return (x+a.x); }
  Mint operator-() const { return (mod-x); }
  Mint operator-(const Mint &a) const { return operator+(-a); }
  Mint operator*(const Mint &a) const { return (x*a.x); }
  Mint operator/(const Mint &a) const { return operator*(binexpo(a.x,mod-2)); }
  Mint operator^(const Mint &a) const { return (binexpo(x,a.x)); }
  Mint &operator+=(const Mint &a) { return *this = operator+(a); }
  Mint &operator-=(const Mint &a) { return *this = operator-(a); }
  Mint &operator*=(const Mint &a) { return *this = operator*(a); }
  Mint &operator/=(const Mint &a) { return *this = operator/(a); }
  Mint &operator^=(const Mint &a) { return *this = operator^(a); }
};

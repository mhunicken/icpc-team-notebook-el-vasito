#include <bits/stdc++.h>
#define fst first
#define snd second
#define fore(x,a,b) for(int x=(a), qwerty=(b); x<qwerty; x++)
using namespace std;
typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll a, ll b){return uniform_int_distribution<ll>(a, b)(rng);}
ll fpow(ll b, ll e, ll p){
  ll r=1;
  while(e)if(e&1)r=(r*b)%p,e^=1; else b=(b*b)%p,e>>=1;
  return r;
}
ll legendre(ll a, ll p){
  if(a%p==0)return 0; if(p==2)return 1;
  return fpow(a,(p-1)/2,p);
}
ll tonelli_shanks(ll n, ll p){
  assert(legendre(n,p)==1); if(p==2)return 1;
  ll s=__builtin_ctzll(p-1), q=(p-1LL)>>s, z=rnd(1,p-1);
  if(s==1)return fpow(n,(p+1)/4LL,p);
  while(legendre(z,p)!=p-1)z=rnd(1,p-1);
  ll c=fpow(z,q,p), r=fpow(n,(q+1)/2,p), t=fpow(n,q,p), m=s;
  while(t!=1){
    ll i=1, ts=(t*t)%p;
    while(ts!=1)i++,ts=(ts*ts)%p;
    ll b=c; 
    fore(_,0,m-i-1)b=(b*b)%p;
    r=r*b%p;c=b*b%p;t=t*c%p;m=i;
  }
  return r;
}

const int MAX_TEST = 2e4;
bool is_prime(ll a){
  for(ll r=2; r*r<=a; r++)if(a%r==0)return 0;
  return 1;
}
int main(){
  vector<pair<ll,ll> > queries = {
    {93,97}, {10,13}, {56,101}, {1030,10009}, {44402,100049},
    {665820697,1000000009}
  };
  while(queries.size()<MAX_TEST){
    ll p=rnd(2, 2e9);
    while(!is_prime(p))p++;
    queries.push_back({fpow(rnd(1,p-1),2,p),p});
  }
  for(auto p:queries){
    ll r=tonelli_shanks(p.fst,p.snd);
    assert(r*r%p.snd==p.fst&&(p.snd-r)*(p.snd-r)%p.snd==p.fst);
  }
}

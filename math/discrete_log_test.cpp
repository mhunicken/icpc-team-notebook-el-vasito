// https://codeforces.com/gym/101853/problem/G
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;
 
ll fastpow(ll a, ll e, ll mod) {
	a%=mod;
	if(e==0) return 1;
	else {
		if(e%2==0) return fastpow((a*a)%mod,e/2,mod);
		else return (a*fastpow(a,e-1,mod))%mod;
	}
}
 
ll gcd(ll a, ll b) { return __gcd(a,b);}
 
ll discrete_log(ll a,ll b,ll m) {//returns x such that a^x = b (mod m) or -1 if inexistent
    a%=m, b%=m;
    if(b == 1) return 0;
    int cnt=0;
    ll tmp=1;
    for(int g=__gcd(a,m);g!=1;g=__gcd(a,m)) {
        if(b%g) return -1;
        m/=g, b/=g;
        tmp = tmp*a/g%m;
        ++cnt;
        if(b == tmp) return cnt;
    }
    map<ll,int> w;
    int s = ceil(sqrt(m));
    ll base = b;
    fore(i,0,s) {
        w[base] = i;
        base=base*a%m;
    }
    base=fastpow(a,s,m);
    ll key=tmp;
    fore(i,1,s+2) {
        key=base*key%m;
        if(w.count(key)) return i*s-w[key]+cnt;
    }
    return -1;
}
 
int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		ll a,b,m;
		scanf("%lld %lld %lld",&a,&b,&m);
		printf("%lld\n",discrete_log(a,b,m));
	}
}

// UVA 10090 - AC
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1031
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

ll euclid(ll a, ll b, ll& x, ll& y){ // a*(x+k*(b/d))+b*(y-k*(a/d))=d
	if(!b){x=1;y=0;return a;}        // (for any k)
	ll d=euclid(b,a%b,x,y);
	ll t=y;y=x-(a/b)*y;x=t;
	return d;
}

void floordiv(ll x, ll y, ll& q, ll& r) {
	q=x/y;r=x%y;
	if((r!=0)&&((r<0)!=(y<0)))q--,r+=y;
}

int main(){
	ll n,c0,n0,c1,n1;
	while(scanf("%lld",&n),n){
		scanf("%lld%lld%lld%lld",&c0,&n0,&c1,&n1);
		bool s=false;
		if(c0*n1>c1*n0)s=true,swap(c0,c1),swap(n0,n1);  // (c0,n0) is better
		ll x0,x1;
		ll g=euclid(n0,n1,x0,x1);
		if(n%g){puts("failed");continue;}
		x0*=n/g;
		x1*=n/g;
		ll k,_;
		floordiv(x1*g,n0,k,_);
		assert(x1-k*(n0/g)>=0);
		if(x0+k*(n1/g)>=0){
			ll r0=x0+k*(n1/g);
			ll r1=x1-k*(n0/g);
			if(s)swap(r0,r1);
			printf("%lld %lld\n",r0,r1);
			continue;
		}
		floordiv(-x0*g+n1-1,n1,k,_);
		assert(x0+k*(n1/g)>=0);
		if(x1-k*(n0/g)>=0){
			ll r0=x0+k*(n1/g);
			ll r1=x1-k*(n0/g);
			if(s)swap(r0,r1);
			printf("%lld %lld\n",r0,r1);
			continue;
		}
		puts("failed");
	}
	return 0;
}

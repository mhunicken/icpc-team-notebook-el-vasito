// https://codeforces.com/contest/1098/problem/E
#include <bits/stdc++.h>
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define pb push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define SZ(s) int(s.size())
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
 
// # of lattice points s.t. ax+by<=c, x,y>0 (a,b is positive integer)
ll f(ll a, ll b, ll c){
	if(c<=0) return 0;
	if(a<b) swap(a, b);
	ll m=c/a;
	if(a==b) return m*(m-1)/2;
	ll k=(a-1)/b, h=(c-a*m)/b;
	return f(b,a-b*k,c-b*(k*m+h))+k*m*(m-1)/2+m*h;
}
 
// # of lattice points s.t. ax+by<=c, 0<x<=X, 0<y<=Y (a,b is positive integer)
ll g(ll a, ll b, ll c, ll X, ll Y){
	if(a*X+b*Y<=c) return X*Y;
	return f(a,b,c)-f(a,b,c-a*X)-f(a,b,c-b*Y)+f(a,b,c-a*X-b*Y);
}
 
ll a[100010],mp[100010];
vector<ii> b;
vector<ll> sum,elem;
 
ll calc(ll n, ll k){	//intervals lower 
	return n*(n+1)/2 - (n-k)*(n-k+1)/2;
}
 
ll get(ll x){
	int n=SZ(b)-1;
	ll ans=0;
	int i=0,j=0;
	while(i<n){
		if(i>j){j++; continue;}
		ll mid=sum[j]-sum[i];
		if(mid+b[i].fst+b[j+1].fst<=x){
			ll inmid=(i==j)?0:elem[j-1]-elem[i];
			ans+=inmid*b[j].snd;
			ans+=g(b[i].fst,b[j+1].fst,x-mid,b[i].snd,b[j+1].snd);
			j++;
		}
		else{
			i++;
			if(i<j){
				mid=sum[j-1]-sum[i];
				ans+=g(b[i].fst,b[j].fst,x-mid,b[i].snd,b[j].snd);
			}
		}
	}
	fore(i,0,n) ans+=calc(b[i].snd,min(b[i].snd,x/b[i].fst));
	return ans;
}
 
int jl[1<<16][16],jr[1<<16][16];
int pl[1<<16][16],pr[1<<16][16];
int pw[1<<16];
 
void build(int n){
	fore(i,0,n) jl[i][0]=jr[i][0]=a[i],pl[i][0]=i+1,pr[i][0]=i-1;
	pr[0][0]=0; pl[n-1][0]=n-1;
	fore(k,1,16) fore(i,0,n){
		jl[i][k]=__gcd(jl[i][k-1],jl[pl[i][k-1]][k-1]);
		jr[i][k]=__gcd(jr[i][k-1],jr[pr[i][k-1]][k-1]);
		pl[i][k]=pl[pl[i][k-1]][k-1];
		pr[i][k]=pr[pr[i][k-1]][k-1];
	}
}
 
int query(int l, int r){
	int len=pw[r-l+1];
	return __gcd(jl[l][len],jr[r][len]);
}
 
int main(){FIN;
	int id=0; pw[1]=0;
	fore(i,2,1<<16){
		pw[i]=id;
		if(!(i&(i-1))) id++;
	}
	int n; cin>>n;
	fore(i,0,n) cin>>a[i];
	build(n);
	fore(i,0,n){
		int pos=i,pre=a[i];
		while(pos<n){
			int l=pos,r=n-1;
			while(l<=r){
				int mid=(l+r)/2;
				if(query(i,mid)==pre) l=mid+1;
				else r=mid-1;
			}
			mp[pre]+=l-pos;
			pre=query(i,l); pos=l;
		}
	}
	fore(i,0,100010) if(mp[i]) b.pb({i,mp[i]});
	sum.resize(SZ(b)); elem.resize(SZ(b));
	sum[0]=b[0].fst*b[0].snd; elem[0]=b[0].snd;
	fore(i,1,SZ(b)){
		sum[i]=sum[i-1]+b[i].fst*b[i].snd;
		elem[i]=elem[i-1]+b[i].snd;
	}
	ll l=1,r=sum.back(),all=elem.back()*(elem.back()+1)/2;
	b.pb({sum.back()+1,1});
	sum.pb(2*sum.back()+1);
	while(l<=r){
		ll mid=(l+r)/2;
		if(2ll*get(mid)>=all) r=mid-1;
		else l=mid+1;
	}
	cout << l << "\n";
}

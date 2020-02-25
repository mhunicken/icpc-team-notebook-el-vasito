// Codeforces 715C - AC
// http://codeforces.com/problemset/problem/715/C
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN 100005

int m,i10;
ll res;

map<int,int> ci;
map<pair<int,int>,int> ci2;

vector<pair<int,int> > g[MAXN];int n;
bool tk[MAXN];

void dfs0(int x, int iv, int p, int f, int c){
	if(!iv)res++;
	ci[iv]++;
	ci2[{iv,c}]++;
	for(auto z:g[x]){
		int y=z.fst,w=z.snd;
		if(y==f||tk[y])continue;
		dfs0(y,(iv+1LL*p*w)%m,(p*10LL)%m,x,c);
	}
}

void dfs1(int x, int v, int p, int f, int c){
	if(!v)res++;
	int kk=(1LL*(m-v)*p)%m;
	res+=ci[kk];
	res-=ci2[{kk,c}];
	for(auto z:g[x]){
		int y=z.fst,w=z.snd;
		if(y==f||tk[y])continue;
		dfs1(y,(v*10LL+w)%m,(1LL*p*i10)%m,x,c);
	}
}

int fat[MAXN]; // father in centroid decomposition
int szt[MAXN]; // size of subtree
int calcsz(int x, int f){
	szt[x]=1;
	for(auto p:g[x]){
		int y=p.fst;
		if(y!=f&&!tk[y])szt[x]+=calcsz(y,x);
	}
	return szt[x];
}
void cdfs(int x=0, int f=-1, int sz=-1){ // O(nlogn)
	if(sz<0)sz=calcsz(x,-1);
	for(auto p:g[x]){
		int y=p.fst;
		if(!tk[y]&&szt[y]*2>=sz){
			szt[x]=0;cdfs(y,f,sz);return;
		}
	}
	ci.clear();ci2.clear();
	for(auto p:g[x]){
		int y=p.fst,w=p.snd;
		if(!tk[y]){
			dfs0(y,w%m,10%m,x,y);
		}
	}
	for(auto p:g[x]){
		int y=p.fst,w=p.snd;
		if(!tk[y]){
			dfs1(y,w%m,i10,x,y);
		}
	}
	tk[x]=true;fat[x]=f;
	for(auto p:g[x]){
		int y=p.fst;
		if(!tk[y])cdfs(y,x);
	}
}
void centroid(){memset(tk,false,sizeof(tk));cdfs();}

ll euclid(ll a, ll b, ll& x, ll& y){ // a*(x+k*(b/d))+b*(y-k*(a/d))=d
	if(!b){x=1;y=0;return a;}          // (for any k)
	ll d=euclid(b,a%b,x,y);
	ll t=y;y=x-(a/b)*y;x=t;
	return d;
}

int inv(int a, int mod){
	ll x,y;
	assert(euclid(a,mod,x,y)==1);
	int r=((x%mod)+mod)%mod;
	assert((1LL*a*r)%mod==1);
	return r;
}


int main(){
	scanf("%d%d",&n,&m);
	if(m==1){printf("%lld\n",1LL*n*(n-1));return 0;}
	i10=inv(10,m);
	fore(_,1,n){
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		g[x].pb({y,w});g[y].pb({x,w});
	}
	centroid();
	printf("%lld\n",res);
	return 0;
}

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define MOD 1000000007
using namespace std;
typedef long long ll;

int pm(int x, int e){
	int r=1;
	while(e){
		if(e&1)r=(1LL*r*x)%MOD;
		e>>=1;
		x=(1LL*x*x)%MOD;
	}
	return r;
}

#define MAXN (1<<18)

typedef int tp;

#define add(n,s,d,k) fore(i,0,n)(d)[i]+=(s)[i]*k
tp* ini(int n){tp *r=new tp[n];fill(r,r+n,0);return r;}
void karatsura(int n, tp* p, tp* q, tp* r){
	if(n<=0)return;
	if(n<35)fore(i,0,n)fore(j,0,n)r[i+j]+=p[i]*q[j];
	else {
		int nac=n/2,nbd=n-n/2;
		tp *a=p,*b=p+nac,*c=q,*d=q+nac;
		tp *ab=ini(nbd+1),*cd=ini(nbd+1),*ac=ini(nac*2),*bd=ini(nbd*2);
		add(nac,a,ab,1);add(nbd,b,ab,1);
		add(nac,c,cd,1);add(nbd,d,cd,1);
		karatsura(nac,a,c,ac);karatsura(nbd,b,d,bd);
		add(nac*2,ac,r+nac,-1);add(nbd*2,bd,r+nac,-1);
		add(nac*2,ac,r,1);add(nbd*2,bd,r+nac*2,1);
		karatsura(nbd+1,ab,cd,r+nac);
		free(ab);free(cd);free(ac);free(bd);
	}
}
vector<tp> multiply(vector<tp> p0, vector<tp> p1){
	int n=max(p0.size(),p1.size());
	tp *p=ini(n),*q=ini(n),*r=ini(2*n);
	fore(i,0,p0.size())p[i]=p0[i];
	fore(i,0,p1.size())q[i]=p1[i];
	karatsura(n,p,q,r);
	vector<tp> rr(r,r+p0.size()+p1.size()-1);
	free(p);free(q);free(r);
	return rr;
}

int r[MAXN];

vector<int> g[MAXN];int n;
bool tk[MAXN];
int szt[MAXN];
void dfs0(int x, int f, int d, vector<int>& z){
	if(d>=z.size())z.resize(d+1,0);
	z[d]++;
	for(int y:g[x])if(!tk[y]&&y!=f)dfs0(y,x,d+1,z);
}
int calcsz(int x, int f){
	szt[x]=1;
	for(auto y:g[x])if(y!=f&&!tk[y])szt[x]+=calcsz(y,x);
	return szt[x];
}
void cdfs(int x=0, int sz=-1){
	if(sz<0)sz=calcsz(x,-1);
	for(auto y:g[x])if(!tk[y]&&szt[y]*2>=sz){
		szt[x]=0;cdfs(y,sz);return;
	}
	tk[x]=true;
	r[0]++;
	vector<int> w={1};
	for(auto y:g[x])if(!tk[y]){
		vector<int> z;
		dfs0(y,-1,1,z);
		vector<int> p=multiply(w,z);
		fore(i,0,p.size())r[i]+=p[i],r[i]%=MOD;
		if(z.size()>w.size())w.resize(z.size(),0);
		fore(i,0,z.size())w[i]+=z[i];
	}
	for(auto y:g[x])if(!tk[y])cdfs(y);
}

int main(){
	scanf("%d",&n);
	fore(i,1,n){
		int x,y;
		scanf("%d%d",&x,&y);x--;y--;
		g[x].pb(y);g[y].pb(x);
	}
	cdfs();
	fore(i,1,n)r[i]=(2*r[i])%MOD;
	int s=0;
	fore(i,0,n)s+=(1LL*r[i]*pm(i+1,MOD-2))%MOD,s%=MOD;
	fore(i,1,n+1)s=(1LL*s*i)%MOD;
	printf("%d\n",s);
	return 0;
}

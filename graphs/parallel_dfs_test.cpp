// Codeforces gym 100109K - AC
// http://codeforces.com/gym/100109/problem/K
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define MOD 99990001
using namespace std;
typedef long long ll;

struct Tree {
	int n,z[2];
	vector<vector<int>> g;
	vector<int> ex,ey,p,w,f,v[2];
	Tree(int n):g(n),w(n),f(n){}
	void add_edge(int x, int y){
		p.pb(g[x].size());g[x].pb(ex.size());ex.pb(x);ey.pb(y);
		p.pb(g[y].size());g[y].pb(ex.size());ex.pb(y);ey.pb(x);
	}
	bool go(int k){ // returns true if it finds new node
		int& x=z[k];
		while(x>=0&&
			(w[x]==g[x].size()||w[x]==g[x].size()-1&&(g[x].back()^1)==f[x]))
			x=f[x]>=0?ex[f[x]]:-1;
		if(x<0)return false;
		if((g[x][w[x]]^1)==f[x])w[x]++;
		int e=g[x][w[x]],y=ey[e];
		f[y]=e;w[x]++;w[y]=0;x=y;
		v[k].pb(x);
		return true;
	}
	vector<int> erase_edge(int e){
		e*=2; // erases eth edge, returns smaller component
		int x=ex[e],y=ey[e];
		p[g[x].back()]=p[e];
		g[x][p[e]]=g[x].back();g[x].pop_back();
		p[g[y].back()]=p[e^1];
		g[y][p[e^1]]=g[y].back();g[y].pop_back();
		f[x]=f[y]=-1;
		w[x]=w[y]=0;
		z[0]=x;z[1]=y;
		v[0]={x};v[1]={y};
		bool d0=true,d1=true;
		while(d0&&d1)d0=go(0),d1=go(1);
		if(d1)return v[0];
		return v[1];
	}
};

int ew[200005];
int n,nc;
int wc[200005]; // which component
int l[200005]; // lazy

int main() {
	scanf("%d",&n);
	Tree t(n);
	fore(i,0,n-1){
		int x,y;
		scanf("%d%d%d",&x,&y,ew+i);x--;y--;
		t.add_edge(x,y);
	}
	nc=1;
	fore(i,1,n){
		int e;
		scanf("%d",&e);e--;
		int c=wc[t.ex[2*e]];
		ew[e]+=l[c];
		ew[e]%=MOD;
		printf("%d\n",ew[e]);fflush(stdout);
		t.erase_edge(e);
		vector<int> v;
		if(t.v[0].size()<t.v[1].size()||t.v[0].size()==t.v[1].size()&&*min_element(t.v[0].begin(),t.v[0].end())<*min_element(t.v[1].begin(),t.v[1].end()))
			v=t.v[0];
		else
			v=t.v[1];
		for(int x:v){
			wc[x]=nc;
			for(int ee:t.g[x]){
				if(ee&1){
					ew[ee/2]+=l[c];
					ew[ee/2]%=MOD;
					ew[ee/2]=(1LL*ew[ee/2]*ew[e])%MOD;
				}
			}
		}
		l[c]+=ew[e];
		l[c]%=MOD;
		nc++;
	}
	return 0;
}

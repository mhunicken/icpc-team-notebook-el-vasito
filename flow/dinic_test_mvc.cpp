// Codeforces gym 100269H - AC
// http://codeforces.com/gym/100269/problem/H
#include <bits/stdc++.h>
#define fst first
#define snd second
#define fore(i,a,n) for(int i=a,to=n;i<to;++i)
#define mp make_pair
#define fst first
#define snd second
#define MAXN 10005
#define pb push_back
#define SZ(x) int((x).size())
#define iter(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
using namespace std;
const int INF = ~(1<<31);
typedef long long ll;
typedef pair<int,int> ii;

int nodes,src,dst; // remember to init nodes
int dist[MAXN],q[MAXN],work[MAXN];
struct edge {int to,rev;ll f,cap;};
vector<edge> g[MAXN];
void add_edge(int s, int t, ll cap){
	g[s].pb((edge){t,SZ(g[t]),0,cap});
	g[t].pb((edge){s,SZ(g[s])-1,0,0});
}
bool dinic_bfs(){
	fill(dist,dist+nodes,-1);dist[src]=0;
	int qt=0;q[qt++]=src;
	for(int qh=0;qh<qt;qh++){
		int u=q[qh];
		fore(i,0,SZ(g[u])){
			edge &e=g[u][i];int v=g[u][i].to;
			if(dist[v]<0&&e.f<e.cap)dist[v]=dist[u]+1,q[qt++]=v;
		}
	}
	return dist[dst]>=0;
}
ll dinic_dfs(int u, ll f){
	if(u==dst)return f;
	for(int &i=work[u];i<SZ(g[u]);i++){
		edge &e=g[u][i];
		if(e.cap<=e.f)continue;
		int v=e.to;
		if(dist[v]==dist[u]+1){
			ll df=dinic_dfs(v,min(f,e.cap-e.f));
			if(df>0){e.f+=df;g[v][e.rev].f-=df;return df;}
		}
	}
	return 0;
}
ll max_flow(int _src, int _dst){
	src=_src;dst=_dst;
	ll result=0;
	while(dinic_bfs()){
		fill(work, work+nodes, 0);
		while(ll delta=dinic_dfs(src,INF))result+=delta;
	}
	return result;
}

map<string,int> pre,su;
int w[5005][2];
char c[5005][600];
vector<int> cc[2][5005];
bool u[5005];
bool vis[5005][5005];
int l=0,r=0;

vector<int> mvc(){
	vector<int> s;
	fore(i,0,l)if(dist[2+i]<0)s.pb(i);
	fore(i,0,r)if(dist[2+l+i]>0)s.pb(l+i);
	return s;
}

int main(){
#ifndef DEMETRIO
	freopen("heavy.in","r",stdin);
	freopen("heavy.out","w",stdout);
#endif

	int n,k;
	scanf("%d%d",&n,&k);
	fore(i,0,n) {
		scanf("%s",c[i]);
	}
	fore(i,0,n) {
		string s = "";
		fore(j,0,k)
			s+= c[i][j];
		if(pre.count(s) == 0)
			pre[s] = l++;
		w[i][0] = pre[s];
		s = "";
		int t = strlen(c[i]);
		fore(j,0,k) {
			s+= c[i][t-k+j];
		}
		if(su.count(s) == 0)
			su[s] = r++;
		w[i][1] = su[s];

	}
	nodes=2+l+r;
	fore(i,0,l)add_edge(0,2+i,1);
	fore(i,0,r)add_edge(2+l+i,1,1);
	fore(i,0,n) {
		if(vis[w[i][0]][w[i][1]] == 0) {
			add_edge(2+w[i][0],2+l+w[i][1],1);
			vis[w[i][0]][w[i][1]] = 1;
		}
		//printf(" %d %d\n",w[i][0],w[i][1]);
		cc[0][w[i][0]].pb(i);
		cc[1][w[i][1]].pb(i);
	}
	max_flow(0,1);
	vector<int> res = mvc();
	printf("%d\n",SZ(res));
	memset(u,false,sizeof(u));
	int s=0;
	fore(i,0,SZ(res)){
		int x=res[i],k=0;
		if(x>=l){
			x-=l;k=1;
		}
		vector<int> sol;
		fore(i,0,SZ(cc[k][x])){
			int w=cc[k][x][i];
			if(u[w])continue;
			else sol.pb(w);
			s++;
			u[w]=true;
		}
		assert(SZ(sol));
		if(SZ(sol)>1)swap(sol[0],sol[1]);
		printf("%d",SZ(sol));
		fore(i,0,SZ(sol))printf(" %d",sol[i]+1);
		puts("");
	}
	assert(s==n);
	return 0;
}

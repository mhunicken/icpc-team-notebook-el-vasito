// Codeforces gym 100765H - AC
// http://codeforces.com/gym/100765/problem/H
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN 2048


namespace D {
int nodes,src,dst; // remember to init nodes
int dist[MAXN],q[MAXN],work[MAXN];
struct edge {int to,rev,id;ll f,cap;};
vector<edge> g[MAXN];
void add_edge(int s, int t, ll cap, int id){
	g[s].pb((edge){t,(int)g[t].size(),id,0,cap});
	g[t].pb((edge){s,(int)g[s].size()-1,id,0,0});
}
bool dinic_bfs(){
	fill(dist,dist+nodes,-1);dist[src]=0;
	int qt=0;q[qt++]=src;
	for(int qh=0;qh<qt;qh++){
		int u=q[qh];
		fore(i,0,g[u].size()){
			edge &e=g[u][i];int v=g[u][i].to;
			if(dist[v]<0&&e.f<e.cap)dist[v]=dist[u]+1,q[qt++]=v;
		}
	}
	return dist[dst]>=0;
}
ll dinic_dfs(int u, ll f){
	if(u==dst)return f;
	for(int &i=work[u];i<g[u].size();i++){
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
		while(ll delta=dinic_dfs(src,1LL<<60))result+=delta;
	}
	return result;
}
}

struct pt {
	ll x,y;
	pt(ll x, ll y):x(x),y(y){}
	pt(){}
	pt operator-(pt p)const{return pt(x-p.x,y-p.y);}
	ll operator%(pt p)const{return x*p.y-y*p.x;}
};

struct Cmp {
	pt r;
	Cmp(pt r):r(r){}
	int cuad(const pt &a)const {
		if(a.x>0&&a.y>=0)return 0;
		if(a.x<=0&&a.y>0)return 1;
		if(a.x<0&&a.y<=0)return 2;
		if(a.x>=0&&a.y<0)return 3;
		assert(a.x==0&&a.y==0);
		return -1;
	}
	bool cmp(const pt& p1, const pt& p2)const {
		int c1=cuad(p1),c2=cuad(p2);
		//if(c1==c2)return p1.y*p2.x<p1.x*p2.y;
		if(c1==c2)return p1%p2>0;
		return c1<c2;
	}
	bool operator()(const pt& p1, const pt& p2)const {
		return cmp(p1-r,p2-r);
	}
};

map<pair<int,int>,int> ei;
map<pair<int,int>,int> ec;

vector<int> g[MAXN];int n; // input graph (must be connected)
int nd;
vector<int> nodes[MAXN]; // nodes delimiting region (in CW order)
map<pair<int,int>,int> ps,es;
void get_dual(vector<pt> p){ // p: points corresponding to nodes
	ps.clear();es.clear();
	fore(x,0,n){
		Cmp pc(p[x]); // (radial order of points)
		auto comp=[&](int a, int b){return pc(p[a],p[b]);};
		sort(g[x].begin(),g[x].end(),comp);
		fore(i,0,g[x].size())ps[{x,g[x][i]}]=i;
	}
	nd=0;
	fore(xx,0,n)for(auto yy:g[xx])if(!es.count({xx,yy})){
		int x=xx,y=yy;nodes[nd].clear();
		while(!es.count({x,y})){
			es[{x,y}]=nd;nodes[nd].pb(y);
			int z=g[y][(ps[{y,x}]+1)%g[y].size()];x=y;y=z;
		}
		nd++;
	}
	D::nodes=nd;
	for(auto p:es){
		pair<int,int> q={p.fst.snd,p.fst.fst};
		assert(es.count(q));
		int i=ei[p.fst],c=ec[p.fst];
		if(es[q]!=p.snd)D::add_edge(p.snd,es[q],c,i);
	}
}

int sgn(ll x){return x<0?-1:x>0;}
struct pol {
	int n;vector<pt> p;
	pol(){}
	pol(vector<pt> _p){p=_p;n=p.size();}
	bool cw(){
		ll r=0;
		fore(i,0,n)r+=p[i]%p[(i+1)%n];
		return r<0;
	}
	bool has(pt q){
		int cnt=0;
		fore(i,0,n){
			int j=(i+1)%n;
			int k=sgn((q-p[j])%(p[i]-p[j]));
			int u=sgn(p[i].y-q.y),v=sgn(p[j].y-q.y);
			if(k>0&&u<0&&v>=0)cnt++;
			if(k<0&&v<0&&u>=0)cnt--;
		}
		return cnt!=0;
	}
};

vector<pt> p;
map<pair<int,int>,int> ids;
int id(int x, int y){
	if(!ids.count({x,y})){
		p.pb(pt(x,y));
		ids[{x,y}]=n++;
	}
	return ids[{x,y}];
}

int m;

int main(){
	scanf("%d",&m);
	fore(i,0,m){
		int x0,y0,x1,y1,c;
		scanf("%d%d%d%d%d",&x0,&y0,&x1,&y1,&c);
		int x=id(x0,y0),y=id(x1,y1);
		g[x].pb(y);g[y].pb(x);
		ei[{x,y}]=ei[{y,x}]=i;
		ec[{x,y}]=ec[{y,x}]=c;
	}
	int x,y;
	scanf("%d%d",&x,&y);
	pt a(x,y);
	scanf("%d%d",&x,&y);
	pt b(x,y);
	get_dual(p);
	int src=-1,dst=-1;
	fore(i,0,nd){
		vector<pt> _q;
		for(auto j:nodes[i])_q.pb(p[j]);
		pol q(_q);
		if(!q.cw())continue;
		if(q.has(a))src=i;
		if(q.has(b))dst=i;
	}
	assert(src!=dst);
	printf("%lld\n",D::max_flow(src,dst));
	vector<int> r;
	fore(x,0,nd)if(D::dist[x]>=0)for(auto e:D::g[x])if(e.cap&&D::dist[e.to]<0)r.pb(e.id);
	printf("%d\n",(int)r.size());
	fore(i,0,r.size()){
		if(i)putchar(' ');
		printf("%d",r[i]+1);
	}
	puts("");
	return 0;
}

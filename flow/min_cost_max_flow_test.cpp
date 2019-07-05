// SPOJ GREED - AC
// https://www.spoj.com/problems/GREED/
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
typedef pair<int,int> ii;

typedef ll tf;
const tf INF=1e18;
struct MCF{
	int n;
	vector<tf> prio,curflow,prevedge,prevnode,pot;
	priority_queue<ll,vector<ll>,greater<ll>> q;
	struct edge{int to, rev; tf f, cap, cost;};
	vector<vector<edge>> g;
	MCF(int n):n(n),prio(n),curflow(n),prevedge(n),prevnode(n),pot(n),g(n){}
	void add_edge(int s, int t, tf cap, tf cost) {
		g[s].pb((edge){t,SZ(g[t]),0,cap,cost});
		g[t].pb((edge){s,SZ(g[s])-1,0,0,-cost});
	}
	pair<tf,tf> get_flow(int s, int t) {
		tf flow=0, flowcost=0;
		while(1){
			q.push(s);
			fill(ALL(prio),INF); 
			prio[s]=0; curflow[s]=INF;
			while(!q.empty()) {
				ll cur=q.top();
				int d=cur>>32, u=cur;
				q.pop();
				if(d!=prio[u]) continue;
				for(int i=0; i<SZ(g[u]); ++i) {
					edge &e=g[u][i];
					int v=e.to;
					if(e.cap<=e.f) continue;
					tf nprio=prio[u]+e.cost+pot[u]-pot[v];
					if(prio[v]>nprio) {
						prio[v]=nprio;
						q.push(((ll)nprio<<32)+v);
						prevnode[v]=u; prevedge[v]=i;
						curflow[v]=min(curflow[u], e.cap-e.f);
					}
				}
			}
			if(prio[t]==INF) break;
			fore(i,0,n) pot[i]+=prio[i];
			tf df=min(curflow[t], INF-flow);
			flow+=df;
			for(int v=t; v!=s; v=prevnode[v]) {
				edge &e=g[prevnode[v]][prevedge[v]];
				e.f+=df; g[v][e.rev].f-=df;
				flowcost+=df*e.cost;
			}
		}
		return {flow,flowcost};
	}
};

int q[512];
int n;

int main(){FIN;
	int tn; cin>>tn;
	while(tn--){
		cin>>n;
		MCF nt(n+2);
		memset(q,0,sizeof(q));
		fore(i,0,n){
			int x; cin >>x; x--;
			q[x]++;
		}
		fore(i,0,n)if(q[i]>0)nt.add_edge(0,2+i,q[i],0);
		fore(i,0,n)nt.add_edge(2+i,1,1,0);
		int m; cin>>m;
		while(m--){
			int x,y; cin>>x>>y; x--; y--;
			nt.add_edge(2+x,2+y,512,1);
			nt.add_edge(2+y,2+x,512,1);
		}
		cout << nt.get_flow(0,1).snd<<"\n";
	}
	return 0;
}

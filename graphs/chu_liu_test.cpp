// Topcoder SRM 584 Div1, 900 - AC
// https://community.topcoder.com/stat?c=problem_statement&pm=12614&rd=15696
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

class FoxTheLinguist {

typedef ll tw;static const tw INF=1<<30;
struct edge {int src,dst;tw w;};
struct ChuLiu {
	int n,r;tw cost;bool found;
	vector<int> no,pr,mark;
	vector<vector<int> > comp,nx;
	vector<tw> mcost;
	vector<vector<edge> > h;
	ChuLiu(int n):n(n),h(n){}
	void add_edge(int x, int y, tw w){h[y].pb((edge){x,y,w});}
	void visit(int v, int s){
		if(mark[v]){
			vector<int> temp=no;found=true;
			do {
				cost+=mcost[v];v=pr[v];
				if(v!=s)while(comp[v].size()>0){
					no[comp[v].back()]=s;
					comp[s].pb(comp[v].back());
					comp[v].pop_back();
				}
			}while(v!=s);
			for(int j:comp[s])if(j!=r)for(edge& e:h[j])
				if(no[e.src]!=s)e.w-=mcost[temp[j]];
		}
		mark[v]=true;
		for(int i:nx[v])if(no[i]!=no[v]&&pr[no[i]]==v)
			if(!mark[no[i]]||i==s)
				visit(i,s);
	}
	tw doit(int _r){ // r: root (O(nm))
		r=_r;
		no.resize(n);comp.clear();comp.resize(n);
		fore(x,0,n)comp[x].pb(no[x]=x);
		for(cost=0;;){
			pr.clear();pr.resize(n,-1);
			mcost=vector<tw>(n,INF);
			fore(j,0,n)if(j!=r)for(edge e:h[j])
				if(no[e.src]!=no[j]&&e.w<mcost[no[j]])
					mcost[no[j]]=e.w,pr[no[j]]=no[e.src];
			nx.clear();nx.resize(n);
			fore(x,0,n)if(pr[x]>=0)nx[pr[x]].pb(x);
			bool stop=true;
			mark.clear();mark.resize(n);
			fore(x,0,n)if(x!=r&&!mark[x]&&!comp[x].empty()){
				found=false;visit(x,x);
				if(found)stop=false;
			}
			if(stop){
				fore(x,0,n)if(pr[x]>=0)cost+=mcost[x];
				return cost;
			}
		}
	}
};
vector<vector<int> > g;
vector<bool> vis;
void dfs(int x){
	if(vis[x])return;
	vis[x]=true;
	for(int y:g[x])dfs(y);
}
public:
int minimalHours(int n, vector<string> courseInfo){
	g=vector<vector<int> >(9*n+1);
	ChuLiu c(9*n+1);
	string s;
	for(string t:courseInfo)s+=t;
	for(int i=0;i<s.size();i+=12){
		int x,y;ll w;
		if(s[i+1]=='0')x=0;
		else x=(s[i]-'A')*9+s[i+1]-'0';
		if(s[i+5]=='0')y=0;
		else y=(s[i+4]-'A')*9+s[i+5]-'0';
		w=(s[i+7]-'0')*1000+(s[i+8]-'0')*100+(s[i+9]-'0')*10+(s[i+10]-'0');
		c.add_edge(x,y,w);
		g[x].pb(y);
	}
	fore(i,0,n)fore(j,1,10){
		int x,y;
		x=i*9+j;
		if(j==1)y=0;
		else y=x-1;
		c.add_edge(x,y,0);
		g[x].pb(y);
	}
	vis=vector<bool>(9*n+1,false);
	dfs(0);
	fore(i,0,9*n+1)if(!vis[i])return -1;
	//return (int)c.doit(0);;
	int r=c.doit(0);
	//fore(x,0,9*n+1)printf("%d %d\n",x,c.pr[x]);
	//fore(x,0,9*n+1){
	//	printf("%d ",x);
	//	for(int y:c.comp[x])printf(" %d",y);
	//	puts("");
	//}
	return r;
}

};

FoxTheLinguist w;

int main(){
	printf("%d\n",w.minimalHours(1,{"A0->A9:1000 A0->A6:0300 A3->A9:0600"}));
	printf("%d\n",w.minimalHours(2,{"A0->A9:1000 B0->B9:1000 A1->B9:0300 B1->A9:0200"}));
	printf("%d\n",w.minimalHours(3,{"C0->A6:00", "01 A3", "->B9:0001 A3->C6:000", "1"," C3->A9:0001 A9->C9:0001 A0->A9:9999"," B0->B9:9999 C0->C9:9999 A6->A9:9999"}));
	printf("%d\n",w.minimalHours(4,{"A0->A6:6666 A0->A9:9999"," B0->B6:6666 B0->B9:9999"," C0->C6:6666 C0->C9:9999"," D0->D6:6666 D0->D9:9999"," A6->B6:0666 B6->C6:0666"," C6->D6:0666 D6->A6:0666"," A9->B9:0099 B9->C9:0099"," C9->D9:0099 D9->A9:0099"}));
	printf("%d\n",w.minimalHours(1,{"A0->A9:9999 A0->A9:8888"}));
	printf("%d\n",w.minimalHours(1,{"A9->A9:0000"," A9->A0:0000"}));
	return 0;
}


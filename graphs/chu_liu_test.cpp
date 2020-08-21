// Topcoder SRM 584 Div1, 900 - AC
// https://community.topcoder.com/stat?c=problem_statement&pm=12614&rd=15696
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

typedef int tw; tw INF=1ll<<30;
class FoxTheLinguist {

//O(n*m) minimum spanning tree in directed graph
//returns -1 if not possible
//included i-th edge if take[i]!=0
struct edge{int u,v,id;tw len;};
struct ChuLiu{
	int n; vector<edge> e;
	vector<int> inc,dec,take,pre,num,id,vis;
	vector<tw> inw;
	void add_edge(int x, int y, tw w){
		inc.pb(0); dec.pb(0); take.pb(0);
		e.pb({x,y,SZ(e),w});
	}
	ChuLiu(int n):n(n),pre(n),num(n),id(n),vis(n),inw(n){}
	tw doit(int root){
		auto e2=e;
		tw ans=0; int eg=SZ(e)-1,pos=SZ(e)-1;
		while(1){
			fore(i,0,n) inw[i]=INF,id[i]=vis[i]=-1;
			for(auto ed:e2) if(ed.len<inw[ed.v]){
				inw[ed.v]=ed.len; pre[ed.v]=ed.u;
				num[ed.v]=ed.id;
			}
			inw[root]=0;
			fore(i,0,n) if(inw[i]==INF) return -1;
			int tot=-1;
			fore(i,0,n){
				ans+=inw[i];
				if(i!=root)take[num[i]]++;
				int j=i;
				while(vis[j]!=i&&j!=root&&id[j]<0)vis[j]=i,j=pre[j];
				if(j!=root&&id[j]<0){
					id[j]=++tot;
					for(int k=pre[j];k!=j;k=pre[k]) id[k]=tot;
				}
			}
			if(tot<0)break;
			fore(i,0,n) if(id[i]<0)id[i]=++tot;
			n=tot+1; int j=0;
			fore(i,0,SZ(e2)){
				int v=e2[i].v;
				e2[j].v=id[e2[i].v];
				e2[j].u=id[e2[i].u];
				if(e2[j].v!=e2[j].u){
					e2[j].len=e2[i].len-inw[v];
					inc.pb(e2[i].id);
					dec.pb(num[v]);
					take.pb(0);
					e2[j++].id=++pos;
				}
			}
			e2.resize(j);
			root=id[root];
		}
		while(pos>eg){
			if(take[pos]>0) take[inc[pos]]++, take[dec[pos]]--;
			pos--;
		}
		return ans;
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


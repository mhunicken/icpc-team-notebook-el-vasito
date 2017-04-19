// UVA 10054 - AC
// https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=995
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN 64

// Undirected version
struct edge {
	int y;
	list<edge>::iterator rev;
	edge(int y):y(y){}
};
list<edge> g[MAXN];
void add_edge(int a, int b){
	g[a].push_front(edge(b));auto ia=g[a].begin();
	g[b].push_front(edge(a));auto ib=g[b].begin();
	ia->rev=ib;ib->rev=ia;
}
vector<int> p;
void go(int x){
	while(g[x].size()){
		int y=g[x].front().y;
		g[y].erase(g[x].front().rev);
		g[x].pop_front();
		go(y);
	}
	p.push_back(x);
}
vector<int> get_path(int x){ // get a path that begins in x
// check that a path exists from x before calling to get_path!
	p.clear();go(x);reverse(p.begin(),p.end());
	return p;
}

int d[MAXN];
int m;

int main(){
	int tn;
	scanf("%d",&tn);
	fore(tc,1,tn+1){
		if(tc>1)puts("");
		printf("Case #%d\n",tc);
		fore(i,0,MAXN)g[i].clear();
		memset(d,0,sizeof(d));
		scanf("%d",&m);
		fore(i,0,m){
			int x,y;
			scanf("%d%d",&x,&y);x--;y--;
			add_edge(x,y);
			d[x]++;d[y]++;
		}
		bool c=true;
		fore(i,0,MAXN)c=c&&d[i]%2==0;
		if(!c){puts("some beads may be lost");continue;}
		vector<int> p;
		fore(i,0,MAXN)if(d[i]){p=get_path(i);break;}
		if(p.size()!=m+1){puts("some beads may be lost");continue;}
		fore(i,0,m)printf("%d %d\n",p[i]+1,p[i+1]+1);
	}
	return 0;
}








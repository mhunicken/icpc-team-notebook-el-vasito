// SPOJ UCV2013B - AC
// http://www.spoj.com/problems/UCV2013B/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN 128
#define INF (1LL<<61)

// g[i][j]: weight of edge (i, j) or INF if there's no edge
// g[i][i]=0
ll g[MAXN][MAXN];int n;
void floyd(){ // O(n^3) . Replaces g with min distances
	fore(k,0,n)fore(i,0,n)if(g[i][k]<INF)fore(j,0,n)if(g[k][j]<INF)
		g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
}
bool inNegCycle(int v){return g[v][v]<0;}
bool hasNegCycle(int a, int b){ // true iff there's neg cycle in between
	fore(i,0,n)if(g[a][i]<INF&&g[i][b]<INF&&g[i][i]<0)return true;
	return false;
}

char s[MAXN][32];

int main(){
	int tc=1;
	while(scanf("%d",&n),n){
		fore(i,0,n){
			scanf("%s",s[i]);
			fore(j,0,n){
				scanf("%lld",&g[i][j]);
				if(i!=j&&!g[i][j])g[i][j]=INF;
				else if(i==j&&g[i][j]>0)g[i][j]=0;
			}
		}
		floyd();
		int q;
		scanf("%d",&q);
		printf("Case #%d:\n",tc++);
		while(q--){
			int x,y;
			scanf("%d%d",&x,&y);
			if(hasNegCycle(x,y))puts("NEGATIVE CYCLE");
			else {
				printf("%s-%s ",s[x],s[y]);
				if(g[x][y]==INF)puts("NOT REACHABLE");
				else printf("%lld\n",g[x][y]);
			}
		}
	}
	return 0;
}

// SPOJ SHPATH - AC
// http://www.spoj.com/problems/SHPATH/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,to=b;i<to;++i)
using namespace std;
typedef long long ll;

#define MAXN 10005

vector<pair<int,int> > g[MAXN];  // u->[(v,cost)]
ll dist[MAXN];
void dijkstra(int x){
	memset(dist,-1,sizeof(dist));
	priority_queue<pair<ll,int> > q;
	dist[x]=0;q.push({0,x});
	while(!q.empty()){
		x=q.top().snd;ll c=-q.top().fst;q.pop();
		if(dist[x]!=c)continue;
		fore(i,0,g[x].size()){
			int y=g[x][i].fst; ll c=g[x][i].snd;
			if(dist[y]<0||dist[x]+c<dist[y])
				dist[y]=dist[x]+c,q.push({-dist[y],y});
		}
	}
}

int n;
char s[MAXN][16];
char s0[16];
char s1[16];

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		scanf("%d",&n);
		fore(i,0,n){
			scanf("%s",s[i]);
			int k;
			scanf("%d",&k);
			while(k--){
				int j;ll c;
				scanf("%d%lld",&j,&c);j--;
				g[i].pb({j,c});
			}
		}
		int q;
		scanf("%d",&q);
		while(q--){
			scanf("%s%s",s0,s1);
			int x,y;
			fore(i,0,n){
				if(!strcmp(s[i],s0))x=i;
				if(!strcmp(s[i],s1))y=i;
			}
			dijkstra(x);
			printf("%lld\n",dist[y]);
		}
		fore(i,0,n)g[i].clear();
	}
	return 0;
}

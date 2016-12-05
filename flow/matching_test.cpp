// UVA 1184 - AC
// https://uva.onlinejudge.org/index.php?option=onlinejudge&Itemid=99999999&category=246&page=show_problem&problem=3625
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,to=b;i<to;++i)
using namespace std;
typedef long long ll;

#define MAXN 128
#define MAXM 128

// both sides numbered [0,n) and [0,m)
vector<int> g[MAXN];
int mat[MAXM];bool vis[MAXN];
int n,m;
int match(int x){
	if(vis[x])return 0;
	vis[x]=true;
	fore(i,0,g[x].size()){
		int y=g[x][i];
		if(mat[y]<0||match(mat[y])){mat[y]=x;return 1;}
	}
	return 0;
}
vector<pair<int,int> > max_matching(){
	vector<pair<int,int> > r;
	memset(mat,-1,sizeof(mat));
	fore(i,0,n)memset(vis,false,sizeof(vis)),match(i);
	fore(i,0,m)if(mat[i]>=0)r.pb(mp(mat[i],i));
	return r;
}

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		int e;
		scanf("%d%d",&n,&e);m=n;
		while(e--){
			int x,y;
			scanf("%d%d",&x,&y);x--;y--;
			g[x].pb(y);
		}
		printf("%d\n",n-(int)max_matching().size());
		fore(i,0,n)g[i].clear();
	}
	return 0;
}

// SPOJ SUBST1 - AC
// http://www.spoj.com/problems/SUBST1/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN (1<<18)
#define INF (1<<30)

struct SuffixTree {
	char s[MAXN];
	map<int,int> to[MAXN];
	int len[MAXN]={INF},fpos[MAXN],link[MAXN];
	int node,pos,sz=1,n=0;
	void clear(){
		node=pos=n=0;
		fore(i,0,sz)to[i].clear();
		sz=1;
	}
	int make_node(int p, int l){
		fpos[sz]=p;len[sz]=l;return sz++;}
	void go_edge(){
		while(pos>len[to[node][s[n-pos]]]){
			node=to[node][s[n-pos]];
			pos-=len[node];
		}
	}
	void add(int c){
		s[n++]=c;pos++;
		int last=0;
		while(pos>0){
			go_edge();
			int edge=s[n-pos];
			int& v=to[node][edge];
			int t=s[fpos[v]+pos-1];
			if(v==0){
				v=make_node(n-pos,INF);
				link[last]=node;last=0;
			}
			else if(t==c){link[last]=node;return;}
			else {
				int u=make_node(fpos[v],pos-1);
				to[u][c]=make_node(n-1,INF);
				to[u][t]=v;
				fpos[v]+=pos-1;len[v]-=pos-1;
				v=u;link[last]=u;last=u;
			}
			if(node==0)pos--;
			else node=link[node];
		}
	}
	ll doit(){
		ll r=0;
		fore(i,1,sz)r+=min(len[i],n-fpos[i]);
		return r;
	}
};

char s[MAXN];
SuffixTree t;

int main(){
	int tn;
	scanf("%d",&tn);fgets(s,MAXN,stdin);
	while(tn--){
		fgets(s,MAXN,stdin);
		t.clear();
		for(int i=0;s[i]&&s[i]!='\n';++i)t.add(s[i]);
		printf("%lld\n",t.doit());
	}
	return 0;
}

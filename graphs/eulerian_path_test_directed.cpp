// Codeforces 508D - AC
// http://codeforces.com/problemset/problem/508/D
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN 4096

struct edge {
	int y;
//	list<edge>::iterator rev;
	edge(int y):y(y){}
};
list<edge> g[MAXN];
void add_edge(int a, int b){
	g[a].push_front(edge(b));//auto ia=g[a].begin();
//	g[b].push_front(edge(a));auto ib=g[b].begin();
//	ia->rev=ib;ib->rev=ia;
}
vector<int> p;
void go(int x){
	while(g[x].size()){
		int y=g[x].front().y;
		//g[y].erase(g[x].front().rev);
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

int n,m;
int in[MAXN],out[MAXN];
char w[MAXN][2];

map<pair<char,char>,int> ids;
int id(char a, char b){
	if(!ids.count({a,b})){
		w[n][0]=a;w[n][1]=b;
		ids[{a,b}]=n++;
	}
	return ids[{a,b}];
}

int main(){
	scanf("%d",&m);
	fore(_,0,m){
		char s[8];
		scanf("%s",s);
		int x=id(s[0],s[1]),y=id(s[1],s[2]);
		add_edge(x,y);
		out[x]++;in[y]++;
	}
	int x=-1;
	fore(i,0,n){
		if(out[i]==in[i]+1){
			if(x>=0){puts("NO");return 0;}
			x=i;
		}
		else if(abs(out[i]-in[i])>1){puts("NO");return 0;}
	}
	if(x<0)x=0;
	vector<int> p=get_path(x);
	if(p.size()!=m+1){puts("NO");return 0;}
	puts("YES");
	putchar(w[x][0]);putchar(w[x][1]);
	fore(i,1,p.size())putchar(w[p[i]][1]);
	puts("");
	return 0;
}




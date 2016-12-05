// UVA 10679 - AC
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,to=b;i<to;++i)
using namespace std;
typedef long long ll;

char red(char c){
	if(c>='a'&&c<='z')return c-'a';
	if(c>='A'&&c<='Z')return 26+c-'A';
	return 52+c-'0';
}
struct vertex {
	int next[64],go[64],p,link;
	char pch;
	vector<int> leaf;
};
vertex t[1<<20];
int sz;
void aho_init(){ //do not forget!!
	t[0].p=t[0].link=-1;
	memset(t[0].next,-1,sizeof(t[0].next));
	memset(t[0].go,-1,sizeof(t[0].go));
	sz=1;
}
void add_string(char *s, int id){
	int v=0;
	for(int i=0;s[i];++i){
		char c=red(s[i]);
		if(t[v].next[c]<0){
			memset(t[sz].next,-1,sizeof(t[sz].next));
			memset(t[sz].go,-1,sizeof(t[sz].go));
			t[sz].p=v;t[sz].pch=c;t[sz].link=-1;
			t[v].next[c]=sz++;
		}
		v=t[v].next[c];
	}
	t[v].leaf.pb(id);
}
int go(int v, char c);
int get_link(int v){
	if(t[v].link<0)
		if(!v||!t[v].p)t[v].link=0;
		else t[v].link=go(get_link(t[v].p),t[v].pch);
	return t[v].link;
}
int go(int v, char c){//remember red
	if(t[v].go[c]<0)
		if(t[v].next[c]>=0)t[v].go[c]=t[v].next[c];
		else t[v].go[c]=v==0?0:go(get_link(v),c);
	return t[v].go[c];
}

bool r[1024];
bool vis[1<<20];

void proc(int x){
	if(vis[x])return;
	vis[x]=true;
	fore(i,0,t[x].leaf.size())r[t[x].leaf[i]]=true;
	proc(t[x].link);
}

char s[100005];
char tt[100005];
int n;

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		aho_init();
		scanf("%s%d",s,&n);
		fore(i,0,n){
			scanf("%s",tt);
			add_string(tt,i);
		}
		int k=0;
		for(int i=0;s[i];++i){
			k=go(k,red(s[i]));
			proc(k);
		}
		fore(i,0,n)puts(r[i]?"y":"n");
	}
	return 0;
}

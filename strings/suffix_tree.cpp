struct SuffixTree {
	char s[MAXN];
	map<int,int> to[MAXN];
	int len[MAXN]={INF},fpos[MAXN],link[MAXN];
	int node,pos,sz=1,n=0;
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
};

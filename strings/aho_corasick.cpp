#define K 32
#define NMAX (1<<20)
struct vertex {
	int next[K];
	bool leaf;
	int p;
	char pch;
	int link;
	int go[K];
};
vertex t[NMAX];
int sz;
void init(){
	t[0].p=t[0].link=-1;
	memset(t[0].next,255,sizeof(t[0].next));
	memset(t[0].go,255,sizeof(t[0].go));
	t[0].leaf=false;
	sz=1;
}
char red(char c){return c-'a';} // change if not only lowercase
void add_string(const string& s){
	int v=0;
	for(int i=0;i<s.length();++i){
		char c=red(s[i]);
		if(t[v].next[c]==-1){
			memset(t[sz].next,255,sizeof(t[sz].next));
			memset(t[sz].go,255,sizeof(t[sz].go));
			t[sz].link=-1;
			t[sz].p=v;
			t[sz].pch=c;
			t[sz].leaf=false;
			t[v].next[c]=sz++;
		}
		v=t[v].next[c];
	}
	t[v].leaf=true;
}
int go(int v, char c);
int get_link(int v){
	if(t[v].link==-1)
		if(v==0||t[v].p==0)t[v].link=0;
		else t[v].link=go(get_link(t[v].p),t[v].pch);
	return t[v].link;
}
int go(int v, char c){
	c=red(c);
	if(t[v].go[c]==-1)
		if(t[v].next[c]!=-1)
			t[v].go[c]=t[v].next[c];
		else
			t[v].go[c]=v==0?0:go(get_link(v),c);
	return t[v].go[c];
}

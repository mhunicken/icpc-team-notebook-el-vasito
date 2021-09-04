vector<int> kmppre(string& t){ // r[i]: longest border of t[0,i)
	vector<int> r(t.size()+1); r[0]=-1; int j=-1;
	fore(i,0,t.size()){
		while(j>=0&&t[i]!=t[j])j=r[j];
		r[i+1]=++j;
	}
	return r;
}
void kmp(string& s, string& t){ // find t in s
	int j=0;vector<int> b=kmppre(t);
	fore(i,0,SZ(s)){
		while(j>=0&&s[i]!=t[j])j=b[j];
		if(++j==SZ(t))printf("Match at %d\n",i-j+1),j=b[j];
	}
}
//KMP automaton
const int MAXN=1e5,MAXC=26;
int wh[MAXN+2][MAXC];//wh[i][j] = jump when adding j to prefix of size i
void build(string &s){
	fore(j,0,MAXC) wh[0][j]=0;
	int lps=0; wh[0][s[0]-'a'] = 1;
	fore(i,1,SZ(s)+1){
		fore(j,0,MAXC) wh[i][j]=wh[lps][j];
		if(i<SZ(s)) wh[i][s[i]-'a'] = i+1, lps = wh[lps][s[i]-'a'];
	}
}

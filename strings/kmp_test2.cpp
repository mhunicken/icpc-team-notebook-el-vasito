// SPOJ NHAY - AC
// http://www.spoj.com/problems/NHAY/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

vector<int> kmppre(string& t){ // r[i]: longest border of t[0,i)
	vector<int> r(t.size()+1);r[0]=-1;
	int j=-1;
	fore(i,0,t.size()){
		while(j>=0&&t[i]!=t[j])j=r[j];
		r[i+1]=++j;
	}
	return r;
}
void kmp(string& t){ // find t in input
	int j=0;vector<int> b=kmppre(t);
	char c;int i=0;
	while(c=getchar(),c!='\n'&&c!=EOF){
		while(j>=0&&c!=t[j])j=b[j];
		if(++j==t.size())printf("%d\n",i-j+1),j=b[j];
		i++;
	}
}

int n;
char *s;

int main(){
	bool p=false;
	while(scanf("%d",&n)!=EOF){
		if(p)puts("");
		p=true;
		s=(char*)malloc(n+5);
		scanf("%s",s);
		assert(getchar()=='\n');
		string ss(s);
		kmp(ss);
	}
	return 0;
}

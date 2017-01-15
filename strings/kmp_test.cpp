// UVA 11888 - AC
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2988
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
void kmp(string& s, string& t){ // find t in s
	int j=0;vector<int> b=kmppre(t);
	fore(i,0,s.size()){
		while(j>=0&&s[i]!=t[j])j=b[j];
		if(++j==t.size())printf("Match at %d\n",i-j+1),j=b[j];
	}
}

string s0,s;

int main(){
	int tn;
	cin>>tn;
	while(tn--){
		cin>>s0;
		s=s0;
		s+="#$";
		reverse(s0.begin(),s0.end());
		s+=s0;
		vector<int> b=kmppre(s);
		int k=s.size();
		set<int> w;
		while(b[k]>0)w.insert(b[k]),k=b[k];
		s=s0;
		s+="#$";
		reverse(s0.begin(),s0.end());
		s+=s0;
		b=kmppre(s);
		k=s.size();
		bool r=false;
		while(b[k]>0)r=r||w.count(s0.size()-b[k]),k=b[k];
		if(r)puts("alindrome");
		else if(w.count(s0.size()))puts("palindrome");
		else puts("simple");
	}
	return 0;
}


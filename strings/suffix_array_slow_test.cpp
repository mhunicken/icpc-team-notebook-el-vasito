// ICPC Live Archive 5794 - AC
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3805
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,to=b;i<to;++i)
using namespace std;

typedef long long ll;

#define MAXN (1<<20)

pair<int, int> sf[MAXN];
bool sacomp(int lhs, int rhs) {return sf[lhs]<sf[rhs];}
vector<int> constructSA(string& s){
	int n=s.size();
	vector<int> sa(n),r(n);
	fore(i,0,n)r[i]=s[i];
	for(int m=1;m<n;m*=2){
		fore(i,0,n)sa[i]=i,sf[i]={r[i],i+m<n?r[i+m]:-1};
		stable_sort(sa.begin(),sa.end(),sacomp);
		r[sa[0]]=0;
		fore(i,1,n)r[sa[i]]=sf[sa[i]]!=sf[sa[i-1]]?i:r[sa[i-1]];
	}
	return sa;
}
vector<int> computeLCP(string& s, vector<int>& sa){
	int n=s.size(),L=0;
	vector<int> lcp(n),plcp(n),phi(n);
	phi[sa[0]]=-1;
	fore(i,1,n)phi[sa[i]]=sa[i-1];
	fore(i,0,n){
		if(phi[i]<0){plcp[i]=0;continue;}
		while(s[i+L]!='$'&&s[i+L]==s[phi[i]+L])L++;  // small modification on this line (specific of the problem)
		plcp[i]=L;
		L=max(L-1,0);
	}
	fore(i,0,n)lcp[i]=plcp[sa[i]];
	return lcp;
}

int m;
int w[MAXN];
int r[MAXN];
char s[MAXN];
set<ll> sol;
stack<pair<int,ll> > st;

int main(){
	while(scanf("%d",&m),m){
		sol.clear();
		string T="$";
		memset(w,-1,sizeof(w));
		fore(i,0,m){
			scanf("%s",s);
			for(int j=0;s[j];++j)w[T.size()+j]=i;
			T+=s;
			for(int j=T.size()-1;T[j]!='$';j--)r[j]=T.size()-j;
			T+="$";
		}
		T+="#";
		vector<int> SA=constructSA(T);
		vector<int> LCP=computeLCP(T,SA);LCP.pb(0);
		fore(i,0,T.size()){
			if(w[SA[i]]>=0&&r[SA[i]]>max(LCP[i],LCP[i+1]))sol.insert(1LL<<w[SA[i]]);
		}
		fore(i,0,T.size()){
			ll r=0;
			while(!st.empty()&&st.top().fst>LCP[i]){
				sol.insert(st.top().snd|r);
				r|=st.top().snd;
				st.pop();
			}
			if(!st.empty())st.top().snd|=r;
			if(!LCP[i])continue;
			if(st.empty()||st.top().fst<LCP[i]){
				assert(w[SA[i-1]]>=0&&w[SA[i]]>=0);
				st.push({LCP[i],r|(1LL<<w[SA[i-1]])|(1LL<<w[SA[i]])});
			}
			else {
				assert(st.top().fst==LCP[i]);
				st.top().snd|=1LL<<w[SA[i]];
			}
		}
		ll r=0;
		while(!st.empty()){
			sol.insert(st.top().snd|r);
			r|=st.top().snd;
			st.pop();
		}
		printf("%d\n",(int)sol.size());
	}
	return 0;
}

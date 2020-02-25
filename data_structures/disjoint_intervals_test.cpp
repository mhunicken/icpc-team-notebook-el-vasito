#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

// stores disjoint intervals as [first, second)
struct disjoint_intervals {
	set<pair<int,int> > s;
	void insert(pair<int,int> v){
		if(v.fst>=v.snd) return;
		auto at=s.lower_bound(v);auto it=at;
		if(at!=s.begin()&&(--at)->snd>=v.fst)v.fst=at->fst,--it;
		for(;it!=s.end()&&it->fst<=v.snd;s.erase(it++))
			v.snd=max(v.snd,it->snd);
		s.insert(v);
	}
};

bool w[1024];
disjoint_intervals z;

int main(){
	fore(_,0,10000){
		memset(w,false,sizeof(w));
		z.s.clear();
		fore(_,0,100){
			int a=rand()%1000,b=min(a-1+rand()%50,1000);
			z.insert({a,b});
			fore(i,a,b)w[i]=true;
			vector<pair<int,int> > v;
			int i=0;
			while(i<1000){
				if(!w[i]){i++;continue;}
				int j=i;
				while(j<1000&&w[j])j++;
				v.pb({i,j});
				i=j;
			}
			vector<pair<int,int> > vs(z.s.begin(),z.s.end());
			assert(v==vs);
		}
	}
	return 0;
}

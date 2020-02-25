// SPOJ LIS2 - AC
// http://www.spoj.com/problems/LIS2/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define INF (1<<30)

// stores pairs (benefit,cost) (erases non-optimal pairs)
struct GCS {
	set<pair<int,int> > s;
	void add(int g, int c){
		pair<int,int> x={g,c};
		auto p=s.lower_bound(x);
		if(p!=s.end()&&p->snd<=x.snd)return;
		if(p!=s.begin()){ // erase pairs with less benefit
			--p;            // and more cost
			while(p->snd>=x.snd){
				if(p==s.begin()){s.erase(p);break;}
				s.erase(p--);
			}
		}
		s.insert(x);
	}
	int get(int gain){ // min cost for some benefit
		auto p=s.lower_bound((pair<int,int>){gain,-INF});
		int r=p==s.end()?INF:p->snd;
		return r;
	}
};


int n,x[100005],y[100005];
GCS w[100005];

int lis(){
	w[0].add(INF,-INF);
	int r=0;
	fore(i,0,n){
		int s=0,e=i+1;
		while(e-s>1){
			int m=(s+e)/2;
			if(w[m].get(-x[i]+1)<y[i])s=m;
			else e=m;
		}
		r=max(r,s+1);
		w[s+1].add(-x[i],y[i]);
	}
	return r;
}


int main(){
	scanf("%d",&n);
	fore(i,0,n)scanf("%d%d",x+i,y+i);
	printf("%d\n",lis());
	return 0;
}

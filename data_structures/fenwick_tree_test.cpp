// SPOJ KQUERY - AC
// http://www.spoj.com/problems/KQUERY/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN 30005

int ft[MAXN+1]; // for more dimensions, make ft multi-dimensional
void upd(int i0, int v){ // add v to i0th element (0-based)
	// add extra fors for more dimensions
	for(int i=i0+1;i<=MAXN;i+=i&-i)ft[i]+=v;
}
int get(int i0){ // get sum of range [0,i0)
	int r=0;
	// add extra fors for more dimensions
	for(int i=i0;i;i-=i&-i)r+=ft[i];
	return r;
}
int get_sum(int i0, int i1){ // get sum of range [i0,i1) (0-based)
	return get(i1)-get(i0);
}

vector<pair<int,pair<int,pair<int,int> > > > e;

int r[200005];
int n,q;

int main(){
	scanf("%d",&n);
	fore(i,0,n){
		int x;
		scanf("%d",&x);
		e.pb({-x,{i,{-1,-1}}});
	}
	scanf("%d",&q);
	fore(qi,0,q){
		int i,j,k;
		scanf("%d%d%d",&i,&j,&k);i--;
		e.pb({-k,{-qi-1,{i,j}}});
	}
	sort(e.begin(),e.end());
	fore(i,0,e.size()){
		if(e[i].snd.fst>=0){
			int p=e[i].snd.fst;
			upd(p,1);
		}
		else {
			int qi=-e[i].snd.fst-1;
			int x=e[i].snd.snd.fst;
			int y=e[i].snd.snd.snd;
			r[qi]=get_sum(x,y);
		}
	}
	fore(i,0,q)printf("%d\n",r[i]);
	return 0;
}

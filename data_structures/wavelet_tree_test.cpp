// SPOJ ILKQUERYIII - AC
// http://www.spoj.com/problems/ILKQUERYIII/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

struct WT {
	vector<int> wt[1<<20];int n;
	void init(int k, int s, int e){
		if(s+1==e)return;
		wt[k].clear();wt[k].pb(0);
		int m=(s+e)/2;
		init(2*k,s,m);init(2*k+1,m,e);
	}
	void add(int k, int s, int e, int v){
		if(s+1==e)return;
		int m=(s+e)/2;
		if(v<m)wt[k].pb(wt[k].back()),add(2*k,s,m,v);
		else wt[k].pb(wt[k].back()+1),add(2*k+1,m,e,v);
	}
	int query0(int k, int s, int e, int a, int b, int i){
		if(s+1==e)return s;
		int m=(s+e)/2;
		int q=(b-a)-(wt[k][b]-wt[k][a]);
		if(i<q)return query0(2*k,s,m,a-wt[k][a],b-wt[k][b],i);
		else return query0(2*k+1,m,e,wt[k][a],wt[k][b],i-q);
	}
	void upd(int k, int s, int e, int i){
		if(s+1==e)return;
		int m=(s+e)/2;
		int v0=wt[k][i+1]-wt[k][i],v1=wt[k][i+2]-wt[k][i+1];
		if(!v0&&!v1)upd(2*k,s,m,i-wt[k][i]);
		else if(v0&&v1)upd(2*k+1,m,e,wt[k][i]);
		else if(v0)wt[k][i+1]--;
		else wt[k][i+1]++;
	}
	void init(int _n){n=_n;init(1,0,n);} // (values in range [0,n))
	void add(int v){add(1,0,n,v);}
	int query0(int a, int b, int i){ // ith element in range [a,b)
		return query0(1,0,n,a,b,i);    // (if it was sorted)
	}
	void upd(int i){ // swap positions i,i+1
		upd(1,0,n,i);
	}
};

vector<int> z[1<<20];
int n,q,c;
int x[1<<20];
pair<int,int> xx[1<<20];
WT wt;

int main(){
	scanf("%d%d",&n,&q);
	fore(i,0,n){
		int k;
		scanf("%d",&k);
		xx[i]={k,i};
	}
	sort(xx,xx+n);
	c=0;
	fore(i,0,n){
		if(i>0&&xx[i].fst!=xx[i-1].fst)c++;
		x[xx[i].snd]=c;
	}
	c++;
	wt.init(c);
	fore(i,0,n)wt.add(x[i]),z[x[i]].pb(i);
	while(q--){
		int t;
		scanf("%d",&t);
		if(t==0){
			int i,l,k;
			scanf("%d%d%d",&i,&l,&k);i++;l--;k--;
			int d=wt.query0(0,i,k);
			if(l>=z[d].size())puts("-1");
			else printf("%d\n",z[d][l]);
		}
		else {
			int i;
			scanf("%d",&i);
			if(x[i]==x[i+1])continue;
			int k=lower_bound(z[x[i]].begin(),z[x[i]].end(),i)-z[x[i]].begin();
			z[x[i]][k]++;
			k=lower_bound(z[x[i+1]].begin(),z[x[i+1]].end(),i+1)-z[x[i+1]].begin();
			z[x[i+1]][k]--;
			wt.upd(i);
			swap(x[i],x[i+1]);
		}
	}
	return 0;
}


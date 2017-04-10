// Codeforces gym 100962A - AC
// http://codeforces.com/group/nSDOId1jpB/contest/100962/problem/A
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double EPS=1e-4;

double reduce(vector<vector<double> >& x){ // returns determinant
	int n=x.size(),m=x[0].size();
	int i=0,j=0;double r=1.;
	while(i<n&&j<m){
		int l=i;
		fore(k,i+1,n)if(abs(x[k][j])>abs(x[l][j]))l=k;
		if(abs(x[l][j])<EPS){j++;r=0.;continue;}
		if(l!=i){r=-r;swap(x[i],x[l]);}
		r*=x[i][j];
		for(int k=m-1;k>=j;k--)x[i][k]/=x[i][j];
		fore(k,0,n){
			if(k==i)continue;
			for(int l=m-1;l>=j;l--)x[k][l]-=x[k][j]*x[i][l];
		}
		i++;j++;
	}
	return r;
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	vector<vector<double> > x(n,vector<double>(m));
	fore(i,0,n)fore(j,0,m)scanf("%lf",&x[i][j]);
	reduce(x);
	int r=0;
	fore(i,0,n){
		bool w=false;
		fore(j,0,m)if(abs(x[i][j])>EPS){w=true;break;}
		r+=w;
	}
	printf("%d\n",r);
	return 0;
}

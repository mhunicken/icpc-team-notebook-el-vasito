// Codeforces gym 101242I - AC
// http://codeforces.com/gym/101242/problem/I
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double EPS=1e-7;

namespace Simplex {
vector<int> X,Y;
vector<vector<double> > A;
vector<double> b,c;
double z;
int n,m;
void pivot(int x,int y){
	swap(X[y],Y[x]);
	b[x]/=A[x][y];
	fore(i,0,m)if(i!=y)A[x][i]/=A[x][y];
	A[x][y]=1/A[x][y];
	fore(i,0,n)if(i!=x&&abs(A[i][y])>EPS){
		b[i]-=A[i][y]*b[x];
		fore(j,0,m)if(j!=y)A[i][j]-=A[i][y]*A[x][j];
		A[i][y]=-A[i][y]*A[x][y];
	}
	z+=c[y]*b[x];
	fore(i,0,m)if(i!=y)c[i]-=c[y]*A[x][i];
	c[y]=-c[y]*A[x][y];
}
pair<double,vector<double> > simplex( // maximize c^T x s.t. Ax<=b, x>=0
		vector<vector<double> > _A, vector<double> _b, vector<double> _c){
	// returns pair (maximum value, solution vector)
	A=_A;b=_b;c=_c;
	n=b.size();m=c.size();z=0.;
	X=vector<int>(m);Y=vector<int>(n);
	fore(i,0,m)X[i]=i;
	fore(i,0,n)Y[i]=i+m;
	while(1){
		int x=-1,y=-1;
		double mn=-EPS;
		fore(i,0,n)if(b[i]<mn)mn=b[i],x=i;
		if(x<0)break;
		fore(i,0,m)if(A[x][i]<-EPS){y=i;break;}
		assert(y>=0); // no solution to Ax<=b
		pivot(x,y);
	}
	while(1){
		double mx=EPS;
		int x=-1,y=-1;
		fore(i,0,m)if(c[i]>mx)mx=c[i],y=i;
		if(y<0)break;
		double mn=1e200;
		fore(i,0,n)if(A[i][y]>EPS&&b[i]/A[i][y]<mn)mn=b[i]/A[i][y],x=i;
		assert(x>=0); // c^T x is unbounded
		pivot(x,y);
	}
	vector<double> r(m);
	fore(i,0,n)if(Y[i]<m)r[Y[i]]=b[i];
	return {z,r};
}
}

#define INF (1<<20)

map<pair<int,int>,int> ids;
int na;

int id(int x, int y){
	if(!ids.count({x,y}))ids[{x,y}]=na++;
	return ids[{x,y}];
}

int n,m;
int d[32][32];
int w[32][32];

void dopath(int x, int y, vector<int>& r){
	if(w[x][y]<0)return;
	dopath(x,w[x][y],r);
	r.pb(w[x][y]);
	dopath(w[x][y],y,r);
}

vector<int> path(int x, int y){
	vector<int> r;
	r.pb(x);
	if(x==y)return r;
	dopath(x,y,r);
	r.pb(y);
	return r;
}

vector<vector<double> > A;
vector<double> c;
vector<double> b;

int x[128],y[128],t[128];

int main(){
	scanf("%d",&n);
	fore(i,0,n)fore(j,0,n){
		scanf("%d",&d[i][j]);
		if(d[i][j]<0)d[i][j]=INF;
		else if(i!=j){
			id(i,j);
		}
	}
	memset(w,-1,sizeof(w));
	fore(k,0,n)fore(i,0,n)fore(j,0,n){
		if(d[i][k]+d[k][j]<d[i][j]){
			d[i][j]=d[i][k]+d[k][j];
			w[i][j]=k;
		}
	}
	scanf("%d",&m);
	fore(i,0,m)scanf("%d%d%d",x+i,y+i,t+i);
	int q;
	scanf("%d",&q);
	while(q--){
		A.clear();b.clear();c.clear();
		int s,dd;
		scanf("%d%d",&s,&dd);
		printf("%d %d",s,dd);
		if(s==dd){
		    puts(" 0.0 0.0");
		    continue;
		}
		fore(i,0,na){
			{vector<double> p(na,0.);
			p[i]=1;
			A.pb(p);
			b.pb(1./30);
			p[i]=-1;
			A.pb(p);
			b.pb(-1./60);}
		}
		fore(i,0,m){
			vector<int> p=path(x[i],y[i]);
			{vector<double> r(na,0.);
			fore(i,0,p.size()-1){
				int x=p[i],y=p[i+1];
				assert(ids.count({x,y}));
				r[id(x,y)]=d[x][y];
			}
			A.pb(r);
			b.pb(1.*t[i]/60);
			fore(i,0,na)r[i]=-r[i];
			A.pb(r);
			b.pb(-1.*t[i]/60);}
		}
		vector<int> p=path(s,dd);
		{vector<double> r(na,0.);
		fore(i,0,p.size()-1){
			int x=p[i],y=p[i+1];
			assert(ids.count({x,y}));
			r[id(x,y)]=d[x][y];
		}
		c=r;}
		double mx=Simplex::simplex(A,b,c).fst*60;
		fore(i,0,na)c[i]=-c[i];
		double mn=Simplex::simplex(A,b,c).fst*-60;
		printf(" %.9lf %.9lf\n",mn,mx);
	}
	return 0;
}

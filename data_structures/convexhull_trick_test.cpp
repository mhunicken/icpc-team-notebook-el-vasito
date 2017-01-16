// Codeforces 319C - AC
// http://codeforces.com/problemset/problem/319/C
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

typedef ll tc;
struct Line{tc m,h;};
struct CHT { // for minimum (for maximum just change the sign of lines)
	vector<Line> c;
	int pos=0;
	tc in(Line a, Line b){
		tc x=b.h-a.h,y=a.m-b.m;
		return x/y+(x%y?!((x>0)^(y>0)):0); // ==ceil(x/y)
	}
	void add(tc m, tc h){ // m's should be non increasing
		Line l=(Line){m,h};
		if(c.size()&&m==c.back().m){
			l.h=min(h,c.back().h);c.pop_back();if(pos)pos--;
		}
		while(c.size()>1&&in(c.back(),l)<=in(c[c.size()-2],c.back())){
			c.pop_back();if(pos)pos--;
		}
		c.pb(l);
	}
	inline bool fbin(tc x, int m){return in(c[m],c[m+1])>x;}
	tc eval(tc x){
		// O(log n) query:
//		int s=0,e=c.size();
//		while(e-s>1){int m=(s+e)/2;
//			if(fbin(x,m-1))e=m;
//			else s=m;
//		}
//		return c[s].m*x+c[s].h;
		// O(1) query (for ordered x's):
		while(pos>0&&fbin(x,pos-1))pos--;
		while(pos<c.size()-1&&!fbin(x,pos))pos++;
		return c[pos].m*x+c[pos].h;
	}
};

ll a[100005];
ll b[100005];
int n;
ll f;

int main(){
	scanf("%d",&n);
	fore(i,0,n){int t;scanf("%d",&t);a[i]=t;}
	fore(i,0,n){int t;scanf("%d",&t);b[i]=t;}
	CHT ch;
	ch.add(b[0],0);
	fore(i,1,n){
		f=ch.eval(a[i]);
		ch.add(b[i],f);
	}
	printf("%lld\n",f);
	return 0;
}

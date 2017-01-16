// Test vs brute force
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
		int s=0,e=c.size();
		while(e-s>1){int m=(s+e)/2;
			if(fbin(x,m-1))e=m;
			else s=m;
		}
		return c[s].m*x+c[s].h;
		// O(1) query (for ordered x's):
		while(pos>0&&fbin(x,pos-1))pos--;
		while(pos<c.size()-1&&!fbin(x,pos))pos++;
		return c[pos].m*x+c[pos].h;
	}
};

struct CHTBrute {
	vector<Line> c;
	void add(tc m, tc h) {
		Line l=(Line){m, h};
		c.pb(l);
	}
	tc eval(tc x){
		tc r=c[0].m*x+c[0].h;
		fore(i,1,c.size())r=min(r,c[i].m*x+c[i].h);
		return r;
	}
};

#define RND(a, b) (rand()%((b)-(a)+1)+(a))
#define MAXM 10000
#define MINIT RND(-1000, 1000)
#define MSTEP RND(0, 10)

#define HVAL RND(-1000, 1000)
#define XVAL RND(-1000, 1000)

int main() {
	tc m,h,x;
	int seed=time(NULL);
	srand(seed);
	while(1){ reset:
		m=MINIT;
		cout<<"CLEAR"<< endl;
		CHT ch;CHTBrute chb;
		fore(_,0,1000){
			m=m-MSTEP;
			if(m>MAXM)goto reset;
			h=HVAL;
			cout<<"ADD "<<m<<' '<<h<<endl;
			ch.add(m,h);
			chb.add(m,h);
		}
		fore(_,0,1000){
			x=XVAL;
			tc v=ch.eval(x);
			tc b=chb.eval(x);
			cout<<"QUERY "<<x<<' '<<v<<' '<<b<<endl;
			assert(v==b||!(cout<<"seed "<<seed<<endl));
		}
	}
	return 0;
}

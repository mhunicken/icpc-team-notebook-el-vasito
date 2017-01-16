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
const tc is_query=-(1LL<<62); // special value for query
struct Line {
	tc m,b;
	mutable multiset<Line>::iterator it,end;
	const Line* succ(multiset<Line>::iterator it) const {
		return (++it==end? NULL : &*it);}
	bool operator<(const Line& rhs) const {
		if(rhs.b!=is_query)return m<rhs.m;
		const Line *s=succ(it);
		if(!s)return 0;
		return b-s->b<(s->m-m)*rhs.m;
	}
};
struct HullDynamic : public multiset<Line> { // for maximum
	bool bad(iterator y){
		iterator z=next(y);
		if(y==begin()){
			if(z==end())return false;
			return y->m==z->m&&y->b<=z->b;
		}
		iterator x=prev(y);
		if(z==end())return y->m==x->m&&y->b<=x->b;
		return (x->b-y->b)*(z->m-y->m)>=(y->b-z->b)*(y->m-x->m);
	}
	iterator next(iterator y){return ++y;}
	iterator prev(iterator y){return --y;}
	void add(tc m, tc b){
		iterator y=insert((Line){m,b});
		y->it=y;y->end=end();
		if(bad(y)){erase(y);return;}
		while(next(y)!=end()&&bad(next(y)))erase(next(y));
		while(y!=begin()&&bad(prev(y)))erase(prev(y));
	}
	tc eval(tc x){
		Line l=*lower_bound((Line){x,is_query});
		return l.m*x+l.b;
	}
};

struct CHTBrute {
	vector<Line> c;
	void add(tc m, tc h) {
		Line l=(Line){m,h};
		c.pb(l);
	}
	tc eval(tc x){
		tc r=c[0].m*x+c[0].b;
		fore(i,1,c.size())r=max(r,c[i].m*x+c[i].b);
		return r;
	}
};

#define RND(a, b) (rand()%((b)-(a)+1)+(a))
#define MVAL RND(-1000, 1000)
#define HVAL RND(-1000, 1000)
#define XVAL RND(-1000, 1000)

int main() {
	tc m,h,x;
	int seed=time(NULL);
	srand(seed);
	while(1){
		cout<<"CLEAR"<< endl;
		HullDynamic ch;CHTBrute chb;
		fore(_,0,2000){
			int t=1;
			if(_)t=rand()%2;
			if(t){
				m=MVAL;h=HVAL;
				cout<<"ADD "<<m<<' '<<h<<endl;
				ch.add(m, h);
				chb.add(m, h);
			}
			else {
				x=XVAL;
				tc v=ch.eval(x);
				tc b=chb.eval(x);
				cout<<"QUERY "<<x<<' '<<v<<' '<<b<<endl;
				assert(v==b||!(cout<<"seed "<<seed<<endl));
			}
		}
	}
	return 0;
}

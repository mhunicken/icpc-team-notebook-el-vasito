// SPOJ HORRIBLE - AC
// http://www.spoj.com/problems/HORRIBLE/
// (Test usage as a segment tree with lazy)
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

typedef struct item *pitem;
struct item {
	int pr,cnt;ll val;
	ll sum; // (paramters for range query)
	ll add; // (parameters for lazy prop)
	pitem l,r;
	item(ll val): pr(rand()),cnt(1),val(val),l(0),r(0),sum(val),add(0) {}
};
void push(pitem it){
	if(it){
		it->val+=it->add;it->sum+=it->cnt*it->add;
		if(it->l)it->l->add+=it->add;
		if(it->r)it->r->add+=it->add;
		it->add=0;
	}
}
int cnt(pitem it){return it?it->cnt:0;}
ll sum(pitem it){return it?push(it),it->sum:0;}
void upd_cnt(pitem it){
	if(it){
		it->cnt=cnt(it->l)+cnt(it->r)+1;
		it->sum=it->val+sum(it->l)+sum(it->r);
	}
}
void merge(pitem& t, pitem l, pitem r){
	push(l);push(r);
	if(!l||!r)t=l?l:r;
	else if(l->pr>r->pr)merge(l->r,l->r,r),t=l;
	else merge(r->l,l,r->l),t=r;
	upd_cnt(t);
}
void split(pitem t, pitem& l, pitem& r, int sz){ // sz:desired size of l
	if(!t){l=r=0;return;}
	push(t);
	if(sz<=cnt(t->l))split(t->l,l,t->l,sz),r=t;
	else split(t->r,t->r,r,sz-1-cnt(t->l)),l=t;
	upd_cnt(t);
}
void output(pitem t){ // useful for debugging
	if(!t)return;
	push(t);
	output(t->l);printf(" %lld",t->val);output(t->r);
}
// use merge and split for range updates and queries

int main(){
	srand(time(0));
	int tn;
	scanf("%d",&tn);
	while(tn--){
		int n,q;
		scanf("%d%d",&n,&q);
		pitem t=0;
		fore(i,0,n)merge(t,t,new item(0));
		while(q--){
			int z,s,e;
			pitem t1,t2;
			scanf("%d%d%d",&z,&s,&e);s--;
			split(t,t,t2,e);
			split(t,t,t1,s);
			if(!z){
				int v;
				scanf("%d",&v);
				t1->add+=v;
			}
			else {
				printf("%lld\n",t1->sum);
			}
			merge(t,t,t1);
			merge(t,t,t2);
		}
	}
	return 0;
}

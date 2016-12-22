// SPOJ TAP2014K - AC
// http://www.spoj.com/problems/TAP2014K/
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
	int pr,cnt;
	int val;
	bool rev;int add;
	pitem l,r;
	item(int val): pr(rand()),cnt(1),val(val),l(0),r(0),rev(0),add(0) {}
};
void push(pitem it){
	if(it){
		if(it->rev){
			swap(it->l,it->r);
			if(it->l)it->l->rev^=true;
			if(it->r)it->r->rev^=true;
			it->rev=false;
		}
		it->val=(it->val+it->add)%26;
		if(it->l)it->l->add+=it->add;
		if(it->r)it->r->add+=it->add;
		it->add=0;
	}
}
int cnt(pitem it){return it?it->cnt:0;}
void upd_cnt(pitem it){
	if(it){
		it->cnt=cnt(it->l)+cnt(it->r)+1;
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
	output(t->l);putchar('a'+t->val);output(t->r);
}
// use merge and split for range updates and queries

int n,q;
char s[100005];

int main(){
	srand(time(0));
	int tn;
	scanf("%d",&tn);
	while(tn--){
		scanf("%s%d",s,&q);n=strlen(s);
		pitem t=0;
		fore(i,0,n)merge(t,t,new item(s[i]-'a'));
		while(q--){
			int s0,e0,s1,e1;
			scanf("%d%d%d%d",&s0,&e0,&s1,&e1);s0--;s1--;
			pitem t1,t2,t3,t4;
			split(t,t,t4,e1);
			split(t,t,t3,s1);
			split(t,t,t2,e0);
			split(t,t,t1,s0);
			t1->rev^=true;t1->add++;
			t3->rev^=true;t3->add++;
			merge(t,t,t3);
			merge(t,t,t2);
			merge(t,t,t1);
			merge(t,t,t4);
		}
		output(t);puts("");
	}
	return 0;
}

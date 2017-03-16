// Codeforces gym 100960H - AC
// http://codeforces.com/gym/100960/problem/H
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
	int pr;bool rev;
	pitem l,r,f,d;
	item():pr(rand()),l(0),r(0),f(0),d(0),rev(0){}
};
void push(pitem t){
	if(t&&t->rev){
		swap(t->l,t->r);
		if(t->l)t->l->rev^=1;
		if(t->r)t->r->rev^=1;
		t->rev=0;
	}
}
void merge(pitem& t, pitem l, pitem r){
	push(l);push(r);
	if(!l||!r)t=l?l:r;
	else if(l->pr>r->pr)merge(l->r,l->r,r),l->r->f=t=l;
	else merge(r->l,l,r->l),r->l->f=t=r;
}
void push_all(pitem t){
	if(t->f)push_all(t->f);
	push(t);
}
void split(pitem t, pitem& l, pitem& r){
	push_all(t);
	l=t->l;r=t->r;t->l=t->r=0;
	while(t->f){
		pitem f=t->f;t->f=0;
		if(t==f->l){
			if(r)r->f=f;
			f->l=r;r=f;
		}
		else {
			if(l)l->f=f;
			f->r=l;l=f;
		}
		t=f;
	}
	if(l)l->f=0;
	if(r)r->f=0;
}
pitem path(pitem p){return p->f?path(p->f):p;}
pitem tail(pitem p){push(p);return p->r?tail(p->r):p;}
pitem expose(pitem p){
	pitem q,r,t;
	split(p,q,r);
	if(q)tail(q)->d=p;
	merge(p,p,r);
	while(t=tail(p),t->d){
		pitem d=t->d;t->d=0;
		split(d,q,r);
		if(q)tail(q)->d=d;
		merge(p,p,d);merge(p,p,r);
	}
	return p;
}
pitem root(pitem v){return tail(expose(v));}
void evert(pitem v){expose(v)->rev^=1;v->d=0;}
void link(pitem v, pitem w){
	evert(v);
	pitem p=path(v);
	merge(p,p,expose(w));
}
void cut(pitem v){
	pitem p,q;
	expose(v);split(v,p,q);v->d=0;
}
void cut(pitem v, pitem w){evert(w);cut(v);}

pitem x[100005];
int n,m;

int main(){
	scanf("%d",&n);
	fore(i,0,n)x[i]=new item();
	char s[16];int a,b;
	while(scanf("%s",s),s[0]!='E'){
		scanf("%d%d",&a,&b);a--;b--;
		if(s[0]=='C'){
			link(x[a],x[b]);
		}
		else if(s[0]=='D'){
			cut(x[a],x[b]);
		}
		else puts(root(x[a])==root(x[b])?"YES":"NO");fflush(stdout);
	}
	return 0;
}

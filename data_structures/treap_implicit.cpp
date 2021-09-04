typedef struct item *pitem;
struct item {
	int pr,cnt,val; pitem l,r,f;
	item(int val): pr(rand()),cnt(1),val(val),l(0),r(0),f(0){}
};
void push(pitem it){
	if(!it)return;
}
int cnt(pitem t){return t?t->cnt:0;}
// int sum(pitem t){return t?push(t),t->sum:0;}
void upd_cnt(pitem t){
	if(t){
		t->cnt=cnt(t->l)+cnt(t->r)+1;
		// t->sum=t->val+sum(t->l)+sum(t->r);
	}
}
void merge(pitem& t, pitem l, pitem r){
	push(l);push(r);
	if(!l||!r)t=l?l:r;
	else if(l->pr>r->pr)merge(l->r,l->r,r),l->r->f=t=l;
	else merge(r->l,l,r->l),r->l->f=t=r;
	upd_cnt(t);
}
void split(pitem t, pitem& l, pitem& r, int sz){
	if(!t){l=r=0;return;}
	push(t);
	if(sz<=cnt(t->l)){
		split(t->l,l,t->l,sz);r=t;
		if(l)l->f=0;
		if(t->l)t->l->f=t;
	}
	else {
		split(t->r,t->r,r,sz-1-cnt(t->l));l=t;
		if(r)r->f=0;
		if(t->r)t->r->f=t;
	}
	upd_cnt(t);
}
void push_all(pitem t){
	if(t->f)push_all(t->f);
	push(t);
}
pitem root(pitem t, int& pos){ // get root and position for node t
	push_all(t); pos=cnt(t->l);
	while(t->f){
		pitem f=t->f;
		if(t==f->r)pos+=cnt(f->l)+1;
		t=f;
	}
	return t;
}

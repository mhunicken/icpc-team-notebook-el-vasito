// example that supports range reverse and addition updates, and range sum query
// (commented parts are specific to this  problem)
typedef struct item *pitem;
struct item {
	int pr,cnt,val;
//	int sum; // (paramters for range query)
//	bool rev;int add; // (parameters for lazy prop)
	pitem l,r;
	item(int val): pr(rand()),cnt(1),val(val),l(0),r(0)/*,sum(val),rev(0),add(0)*/ {}
};
void push(pitem it){
	if(it){
		/*if(it->rev){
			swap(it->l,it->r);
			if(it->l)it->l->rev^=true;
			if(it->r)it->r->rev^=true;
			it->rev=false;
		}
		it->val+=it->add;it->sum+=it->cnt*it->add;
		if(it->l)it->l->add+=it->add;
		if(it->r)it->r->add+=it->add;
		it->add=0;*/
	}
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
	output(t->l);printf(" %d",t->val);output(t->r);
}
// use merge and split for range updates and queries

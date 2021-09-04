typedef struct item *pitem;
struct item {
	int pr,key,cnt; pitem l,r;
	item(int key):key(key),pr(rand()),cnt(1),l(0),r(0) {}
};
int cnt(pitem t){return t?t->cnt:0;}
void upd_cnt(pitem t){if(t)t->cnt=cnt(t->l)+cnt(t->r)+1;}
void split(pitem t, int key, pitem& l, pitem& r){ // l: <= key, r: > key
	if(!t)l=r=0;
	else if(key<t->key)split(t->l,key,l,t->l),r=t;
	else split(t->r,key,t->r,r),l=t;
	upd_cnt(t);
}
void insert(pitem& t, pitem it){
	if(!t)t=it;
	else if(it->pr>t->pr)split(t,it->key,it->l,it->r),t=it;
	else insert(it->key<t->key?t->l:t->r,it);
	upd_cnt(t);
}
void merge(pitem& t, pitem l, pitem r){
	if(!l||!r)t=l?l:r;
	else if(l->pr>r->pr)merge(l->r,l->r,r),t=l;
	else merge(r->l,l,r->l),t=r;
	upd_cnt(t);
}
void erase(pitem& t, int key){
	if(t->key==key)merge(t,t->l,t->r);
	else erase(key<t->key?t->l:t->r,key);
	upd_cnt(t);
}

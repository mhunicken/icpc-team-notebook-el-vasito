// Returns planar graph representing Delaunay's triangulation.
// Edges for each vertex are in ccw order.
// It can work with doubles, but also integers (replace long double in line 51)
typedef struct QuadEdge* Q;
struct QuadEdge {
	int id,used;
	pt o;
	Q rot,nxt;
	QuadEdge(int id=-1, pt o=pt(INF,INF)):id(id),used(0),o(o),rot(0),nxt(0){}
	Q rev(){return rot->rot;}
	Q next(){return nxt;}
	Q prev(){return rot->next()->rot;}
	pt dest(){return rev()->o;}
};

Q edge(pt a, pt b, int ida, int idb){
	Q e1=new QuadEdge(ida,a);
  Q e2=new QuadEdge(idb,b);
  Q e3=new QuadEdge;
  Q e4=new QuadEdge;
  tie(e1->rot,e2->rot,e3->rot,e4->rot)={e3,e4,e2,e1};
  tie(e1->nxt,e2->nxt,e3->nxt,e4->nxt)={e1,e2,e4,e3};
  return e1;
}

void splice(Q a, Q b){
	swap(a->nxt->rot->nxt,b->nxt->rot->nxt);
	swap(a->nxt,b->nxt);
}

void del_edge(Q& e, Q ne){
	splice(e,e->prev()); splice(e->rev(),e->rev()->prev());
	delete e->rev()->rot; delete e->rev();
	delete e->rot; delete e;
	e=ne;
}

Q conn(Q a, Q b){
	Q e=edge(a->dest(),b->o,a->rev()->id,b->id);
	splice(e,a->rev()->prev());
	splice(e->rev(),b);
	return e;
}

auto area(pt p, pt q, pt r){return (q-p)%(r-q);}

// is p in circunference formed by (a,b,c)?
bool in_c(pt a, pt b, pt c, pt p){
	// Warning: this number is O(max_coord^4).
	// Consider using int128 or using an alternative method for this function
	long double p2=p*p,A=a*a-p2,B=b*b-p2,C=c*c-p2;
	return area(p,a,b)*C+area(p,b,c)*A+area(p,c,a)*B>EPS;
}

pair<Q,Q> build_tr(vector<pt>& p, int l, int r){
	if(r-l+1<=3){
		Q a=edge(p[l],p[l+1],l,l+1),b=edge(p[l+1],p[r],l+1,r);
		if(r-l+1==2) return {a,a->rev()};
		splice(a->rev(),b);
		auto ar=area(p[l],p[l+1],p[r]);
		Q c=abs(ar)>EPS?conn(b,a):0;
		if(ar>=-EPS) return {a,b->rev()};
		return {c->rev(),c};
	}
	int m=(l+r)/2;
	auto [la,ra]=build_tr(p,l,m);
	auto [lb,rb]=build_tr(p,m+1,r);
	while(1){
		if(ra->dest().left(lb->o,ra->o)) ra=ra->rev()->prev();
		else if(lb->dest().left(lb->o,ra->o)) lb=lb->rev()->next();
		else break;
	}
	Q b=conn(lb->rev(),ra);
	auto valid=[&](Q e){return b->o.left(e->dest(),b->dest());};
	if(ra->o==la->o) la=b->rev();
	if(lb->o==rb->o) rb=b;
	while(1){
		Q L=b->rev()->next();
		if(valid(L)) while(in_c(b->dest(),b->o,L->dest(),L->next()->dest())) del_edge(L,L->next());
		Q R=b->prev();
		if(valid(R)) while(in_c(b->dest(),b->o,R->dest(),R->prev()->dest())) del_edge(R,R->prev());
		if(!valid(L)&&!valid(R)) break;
		if(!valid(L)||(valid(R)&&in_c(L->dest(),L->o,R->o,R->dest()))) b=conn(R,b->rev());
		else b=conn(b->rev(),L->rev());
	}
	return {la,rb};
}

vector<vector<int>> delaunay(vector<pt> v){
	int n=SZ(v); auto tmp=v;
	vector<int> id(n); iota(ALL(id),0);
	sort(ALL(id),[&](int l, int r){return v[l]<v[r];});
	fore(i,0,n) v[i]=tmp[id[i]];
	assert(unique(ALL(v))==v.end());
	vector<vector<int>> g(n);
	int col=1;
	fore(i,2,n) col&=abs(area(v[i],v[i-1],v[i-2]))<=EPS;
	if(col){
		fore(i,1,n) g[id[i-1]].pb(id[i]),g[id[i]].pb(id[i-1]);
	}
	else{
		Q e=build_tr(v,0,n-1).fst;
		vector<Q> edg={e};
		for(int i=0;i<SZ(edg);e=edg[i++]){
			for(Q at=e;!at->used;at=at->next()){
				at->used=1;
				g[id[at->id]].pb(id[at->rev()->id]);
				edg.pb(at->rev());
			}
		}
	}
	return g;
}

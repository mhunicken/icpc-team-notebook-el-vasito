// given a set of points, answer queries of nearest point in O(log(n))
bool onx(pt a, pt b){return a.x<b.x;}
bool ony(pt a, pt b){return a.y<b.y;}
struct Node {
	pt pp;
	ll x0=INF, x1=-INF, y0=INF, y1=-INF;
	Node *first=0, *second=0;
	ll distance(pt p){
		ll x=min(max(x0,p.x),x1);
		ll y=min(max(y0,p.y),y1);
		return (pt(x,y)-p).norm2();
	}
	Node(vector<pt>&& vp):pp(vp[0]){
		for(pt p:vp){
			x0=min(x0,p.x); x1=max(x1,p.x);
			y0=min(y0,p.y); y1=max(y1,p.y);
		}
		if(SZ(vp)>1){
			sort(ALL(vp),x1-x0>=y1-y0?onx:ony);
			int m=SZ(vp)/2;
			first=new Node({vp.begin(),vp.begin()+m});
			second=new Node({vp.begin()+m,vp.end()});
		}
	}
};
struct KDTree {
	Node* root;
	KDTree(const vector<pt>& vp):root(new Node({ALL(vp)})) {}
	pair<ll,pt> search(pt p, Node *node){
		if(!node->first){
			//avoid query point as answer
			//if(p==node->pp) {INF,pt()};
			return {(p-node->pp).norm2(),node->pp};
		}
		Node *f=node->first, *s=node->second;
		ll bf=f->distance(p), bs=s->distance(p);
		if(bf>bs)swap(bf,bs),swap(f,s);
		auto best=search(p,f);
		if(bs<best.fst) best=min(best,search(p,s));
		return best;
	}
	pair<ll,pt> nearest(pt p){return search(p,root);}
};

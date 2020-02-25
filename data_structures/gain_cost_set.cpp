// stores pairs (benefit,cost) (erases non-optimal pairs)
struct GCS {
	set<pair<int,int> > s;
	void add(int g, int c){
		pair<int,int> x={g,c};
		auto p=s.lower_bound(x);
		if(p!=s.end()&&p->snd<=x.snd)return;
		if(p!=s.begin()){ // erase pairs with less benefit
			--p;            // and more cost
			while(p->snd>=x.snd){
				if(p==s.begin()){s.erase(p);break;}
				s.erase(p--);
			}
		}
		s.insert(x);
	}
	int get(int gain){ // min cost for some benefit
		auto p=s.lower_bound((pair<int,int>){gain,-INF});
		int r=p==s.end()?INF:p->snd;
		return r;
	}
};

// stores disjoint intervals as [first, second)
struct disjoint_intervals {
	set<pair<int,int> > s;
	void insert(pair<int,int> v){
		if(v.fst>=v.snd) return;
		auto at=s.lower_bound(v);auto it=at;
		if(at!=s.begin()&&(--at)->snd>=v.fst)v.fst=at->fst,--it;
		for(;it!=s.end()&&it->fst<=v.snd;s.erase(it++))
			v.snd=max(v.snd,it->snd);
		segs.insert(v);
	}
};

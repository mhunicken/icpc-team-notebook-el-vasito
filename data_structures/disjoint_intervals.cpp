struct DisjointSet { // [l, r)
  set<pair<int, int>> s;
  void remove(int l, int r) {
    vector<pair<int, int>> t;
    auto it = s.lower_bound({r, 0});
    if(it == s.begin()) return;
    while(it-- != s.begin()) {
      if(it->snd <= l) break;
      t.pb(*it);
    }
    for(auto x : t) {
      s.erase(x);
      if(x.fst < l) s.insert({x.fst, l});
      if(x.snd > r) s.insert({r, x.snd});
    }
  }
  void add(int l, int r) {
    vector<pair<int, int>> t;
    auto it = s.lower_bound({r, 0});
    if(it != s.begin()) while(it-- != s.begin()) {
      if(it->snd <= l) break;
      t.pb(*it);
    }
    for(auto x : t) {
      s.erase(x); l = min(l, x.fst); r = max(r, x.snd);
    }
    s.insert({l, r});
  }
};

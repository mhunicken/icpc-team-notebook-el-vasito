// sort by x
ll closest(vector<ii> &p) {
  int n = SZ(p);
  set<ii> s;
  ll best = 1e18;
  int j = 0;
  fore(i, 0, n) {
  ll d = ceil(sqrt(best));
  while(p[i].fst - p[j].fst >= best) s.erase({p[j].snd, p[j].fst}), j++;
  auto it1=s.lower_bound({p[i].snd-d,p[i].fst});
  auto it2=s.upper_bound({p[i].snd+d,p[i].fst});
  for(auto it = it1; it != it2; ++it) {
    ll dx = p[i].fst - it->snd;
    ll dy = p[i].snd - it->fst;
    best = min(best, dx * dx + dy * dy);
  }
  s.insert({p[i].snd, p[i].fst});
  }
  return best;
}
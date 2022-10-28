// sort by x
ll closest(vector<ii> &pts) {
  int n = SZ(pts);
  set<ii> s;
  ll best = 1e18;
  int j = 0;
  fore(i, 0, n) {
    ll d = ceil(sqrt(best));
    while(pts[i].fst - pts[j].fst >= best) s.erase({pts[j].snd, pts[j].fst}), j++;
    auto it1 = s.lower_bound({pts[i].snd - d, pts[i].fst});
    auto it2 = s.upper_bound({pts[i].snd + d, pts[i].fst});
    for(auto it = it1; it != it2; ++it) {
      ll dx = pts[i].fst - it->snd;
      ll dy = pts[i].snd - it->fst;
      best = min(best, dx * dx + dy * dy);
    }
    s.insert({pts[i].snd, pts[i].fst});
  }
  return best;
}
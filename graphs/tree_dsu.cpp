vi g[N]; int sz[N]; bool bigboy[N];
void add(int x, int y = -1, int k) {
  for(auto v : g[x]) if(v != y && !bigboy[v]) add(v, x, k);
  // do something
}
void dfs(int x, int y = -1, int k = 1) { // don't forget prec
  int mx = -1, h = -1;
  for(auto v : g[x]) if(v != y && mx < sz[v]) mx = sz[v], h = v;
  for(auto v : g[x]) if(v != y && v != h) dfs(v, x, 0);
  if(h != -1) bigboy[h] = 1, dfs(h, x, 1);
  add(x, y, 1); solve(x, y);
  if(h != -1) bigboy[h] = 0;
  if(!k) add(x, y, -1);
}
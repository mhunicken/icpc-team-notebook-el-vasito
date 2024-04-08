typedef int tf;
typedef int tc;
const tc INFCOST = numeric_limits<tc>::max()/2;
const int scale=2;
struct mcSFlow{
  int n, s, t; tc eps;
  vector<int> isq, cur, co; vector<tf> ex; vector<tc> h; vector<vector<int>> hs;
  struct edge{int to, rev; tf f; tc c;};
  vector<vector<edge>> g;
  mcSFlow(int n,int s,int t):eps(0),n(n),s(s),t(t),g(n){}
  void add_edge(int a, int b, tc cost, tf cap){
  if(a==b){assert(cost>=0); return;}
  cost*=n; eps = max(eps, abs(cost));
  g[a].pb({b, SZ(g[b]), cap, cost});
  g[b].pb({a, SZ(g[a])-1, 0, -cost});
  }
  void add_flow(edge& e, tf f) {
  edge &back = g[e.to][e.rev];
  if (!ex[e.to] && f) hs[h[e.to]].push_back(e.to);
  e.f -= f; ex[e.to] += f;
  back.f += f; ex[back.to] -= f;
  }
  tf max_flow() {
  ex.assign(n,0),h.assign(n,0),co.assign(2*n,0),cur.assign(n,0),hs.resize(2*n);
  h[s] = n, ex[t] = 1, co[0] = n - 1;
  for(auto &e:g[s]) add_flow(e, e.f);
  if(hs[0].size()) for (int hi=0;hi>=0;) {
    int u = hs[hi].back(); hs[hi].pop_back();
    while (ex[u] > 0) { // discharge u
    if (cur[u] == g[u].size()) {
      h[u] = 1e9;
      fore(i,0,SZ(g[u])){
      auto &e = g[u][i];
      if (e.f && h[u] > h[e.to]+1) h[u] = h[e.to]+1, cur[u] = i;
      }
      if(hi==n)break;
      if(++co[h[u]] && !--co[hi] && hi<n){
      fore(i,0,n)if(hi < h[i] && h[i] < n){
        --co[h[i]]; h[i] = n + 1;
      }
      }
      hi = h[u];
    } else if (g[u][cur[u]].f && h[u] == h[g[u][cur[u]].to]+1) {
      add_flow(g[u][cur[u]], min(ex[u], g[u][cur[u]].f));
    } else ++cur[u];
			}
    while (hi>=0 && hs[hi].empty()) --hi;
  }
  return -ex[s];
  }
  void push(edge &e, tf amt){
  if(e.f < amt) amt=e.f;
  e.f-=amt; ex[e.to]+=amt;
  g[e.to][e.rev].f+=amt;
  ex[g[e.to][e.rev].to]-=amt;
  }
  void relabel(int vertex){
  tc newHeight = -INFCOST;
		fore(i,0,SZ(g[vertex])){
    edge const&e = g[vertex][i];
    if(e.f && newHeight < h[e.to]-e.c){
    newHeight=h[e.to]-e.c; cur[vertex]=i;
    }
  }
  h[vertex] = newHeight - eps;
  }
  pair<tf, tc> minCostMaxFlow(){
  tc retCost = 0;
  fore(i,0,n)for(edge &e:g[i])retCost+=e.c*(e.f);
  tf retFlow = max_flow(); 
  h.assign(n, 0); ex.assign(n, 0); isq.assign(n, 0); cur.assign(n,0);
  queue<int> q;
  for(;eps;eps>>=scale){
    fill(cur.begin(), cur.end(), 0);
    fore(i,0,n) for(auto &e:g[i])
    if(h[i] + e.c - h[e.to] < 0 && e.f) push(e, e.f);
    fore(i,0,n) if(ex[i]>0)q.push(i),isq[i]=1;
    while(!q.empty()){
    int u=q.front();q.pop();
    isq[u]=0;
    while(ex[u]>0){
      if(cur[u] == g[u].size()) relabel(u);
      for(int &i=cur[u], max_i = g[u].size();i<max_i;++i){
      edge &e=g[u][i];
      if(h[u] + e.c - h[e.to] < 0){
        push(e, ex[u]);
        if(ex[e.to]>0 && isq[e.to]==0) q.push(e.to), isq[e.to]=1;
        if(ex[u]==0) break;
      }
      }
    }
    }
    if(eps>1 && eps>>scale==0)eps = 1<<scale;
  }
  fore(i,0,n) for(edge &e:g[i])retCost -= e.c*(e.f);
  return make_pair(retFlow, retCost/2/n);
  }
  tf getFlow(edge const &e){
  return g[e.to][e.rev].f;
  }
};

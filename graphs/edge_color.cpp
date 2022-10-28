struct EC{ // for bipartite graphs O(n + m)
  vector<ii> has[2][MAXN]; // unordered_map if MAX_DEGREE is large
  int deg[2][MAXN],col[MAXM],c[2];
  void dfs(int x, int p){
    auto i=has[p][x][c[!p]];
    if(has[!p][i.fst][c[p]].snd)dfs(i.fst,!p);
    else has[!p][i.fst][c[!p]]={0,0};
    has[p][x][c[p]]=i,has[!p][i.fst][c[p]]={x,i.snd};
    col[i.snd]=c[p];
  }
  int solve(vector<ii> &e, vector<int> &res){ // edges (x, y), result vector
    int m=SZ(e),ans=0;
    fore(i,0,m)ans=max({ans,++deg[0][e[i].fst+1],++deg[1][e[i].snd+1]});
    fore(i,0,2)fore(j,0,MAXN)has[i][j].resize(ans+1,{0,0});
    fore(i,0,m){
      int x[2]={e[i].fst+1,e[i].snd+1};
      fore(d,0,2)for(c[d]=1;has[d][x[d]][c[d]].snd;c[d]++);
      if(c[0]!=c[1])dfs(x[1],1);
      fore(d,0,2)has[d][x[d]][c[0]]={x[!d],i+1};
      col[i+1]=c[0];
    }
    res.resize(m);fore(i,0,m)res[i]=col[i+1]; // color of each edge
    return ans; // amount of colors used
  }
} ec;
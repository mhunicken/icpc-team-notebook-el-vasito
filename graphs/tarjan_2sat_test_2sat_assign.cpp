#include <bits/stdc++.h>
#ifdef DBP
#define deb(...) fprintf(stderr,__VA_ARGS__)
#else
#define deb(...) 0
#endif
#define fst first
#define snd second
#define fore(x,a,b) for(int x=(a), qwerty=(b); x<qwerty; x++)
#define pb push_back
#define mset(a,v) memset((a),(v),sizeof(a))
#define ALL(a) (a).begin(), (a).end()
#define SZ(a) int((a).size())
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;
 int f, c, w;
const int MAXN=1e6+5, F=MAXN;
// MAXN: max number of nodes or 2 * max number of variables (2SAT)
bool truth[MAXN]; // truth[cmp[i]]=value of variable i (2SAT)
int nvar;int neg(int x){return MAXN-1-x;} // (2SAT)
vector<int> g[MAXN];
int n,lw[MAXN],idx[MAXN],qidx,cmp[MAXN],qcmp;
stack<int> st;
void tjn(int u){
    lw[u]=idx[u]=++qidx;
    st.push(u);cmp[u]=-2;
    for(int v:g[u]){
        if(!idx[v]||cmp[v]==-2){
            if(!idx[v]) tjn(v);
            lw[u]=min(lw[u],lw[v]);
        }
    }
    if(lw[u]==idx[u]){
        int x,l=-1;
        do{x=st.top();st.pop();cmp[x]=qcmp;if(x<c||neg(x)<c)l=x;}while(x!=u);
        if(l!=-1)truth[qcmp]=(cmp[neg(l)]<0); // (2SAT)
        qcmp++;
    }
}
void scc(){
    memset(idx,0,sizeof(idx));qidx=0;
    memset(cmp,-1,sizeof(cmp));qcmp=0;
    fore(i,0,n)if(!idx[i])tjn(i);
}
// Only for 2SAT:
void addor(int a, int b){g[neg(a)].pb(b);g[neg(b)].pb(a);}
bool satisf(int _nvar){
    nvar=_nvar;n=MAXN;scc();
    fore(i,0,nvar)if(cmp[i]==cmp[neg(i)])return false;
    return true;
}
 
vector<int> wishes[F];
int get(int v){if(v<0)return neg(-v-1); return v-1;}
int main(){FIN;
    cin >> f >> c >> w;
    n = c;
    fore(x,0,w){
        int a,b;cin>>a>>b;a--;
        wishes[a].pb(b);
    }
    fore(x,0,f){
        int st = n;
        if(SZ(wishes[x])<=1)continue;
        for(int v:wishes[x]){
            if(st!=n)g[n].pb(n-1);
            g[n].pb(get(v));
            n++;
        }
        int cnt = SZ(wishes[x]);
        for(int v:wishes[x]){
            if(cnt>1)g[n].pb(n+1);
            g[n].pb(get(v));
            n++;cnt--;
        }
        g[neg(get(wishes[x][0]))].pb(st+SZ(wishes[x])+1);
        g[neg(get(wishes[x].back()))].pb(st+SZ(wishes[x])-2);
        fore(i,1,SZ(wishes[x])-1){
            g[neg(get(wishes[x][i]))].pb(st+i-1);
            g[neg(get(wishes[x][i]))].pb(st+i+SZ(wishes[x])+1);
        }
    }
    if(satisf(c)){
        vector<int> ans;
        fore(x,0,c)if(truth[cmp[x]])ans.pb(x+1);
        cout<<SZ(ans)<<"\n";
        fore(x,0,SZ(ans))cout<<ans[x]<<" \n"[x+1==SZ(ans)];
    }else cout<<"-1\n";
}

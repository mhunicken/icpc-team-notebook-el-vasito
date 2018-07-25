#include <bits/stdc++.h>
#define fore(x,a,b) for(int x=a, qwerty=b; x<qwerty; x++)
#define ALL(a) (a).begin(),(a).end()
#define SZ(a) ((int)(a).size())
#define pb push_back
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fst first
#define snd second
using namespace std;
typedef long long ll;

struct palindromic_tree{
    static const int SIGMA=26;
    struct Node{
        int len, link, to[SIGMA];
        ll cnt;
        Node(int len, int link=0, ll cnt=1):len(len),link(link),cnt(cnt){
            memset(to,0,sizeof(to));
        }
    };
    vector<Node> ns;
    int last;
    palindromic_tree():last(0){ns.pb(Node(-1));ns.pb(Node(0));}
    void reset(){ns.clear();last=0;ns.pb(Node(-1));ns.pb(Node(0));}
    void add(int i, string &s){
        int p=last, c=s[i]-'a';
        while(s[i-ns[p].len-1]!=s[i])p=ns[p].link;
        if(ns[p].to[c]){
            last=ns[p].to[c];
            ns[last].cnt++;
        }else{
            int q=ns[p].link;
            while(s[i-ns[q].len-1]!=s[i])q=ns[q].link;
            q=max(1,ns[q].to[c]);
            last=ns[p].to[c]=SZ(ns);
            ns.pb(Node(ns[p].len+2,q,1));
        }
    }
};

palindromic_tree pt1, pt2;
string s, t;

ll solve(int a, int b){
    ll ans = a > 1 && b > 1 ? pt1.ns[a].cnt * pt2.ns[b].cnt : 0;
    fore(c,0,pt1.SIGMA)if(pt1.ns[a].to[c] && pt2.ns[b].to[c])
        ans += solve(pt1.ns[a].to[c],pt2.ns[b].to[c]);
    return ans;
}

int main(){FIN;
    int T; cin >> T;
    fore(tc,1,T+1){
        pt1.reset();pt2.reset();
        cin >> s >> t;
        fore(i,0,SZ(s))pt1.add(i,s);
        fore(i,0,SZ(t))pt2.add(i,t);

        for(int i=SZ(pt1.ns)-1; i>=0; i--)
            pt1.ns[pt1.ns[i].link].cnt+=pt1.ns[i].cnt;
        for(int i=SZ(pt2.ns)-1; i>=0; i--)
            pt2.ns[pt2.ns[i].link].cnt+=pt2.ns[i].cnt;

        ll ans = solve(0,0) + solve(1,1);
        cout << "Case #"<<tc<<": "<< ans << "\n";
    }
}

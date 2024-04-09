int n,sq,nq; // size, sqrt(size), #queries
struct qu{int l,r,id;}; // HILT -> ll ord;
qu qs[MAXN]; ll ans[MAXN]; // ans[i] = answer to ith query
/* HILT:
const int HOLG = 18, HON = 1 << HOLG; // HON*HON is the size of the square (HON >= MAXN)
ll hilbertOrder(int x, int y){
  ll rx, ry, s, d = 0;
  for(s=HON/2; s>0; s/=2){
    rx = (x&s)>0, ry = (y&s)>0;
    d += s*s*((3*rx)^ry);
    if(!ry){
      if(rx) x = HON-1-x, y = HON-1-y;
      swap(x, y);
    }
  }
  return d;
}
bool qcomp(const qu &a, const qu &b) { return a.ord < b.ord; }
*/
bool qcomp(const qu &a, const qu &b){
  if(a.l/sq!=b.l/sq) return a.l<b.l;
  return (a.l/sq)&1?a.r<b.r:a.r>b.r;
}
void mos(){
  fore(i,0,nq)qs[i].id=i; // HILT -> qs[i].ord = hilbertOrder(qs[i].l, qs[i].r);
  sq=sqrt(n)+.5; sort(qs,qs+nq,qcomp); int l=0,r=0; init();
  fore(i,0,nq){
    qu q=qs[i];
    while(l>q.l)add(--l);
    while(r<q.r)add(r++);
    while(l<q.l)remove(l++);
    while(r>q.r)remove(--r);
    ans[q.id]=get_ans();
  }
}
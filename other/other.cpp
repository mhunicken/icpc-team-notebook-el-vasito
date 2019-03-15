mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//int v=uniform_int_distribution<int>(a, b)(rng);

//primitive root: a is pr of P if a^((P-1)/p)%P!=1 for all p|(P-1)
//a^n = a^(phi(m)+n%phi(m)) (mod m) if n > lg(m)

//knuth: dp[i][j] = min(i<k<j) {dp[i][k]+dp[k][j]} + C[i][j]
//A[i,j-1]<=A[i,j]<=A[i+1,j] (A is optimal position) reduces to O(n^2)

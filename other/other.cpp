mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int v=uniform_int_distribution<int>(a, b)(rng);

//knuth: dp[i][j] = min(i<k<j) {dp[i][k]+dp[k][j]} + C[i][j]
//A[i,j-1]<=A[i,j]<=A[i+1,j] (A is optimal position) reduces to O(n^2)

//Matrix-tree theorem. Let matrix T=[t_ij], where t_ij is the number
//of multiedges between i and j, for i!=j, and t_ii=-deg_i. Number of
//spanning trees of a graph is equal to the determinant of a matrix
//obtained by deleting any k-th row and k-th column from T.

//Prufer code of a tree: Repeatedly remove the leaf with the smallest
//label and output its only neighbor's label until one edge remains.
//The seq has length n-2. Two isomorphic trees have the same sequence
//and every sequence of integeres from 1 and n corresponds to a tree.
//Corollary:the number of labelled trees with n vertices is n^(n-2).

//B_k=A^-1%x^a; B_k+1 = B_k(2 - A*B_k)%x^(2a); B0=a0^-1
//D^R=A^R*(B^R)^-1 % (x^(n-m+1)); A=B*D+R

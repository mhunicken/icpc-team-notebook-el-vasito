// double inf
const double DINF=numeric_limits<double>::infinity();
// Iterate over non empty subsets of bitmask
for(int s=m;s;s=(s-1)&m) // Decreasing order
for (int s=0;s=s-m&m;) 	 // Increasing order

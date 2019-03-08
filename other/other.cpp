mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//int v=uniform_int_distribution<int>(a, b)(rng);

//primitive root: a is pr of P if a^((P-1)/p)%P!=1 for all p|(P-1)

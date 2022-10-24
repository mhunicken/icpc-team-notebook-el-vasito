// Esta es la parte especifica de este problema
struct Data {/** Datos que almaceno de un subarbol**/};
Data combine(const Data &a, const Data &b){
	Data ret;/// Sean a y b dos subarboles con la misma raiz, unirlos
	return ret;
}
Data extend(const Data &a, int value){
	Data ret;/// Colgar al nodo subarbol a de una nueva raiz
	return ret;
}
Data leaf(){ /// Puede ser necesario pasar mas parametros
	Data ret;/// Lo que debe devolver una hoja
	return ret;
}
struct Edge{int child, value;/**Agregar Informacion que contiene una arista**/};
// Esto seria la tecnica de cambio de raiz general, independiente del problema
const int MAXN = 1000006;
vector<Edge> g[MAXN];
Data res[MAXN]; // La respuesta tomando ese subarbol como raiz
Data subtree[MAXN]; // El clasico subarbol con raiz en el nodo
Data extendedSubtree[MAXN]; // El clasico + la arista al padre
Data parentSubtree[MAXN]; // El "complemento" en aristas del extended
Data extendedParentSubtree[MAXN]; // El "complemento" en aristas del subtree
void dfsSubtree(int node, int parent){
	subtree[node] = leaf();
	for (Edge e : g[node])
	if (e.child != parent){
		dfsSubtree(e.child, node);
		extendedSubtree[e.child] = extend(subtree[e.child], e.value);
		subtree[node] = combine(extendedSubtree[e.child], subtree[node]);
	}
}
void dfsParentSubtree(int node, int parent){
	const int D = SZ(g[node]);
	vector<Data> prefixes(D+1),suffixes(D+1);
	#define EDGE g[node][i]
	#define ELEM (EDGE.child == parent ? extendedParentSubtree[node] : extendedSubtree[EDGE.child])
	prefixes[0] = leaf();
	fore(i, 0, D) prefixes[i+1] = combine(ELEM, prefixes[i]);
	suffixes[D] = leaf();
	for(int i=D-1;i>=0;i--)suffixes[i] = combine(ELEM, suffixes[i+1]);
	// En este punto, prefixes[D] == suffixes[0] == el valor con este nodo como raiz
	res[node] = prefixes[D];// Me guardo la respuesta si ese nodo es la raiz
	fore(i, 0, D)
	if (EDGE.child != parent){
		parentSubtree[EDGE.child] = combine(prefixes[i], suffixes[i+1]);
		extendedParentSubtree[EDGE.child] = extend(parentSubtree[EDGE.child], EDGE.value);
		dfsParentSubtree(EDGE.child, node);
	}
}

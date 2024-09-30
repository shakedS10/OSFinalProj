#include "algorithms.hpp"

using namespace std;




int minKey(const vector<int>& key, const vector<bool>& inMST, int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!inMST[v] && key[v] < min) {
            min = key[v], min_index = v;
        }
    }

    return min_index;
}

// Function to implement Prim's algorithm and return the MST as a directed adjacency matrix
Tree prim(Graph& graph) {
    int V = graph.getV();  // Number of vertices

    // Array to store the constructed MST
    vector<int> parent(V);

    // Key values used to pick minimum weight edge in cut
    vector<int> key(V, INT_MAX);

    // To represent the set of vertices not yet included in MST
    vector<bool> inMST(V, false);

    // Always include the first vertex in MST.
    key[0] = 0;        // Make key 0 so that this vertex is picked first
    parent[0] = -1;    // First node is always the root of MST

    vector<vector<int>> g = graph.getAdj();
    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, inMST, V);

        // Add the picked vertex to the MST set
        inMST[u] = true;

        
        // Update the key and parent index of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++) {
            // graph[u][v] is non-zero only for adjacent vertices
            // Update key only if graph[u][v] is smaller than key[v] and v is not yet included in MST
            if (g[u][v] && !inMST[v] && g[u][v] < key[v]) {
                parent[v] = u;
                key[v] = g[u][v];
            }
        }
    }

    // Create an adjacency matrix for the directed MST
    vector<vector<int>> mst(V, vector<int>(V, 0));

    // Construct the MST graph, directed from parent to child
    for (int i = 1; i < V; i++) {
        mst[parent[i]][i] = g[parent[i]][i];  // Directed edge from parent to child
    }
    Tree tree(mst);
    return tree;
}

// Struct to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// A utility function to find the root of an element with path compression
int findRoot(vector<int>& parent, int i) {
    if (parent[i] != i)
        parent[i] = findRoot(parent, parent[i]);
    return parent[i];
}

// A utility function to union two subsets
void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
    int rootX = findRoot(parent, x);
    int rootY = findRoot(parent, y);

    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

// Function to implement Kruskal's algorithm and return the MST as a directed adjacency matrix
Tree kruskal(Graph& graph) {
    int V = graph.getV();  // Number of vertices
    vector<Edge> edges;
    vector<vector<int>> g = graph.getAdj();
    // Step 1: Convert the adjacency matrix into a list of edges
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (g[i][j] != 0 && g[i][j] != INT_MAX) {
                edges.push_back({i, j, g[i][j]});
            }
        }
    }

    // Step 2: Sort all the edges in non-decreasing order of their weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    // Step 3: Create a parent and rank array for Union-Find
    vector<int> parent(V);
    vector<int> rank(V, 0);

    // Initialize the parent of each vertex to itself
    for (int i = 0; i < V; i++)
        parent[i] = i;

    // MST to store the result as an adjacency matrix
    vector<vector<int>> mst(V, vector<int>(V, 0));

    // Step 4: Pick edges one by one and add them to the MST if they do not form a cycle
    int edgesInMST = 0;
    for (auto& edge : edges) {
        if (edgesInMST == V - 1)  // Stop when MST has V-1 edges
            break;

        int u = edge.src;
        int v = edge.dest;

        int rootU = findRoot(parent, u);
        int rootV = findRoot(parent, v);

        // If including this edge does not cause a cycle, include it in the MST
        if (rootU != rootV) {
            mst[u][v] = edge.weight;  // Directed edge from u to v
            unionSets(parent, rank, rootU, rootV);
            edgesInMST++;
        }
    }

    Tree tree(mst);
    return tree;
}


void newGraph(Graph &graph, int m, int n, int fd) {
    
    
    cout << "new graph: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << graph.getAdj()[i][j] << " ";
        }
        cout << endl;
    }
    
}

void newEdge(int a, int b, int w, Graph &graph) {
    graph.addEdge(a-1, b-1, w);
}

void removeEdge(int a, int b, Graph &graph) {
    graph.removeEdge(a-1, b-1);
}
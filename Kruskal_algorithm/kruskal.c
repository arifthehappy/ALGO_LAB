#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 1000

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent, rank;
};

// Global variables
struct Edge edges[MAX_EDGES];
int parent[MAX_EDGES];

// Function prototypes
int find(int vertex);
void unionSets(int x, int y);
int kruskal(int numVertices, int numEdges);

int compareEdges(const void *a, const void *b) {
    return ((struct Edge *)a)->weight - ((struct Edge *)b)->weight;
}

// input.txt
// number_of_vertices number_of_edges
// source_vertex destination_vertex weight
// source_vertex destination_vertex weight
// ...


int main() { 
    FILE *file;
    int numVertices, numEdges;
    
    // Open the input file
    file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the number of vertices and edges
    fscanf(file, "%d %d", &numVertices, &numEdges);

    // Read the edges from the file
    for (int i = 0; i < numEdges; i++) {
        fscanf(file, "%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    // Close the file
    fclose(file);

    // Calculate the minimum spanning tree cost
    int minSpanningTreeCost = kruskal(numVertices, numEdges);

    // Print the result
    printf("Cost of the minimum spanning tree: %d\n", minSpanningTreeCost);

    return 0;
}

int find(int vertex) {
    if (parent[vertex] == -1) {
        return vertex;
    }
    return find(parent[vertex]);
}

void unionSets(int x, int y) {
    int xRoot = find(x);
    int yRoot = find(y);

    if (xRoot != yRoot) {
        parent[xRoot] = yRoot;
    }
}

int kruskal(int numVertices, int numEdges) {
    // Initialize parent array for union-find
    for (int i = 0; i < numVertices; i++) {
        parent[i] = -1;
    }

    // Create a min heap for edges
    qsort(edges, numEdges, sizeof(struct Edge), compareEdges);


    int minSpanningTreeCost = 0;
    int numEdgesInTree = 0;

    // Process each edge in sorted order
    for (int i = 0; i < numEdges; i++) {
        struct Edge currentEdge = edges[i];

        // Check if adding the current edge forms a cycle
        if (find(currentEdge.src) != find(currentEdge.dest)) {
            // Include the edge in the minimum spanning tree
            minSpanningTreeCost += currentEdge.weight;
            unionSets(currentEdge.src, currentEdge.dest);
            numEdgesInTree++;

            // Stop when all vertices are included in the tree
            if (numEdgesInTree == numVertices - 1) {
                break;
            }
        }
    }

    return minSpanningTreeCost;
}

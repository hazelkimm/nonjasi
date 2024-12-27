#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Directions for 8 possible moves (up, down, left, right, and diagonals)
int directions[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    { 0, -1},          { 0, 1},
    { 1, -1}, { 1, 0}, { 1, 1}
};

// Function to check if the cell is valid and safe
bool is_safe(char** M, int r, int c, int rows, int cols) {
    return (r >= 0 && r < rows && c >= 0 && c < cols && M[r][c] == '1');
}

// Function to convert 2D matrix to adjacency list
int** convert_matrix_to_graph(char** M, int rows, int cols, int** sizes) {
    int total_nodes = rows * cols;

    // Allocate adjacency list
    int** adj = (int**)malloc(total_nodes * sizeof(int*));
    *sizes = (int*)calloc(total_nodes, sizeof(int)); // Array to track sizes of each adjacency list

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (M[r][c] == '1') {
                int idx = r * cols + c;
                adj[idx] = (int*)malloc((1 + 8) * sizeof(int)); // Allocate space for self and neighbors
                adj[idx][(*sizes)[idx]++] = idx; // Add self to adjacency list

                for (int d = 0; d < 8; d++) {
                    int nr = r + directions[d][0];
                    int nc = c + directions[d][1];
                    if (is_safe(M, nr, nc, rows, cols)) {
                        int n_idx = nr * cols + nc;
                        adj[idx][(*sizes)[idx]++] = n_idx; // Add neighbor
                    }
                }
            } else {
                adj[r * cols + c] = NULL; // No adjacency for water cells
            }
        }
    }

    return adj;
}

// DFS Utility Function
void dfs_util(int v, int** adj, int* sizes, bool* visited) {
    visited[v] = true;

    for (int i = 0; i < sizes[v]; i++) {
        int neighbor = adj[v][i];
        if (!visited[neighbor]) {
            dfs_util(neighbor, adj, sizes, visited);
        }
    }
}

// Function to count islands using DFS
int count_islands(char** M, int rows, int cols) {
    int* sizes; // To store sizes of adjacency lists
    int** adj = convert_matrix_to_graph(M, rows, cols, &sizes);

    int total_nodes = rows * cols;
    int num_islands = 0;

    bool* visited = (bool*)calloc(total_nodes, sizeof(bool)); // Track visited nodes

    // Traverse all nodes
    for (int i = 0; i < total_nodes; i++) {
        if (!visited[i] && sizes[i] > 0) {
            dfs_util(i, adj, sizes, visited);
            num_islands++; // Increment count for each connected component
        }
    }

    // Free memory
    for (int i = 0; i < total_nodes; i++) {
        if (adj[i]) {
            free(adj[i]);
        }
    }
    free(adj);
    free(sizes);
    free(visited);

    return num_islands;
}

// Main function for testing
int main() {
    // Example matrix as a dynamically allocated 2D array
    int rows = 5, cols = 5;

    // Allocate memory for the matrix
    char** M = (char**)malloc(rows * sizeof(char*));
    char data[5][5] = {
        {'1', '1', '0', '0', '0'},
        {'0', '1', '0', '0', '1'},
        {'1', '0', '0', '1', '1'},
        {'0', '0', '0', '0', '0'},
        {'1', '0', '1', '1', '0'}
    };

    for (int i = 0; i < rows; i++) {
        M[i] = (char*)malloc(cols * sizeof(char));
        for (int j = 0; j < cols; j++) {
            M[i][j] = data[i][j];
        }
    }

    printf("Number of Islands in M: %d\n", count_islands(M, rows, cols));
    // Expected Output: 4

    // Free matrix memory
    for (int i = 0; i < rows; i++) {
        free(M[i]);
    }
    free(M);

    return 0;
}
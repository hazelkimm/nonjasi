#include <iostream>
#include <vector>

using namespace std;

// Directions for the 8 possible moves (up, down, left, right, and diagonals)
int directions[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    { 0, -1},          { 0, 1},
    { 1, -1}, { 1, 0}, { 1, 1}
};

// Function to check if the cell is valid and safe
bool is_safe(const vector<vector<char>>& M, int r, int c) {
    int rows = M.size();
    int cols = M[0].size();
    return (r >= 0 && r < rows && c >= 0 && c < cols && M[r][c] == '1');
}

// Function to convert 2D matrix to adjacency list
vector<vector<int>> convert_matrix_to_graph(const vector<vector<char>>& M) {
    int rows = M.size();
    int cols = M[0].size();
    int total_nodes = rows * cols;

    // Create an adjacency list
    vector<vector<int>> adj(total_nodes);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (M[r][c] == '1') {
                int idx = r * cols + c;
                adj[idx].push_back(idx); // Add self-loop for convenience

                for (int d = 0; d < 8; d++) {
                    int nr = r + directions[d][0];
                    int nc = c + directions[d][1];

                    if (is_safe(M, nr, nc)) {
                        int n_idx = nr * cols + nc;
                        adj[idx].push_back(n_idx); // Add neighbor
                    }
                }
            }
        }
    }

    return adj;
}

// DFS Utility Function
void dfs_util(int v, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[v] = true;

    for (int neighbor : adj[v]) {
        if (!visited[neighbor]) {
            dfs_util(neighbor, adj, visited);
        }
    }
}

// Function to count islands using DFS
int count_islands(const vector<vector<char>>& M) {
    int rows = M.size();
    int cols = M[0].size();
    int total_nodes = rows * cols;

    // Convert the matrix to an adjacency list
    vector<vector<int>> adj = convert_matrix_to_graph(M);

    // Initialize visited array
    vector<bool> visited(total_nodes, false);

    int count = 0;

    // Traverse all nodes
    for (int i = 0; i < total_nodes; i++) {
        if (!visited[i] && !adj[i].empty()) {
            dfs_util(i, adj, visited);
            count++; // Increment count for each connected component
        }
    }

    return count;
}

// Main function
int main() {
    // Example 2D matrix as a vector of vector<char>
    vector<vector<char>> M = {
        {'1', '1', '0', '0', '0'},
        {'0', '1', '0', '0', '1'},
        {'1', '0', '0', '1', '1'},
        {'0', '0', '0', '0', '0'},
        {'1', '0', '1', '1', '0'}
    };

    cout << "Number of Islands in M: " << count_islands(M) << endl;
    // Expected Output: 4

    return 0;
}
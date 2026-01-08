#include <iostream>
using namespace std;

const int MAX = 100;
int adj[MAX][MAX];     // adjacency matrix
bool visited[MAX];     // visited array
int n;                 // number of nodes

// DFS function
void DFS(int node) {
    cout << "Visiting: " << node << endl;
    visited[node] = true;

    for (int neighbor = 0; neighbor < n; neighbor++) {
        if (adj[node][neighbor] == 1 && !visited[neighbor]) {
            DFS(neighbor);
        }
    }
}

int main() {
    cout << "Enter number of nodes: ";
    cin >> n;

    // Initialize adjacency matrix
    cout << "Enter adjacency matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    // Initialize visited array
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    int start;
    cout << "Enter starting node: ";
    cin >> start;

    cout << "\nStarting DFS...\n";
    DFS(start);

    return 0;
}

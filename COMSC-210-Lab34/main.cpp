// COMSC-210 | Lab 34 | Xiao Zhang

//  main.cpp
//  COMSC-210-Lab34
//
//  Created by Xiao Zhang on 11/22/24.
//

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Graph {
public:
    int V; // I use V for vertices
    vector<vector<pair<int, int>>> adj; // Creating adjacency list

    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        // Add an edge from u to v and from v to u (since it's undirected)
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    void displayGraph() { // Print the adjacency list to show the graph
        cout << "Graph's adjacency list:\n";
        for (int i = 0; i < V; i++) {
            cout << i << " --> ";
            for (auto edge : adj[i]) {
                cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            cout << endl;
        }
    }

    void DFS(int start) { // A basic Depth-First Search using a stack
        vector<bool> visited(V, false);  // Keep track of visited nodes
        stack<int> s;
        s.push(start);

        cout << "DFS starting from vertex " << start << ":\n";
        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) { // Check if we haven't visited this node yet
                cout << node << " ";
                visited[node] = true; // Mark it as visited
            }

            for (auto neighbor : adj[node]) { // Now we will push all unvisited neighbors to the stack
                if (!visited[neighbor.first]) {
                    s.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    void BFS(int start) {  // A basic Breadth-First Search using a queue
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS starting from vertex " << start << ":\n";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (auto neighbor : adj[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true; // Mark them as visited
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Graph g(7);

    g.addEdge(0, 1, 12);
    g.addEdge(0, 2, 8);
    g.addEdge(0, 3, 21);
    g.addEdge(2, 3, 6);
    g.addEdge(2, 6, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 5);
    g.addEdge(4, 5, 9);
    g.addEdge(5, 6, 6);

    g.displayGraph();
    g.DFS(0);
    g.BFS(0);

    return 0;
}

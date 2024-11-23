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
#include <climits>
using namespace std;

class Graph {
public:
    int V; // I use V for vertices (now it stands for stations)
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
        cout << "Transportation Network:\n";
        cout << "========================\n";
        for (int i = 0; i < V; i++) {
            cout << "Station " << i << " connects to: ";
            for (auto edge : adj[i]) {
                cout << "Station " << edge.first << " (Distance: " << edge.second << " km) ";
            }
            cout << endl;
        }
    }

    void DFS(int start) { // A basic Depth-First Search using a stack
        vector<bool> visited(V, false);  // Keep track of visited stations
        stack<int> s;
        s.push(start);

        cout << "DFS starting from Station " << start << ":\n";
        while (!s.empty()) {
            int station = s.top();
            s.pop();

            if (!visited[station]) { // Check if we haven't visited this station yet
                cout << "Station " << station << " ";
                visited[station] = true; // Mark it as visited
            }

            for (auto neighbor : adj[station]) { // Now we will push all unvisited neighbors to the stack
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

        cout << "BFS starting from Station " << start << ":\n";
        while (!q.empty()) {
            int station = q.front();
            q.pop();
            cout << "Station " << station << " ";

            for (auto neighbor : adj[station]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true; // Mark them as visited
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }
    
    void primMST() {
        vector<int> key(V, INT_MAX); // Key values to pick minimum weight edge
        vector<int> parent(V, -1); // Parent nodes in MST
        vector<bool> inMST(V, false); // To check if a station is already included in MST
        key[0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-heap
        pq.push({0, 0}); // Push starting station

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            inMST[u] = true;

            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({key[v], v});
                }
            }
        }

        cout << "\nMinimum Spanning Tree edges with Distance:\n";
        for (int i = 1; i < V; i++) {
            cout << "Station " << parent[i] << " - Station " << i << ": " << key[i] << " km\n";
        }
    }
};

int main() {
    // Creating a graph representing a transportation network (stations 0 to 8)
    Graph g(9); // I use 9 stations as an example

    // Adding routes between stations (edges with distances in km)
    g.addEdge(0, 1, 8);
    g.addEdge(0, 2, 21);
    g.addEdge(1, 2, 6);
    g.addEdge(1, 3, 5);
    g.addEdge(1, 4, 4);
    g.addEdge(2, 7, 11);
    g.addEdge(2, 8, 8);
    g.addEdge(3, 4, 9);
    g.addEdge(5, 6, 10);
    g.addEdge(5, 7, 15);
    g.addEdge(5, 8, 5);
    g.addEdge(6, 7, 3);
    g.addEdge(6, 8, 7);

    g.primMST();
    return 0;
}

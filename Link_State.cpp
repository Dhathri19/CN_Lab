/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

class Graph {
   private:
    int V;
    vector<pair<int, int>>* adjList;

   public:
    Graph(int V) {
        this->V = V;
        adjList = new vector<pair<int, int>>[V];
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back(make_pair(v, weight));
        adjList[v].push_back(make_pair(u, weight));
    }

    void dijkstra(int src, vector<int>& dist, vector<int>& prev) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<bool> visited(V, false);

        dist[src] = 0;
        pq.push(make_pair(0, src));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) {
                continue;
            }

            visited[u] = true;

            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                int newDist = dist[u] + weight;

                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                    pq.push(make_pair(newDist, v));
                }
            }
        }
    }

    void shortestPath(int src) {
        vector<int> dist(V, INT_MAX);
        vector<int> prev(V, -1);

        dijkstra(src, dist, prev);

        for (int i = 0; i < V; i++) {
            if (i != src) {
                cout << "Shortest path from router " << src + 1 << " to " << i + 1 << ": ";

                if (dist[i] == INT_MAX) {
                    cout << "No path exists" << endl;
                } else {
                    cout << i + 1 << " via ";
                    int curr = i;
                    while (prev[curr] != -1) {
                        cout << prev[curr] + 1 << " -> ";
                        curr = prev[curr];
                    }
                    cout << src + 1 << " Distance: " << dist[i] << endl;
                }
            }
        }
    }
};

int main() {
    int V;
    cout << "Enter the number of nodes or routers in the network: ";
    cin >> V;
    Graph g(V);
    cout << "Enter the adjacency matrix with weights or costs of the network:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            int weight;
            cin >> weight;
            if (weight != 0) {
                g.addEdge(i, j, weight);
            }
        }
    }

    for (int i = 0; i < V; i++) {
        g.shortestPath(i);
        cout << endl;
    }
    return 0;
}

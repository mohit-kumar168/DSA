#include <iostream>
#include <vector>
using namespace std;

struct Edge {
  int src;
  int dest;
  int weight;
};

int vertices, edges;
vector<Edge> graph;
vector<int> dist;

void bellmanFord(int source) {
  // Initialize distances
  for (int i = 0; i < vertices; i++) {
    dist[i] = 999999; // Infinity
  }
  dist[source] = 0;

  // Relax edges (V-1) times
  for (int i = 0; i < vertices - 1; i++) {
    for (int j = 0; j < edges; j++) {
      int u = graph[j].src;
      int v = graph[j].dest;
      int w = graph[j].weight;

      if (dist[u] != 999999 && dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
      }
    }
  }

  // Check for negative weight cycles
  for (int j = 0; j < edges; j++) {
    int u = graph[j].src;
    int v = graph[j].dest;
    int w = graph[j].weight;

    if (dist[u] != 999999 && dist[u] + w < dist[v]) {
      cout << "Graph contains negative weight cycle\n";
      return;
    }
  }

  // Print results
  cout << "\nVertex\tDistance from Source " << source << "\n";
  for (int i = 0; i < vertices; i++) {
    cout << i << "\t";
    if (dist[i] == 999999) {
      cout << "INF\n";
    } else {
      cout << dist[i] << "\n";
    }
  }
}

int main() {
  cout << "Enter number of vertices: ";
  cin >> vertices;

  cout << "Enter number of edges: ";
  cin >> edges;

  dist.resize(vertices);
  graph.resize(edges);

  cout << "Enter edges (source destination weight):\n";
  for (int i = 0; i < edges; i++) {
    cin >> graph[i].src >> graph[i].dest >> graph[i].weight;
  }

  int source;
  cout << "Enter source vertex: ";
  cin >> source;

  bellmanFord(source);

  return 0;
}

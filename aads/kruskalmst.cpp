#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
  int from;
  int to;
  int cost;
};

int totalVertices, totalEdges;
vector<Edge> allEdges;
vector<int> parent;

int findParent(int vertex) {
  if (parent[vertex] == vertex) {
    return vertex;
  }
  parent[vertex] = findParent(parent[vertex]);
  return parent[vertex];
}

void connectGroups(int vertex1, int vertex2) {
  int parent1 = findParent(vertex1);
  int parent2 = findParent(vertex2);

  if (parent1 != parent2) {
    parent[parent1] = parent2;
  }
}

bool isCheaper(Edge edge1, Edge edge2) { return edge1.cost < edge2.cost; }

void findMinimumSpanningTree() {
  sort(allEdges.begin(), allEdges.end(), isCheaper);

  parent.resize(totalVertices);
  for (int i = 0; i < totalVertices; i++) {
    parent[i] = i;
  }

  vector<Edge> treeEdges;
  int totalCost = 0;

  for (int i = 0; i < totalEdges; i++) {
    int from = allEdges[i].from;
    int to = allEdges[i].to;
    int cost = allEdges[i].cost;

    int parent1 = findParent(from);
    int parent2 = findParent(to);

    if (parent1 != parent2) {
      treeEdges.push_back(allEdges[i]);
      totalCost += cost;
      connectGroups(from, to);
    }

    if (treeEdges.size() == totalVertices - 1) {
      break;
    }
  }

  cout << "\nEdges in Minimum Spanning Tree:\n";
  cout << "From\tTo\tCost\n";
  for (int i = 0; i < treeEdges.size(); i++) {
    cout << treeEdges[i].from << "\t" << treeEdges[i].to << "\t"
         << treeEdges[i].cost << "\n";
  }
  cout << "\nTotal Cost: " << totalCost << "\n";
}

int main() {
  cout << "Enter number of vertices: ";
  cin >> totalVertices;

  cout << "Enter number of edges: ";
  cin >> totalEdges;

  allEdges.resize(totalEdges);

  cout << "Enter edges (from to cost):\n";
  for (int i = 0; i < totalEdges; i++) {
    cin >> allEdges[i].from >> allEdges[i].to >> allEdges[i].cost;
  }

  findMinimumSpanningTree();

  return 0;
}

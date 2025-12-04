#include <iostream>
using namespace std;

int parent[100], rnk[100], U[100], V[100], W[100];

int find(int x) {
  if (parent[x] != x)
    parent[x] = find(parent[x]);
  return parent[x];
}

void unionSet(int a, int b) {
  a = find(a);
  b = find(b);
  if (a != b) {
    if (rnk[a] < rnk[b])
      parent[a] = b;
    else if (rnk[b] < rnk[a])
      parent[b] = a;
    else {
      parent[b] = a;
      rnk[a]++;
    }
  }
}

int main() {
  int n, m;

  cout << "No. of nodes: ";
  cin >> n;

  cout << "No. of edges: ";
  cin >> m;

  cout << "Enter edges(u v w): " << endl;
  for (int i = 0; i < m; i++) {
    cout << "Edge " << i + 1 << ": ";
    cin >> U[i] >> V[i] >> W[i];
  }

  for (int i = 1; i <= n; i++) {
    parent[i] = i;
    rnk[i] = 0;
  }

  for (int i = 0; i < m; i++) {
    for (int j = i + 1; j < m; j++) {
      if (W[j] < W[i]) {
        swap(U[i], U[j]);
        swap(V[i], V[j]);
        swap(W[i], W[j]);
      }
    }
  }

  cout << endl << "Edges in MST: " << endl;
  int mstTotal = 0;

  for (int i = 0; i < m; i++) {
    int u = U[i];
    int v = V[i];
    int w = W[i];

    if (find(u) != find(v)) {
      cout << u << "--" << v << " (Weight = " << w << ")" << endl;
      mstTotal += w;
      unionSet(u, v);
    }
  }

  cout << "Total cost of mst: " << mstTotal << endl;
  return 0;
}

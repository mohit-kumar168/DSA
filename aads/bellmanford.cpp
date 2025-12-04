#include <iostream>
using namespace std;

int main() {
  int n, m, s;

  cout << "Number of nodes: ";
  cin >> n;

  cout << "Number of edges: ";
  cin >> m;

  cout << "Source node: ";
  cin >> s;

  int u[100], v[100], w[100]; // max 100 edges (simple)
  cout << "Enter edges (u v w):\n";

  for (int i = 0; i < m; i++) {
    cout << "Edge " << i + 1 << ": ";
    cin >> u[i] >> v[i] >> w[i];
  }

  int INF = 1e9;
  int d[100];
  for (int i = 0; i < n; i++)
    d[i] = INF;
  d[s] = 0;

  for (int k = 1; k < n; k++)
    for (int i = 0; i < m; i++)
      if (d[u[i]] != INF && d[u[i]] + w[i] < d[v[i]])
        d[v[i]] = d[u[i]] + w[i];

  for (int i = 0; i < m; i++)
    if (d[u[i]] != INF && d[u[i]] + w[i] < d[v[i]]) {
      cout << "\nNegative cycle detected.\n";
      return 0;
    }

  cout << "\nShortest distances:\n";
  for (int i = 0; i < n; i++)
    cout << "Node " << i << " : " << d[i] << "\n";

  return 0;
}

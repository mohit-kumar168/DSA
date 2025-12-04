#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Randomized Quick Sort And Random Select
void print_array(vector<int> &arr);
void randomized_quick_sort(vector<int> &arr, int low, int high);
int randomized_partition(vector<int> &arr, int low, int high);
int partition(vector<int> &arr, int low, int high);
int random_select(vector<int> &arr, int low, int high, int k);

// KMP
void kmp(string t, string p);
void lsp_table(vector<int> &lsp, string p);
void match_and_search(vector<int> &lsp, string t, string p);

// Brute Force Suffix Tries
struct Node {
  unordered_map<char, Node *> children;
};

class SuffixTree {
  Node *root;

public:
  SuffixTree(string text) {
    root = new Node();
    text += '$';

    for (int i = 0; i < text.size(); i++) {
      Node *node = root;
      for (int j = i; j < text.size(); j++) {
        char c = text[j];
        if (node->children.find(c) == node->children.end()) {
          node->children[c] = new Node();
        }
        node = node->children[c];
      }
    }
  }

  bool search(string pattern) {
    Node *node = root;
    for (char c : pattern) {
      if (node->children.find(c) == node->children.end()) {
        return false;
      }
      node = node->children[c];
    }
    return true;
  }
};

// Kruskal Algorithm
int parent[100], rnk[100], U[100], V[100], W[100];

int find(int x) {
  if (parent[x] != x)
    parent[x] = find(parent[x]);
  return parent[x];
}

void unionSet(int a, int b) {
  a = find(a), b = find(b);
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
  /*
  srand(time(0));
  vector<int> arr = {10, 0, 5, 2, 7};
  int n = arr.size();
  cout << "Original Array: ";
  print_array(arr);

  randomized_quick_sort(arr, 0, n - 1);
  cout << "Sorted Array: ";
  print_array(arr);

  vector<int> copyArray = arr;
  int elem = random_select(copyArray, 0, n - 1, 2);
  cout << "2nd smallest element: " << elem << endl;
*/
  /*
    string t = "ababcabcabababd";
    string p = "ababd";
    kmp(t, p);
  */

  /*
    SuffixTree tree("bananan");
    cout << tree.search("nan") << endl;
  */

  int n, m;
  cout << "Enter no of node and edges: ";
  cin >> n >> m;

  cout << "Enter edges(u v w): " << endl;
  for (int i = 0; i < m; i++) {
    cout << "Edge " << i + 1 << ": ";
    cin >> U[i] >> V[i] >> W[i];
  }

  for (int i = 1; i < m; i++) {
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

  cout << "\nEdges in MST: " << endl;
  int mstTotal = 0;

  for (int i = 0; i < m; i++) {
    int u = U[i], v = V[i], w = W[i];

    if (find(u) != find(v)) {
      cout << u << "--" << v << " (Weight = " << w << ")" << endl;
      mstTotal += w;
      unionSet(u, v);
    }
  }
  cout << "Total cost of mst: " << mstTotal << endl;

  return 0;
}

void print_array(vector<int> &arr) {
  for (int i : arr) {
    cout << i << " ";
  }
  cout << endl;
}

// Randomized Quick Sort And Random Select
void randomized_quick_sort(vector<int> &arr, int low, int high) {
  if (low < high) {
    int partitionIndex = randomized_partition(arr, low, high);
    randomized_quick_sort(arr, low, partitionIndex - 1);
    randomized_quick_sort(arr, partitionIndex + 1, high);
  }
}

int randomized_partition(vector<int> &arr, int low, int high) {
  int randomIndex = low + rand() % (high - low + 1);
  swap(arr[randomIndex], arr[high]);
  return partition(arr, low, high);
}

int partition(vector<int> &arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;
  for (int j = low; j < high; j++) {
    if (arr[j] <= pivot) {
      i++;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[high]);
  return i + 1;
}

int random_select(vector<int> &arr, int low, int high, int k) {
  if (low == high) {
    return arr[low];
  }

  int q = randomized_partition(arr, low, high);
  int leftCount = q - low + 1;

  if (q == k) {
    return arr[q];
  } else if (k < leftCount) {
    return random_select(arr, low, q - 1, k);
  } else {
    return random_select(arr, q + 1, high, k - leftCount);
  }
}

// KMP
void kmp(string t, string p) {
  vector<int> lsp(p.size(), 0);
  lsp_table(lsp, p);
  match_and_search(lsp, t, p);
}

void lsp_table(vector<int> &lsp, string p) {
  for (int i = 1; i < p.size(); i++) {
    int j = lsp[i - 1];
    while (j > 0 && p[i] != p[j]) {
      j = lsp[j - 1];
    }
    if (p[i] == p[j]) {
      j++;
    }
    lsp[i] = j;
  }
}

void match_and_search(vector<int> &lsp, string t, string p) {
  int suf = 0, pre = 0;
  while (pre < p.size() && suf < t.size()) {
    if (t[suf] == p[pre]) {
      suf++;
      pre++;
    } else {
      if (pre == 0) {
        suf++;
      } else {
        pre = lsp[pre - 1];
      }
    }
  }
  if (pre == p.size()) {
    cout << "Fount Pattern at index: " << suf - pre << endl;
  }
}

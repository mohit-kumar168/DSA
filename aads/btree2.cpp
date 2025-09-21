#include <iostream>
#include <vector>
using namespace std;

class BTree {
    struct Node {
        vector<int> keys;
        vector<Node*> children;
        bool leaf;
        
        Node(bool isLeaf) : leaf(isLeaf) {}
    };
    
    Node* root;
    int minDegree; // t
    
    // Insert into non-full node
    void insertNonFull(Node* node, int key) {
        int i = node->keys.size() - 1;
        
        if (node->leaf) {
            node->keys.push_back(0);
            while (i >= 0 && node->keys[i] > key) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
        } else {
            while (i >= 0 && node->keys[i] > key) i--;
            i++;
            if (node->children[i]->keys.size() == 2 * minDegree - 1) {
                splitChild(node, i);
                if (node->keys[i] < key) i++;
            }
            insertNonFull(node->children[i], key);
        }
    }
    
    // Split child node
    void splitChild(Node* parent, int index) {
        Node* fullChild = parent->children[index];
        Node* newChild = new Node(fullChild->leaf);
        
        // Move half keys to new child
        for (int i = 0; i < minDegree - 1; i++) {
            newChild->keys.push_back(fullChild->keys[i + minDegree]);
        }
        
        // Move half children if not leaf
        if (!fullChild->leaf) {
            for (int i = 0; i < minDegree; i++) {
                newChild->children.push_back(fullChild->children[i + minDegree]);
            }
            fullChild->children.resize(minDegree);
        }
        
        // Insert new child in parent
        parent->children.insert(parent->children.begin() + index + 1, newChild);
        parent->keys.insert(parent->keys.begin() + index, fullChild->keys[minDegree - 1]);
        
        // Resize full child
        fullChild->keys.resize(minDegree - 1);
    }
    
    // Search helper
    Node* searchHelper(Node* node, int key) {
        if (!node) return nullptr;
        
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i]) i++;
        
        if (i < node->keys.size() && key == node->keys[i]) return node;
        if (node->leaf) return nullptr;
        
        return searchHelper(node->children[i], key);
    }
    
    // Delete helper
    void deleteHelper(Node* node, int key) {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i]) i++;
        
        if (i < node->keys.size() && node->keys[i] == key) {
            if (node->leaf) {
                node->keys.erase(node->keys.begin() + i);
            } else {
                // Find predecessor and replace
                Node* pred = node->children[i];
                while (!pred->leaf) pred = pred->children.back();
                int predKey = pred->keys.back();
                node->keys[i] = predKey;
                deleteHelper(node->children[i], predKey);
            }
        } else if (!node->leaf) {
            deleteHelper(node->children[i], key);
        }
    }
    
    // Print helper
    void printHelper(Node* node) {
        if (!node) return;
        
        for (int i = 0; i < node->keys.size(); i++) {
            if (!node->leaf) printHelper(node->children[i]);
            cout << node->keys[i] << " ";
        }
        if (!node->leaf) printHelper(node->children.back());
    }

public:
    BTree(int degree) : minDegree(degree), root(nullptr) {}
    
    // Insert key
    void insert(int key) {
        if (!root) {
            root = new Node(true);
            root->keys.push_back(key);
            return;
        }
        
        if (root->keys.size() == 2 * minDegree - 1) {
            Node* newRoot = new Node(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0);
            root = newRoot;
        }
        insertNonFull(root, key);
    }
    
    // Search key
    bool search(int key) {
        return searchHelper(root, key) != nullptr;
    }
    
    // Delete key
    void remove(int key) {
        if (root) {
            deleteHelper(root, key);
            if (root->keys.empty() && !root->leaf) {
                Node* oldRoot = root;
                root = root->children[0];
                delete oldRoot;
            }
        }
    }
    
    // Print tree
    void print() {
        cout << "B-Tree: ";
        printHelper(root);
        cout << endl;
    }
};

// Example usage
int main() {
    BTree tree(3); // Minimum degree = 3
    
    cout << "=== B-Tree Demo ===" << endl;
    
    // Insert keys
    cout << "\n1. Inserting keys: 10, 20, 5, 6, 12, 30, 7, 17" << endl;
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int key : keys) {
        tree.insert(key);
        cout << "Inserted " << key << " -> ";
        tree.print();
    }
    
    // Search keys
    cout << "\n2. Searching keys:" << endl;
    for (int key : {5, 15, 20}) {
        cout << "Search " << key << ": " << (tree.search(key) ? "Found" : "Not Found") << endl;
    }
    
    // Delete keys
    cout << "\n3. Deleting keys:" << endl;
    for (int key : {6, 12, 7}) {
        cout << "Deleting " << key << " -> ";
        tree.remove(key);
        tree.print();
    }
    
    cout << "\nFinal tree: ";
    tree.print();
    
    return 0;
}

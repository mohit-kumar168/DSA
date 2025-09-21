#include <iostream>
#include <vector>
using namespace std;

class btnode{
    public:
	int t;                          // Minimum degree
	vector<int>keys;                // Array of keys
	vector<btnode* >child;         	// Array of child pointers
	int n;                        	// No of keys currently filled
	bool leaf;                      // Is this node a leaf?

	btnode(int _t, bool _leaf) : t(_t), leaf(_leaf), n(0) {
	    keys.resize(2*t - 1);
	    child.resize(2*t);
	}
	
	void traverse() {
	    int i;
	    for(i = 0; i < n; i++){
		if(!leaf) {
		    if(child[i]) child[i] -> traverse();
		}
		cout<<keys[i]<<" ";
	    }
	    if(!leaf) {
		if(child[i]) child[i] -> traverse();
	    }
	}
	void insert_not_null(int val) {
	    int i = n - 1;
	    if(leaf) {
		while(i >= 0 && keys[i] > val) {
		    keys[i + 1] = keys[i];
		    i--;
		}
		keys[i + 1] = val;
		n++;
	    } else {
		while(i >= 0 && keys[i] > val) i--;
		i++;
		if(child[i] == nullptr) {
		    child[i] = new btnode(t, true);
		}

		if(child[i] -> n == 2*t -1) {
		    split_child(i, child[i]);
		    if(keys[i] < val) i++;
		}
		child[i] -> insert_not_null(val);
	    }
	}
	void split_child(int i, btnode* y) {
	    btnode* z = new btnode(y -> t, y -> leaf);
	    z -> n = t - 1;
	    
	    for(int j = 0; j < t - 1; j++) {
		z -> keys[j] = y -> keys[j + t];
	    }
	    
	    if(!y -> leaf) {
		for(int j = 0; j < t; j++) {
		    z -> child[j] = y -> child[j + t];
		}
	    }
	    
	    y -> n = t - 1;
	    for(int j = n; j >= i + 1; j--) {
		child[j + 1] = child[j];
	    }
	    child[i + 1] = z;
	    
	    for(int j = n - 1; j >= i; j--) {
		keys[j + 1] = keys[j];
	    }
	    keys[i] = y -> keys[t - 1];
	    n++;
	}
};


class btree {
    public:
	btnode* root;
	int t;
	
	btree(int _t) : root(nullptr), t(_t) {}
	
	void traverse() {
	    if(root != nullptr) root -> traverse();
	}
	
	void insert(int val) {
	    if(root == nullptr) {
		root = new btnode(t, true);
		root -> keys[0] = val;
		root -> n = 1;
	    } else {
		if(root -> n == 2*t - 1) {
		    btnode* s = new btnode(t, false);
		    s -> child[0] = root;
		    s -> split_child(0, root);

		    int i = 0;
		    if(s -> keys[0] < val) {
			i++;
		    }
		    s -> child[i] -> insert_not_null(val);
		    root = s;
		} else {
		    root -> insert_not_null(val);
		}
	    }
	}
};

int main() {
    btree tree(3);
    vector<int>keys = {10, 20, 5, 6, 12, 30, 7, 17};
    for(int k : keys) {
	tree.insert(k);
    }

    cout<<"Traversal of the B-Tree: ";
    tree.traverse();
    cout<<endl;

    return 0;
}

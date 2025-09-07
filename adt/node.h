#include <iostream>
using namespace std;

template <typename T> class node {
public:
  T data;
  node *next;
  node(T val) : data(val), next(nullptr) {}
};

template <typename T> class dnode {
public:
  T data;
  dnode *prev;
  dnode *next;
  dnode(T val) : data(val), prev(nullptr), next(nullptr) {}
};

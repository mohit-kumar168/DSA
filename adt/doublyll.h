#include "../adt/node.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class doublyll{
    private:
	dnode<T>* head;
	dnode<T>* tail;

    public:
	doublyll(): head(nullptr), tail(nullptr) {}
	void insert_at_head(T);
	void insert_at_tail(T);
	void insert_at_position(int, T);
	T remove_from_head();
	T remove_from_tail();
	T remove_from_position(int);
	void display();
};

template <typename T>
void doublyll<T> :: insert_at_head(T val){
    dnode<T>* newnode = new dnode<T>(val);
    if(!head){
	head = newnode;
	tail = newnode;
	return;
    }
    newnode -> next = head;
    head -> prev = newnode;
    head = newnode;
}

template <typename T>
void doublyll<T> :: insert_at_tail(T val){
    dnode<T>* newnode = new dnode<T>(val);
    if(!head){
	head = newnode;
	tail = newnode;
	return;
    }

    tail -> next = newnode;
    newnode -> prev = tail;
    tail = newnode;
}

template <typename T>
void doublyll<T> :: insert_at_position(int idx, T val){
    if(idx == 1 || !head){
	return insert_at_head(val);
    }

    dnode<T>* temp = head;
    int n = 2;
    while(n != idx && temp -> next){
	temp = temp -> next;
	n++;
    }
    if(!temp -> next){
	return insert_at_tail(val);
    }

    dnode<T>* node_to_be_inserted = new dnode<T>(val);
    node_to_be_inserted -> next = temp -> next;
    node_to_be_inserted -> prev = temp;
    temp -> next -> prev = node_to_be_inserted;
    temp -> next = node_to_be_inserted;
}

template <typename T>
T doublyll<T> :: remove_from_head(){
    if(!head){
	throw runtime_error("List is empty, Nothing to delete");
    }
    dnode<T>* temp = head;
    T value = temp -> data;
    head = temp -> next;
    delete temp;
    cout<<"'"<<value<<"' is removed from the list"<<endl;
    return value;
}

template <typename T>
T doublyll<T> :: remove_from_tail(){
    if(!head){
	throw runtime_error("List is empty, Nothing to delete");
    }
    dnode<T>* temp = tail;
    T value = temp -> data;
    tail = temp -> prev;
    tail -> next = nullptr;
    delete temp;
    cout<<"'"<<value<<"' is removed from the list"<<endl;
    return value;
}

template <typename T>
T doublyll<T> :: remove_from_position(int idx){
    if(!head){
	throw runtime_error("List is empty, Nothing to delete");
    }

    if(idx == 1){
	return remove_from_head();
    }
    
    dnode<T>* temp = head;
    int n = 1;
    while(n != idx && temp){
	temp = temp -> next;
	n++;
    }
    if(!temp){
	throw runtime_error("index is out of bound unable to perform delete operation");
    }
    if(!temp -> next && temp -> prev){
	return remove_from_tail();
    }

    T value = temp -> data;
    temp -> prev -> next = temp -> next;
    temp -> next -> prev = temp -> prev;
    delete temp;
    cout<<"'"<<value<<"' is removed from the list"<<endl;
    return value;
}

template <typename T>
void doublyll<T> :: display(){
    dnode<T>* temp = head;
    while(temp){
	cout<<temp -> data<<" -> ";
	temp = temp -> next;
    }
    cout<<"NULL"<<endl;
}


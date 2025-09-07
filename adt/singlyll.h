#include <iostream>
#include "./node.h"
using namespace std;

template <typename T>
class singlyll{
	private:
		node<T>* head;
	
	public:
		singlyll(): head(nullptr) {}

		void insert_at_head(T);
		void insert_at_tail(T);
		void insert_at_position(int, T);
		T remove_from_head();
		T remove_from_tail();
		T remove_from_position(int);
		void display();
};

template <typename T>
void singlyll<T> :: insert_at_head(T val){
	node<T>* newnode = new node<T>(val);
	if(!head){
		head = newnode;
		return;
	}

	newnode -> next = head;
	head = newnode;
}

template <typename T>
void singlyll<T> :: insert_at_tail(T val){
	node<T>* newnode = new node<T>(val);
	if(!head){
		head = newnode;
		return;
	}

	node<T>* temp = head;
	while(temp -> next){
		temp = temp -> next;
	}
	temp -> next = newnode;
}

template <typename T>
void singlyll<T> :: insert_at_position(int idx, T val){
	int n = 2;
	if(!head || idx == 1){
		insert_at_head(val);
		return;
	}
	
	node<T>* temp = head;
	while(n != idx && temp -> next != nullptr){
		temp = temp -> next;
		n++;
	}
	if(temp -> next == nullptr){
		insert_at_tail(val);
		return;
	}

	node<T>* newnode = new node<T>(val);
	newnode -> next = temp -> next;
	temp -> next = newnode;
}

template <typename T>
T singlyll<T> :: remove_from_head(){
	if(!head){
		throw runtime_error("List is empty, cannot delete");
	}
	node<T>* temp = head;
	T value = temp -> data;
	head = head -> next;
	temp -> next = nullptr;
	delete temp;
	cout<<"'"<<value<<"' is removed from the list."<<endl;
	return value;
}

template <typename T>
T singlyll<T> :: remove_from_tail(){
	if(!head){
		throw runtime_error("List is empty, cannot delete");
	}
	if(!head -> next){
		T value = head -> data;
		delete head;
		head = nullptr;
		cout<<"'"<<value<<"' is removed from the list."<<endl;
		return value;
	}

	node<T>* temp = head;
	while(temp -> next -> next){
		temp = temp -> next;
	}
	node<T>* node_to_be_deleted = temp -> next;
	T value = node_to_be_deleted -> data;
	temp -> next = nullptr;
	delete node_to_be_deleted;
	cout<<"'"<<value<<"' is removed from the list."<<endl;
	return value;
}

template <typename T>
T singlyll<T> :: remove_from_position(int idx){
	if(!head){
		throw runtime_error("List is empty, cannot delete");
	}
	if(idx == 1){
		return remove_from_head();
	}

	int n = 2;
	node<T>* temp = head;
	while(n != idx && temp -> next -> next){
		temp = temp -> next;
		n++;
	}

	if(!temp -> next){
		return remove_from_tail();
	}

	node<T>* node_to_be_deleted = temp -> next;
	T value = node_to_be_deleted -> data;
	temp -> next = node_to_be_deleted -> next;
	delete node_to_be_deleted;
	cout<<"'"<<value<<"' is removed from the list."<<endl;
	return value;
}
		

template <typename T>
void singlyll<T> :: display(){
	node<T>* temp = head;
	while(temp){
		cout<<temp -> data<<" -> ";
		temp = temp -> next;
	}
	cout<<"null"<<endl;
}

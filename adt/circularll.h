#include <iostream>
#include "../adt/node.h"
using namespace std;

template <typename T>
class circularll {
    private:
	node<T>* cursor;
    public:
	circularll() : cursor(nullptr) {}
	void insert(T);
	void display();
};

template <typename T>
void circularll<T> :: insert(T val){
    node<T>* temp = new node(val);
    if(!cursor){
	cursor = temp;
	cursor -> next = cursor;
	return;
    }
    temp -> next = cursor -> next;
    cursor -> next = temp;
}

template <typename T>
void circularll<T> :: display(){
    if(!cursor){
	cout<<"List is empty, Nothing to display"<<endl;
	return;
    }
    node<T>* temp = cursor;
    do{
	cout<<temp -> data<<" -> ";
	temp = temp -> next;
    }while(temp != cursor);
    cout<<temp -> data<<endl;
}

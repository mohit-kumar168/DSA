#include <iostream>
#include <string>
#include "../adt/doublyll.h"
using namespace std;

int main(){
    doublyll<int> dll;
    dll.insert_at_head(1);
    dll.insert_at_head(2);
    dll.insert_at_head(3);
    dll.insert_at_tail(4);
    dll.insert_at_tail(5);
    dll.insert_at_tail(6);
    dll.insert_at_position(1, 0);
    dll.insert_at_position(4, 10);
    dll.insert_at_position(9, 15);
    dll.display();
    //dll.remove_from_head();
    //dll.remove_from_tail();
    dll.remove_from_position(1);
    dll.remove_from_position(8);
    dll.remove_from_position(4);
    dll.display();

    doublyll<string> sdll;
    sdll.insert_at_head("Hello");
    sdll.remove_from_head();
    sdll.insert_at_head("World");
    sdll.insert_at_tail("My Name is");
    sdll.insert_at_tail("Mohit");
    sdll.display();
    sdll.remove_from_tail();
    sdll.display();
    return 0;
}

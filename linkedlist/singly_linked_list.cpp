#include "../adt/singlyll.h"
#include <iostream>
#include <string>

int main() {
  singlyll<int> ll;
  cout << "Expected result: 0 -> 30 -> 100 -> 20 -> 10 -> 40 -> 50 -> 60 -> 70 "
          "-> NULL"
       << endl;
  ll.insert_at_head(10);
  ll.insert_at_head(20);
  ll.insert_at_head(30);
  ll.insert_at_tail(40);
  ll.insert_at_tail(50);
  ll.insert_at_tail(60);
  ll.insert_at_position(1, 0);
  ll.insert_at_position(8, 70);
  ll.insert_at_position(3, 100);
  ll.display();

  // ll.remove_from_head();
  // ll.remove_from_tail();
  ll.remove_from_position(1);
  ll.remove_from_position(8);
  ll.remove_from_position(4);
  cout << "Expected result: 30 -> 100 -> 20 -> 40 -> 50 -> 60 -> NULL" << endl;
  ll.display();

  singlyll<string> sll;
  cout << "Expected result: Someone -> World -> Happy -> Hello -> How -> Are "
          "-> Home -> NULL"
       << endl;
  sll.insert_at_head("Hello");
  sll.insert_at_head("World");
  sll.insert_at_tail("How");
  sll.insert_at_tail("Are");
  sll.insert_at_position(1, "Someone");
  sll.insert_at_position(6, "Home");
  sll.insert_at_position(3, "Happy");
  sll.display();

  // sll.remove_from_head();
  // sll.remove_from_tail();
  sll.remove_from_position(1);
  sll.remove_from_position(6);
  sll.remove_from_position(4);
  cout << "Expected result: World -> Happy -> Hello -> Are -> NULL" << endl;
  sll.display();

  return 0;
}

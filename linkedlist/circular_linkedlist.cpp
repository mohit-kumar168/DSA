#include <iostream>
#include "../adt/circularll.h"
using namespace std;

int main() {
    circularll<int> cll;
    cll.insert(1);
    cll.insert(2);
    cll.insert(3);
    cll.insert(4);
    cll.display();
    return 0;
}

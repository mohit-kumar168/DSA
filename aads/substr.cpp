#include <iostream>
using namespace std;

int checkTarget(string str, string tar) {
    int i = 0;  // starting index of current match attempt
    int k = 0;  // pointer for target

    for (int j = 0; j < str.length(); j++) {
        if (str[j] == tar[k]) {
            if (k == 0) {
                i = j;
            }
            if (k == tar.length() - 1) {
                return i;
            }
            k++;
        } else {
            if (k > 0) {
                j = i;
            }
            k = 0;
        }
    }

    return -1;
}

int main() {
    string str = "AABDBCD";
    string target = "ABD";

    cout << "Present at index: " << checkTarget(str, target) << endl;

    return 0;
}

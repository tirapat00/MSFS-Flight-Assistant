#include <iostream>
#include <string>

using namespace std;

// converts character array
// to string and returns it
string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        if (a[i] != '.') {
            s = s + a[i];
        }
        else if (a[i] == '.') {
            return s;
        }
    }
}
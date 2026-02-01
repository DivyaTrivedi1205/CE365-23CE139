#include <iostream>
using namespace std;

int main() {
    string s;
    cout << "Enter a string: ";
    cin >> s;

    int i = 0;
    while (i < s.size() && s[i] == 'a') i++;

    if (i + 1 < s.size() && s[i] == 'b' && s[i + 1] == 'b' && i + 2 == s.size())
        cout << "Valid String";
    else
        cout << "Invalid String";

    return 0;
}

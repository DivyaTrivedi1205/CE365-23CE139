#include <iostream>
using namespace std;

int main() {
    int ns, st, accCount;
    char sym[40];
    int trans[50][10];

    cout << "Enter number of input symbols: ";
    cin >> ns;

    cout << "Enter symbols: ";
    for (int i = 0; i < ns; i++) cin >> sym[i];

    cout << "Enter number of states: ";
    cin >> st;

    cout << "Enter initial state: ";
    int start;
    cin >> start;

    cout << "Enter number of accepting states: ";
    cin >> accCount;

    int acc[10];
    cout << "Enter accepting states: ";
    for (int i = 0; i < accCount; i++) cin >> acc[i];

    cout << "Enter transitions:\n";
    for (int i = 1; i <= st; i++) {
        for (int j = 0; j < ns; j++) {
            cout << i << " to " << sym[j] << " -> ";
            cin >> trans[i][j];
        }
    }

    int choice;
    while (true) {
        cout << "\n1. Check string\n2. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 2) break;

        string s;
        cout << "Enter string: ";
        cin >> s;

        int cur = start;
        bool invalid = false;

        for (char c : s) {
            int idx = -1;
            for (int i = 0; i < ns; i++)
                if (sym[i] == c) idx = i;

            if (idx == -1) {
                invalid = true;
                break;
            }
            cur = trans[cur][idx];
        }

        bool ok = false;
        for (int i = 0; i < accCount; i++)
            if (cur == acc[i]) ok = true;

        if (!invalid && ok)
            cout << "Valid string\n";
        else
            cout << "Invalid string\n";
    }

    cout << "Program terminated";
    return 0;
}

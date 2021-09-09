#include <bits/stdc++.h>
#include <unistd.h>
#include "connections.h"
using namespace std;

int main()
{
    Connection C;
    int n;
    while (true)
    {
        cout << yellow_bold;
        cout << "\n---------------------------------------------------------------------------------\n\n";
        cout << setw(45) << "CONNECTIONS";
        cout << "\n\n---------------------------------------------------------------------------------\n\n";
        cout << "\033[0;36m";
        cout << "1. User Mode \n2. Admin Mode \n3. Exit \nEnter mode: ";
        cout << "\033[0;33m";
        cin >> n;
        cout << "\033[0;36m";
        switch (n)
        {
        case 1:
            C.user();
            break;
        case 2:
            C.admin();
            break;
        case 3:
            cout << "\033[0;33m";
            cout << "\n\nExiting.";
            cout.flush();
            sleep(1);
            cout << ".";
            cout.flush();
            sleep(1);
            cout << ".";
            cout.flush();
            sleep(1);
            cout << ".";
            cout.flush();
            sleep(1);
            cout << ".\n";
            exit(0);
        default:
            cout << red_bold;
            cout << "\nInvalid option! Try again!";
        }
    }
    return 0;
}
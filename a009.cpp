#include <iostream>
using namespace std;

int main()
{
    string encrypted;
    getline(cin, encrypted);
    for (int i = 0; i < encrypted.size(); i++)
    {
        cout << char(encrypted[i] - 7);
    }
}

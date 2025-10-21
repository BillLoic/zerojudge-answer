#include <iostream>
#include <cmath>
using namespace std;

int isprime(int number)
{
    if (number==1) return 0;
    if (number==2) return 1;
    for (int x=2; x<sqrt((double)number); x++)
    {
        //cout << "Trying " << x << endl;
        if (!isprime(x)) continue;
        else if (number%x==0) return 0;
        else continue;
    }
    return 1;
}

int main()
{
    int number, number_temp, power=0;
    cin >> number;
    number_temp = number;
    for (int i = 2; i<=number; i++)
    {
        if (!isprime(i)) continue;  // Save some time.
        power = 0;
        while (number%i==0)
        {
            number/=i;
            power++;
        }
        if (power==0) continue;
        else if (power==1) cout << i;
        else cout << i << "^" << power;

        if (number != 1)
            cout << " * ";
    }
    return 0;
}

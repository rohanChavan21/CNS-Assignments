#include <bits/stdc++.h>
using namespace std;

int findGCD(int num1, int num2)
{
    if (num2 == 0)

    return num1;
    cout<<num1/num2<<"\t"<<num1<<"\t"<<num2<<"\t"<<num1%num2<<endl;
    return findGCD(num2, num1%num2);
}
int main()
{
    int num1, num2;
    cin >> num1 >> num2;
    int gcd = findGCD(num1, num2);
    cout << "GCD is " << gcd << endl;
    return 0;
}
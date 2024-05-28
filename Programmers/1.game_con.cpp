#include <iostream>
#include <algorithm>
using namespace std;

int N, A, B;

int main() 
{
    cin >> N >> A >> B;
    int i = 1, r = 0;
    while (true)
    {
        if (i == N)
            break;
        else 
        {
            i *= 2;
            r += 1;
        }
    }
    for (int i = 1; i <= r; i++)
    {
        if (A % 2 == 0)
        {
            if (A-1 == B)
            {
                cout << i;
                break;
            }
        }
        else 
        {
            if (A+1 == B)
            {
                cout << i;
                break;
            }    
        }
        A = (A+1) / 2;
        B = (B+1) / 2;
    }
}
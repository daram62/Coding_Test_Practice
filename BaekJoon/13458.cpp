// 13458 시험 감독

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

long long A, B, C, cnt;
long long Arr[1000001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	
    cin >> A;
    
    for (int i = 0; i < A; i++)
    {
        cin >> Arr[i];
    }

    cin >> B >> C;

    for (int i = 0; i < A; i++)
    {
        Arr[i] -= B;
        cnt ++;

        // 총 감독 감시 가능 인원 먼저 빼기
        if (Arr[i] > 0)
        {  
            cnt += ceil(static_cast<double>(Arr[i]) / C);
        }
    }
    cout << cnt << endl;

    return 0;
}

/*
3 시험장
3 4 5명씩 있음

총감 2, 부감 2 가능
2명, 2명, 3먕

먼저 총감 인원 빼고, 남은인원에 부감 감독 가능 인원 나눠서 카운트에 더하기

*/
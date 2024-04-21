// 14501 퇴사 

/* 
DP
구글링했으니까 다시 한번 정리하기
*/
#include <iostream>
#include <algorithm>
using namespace std;

int N;
int T[16], P[16];

int Time[16];

void Dp();

int main() {
    ios::sync_with_stdio(false);   
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        cin >> T[i] >> P[i];
    }

    Dp();

    cout << Time[1] << endl;
    
    return 0;

}

void Dp(){
    int last;
    for (int i = N; i > 0; i--) // 뒤에서부터 갈거니까!
    {
        last = T[i] + i;
        if (last > N + 1)
        {
            Time[i] = Time[i+1];
        }
        else {
            Time[i] = max(Time[i+1], Time[last] + P[i]);
        }
    }
}

/*
에반데... 이게 실버라고..?

ㅠㅠ 질문 게시판 봄 ㅠㅠㅠㅠㅠㅠ 너무 어려워요

뒤에서부터 가라고? 다시 생각해보자
? 난 모르곘음 진짜로,, 

7일, 6일 진행 불가
5일 - 15 더하기
4일 - 20 더하기
3일 - 10 더하기
2일 - 
*/
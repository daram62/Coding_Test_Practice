// 20055 컨베이어 벨트 위의 로봇

/*
아 왜 틀렸는지 알았다..
넌 배열에서 시작했으니까 편하게 하려고 범위를 1부터 시작했는데
지금 쓰는건 deque 덱이잖아... 그래서 범위가 안맞았던거임...
ㅠㅠㅠ그래서 막 구글링을 하면 안되는구나
*/

#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

int N, K, x;
int stg = 0;

deque<int> A; 
deque<bool> robot;

bool count()
{
    int cnt = 0;
    bool end = false;
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] == 0) {
            cnt ++;
        }
    }
    if (cnt >= K) {
        end = true;
    }
    return end;
}

void stage()
{
    while(1) {
        if(count()) 
            break;
        stg ++;
        // 1번째. 벨트 회전시키기
        A.push_front(A.back());
        A.pop_back();

        // 로봇도 회전시키기
        robot.push_front(robot.back());
        robot.pop_back();

        // 로봇이 내리는 위치에 존재한다면 제거하기
        robot[N-1] = false;
        
        // 2번째. 가장 먼저 벨트에 올라간 로봇부터 회전하는 방향으로 한 칸 이동
        // 로봇은 어짜피 N에 도달하면 내리니까 윗 벨트만 확인하면 됨
        for (int i = N - 2; i >= 0; i--)
        {
            // i에 로봇 존재, i+1에 로봇이 없고, 내구도 1 이상일때 로봇 이동
            if (robot[i] && !robot[i+1] && A[i+1] >= 1) {
                robot[i] = false;
                robot[i+1] = true;
                A[i+1] --;   
            }
        }
        
        robot[N-1] = false;

        // 3번째. 로봇 올리기
        // 올리는 위치에 내구도가 1 이상이고, 로봇이 없으면 올리기
        if (A[0] >= 1 && !robot[0]) {
            robot[0] = true;
            A[0]--;
        }

    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	
    cin >> N >> K;

    for (int i = 0; i < 2 * N; i++)
    {
        cin >> x;
        A.push_back(x);
        robot.push_back(false);
    }

    stage();

    cout << stg << endl;
	return 0;
}
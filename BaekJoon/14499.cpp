#include <iostream>
#include <algorithm>
using namespace std;

int N, M; // 지도 세로, 가로
int x, y, K; // 주사위 좌표, 명령 K
int map[21][21]; // 지도 2차원 배열
int cmd[1001]; // 명령 저장하는 배열

int dice[8];

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 지도 크기, 주사위 좌표, 명령 개수 입력
    cin >> N >> M >> x >> y >> K;

    // 지도에 좌표 별로 숫자 입력
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> map[i][j];
        }
    }

    // 명령 입력
    for (int i = 1; i <= K; i++)
    {
        cin >> cmd[i];
    }

    // 메인 구현 시작
    for (int i = 1; i <= K; i++)
    {   
        if (cmd[i] == 1) // east
        {   
            // 지도 바깥으로 이동하는지 체크
            if (y+1 >= M)
                continue;
            y++;

            int temp = dice[3];
            dice[3] = dice[1];
            dice[1] = dice[4];
            dice[4] = dice[6];
            dice[6] = temp; 
        }
        else if (cmd[i] == 2) // west
        {
            if (y-1 < 0)
                continue;
            y--;

            int temp = dice[4];
            dice[4] = dice[1];
            dice[1] = dice[3];
            dice[3] = dice[6];
            dice[6] = temp;
        }
        else if (cmd[i] == 3) // north
        {
            if (x-1 < 0)
                continue;
            x--;

            int temp = dice[2];
            dice[2] = dice[1];
            dice[1] = dice[5];
            dice[5] = dice[6];
            dice[6] = temp; 
        }
        else // (cmd[i] == 4) // south
        {
            if (x+1 >= N)
                continue;
            x++;

            int temp = dice[6];
            dice[6] = dice[5];
            dice[5] = dice[1];
            dice[1] = dice[2];
            dice[2] = temp; 
        }

        if (map[x][y] == 0)
            map[x][y] = dice[6];
        else {
            dice[6] = map[x][y];
            map[x][y] = 0;
        }
        cout << dice[1] << endl;
    }
}

/*
    주사위 배열 선언
    지도 2차원 배열 선언하고 숫자 입력 (메모리 초과는 안날까?)
    동 - 1, 서 - 2, 북 - 3, 남 - 4

      2
    4 1 3
      5
      6
    이대로 주사위 배열 생각해두기 

    윗면이 1, 동쪽이 3이래
    그럼 시작 아랫면은 무조건 6이네

    이때, 움직이면
    동 - 3이 아래
    서 - 4가 아래
    남 - 5가 아래
    북 - 2가 아래

    배열 인덱스는 고정해두고 수를 바꿔야하는구나
    항상 주사위[1]을 출력해야하는 거임;

      2
    4 1 3
      5
      6
    이대로 주사위 배열 생각해두기 

    남이면 
      6
    4 2 3
      1
      5
    이런 느낌으로,
    1에 있는 수를 5로,
    5에 있는 수를 6으로,
    6에 있는 수를 2로,
    2에 있는 수를 1로
     
    이걸 어떻게 코딩할까
    주사위 배열을 두개 만들어야 하나? 
    dice1 배열로 시작해서
    dice2 배열에 저장
    명령 홀짝 횟수에 따라, dice1 <-> dice2 바꿔서 진행

    dice2[5] = dice1[1]
    dice2[6] = dice1[5]
    dice2[2] = dice1[6]
    dice2[1] = dice1[2]
    dice2[4] = dice1[4]
    dice2[3] = dice1[3]

    이렇게! 
    해볼까용

    [0,0]
    위치에서 움직였을 때에 지도 좌표 벗어나면 그냥 그 명령 무시  

    북이면
      1
    4 5 3
      6
      2

    이런 느낌으로 배열 안의 수를 바꾸기 
    동서가 조금,, 빡센디?

    동이면 
      2
    6 4 1
      5
      3
    
    서면
      2
    1 3 6
      5
      4
    
    이렇게 배열 안의 값을 이동시키기..?

    함 해보까용
*/
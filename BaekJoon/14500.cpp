// 14500 테트로미노

#include <iostream>
#include <algorithm>
using namespace std;

int N, M ; // 종이 세로, 가로 크기
int graph[502][502]; // 종이 이중 배열
bool visited[502][502]; // 종이에서 방문 체크

int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} }; // 방향 저장 E, W, N, S
int result;

// 좌표가 종이 안에 있는지 체크
bool inside(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M)
        return false;
    return true;
}

// 어려워
void dfs(int x, int y, int depth, int sum) {
    // depth가 3일 때, 탐색이 모두 끝났음
    if (depth == 3) {
        result = max(result, sum);
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        int nX = x + dir[i][0];
        int nY = y + dir[i][1];

        // 종이 바깥으로 벗어난다면 탐색 빠져나오기
        // 이미 방문한 곳이어도 빠져나오기
        if(!inside(nX, nY) || visited[nX][nY])
            continue;

        visited[nX][nY] = true;
        dfs(nX, nY, depth + 1, sum + graph[nX][nY]);
        // 나중에 다시 탐색해야하니까
        visited[nX][nY] = false;
    }
}

// ㅗ 얘는 dfs 계산이 불가능해용
// ㅗ 이 블럭만 따로 계산해주는 과정
void block1(int x, int y) { // ㅗ
    int sum = graph[x][y] + graph[x][y+1] + graph[x][y+2] + graph[x-1][y+1];
    result = max(result, sum);
}

void block2(int x, int y) { // ㅜ
    int sum = graph[x][y] + graph[x][y+1] + graph[x][y+2] + graph[x+1][y+1];
    result = max(result, sum);
}

void block3(int x, int y) { // ㅏ
    int sum = graph[x][y] + graph[x+1][y] + graph[x+2][y] + graph[x+1][y+1];
    result = max(result, sum);
}

void block4(int x, int y) { // ㅓ
    int sum = graph[x][y] + graph[x-1][y+1] + graph[x][y+1] + graph[x+1][y+1];
    result = max(result, sum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 종이 크기 입력
    cin >> N >> M;
    // 종이 안에 적힌 수 입력
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> graph[i][j];
        }
    }

    // 매인 기능 ㄱㄱ
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            // 방문 체크
            visited[i][j] = true;
            dfs(i, j, 0, graph[i][j]);
            visited[i][j] = false;
            
            // ㅗ 블럭 계산 과정
            if (i-1 >= 0 && j+2 < M)
                block1(i, j);
            if (i+1 < N && j+2 < M)
                block2(i, j);
            if (i+2 < N && j+1 < M)
                block3(i, j);
            if (i-1 >= 0 && i+1 < N && j+1 < M)
                block4(i, j);   
        }
    }

    cout << result;
    return 0;
}
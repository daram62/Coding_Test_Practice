#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

int L, N, Q; // 체스판 크기, 기사의 수, 왕의 명령 개수
int chess[42][42]; // 체스판 (빈칸, 함정, 벽)
int cmd[101][101]; // 왕 명령

map<int, int> knight[32]; // 기사 위치
map<int, int> k_shield[32]; // 기사 방패 크기
int k_hp[32]; // 기사 체력
int k_board[42][42]; // 체스판에서 기사 위치
int k_score[32]; // 기사 점수 
bool isKnight[32]; // 기사 생존 여부

// 이동 방향 저장
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void Print(int T);
void Push(int T, int idx, int dir);
bool CanMove(int idx, int dir);
void damage(int idx);
void reset(int idx);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 체스판 크기, 기사 수, 명령 개수 입력
    cin >> L >> N >> Q;

    // 체스판 밖 벽으로 체크해두기
    for (int i = 0; i <= L+1; i++) {
        for (int j = 0; j <= L+1; j++) {
            chess[i][j] = 2;
        }
    }
    // 체스판 정보 입력
    for (int i = 1; i <= L; i++) {
        for (int j = 1; j <= L; j++) {
            cin >> chess[i][j]; // 0 - 빈칸, 1 - 함정, 2 - 벽
        }
    }
    // 기사 정보 입력
    for (int i = 1; i <= N; i++) {
        int r, c, h, w, k;
        cin >> r >> c >> h >> w >> k;
        
        knight[i][0] = r; // 기사 위치 입력
        knight[i][1] = c;
        k_shield[i][0] = h; // 기사 방패 입력
        k_shield[i][1] = w;
        k_hp[i] = k; // 기사 체력 입력
        isKnight[i] = true; // 기사 생존 여부 체크

        for (int j = r; j < r+h; j++) { // 기사 면적대로 체스판에 체크
            for (int k = c; k < c+w; k++) {
                k_board[j][k] = i;
            }
        }
    }

    for (int i = 1; i <= Q; i++)
    {
        cin >> cmd[i][0] >> cmd[i][1];
    }

    // 명령 이행 시작
    for (int T = 1; T <= Q; T++)
    {   
        // 이동할 기사 번호, 방향 저장
        int k_idx = cmd[T][0], dir = cmd[T][1];
        // 이동할 기사가 탈락했다면 그냥 무시하고 다음 명령 진행
        if (!isKnight[k_idx]) 
            continue;
        if(CanMove(k_idx, dir)) {
            Push(T, k_idx, dir);
        }
        //Print(T);
    }
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        if (isKnight[i])
        {
            sum += k_score[i];
        }
    }
    cout << sum << endl;
}

void Print(int T) {
    cout << T << "턴 후 기사들 위치" << endl;
    for (int i = 1; i <= L; i++) {
        for (int j = 1; j <= L; j++) {
            cout << k_board[i][j] << " ";
        }
        cout << endl;
    }
}

bool CanMove(int idx, int dir) {
    int nx, ny;
    nx = knight[idx][0] + dx[dir];
    ny = knight[idx][1] + dy[dir];

    for (int i = nx; i < nx+k_shield[idx][0]; i++) {
        for (int j = ny; j < ny+k_shield[idx][1]; j++) {
            // 움직이려는 칸에 벽이 존재한다면,
            if (chess[i][j] == 2) {
                return false;
            }
        }
    }
    for (int i = nx; i < nx+k_shield[idx][0]; i++) {
        for (int j = ny; j < ny+k_shield[idx][1]; j++) {
            if (k_board[i][j] != 0 && k_board[i][j] != idx) {
                // 움직이려는 칸에 다른 기사가 있다면, 
                if(!CanMove(k_board[i][j], dir)) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Push(int T, int idx, int dir) {    
    reset(idx);
    knight[idx][0] += dx[dir];
    knight[idx][1] += dy[dir];

    int nx, ny, h, w;
    nx = knight[idx][0];
    ny = knight[idx][1];
    h = k_shield[idx][0];
    w = k_shield[idx][1];
    
    for (int i = nx; i < nx+h; i++) {
        for (int j = ny; j < ny+w; j++) {
            if (k_board[i][j] != 0 && k_board[i][j] != idx) {
                Push(T, k_board[i][j], dir);
            }
        }
    }

    for (int i = nx; i < nx+h; i++) {
        for (int j = ny; j < ny+w; j++) {
            k_board[i][j] = idx;
        }
    }
    if (idx != cmd[T][0]) {
        damage(idx);
    }
}

void damage(int idx) {
    int cnt = 0;
    for (int i = 1; i <= L; i++) {
        for (int j = 1; j <= L; j++) {
            if (k_board[i][j] == idx && chess[i][j] == 1) {
                cnt ++;
            }
        }
    }
    k_hp[idx] -= cnt;
    if (k_hp[idx] <= 0)
    {
        isKnight[idx] = false;
        reset(idx);
    }
    else 
        k_score[idx] += cnt;
}

void reset(int idx) {
    int x, y, h, w;
    x = knight[idx][0];
    y = knight[idx][1];
    h = k_shield[idx][0];
    w = k_shield[idx][1];

    for (int i = x; i < x+h; i++) {
        for (int j = y; j < y+w; j++) {
            k_board[i][j] = 0;
        }
    }
}
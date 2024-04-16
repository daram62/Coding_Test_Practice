// 17144 미세먼지 안녕!

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#define endl '\n'
using namespace std;

int R, C, T;
map <int, int> home[52];
map <int, int> temp_home[52];
vector <map <int, int> > machine[2];

int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

void Print() {
    cout << endl;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cout << home[i][j] << " "; 
        }
        cout << endl;
    }
}

void temp_Print() {
    cout << endl;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cout << temp_home[i][j] << " "; 
        }
        cout << endl;
    }
}
void temp_reset() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            temp_home[i][j] = home[i][j];
        }
    }
}

void home_reset() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            home[i][j] = temp_home[i][j];
        }
    }
}

void Dust() {
    // 템프배열에 기존 배열 값 넣어주기
    temp_reset();

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            // 더할 미세먼지 값 계산
            int dust = home[i][j] / 5;
            if (dust > 0) {
                //cout << i << ", " << j << " = " << home[i][j] << " => " << dust << endl;
                    // 인접 네 방향 체크
                for (int k = 0; k < 4; k++) {
                    int nr = i + dx[k];
                    int nc = j + dy[k];
                    if (temp_home[nr][nc] == -1) // 인접 칸이 공기청정기이면
                        continue;
                    else if (nr < 1 || nr > R || nc < 1 || nc > C) // 범위 벗어나면
                        continue;   
                    // 확산 가능하면 미세먼지 값 더하기
                    //cout << nr << ", " << nc << " += " << dust << endl;
                    temp_home[nr][nc] += dust;
                    //cout << temp_home[nr][nc] << endl;
                    // 확산한 뒤 그 값 기존 블럭에서 빼기
                    temp_home[i][j] -= dust;
                    //cout << temp_home[i][j] << endl;
                }
                //cout << "----------------------------" << endl;
            }
        }
    }
    home_reset();
}

void clean_upper(int r, int c) {
    temp_reset();
    int sr = r, sc = c;
    temp_home[r][c+1] = 0;
    c++;
    int dir = 3; // 기본 방향 우
    while (true) 
    {   
        int nr = r + dx[dir];
        int nc = c + dy[dir];

        if (nr == sr && nc == sc) {
            // 한 바퀴 다 돌고 시작점 도착
            break;
        }
        if (nr < 1 || nr > R || nc < 1 || nc > C) // 범위 벗어나면
        {   
            // 방향 바꾸기 
            if (dir == 3) {
                dir = 0;
                nr = r - 1;
                nc = c;
            }
            else if (dir == 0) {
                dir = 2;
                nr = r;
                nc = c - 1;
            }
            else if (dir == 2) {
                dir = 1;
                nr = r + 1;
                nc = c;
            }
        }
        temp_home[nr][nc] = home[r][c];
        r = nr;
        c = nc;
    }
    home_reset();
}

void clean_lower(int r, int c) {
    temp_reset();
    int sr = r, sc = c;
    temp_home[r][c+1] = 0;
    c++;
    int dir = 3; // 기본 방향 우
    while (true) 
    {   
        int nr = r + dx[dir];
        int nc = c + dy[dir];

        if (nr == sr && nc == sc) {
            // 한 바퀴 다 돌고 시작점 도착
            break;
        }
        if (nr < 1 || nr > R || nc < 1 || nc > C) // 범위 벗어나면
        {   
            // 방향 바꾸기 
            if (dir == 3) {
                dir = 1;
                nr = r + 1;
                nc = c;
            }
            else if (dir == 1) {
                dir = 2;
                nr = r;
                nc = c - 1;
            }
            else if (dir == 2) {
                dir = 0;
                nr = r - 1;
                nc = c;
            }
        }
        temp_home[nr][nc] = home[r][c];
        r = nr;
        c = nc;
    }
    home_reset();
}

void Dust_sum() {
    int sum = 2;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            sum += home[i][j];
        }
    }
    cout << sum << endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 크기, 시간 입력받기
    cin >> R >> C >> T;
    
    // 미세먼지, 공기청정기 위치 입력받기
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> home[i][j];
        }
    }
    for (int t = 0; t < T; t++) 
    {
        // 미세먼지 확산 함수
        Dust();
        //Print();
        // 공기청정기 작동 함수
        // 반복문 돌려서 공기청정기 위치 찾고, 작동 함수 돌리기
        bool found = false;
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                if (home[i][j] == -1)
                {
                    found = true;
                    clean_upper(i,j);
                    clean_lower(i+1,j);
                    break;
                }
            }
            if (found)
                break;
        }
        //Print();
    }
    // 미세먼지 양 출력
    Dust_sum();
    return 0;
}
#include<iostream>
#pragma warning (disable:4996)
#define MAX 16
#define PATH 0
#define WALL 1
#define BLOCKED 2
#define VISITED 3
#define TURN 4
#define FIND 5
#define DEBUG
enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
};
using namespace std;

int N, T;
int maze[MAX][MAX];
bool FindeMazePath(int x, int y, int dir);
void Display();
bool IsPathable(int x, int y, int dir);
class Offset{
public:
	int x, y;
	void SetOffset(int dir){
		switch (dir){
		case 0: x = -1; y = 0; break;
		case 1: x = 0; y = 1; break;
		case 2: x = 1; y = 0; break;
		case 3: x = 0; y = -1; break;
		}
	}
};
Offset offsets[4];
int main()
{
	FILE *fp = fopen("input2.txt", "r");
	fscanf(fp, "%d", &T);
	for (int i = 0; i < 4; i++)
		offsets[i].SetOffset(i);
	while (T>0) {
		T--;
		fscanf(fp, "%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				fscanf(fp, "%d", &maze[i][j]);
		}
		int ans = FindeMazePath(0, 0, UP);
		if (ans)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}
bool FindeMazePath(int x, int y, int dir)
{
	if (x == N - 1 && y == N - 1)
		return true;
	else if (maze[x][y] == TURN)
		return false;
	else if (IsPathable(x, y, dir)){
		maze[x][y] = VISITED;
		Display();
		if (FindeMazePath(x + offsets[dir].x, y + offsets[dir].y, dir))
			return true;
		return false;
	}
	else {
		maze[x][y] = TURN;
		Display();
		for (int i = 0; i < 4; i++){
			if (IsPathable(x, y, i)){
				if (FindeMazePath(x + offsets[i].x, y + offsets[i].y, i))
					return true;
			}
		}
		return false;
	}
}
#ifdef DEBUG
void Display()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
#endif
bool IsPathable(int x, int y, int dir)
{
	if (dir == 0 && (x - 1 < 0 || maze[x - 1][y] == WALL))
		return false;
	else if (dir == 1 && (y + 1 > N - 1 || maze[x][y + 1] == WALL))
		return false;
	else if (dir == 2 && (x + 1 > N - 1 || maze[x + 1][y] == WALL))
		return false;
	else if (dir == 3 && (y - 1 < 0 || maze[x][y - 1] == WALL))
		return false;
	return true;
}
#include<iostream>
#define MAX 16
#define PATH 0
#define WALL 1
#define BLOCKED 2
#define VISITED 3
//#define DEBUG
using namespace std;

int N, K, T;
int maze[MAX][MAX];
int FindeMazePath(int x, int y, int dist);
void Display();
int main()
{
	FILE *fp = fopen("input1.txt", "r");
	fscanf(fp, "%d", &T);
	while (T>0) {
		T--;
		fscanf(fp, "%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				fscanf(fp, "%d", &maze[i][j]);
		}
		fscanf(fp, "%d", &K);
		cout << /*"경로의 개수 : " << */FindeMazePath(0, 0, 0) << endl;
	}
	return 0;
}
int FindeMazePath(int x, int y, int dist)
{
	int sum = 0;
	if (maze[x][y] != PATH) {
		return 0;
	}
	if (dist > K) {
		return 0;
	}
	if (x < 0 || y < 0 || x >= N || y >= N) {
		return 0;
	}
	else if (x == N - 1 && y == N - 1) {
#ifdef DEBUG
		Display();
#endif
		maze[x][y] = PATH;
		return 1;
	}
	else {
		maze[x][y] = VISITED;
		sum += FindeMazePath(x - 1, y, dist+1) + FindeMazePath(x, y - 1, dist+1) + FindeMazePath(x + 1, y, dist+1) + FindeMazePath(x, y + 1, dist+1);
		if (sum > 0) {
			maze[x][y] = PATH;
			return sum;
		}
		maze[x][y] = PATH;
		return 0;
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
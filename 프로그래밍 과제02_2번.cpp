#include<iostream>
#define MAX 100
using namespace std;

int N, K;
int RecursiveFloor(int startIndex, int endIndex, int data[]);
int RecursiveCeiling(int startIndex, int endIndex, int data[]);
int main()
{
	int data[MAX];
	while (1) {
		cin >> N;
		for (int i = 0; i < N; i++)
			cin >> data[i];
		cin >> K;
		cout << RecursiveFloor(0, N - 1, data) << endl;
		cout << RecursiveCeiling(0, N - 1, data) << endl;
	}

	return 0;
}
int RecursiveFloor(int startIndex, int endIndex, int data[]) {
	int middleIndex = (startIndex + endIndex) / 2;
	if (data[middleIndex] == K)
		return data[middleIndex];
	else if (startIndex == N - 1 && data[startIndex] <= K)
		return data[startIndex];
	else if (endIndex == 0 && data[endIndex] >= K)
		return -1;
	else if (data[middleIndex] < K) {
		if (data[middleIndex + 1] > K)
			return data[middleIndex];
		middleIndex += 1;
		return RecursiveFloor(middleIndex, endIndex, data);
	}
	else if (data[middleIndex] > K) {
		if (data[middleIndex - 1] < K)
			return data[middleIndex - 1];
		middleIndex -= 1;
		return RecursiveCeiling(startIndex, middleIndex, data);
	}
}
int RecursiveCeiling(int startIndex, int endIndex, int data[]) {
	int middleIndex = (startIndex + endIndex) / 2;
	if (data[middleIndex] == K)
		return data[middleIndex];
	else if (endIndex == 0 && data[endIndex] >= K)
		return data[endIndex];
	else if (startIndex == N-1 && data[startIndex] <= K)
		return -1;
	else if (data[middleIndex] > K) {
		if (data[middleIndex - 1] < K)
			return data[middleIndex];
		middleIndex -= 1;
		return RecursiveFloor(startIndex, middleIndex, data);
	}
	else if (data[middleIndex] < K) {
		if (data[middleIndex + 1] > K)
			return data[middleIndex + 1];
		middleIndex += 1;
		return RecursiveCeiling(middleIndex, endIndex, data);
	}
}
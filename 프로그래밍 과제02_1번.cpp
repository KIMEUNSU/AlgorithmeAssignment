#include<iostream>
#define MAX 100
using namespace std;

int N, K;
int RecursiveGetSum(int startIndex, int endIndex, int data[]);
int main()
{
	int data[MAX];
	while (1) {
		cin >> N;
		for (int i = 0; i < N; i++)
			cin >> data[i];
		cin >> K;
		int result = RecursiveGetSum(0, N - 1, data);
		cout << result << endl;
	}

	return 0;
}
int RecursiveGetSum(int startIndex, int endIndex, int data[])
{
	static int count = 0;
	if (startIndex >= endIndex)
		return count;
	int sum = data[startIndex] + data[endIndex];
	if (sum > K) {
		endIndex--;
		return RecursiveGetSum(startIndex, endIndex, data);
	}
	else if (sum < K) {
		startIndex++;
		return RecursiveGetSum(startIndex, endIndex, data);
	}
	else {
		count++;
		startIndex++;
		endIndex--;
		return RecursiveGetSum(startIndex, endIndex, data);
	}

}
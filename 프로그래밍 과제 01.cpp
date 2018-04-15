#include<iostream>
#include<fstream>
#include<math.h>
#define MAX 10000
using namespace std;

int M, N, i, j;
int process(int data[]);
int main()
{
	int data[MAX];
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &N);
	M = (int)sqrt(N);
	for (int k = 0; k < N; k++)
		fscanf(fp, "%d", &data[k]);
	while (1) {
		cin >> i >> j;
		if (i == -1)
			break;
		else
			process(data);
	}

	return 0;
}
int process(int data[])
{
	int group_min[MAX];			// 각 그룹의 최소값 저장
	int min_list[MAX];			// 각 그룹 및 최소값이라 추측되는 양 끝 그룹의 값 저장
	int min_index_list[MAX];	// 최솟값들의 인덱스 저장
	int cnt = 0;				// 최솟값들의 순서를 보장하기위한 보조 인덱스
	int group_index = 0;		// 그룹 인덱스

	// 각 그룹의 최솟값을 저장
	for (int i = 0; i < N; i+=M) {
		group_min[group_index] = data[i];
		min_index_list[group_index] = i;
		for (int j = i; j < (i)+(M-1); j++) {
			if (data[j + 1] < group_min[group_index]) {
				group_min[group_index] = data[j + 1];
				min_index_list[group_index] = j + 1;
			}
		}
		group_index++;
	}
	// 범위 벗어난 경우 나머지값들은 다 최솟값이 된다
	// 각 그룹의 첫번째부터 시작하면 미리 구한 최솟값 사용하면 된다
	if (i%M == 0) {
		min_list[cnt] = group_min[i / M];
		min_index_list[cnt] = min_index_list[i / M];
		cnt++;
	}
	// 각 그룹의 마지막부터 시작하면 그게 최솟값으로 사용된다
	else if (i%M == M - 1) {
		min_list[cnt] = data[i];
		min_index_list[cnt] = i;
		cnt++;
	}
	// 그 사이에 시작하면 모두다 넣는다
	else {
		for (int a = i; a%M != 0; a++) {
			min_list[cnt] = data[a];
			min_index_list[cnt] = a;
			cnt++;
		}
	}
	// 중간에는 미리 구해둔 최솟값들을 사용한다
	for (int k = (i / M) + 1; k < (j / M); k++) {
		min_list[cnt] = group_min[k];
		min_index_list[cnt] = min_index_list[k];
		cnt++;
	}
		
	// 각 그룹의 첫번째에서 끝나면 그게 최솟값
	if (j%M == 0) {
		min_list[cnt] = data[j];
		min_index_list[cnt] = j;
		cnt++;
	}
	// 각 그룹의 마지막에서 끝나면 미리 구한 최솟값 사용하면 된다
	else if (j%M == M - 1) {
		min_list[cnt] = group_min[j / M];
		min_index_list[cnt] = min_index_list[j / M];
		cnt++;
	}
	// 그 사이에 끝나면 모두다 넣는다.
	else {
		for (int a = j; a%M != 0; a--) {
			min_list[cnt] = data[a];
			min_index_list[cnt] = a;
			cnt++;
		}
	}

	// 지금까지구한 최솟값들의 리스트에서 진짜 최솟값을 구한다.
	int genuine_min = min_list[0];
	int min_index = 0;
	for (int i = 1; i < cnt; i++) {
		if (genuine_min > min_list[i]) {
			genuine_min = min_list[i];
			min_index = min_index_list[i];
			//min_index = i;
		}
	}

	cout << "data[" << min_index << "] = " << genuine_min << endl;

	return 0;
}
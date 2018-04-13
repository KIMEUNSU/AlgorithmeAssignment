#include<iostream>
#include<vector>
#include<time.h>
#define MAX 100000
#define LEFT(x) (2*x+1)
#define RIGHT(x) (2*x+2)
#define PARENT(x) ((x-1)/2)

using namespace std;

void Swap(int &x, int &y);
double HeapTest(int N, int M);
double NormalTest(int N, int M);
class NormalPriorityQueue {
public:
	vector<int> commonData;

	void Add(int n) {
		commonData.push_back(n);
	}
	int ExtractMax() {
		int maxIndex = 0;
		int max;
		for (int i = 0; i < commonData.size(); i++) {
			if (commonData.at(maxIndex) < commonData.at(i))
				maxIndex = i;
		}
		max = commonData.at(maxIndex);
		Swap(commonData.at(maxIndex), commonData.at(commonData.size() - 1));
		commonData.pop_back();
		return max;
	}
	void Print()
	{
		for (int i = 0; i < commonData.size(); i++)
			cout << commonData.at(i) << " ";
		cout << endl;
	}
	bool IsEmpty() {
		if (commonData.size() == 0)
			return true;
		return false;
	}
};
class HeapPriorityQueue {
public:
	vector<int> maxHeap;
	int sortedNum = 0;

	/*void GetRandNumber(int N) {
		for (int i = 0; i < N; i++)
			maxHeap.push_back(rand() % N);
	}*/
	void Add(int n) {
		maxHeap.push_back(n);
		int i = maxHeap.size() - 1;
		while (i > 0 && maxHeap.at(PARENT(i)) < maxHeap.at(i)) {
			Swap(maxHeap.at(PARENT(i)), maxHeap.at(i));
			i = PARENT(i);
		}
	}
	int ExtractMax() {
		if (maxHeap.size() < 0)
			return 0;
		int max = maxHeap.at(0);
		Swap(maxHeap.at(0), maxHeap.at(maxHeap.size() - 1));
		maxHeap.pop_back();
		MaxHeapify(0);
		return max;
	}
	void BuildHeap() {
		for (int i = (maxHeap.size() - 1) / 2; i >= 0; i--) {
			MaxHeapify(i);
		}
		cout << "Built Max_Heap" << endl;
		Print();
	}
	void MaxHeapify(int i) {
		if (LEFT(i) >= maxHeap.size() - sortedNum)
			return;
		int k = LEFT(i);
		if (RIGHT(i) < maxHeap.size() - sortedNum && (maxHeap.at(k) < maxHeap.at(RIGHT(i))))
			k = RIGHT(i);
		if (maxHeap.at(i) >= maxHeap.at(k))
			return;
		Swap(maxHeap.at(i), maxHeap.at(k));
		MaxHeapify(k);
	}
	void HeapSort() {
		BuildHeap();
		for (int i = maxHeap.size() - 1; i >= 0; i--) {
			Swap(maxHeap.at(0), maxHeap.at(i));
			sortedNum++;
			MaxHeapify(0);
		}
		sortedNum = 0;
	}
	void Print() {
		for (int i = 0; i < maxHeap.size(); i++)
			cout << maxHeap.at(i) << " ";
		cout << endl;
	}
	bool IsEmpty() {
		if (maxHeap.size() == 0)
			return true;
		return false;
	}
};

HeapPriorityQueue hq;
NormalPriorityQueue cq;
int main()
{
	srand((unsigned)time(NULL));
	int N, M;
	cout << "N, M 을 입력하세요: ";
	cin >> N >> M;
	cout << "힙 우선순위 큐 실행시간: " << HeapTest(N, M) << endl;
	cout << "정렬되지 않은 배열 우선순위 큐 실행시간 : " << NormalTest(N, M) << endl;

	return 0;
}
void Swap(int &x, int &y)
{
	int tmp = x;
	x = y;
	y = tmp;
}
double HeapTest(int N, int M)
{
	double before = clock();
	for (int i = 0; i < N; i++)
		hq.Add(rand() % N);
	//cout << "heapify 된 힙 : " << endl;
	//hq.Print();
	for (int i = 0; i < M; i++) {
		if (rand() % 2 == 0 || hq.IsEmpty()) {
			//cout << "Insert: ";
			hq.Add(rand() % N);
			//hq.Print();
		}
		else {
			//cout << "Extract: ";
			hq.ExtractMax();
			//hq.Print();
		}
	}
	double result = (double)(clock() - before) / CLOCKS_PER_SEC;
	return result;
}
double NormalTest(int N, int M)
{
	double before = clock();

	for (int i = 0; i < N; i++)
		cq.Add(rand() % N);
	//cout << "정렬되지 않은 배열 : " << endl;
	//cq.Print();
	for (int i = 0; i < M; i++) {
		if (rand() % 2 == 0 || cq.IsEmpty()) {
			//cout << "Insert: ";
			cq.Add(rand() % N);
			//cq.Print();
		}
		else {
			//cout << "Extract: ";
			cq.ExtractMax();
			//cq.Print();
		}
	}

	double result = (double)(clock() - before) / CLOCKS_PER_SEC;
	return result;
}
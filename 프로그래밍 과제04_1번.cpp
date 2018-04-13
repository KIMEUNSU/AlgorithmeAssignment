#include<iostream>
#include<algorithm>
#include<vector>
#include<time.h>
#define MAX 100000
#define RIGHT 0
#define MIDDLE 1
#define RAND 2
#define LEFT_CHILD(x) (2*x + 1)
#define RIGHT_CHILD(x) (2*x + 2)
#define PARENT(x) ((x-1)/2)
using namespace std;

int tempArray[MAX];

double BubbleSort(int data[], int N);
double SelectionSort(int data[], int N);
double InsertionSort(int data[], int N);
void MergeSort(int data[], int left, int right);
void Merge(int data[], int left, int mid, int right);
double MergeSortTimeCheck(int data[], int left, int right);
void QuickSort(int data[], int left, int right, int pivotNum);
int QuickSortPartition_RightPivot(int data[], int left, int right);
int QuickSortPartition_MiddlePivot(int data[], int left, int right);
int QuickSortPartition_RandomPivot(int data[], int left, int right);
double QuickSortTimeCheck(int data[], int left, int right, int pivotNum);
double HeapSort(int data[], int N);
void InitHeap(int data[], int N);
void MakeHeap(int data[], int N);
int FindMaxIndex(int data[], int N, int now);
double LibrarySortTimeCheck(int data[], int N);
void Swap(int &x, int &y);
void Print(int data[], int N);
void PrintVector(vector<int> v);
void FillRandomeNumber(int data[], int N);
void FillReversedNumber(int data[], int N);
void MakeTable();
int main()
{
	int data[MAX];
	srand((unsigned)time(NULL));
	cout << fixed; cout.precision(3);
	MakeTable();
	/* Bubble Sort */
	cout << "Bubble" << "\t\t";
	FillRandomeNumber(data, 1000); cout << BubbleSort(data, 1000) << "\t\t";
	FillReversedNumber(data, 1000); cout << BubbleSort(data, 1000) << "\t\t";
	FillRandomeNumber(data, 10000); cout << BubbleSort(data, 10000) << "\t\t";
	FillReversedNumber(data, 10000); cout << BubbleSort(data, 10000) << "\t\t";
	//FillRandomeNumber(data, 100000); cout << BubbleSort(data, 100000) << "\t\t";
	//FillReversedNumber(data, 100000); cout << BubbleSort(data, 100000) << "\t\t";
	cout << endl;
	/* Selection Sort */
	cout << "Selection" << "\t";
	FillRandomeNumber(data, 1000); cout << SelectionSort(data, 1000) << "\t\t";
	FillReversedNumber(data, 1000); cout << SelectionSort(data, 1000) << "\t\t";
	FillRandomeNumber(data, 10000); cout << SelectionSort(data, 10000) << "\t\t";
	FillReversedNumber(data, 10000); cout << SelectionSort(data, 10000) << "\t\t";
	//FillRandomeNumber(data, 100000); cout << SelectionSort(data, 100000) << "\t\t";
	//FillReversedNumber(data, 100000); cout << SelectionSort(data, 100000) << "\t\t";
	cout << endl;
	/* Insert Sort */
	cout << "Insersion" << "\t";
	FillRandomeNumber(data, 1000); cout << InsertionSort(data, 1000) << "\t\t";
	FillReversedNumber(data, 1000); cout << InsertionSort(data, 1000) << "\t\t";
	FillRandomeNumber(data, 10000); cout << InsertionSort(data, 10000) << "\t\t";
	FillReversedNumber(data, 10000); cout << InsertionSort(data, 10000) << "\t\t";
	//FillRandomeNumber(data, 100000); cout << InsertionSort(data, 100000) << "\t\t";
	//FillReversedNumber(data, 100000); cout << InsertionSort(data, 100000) << "\t\t";
	cout << endl;
	/* Merge Sort */
	cout << "Merge" << "\t\t";
	FillRandomeNumber(data, 1000); cout << MergeSortTimeCheck(data, 0, 999) << "\t\t";
	FillReversedNumber(data, 1000); cout << MergeSortTimeCheck(data, 0, 999) << "\t\t";
	FillRandomeNumber(data, 10000); cout << MergeSortTimeCheck(data, 0, 9999) << "\t\t";
	FillReversedNumber(data, 10000); cout << MergeSortTimeCheck(data, 0, 9999) << "\t\t";
	FillRandomeNumber(data, 100000); cout << MergeSortTimeCheck(data, 0, 99999) << "\t\t";
	FillReversedNumber(data, 100000); cout << MergeSortTimeCheck(data, 0, 99999) << "\t\t";
	cout << endl;
	/* Quick Sort Right Pivot */
	cout << "Quick1" << "\t\t";
	FillRandomeNumber(data, 1000); cout << QuickSortTimeCheck(data, 0, 999, RIGHT) << "\t\t";
	FillReversedNumber(data, 1000); cout << QuickSortTimeCheck(data, 0, 999, RIGHT) << "\t\t";
	FillRandomeNumber(data, 10000); cout << QuickSortTimeCheck(data, 0, 9999, RIGHT) << "\t\t";
	FillReversedNumber(data, 10000); cout << QuickSortTimeCheck(data, 0, 9999, RIGHT) << "\t\t";
	FillRandomeNumber(data, 100000); cout << QuickSortTimeCheck(data, 0, 99999, RIGHT) << "\t\t";
	//FillReversedNumber(data, 100000); cout << QuickSortTimeCheck(data, 0, 99999, RIGHT) << "\t\t";
	cout << endl;
	/* Quick Sort Middle Pivot */
	cout << "Quick2" << "\t\t";
	FillRandomeNumber(data, 1000); cout << QuickSortTimeCheck(data, 0, 999, MIDDLE) << "\t\t";
	FillReversedNumber(data, 1000); cout << QuickSortTimeCheck(data, 0, 999, MIDDLE) << "\t\t";
	FillRandomeNumber(data, 10000); cout << QuickSortTimeCheck(data, 0, 9999, MIDDLE) << "\t\t";
	FillReversedNumber(data, 10000); cout << QuickSortTimeCheck(data, 0, 9999, MIDDLE) << "\t\t";
	FillRandomeNumber(data, 100000); cout << QuickSortTimeCheck(data, 0, 99999, MIDDLE) << "\t\t";
	FillReversedNumber(data, 100000); cout << QuickSortTimeCheck(data, 0, 99999, MIDDLE) << "\t\t";
	cout << endl;
	/* Quick Sort Random Pivot */
	cout << "Quick3" << "\t\t";
	FillRandomeNumber(data, 1000); cout << QuickSortTimeCheck(data, 0, 999, RAND) << "\t\t";
	FillReversedNumber(data, 1000); cout << QuickSortTimeCheck(data, 0, 999, RAND) << "\t\t";
	FillRandomeNumber(data, 10000); cout << QuickSortTimeCheck(data, 0, 9999, RAND) << "\t\t";
	FillReversedNumber(data, 10000); cout << QuickSortTimeCheck(data, 0, 9999, RAND) << "\t\t";
	FillRandomeNumber(data, 100000); cout << QuickSortTimeCheck(data, 0, 99999, RAND) << "\t\t";
	FillReversedNumber(data, 100000); cout << QuickSortTimeCheck(data, 0, 99999, RAND) << "\t\t";
	cout << endl;
	/* Heap Sort */
	cout << "Heap" << "\t\t";
	FillRandomeNumber(data, 1000); cout << HeapSort(data, 1000) << "\t\t";
	FillReversedNumber(data, 1000); cout << HeapSort(data, 1000) << "\t\t";
	FillRandomeNumber(data, 10000); cout << HeapSort(data, 10000) << "\t\t";
	FillReversedNumber(data, 10000); cout << HeapSort(data, 10000) << "\t\t";
	FillRandomeNumber(data, 100000); cout << HeapSort(data, 100000) << "\t\t";
	FillReversedNumber(data, 100000); cout << HeapSort(data, 100000) << "\t\t";
	cout << endl;
	/* Library Sort */
	cout << "Library" << "\t\t";
	FillRandomeNumber(data, 1000); cout << LibrarySortTimeCheck(data, 1000) << "\t\t";
	FillReversedNumber(data, 1000); cout << LibrarySortTimeCheck(data, 1000) << "\t\t";
	FillRandomeNumber(data, 10000); cout << LibrarySortTimeCheck(data, 10000) << "\t\t";
	FillReversedNumber(data, 10000); cout << LibrarySortTimeCheck(data, 10000) << "\t\t";
	FillRandomeNumber(data, 100000); cout << LibrarySortTimeCheck(data, 100000) << "\t\t";
	FillReversedNumber(data, 100000); cout << LibrarySortTimeCheck(data, 100000) << "\t\n";


	/*cout << "정렬 전: " << endl;
	FillRandomeNumber(data, 10);
	Print(data, 10);
	cout << "정렬 후: " << endl;
	LibrarySortTimeCheck(data, 10);*/


	return 0;
}
double BubbleSort(int data[], int N)
{
	double beforeTime = clock();
	for (int i = N - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (data[j] > data[j + 1])
				Swap(data[j], data[j + 1]);
		}
	}
	double result = (double)(clock() - beforeTime) / CLOCKS_PER_SEC;
	return result;
}
double SelectionSort(int data[], int N)
{
	double beforeTime = clock();
	for (int i = 0; i < N; i++) {
		int min = data[i];
		int least = i;
		for (int j = i; j < N; j++) {
			if (data[j] < min) {
				min = data[j]; least = j;
			}
		}
		int tmp = data[i];
		data[i] = data[least];
		data[least] = tmp;
	}
	double result = (double)(clock() - beforeTime) / CLOCKS_PER_SEC;
	return result;
}
double InsertionSort(int data[], int N)
{
	double beforeTime = clock();
	for (int i = 0; i < N; i++) {
		int j = i - 1;
		int key = data[i];
		while (data[j] > key && j >= 0) {
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = key;
	}
	double result = (double)(clock() - beforeTime) / CLOCKS_PER_SEC;
	return result;
}
double MergeSortTimeCheck(int data[], int left, int right)
{
	double beforeTime = clock();
	MergeSort(data, left, right);
	double result = (double)(clock() - beforeTime) / CLOCKS_PER_SEC;
	return result;
}
void MergeSort(int data[], int left, int right)
{
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		MergeSort(data, left, mid);
		MergeSort(data, mid + 1, right);
		Merge(data, left, mid, right);
	}
}
void Merge(int data[], int left, int mid, int right)
{
	int i, j, k, m;
	i = left; j = mid + 1; k = left;
	while (i <= mid && j <= right) {
		if (data[i] < data[j]) {
			tempArray[k] = data[i]; i++;
		}
		else {
			tempArray[k] = data[j]; j++;
		}
		k++;
	}
	if (i > mid) {
		for (m = j; m <= right; m++) {
			tempArray[k] = data[m];
			k++;
		}
	}
	else {
		for (m = i; m <= mid; m++) {
			tempArray[k] = data[m];
			k++;
		}
	}
	for (m = left; m <= right; m++) {
		data[m] = tempArray[m];
	}
}
double QuickSortTimeCheck(int data[], int left, int right, int pivot)
{
	double beforeTime = clock();
	QuickSort(data, left, right, pivot);
	double result = (double)(clock() - beforeTime) / CLOCKS_PER_SEC;
	return result;
}
void QuickSort(int data[], int left, int right, int pivot)
{
	int pivotIndex;
	if (left < right) {
		if (pivot == RIGHT) {
			pivotIndex = QuickSortPartition_RightPivot(data, left, right);
			QuickSort(data, left, pivotIndex - 1, pivot);
			QuickSort(data, pivotIndex + 1, right, pivot);
		}
		else if (pivot == MIDDLE) {
			pivotIndex = QuickSortPartition_MiddlePivot(data, left, right);
			QuickSort(data, left, pivotIndex - 1, pivot);
			QuickSort(data, pivotIndex + 1, right, pivot);
		}
		else if (pivot == RAND) {
			pivotIndex = QuickSortPartition_RandomPivot(data, left, right);
			QuickSort(data, left, pivotIndex - 1, pivot);
			QuickSort(data, pivotIndex + 1, right, pivot);
		}
	}
}
int QuickSortPartition_RightPivot(int data[], int left, int right)
{
	int remember = data[right];
	int i = left - 1;
	for (int j = left; j < right; j++) {
		if (data[j] <= remember) {
			i++; Swap(data[i], data[j]);
		}
	}
	Swap(data[i + 1], data[right]);
	return i + 1;
}
int QuickSortPartition_MiddlePivot(int data[], int left, int right)
{
	int remember;
	int l = data[left], m = data[(left + right) / 2], r = data[right];
	if ((l <= m && m <= r) || (r <= m && m <= l)) {
		remember = m;
		Swap(data[(left + right) / 2], data[right]);
	}
	else if ((m <= l && l <= r) || (r <= l && l <= m)) {
		remember = l;
		Swap(data[left], data[right]);
	}
	else if ((m <= r && r <= l) || (l <= r && r <= m)) {
		remember = r;
		// don't need to swap
	}

	int i = left - 1;
	for (int j = left; j < right; j++) {
		if (data[j] <= remember) {
			i++; Swap(data[i], data[j]);
		}
	}
	Swap(data[i + 1], data[right]);
	return i + 1;
}
int QuickSortPartition_RandomPivot(int data[], int left, int right)
{
	int randomIndex = rand() % (right - left + 1) + left;
	int remember = data[randomIndex];
	Swap(data[randomIndex], data[right]);

	int i = left - 1;
	for (int j = left; j < right; j++) {
		if (data[j] <= remember) {
			i++; Swap(data[i], data[j]);
		}
	}
	Swap(data[i + 1], data[right]);
	return i + 1;
}
double HeapSort(int data[], int N)
{
	double beforeTime = clock();
	int on = N;
	InitHeap(data, N);
	N--;
	Swap(data[0], data[N]);
	while (N > 1) {
		MakeHeap(data, N);
		N--;
		Swap(data[0], data[N]);
	}
	double result = (double)(clock() - beforeTime) / CLOCKS_PER_SEC;
	return result;
}
void InitHeap(int data[], int N)
{
	int parent = 0;
	int now = 0;
	int i;
	for (i = 1; i < N; i++) {
		now = i;
		while (now > 0) {
			parent = PARENT(now);
			if (data[now] > data[parent]) {
				Swap(data[now], data[parent]);
				now = parent;
			}
			else
				break;
		}
	}
}
void MakeHeap(int data[], int N)
{
	int now = 0;
	int myParent = 0;
	while (LEFT_CHILD(now) < N) {
		myParent = FindMaxIndex(data, N, now);
		if (myParent == now)
		{
			break;
		}
		Swap(data[myParent], data[now]);
		now = myParent;
	}
}
int FindMaxIndex(int data[], int N, int now)
{
	int lc = LEFT_CHILD(now);
	int rc = RIGHT_CHILD(now);

	if (rc >= N)
	{
		if (data[now] < data[lc])
			return lc;
		return now;
	}
	if (data[lc] < data[rc]) {
		return rc;
	}
	return lc;
}
double LibrarySortTimeCheck(int data[], int N)
{
	double beforeTime = clock();
	vector <int> dataVec;
	for (int i = 0; i < N; i++)
		dataVec.push_back(data[i]);
	sort(dataVec.begin(), dataVec.end());
	//PrintVector(dataVec);
	double result = (double)(clock() - beforeTime) / CLOCKS_PER_SEC;
	return result;
}
void Swap(int &x, int &y)
{
	int tmp = x;
	x = y;
	y = tmp;
}
void Print(int data[], int N)
{
	for (int i = 0; i < N; i++)
		cout << data[i] << " ";
	cout << endl;
}
void PrintVector(vector<int> v)
{
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}
void FillRandomeNumber(int data[], int N)
{
	for (int i = 0; i < N; i++) {
		data[i] = (rand() % N) + 1;		// 1 ~ N 사이의 랜덤 정수로 채움
	}
}
void FillReversedNumber(int data[], int N)
{
	for (int i = 0; i < N; i++) {
		data[i] = N - i;
	}
}
void MakeTable()
{
	cout << "\t   " << "Random1000     " << "Reverse1000     " << "Random10000     " << "Reverse10000     " << "Random100000     " << "Reverse100000     " << endl;
}
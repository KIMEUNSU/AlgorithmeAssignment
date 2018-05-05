#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<time.h>
#pragma warning (disable:3867)
#define NHASH 4093
#define MULTIPLIER 31
#define MAX 200
//#define DEBUG
using namespace std;

typedef struct suffix {
	string sword;
	int freq;
	suffix *next;
}Suffix;
typedef struct prefix {
	string pword1;
	string pword2;
	suffix *suf;
	int sumFreq;
}Prefix;
typedef struct node {
	prefix *data;
	node *next;
}Node;

Node *htable[NHASH];
char inputString[MAX];
unsigned int Hash(const char *key1, const char *key2);
bool ReadFile(string title);
Prefix* MakePrefix(char *key1, char *key2);
Suffix* MakeSuffix(char *suffix);
Node*& MakeNode(Prefix *p);
void PrintHashTable();
void PrintFakeText();
void MakeFakeText(Prefix *p, int count);
Suffix* GetRandomSuffix(Prefix *p);
Prefix* FindPrefix(const char *key1, const char *key2);

int main()
{
	srand((unsigned)time(NULL));
	string textName;
	cout << "Input text to read: ";
	cin >> textName;
	cout << textName <<".txt를 읽는중..." << endl;
	if (!ReadFile(textName))
		return 0;
#ifdef DEBUG
	PrintHashTable();
#endif // DEBUG
	cout << "Markov Chain >>" << endl << endl;
	PrintFakeText();

	return 0;
}

unsigned int Hash(const char *key1, const char *key2) {
	unsigned int h = 0;
	unsigned char *p;

	for (p = (unsigned char *)key1; *p != '\0' ; p++)
		h = MULTIPLIER * h + *p;
	for (p = (unsigned char *)key2; *p != '\0'; p++)
		h = MULTIPLIER * h + *p;
	return h % NHASH;
}
bool ReadFile(string title)
{
	
	char *token = NULL, *key1 = NULL, *key2 = NULL, *suffix = NULL;
	string K1, K2;
	fstream fin;
	fin.open(title + ".txt");
	if (fin.fail()) {
		cout << title << ".txt is not exist." << endl;
		return false;
	}
	fin.getline(inputString, MAX);
	token = strtok(inputString, " ");
	
	// 한 줄 마다 루프돌면서 토크나이징 & prefix 추가
	while (!fin.eof()) {
		key1 = key2;
		key2 = suffix;
		suffix = token;

		// 맨 처음 tokenizing 시 continuenull 스트링
		if (key1 == NULL) {
			token = strtok(NULL, " ");
			continue;
		}
		// 줄의 끝에 도달하면 다음 줄 첫 글자가 suffix
		else if (suffix == NULL) {
			// 줄바꾸면 key1, key2의 내용이 달라지므로 저장
			K1 = key1;
			K2 = key2;
			do {
				if (fin.eof())
					break;
				fin.getline(inputString, MAX);
			} while (inputString[0] == '\0');
			suffix = strtok(inputString, " ");
			key1 = (char *)K1.c_str();
			key2 = (char *)K2.c_str();
		}
		// key1, key2 로 이루어진 객체 생성
		Prefix *p = MakePrefix(key1, key2);
			
		// key1 과 key2 로 hash한 index에 노드가 없으면 처음 노드 만든다
		unsigned int index = Hash(key1, key2);
		Node *&n = htable[index];
		if (n == NULL) {
			Node *newN = MakeNode(p);
			n = newN;
			// suffix 있으면 추가
			if (suffix != NULL) {
				Suffix *s = MakeSuffix(suffix);
				n->data->suf = s;
				n->data->sumFreq++;
			}
		}
		// hash한 index에 노드가 존재한다면 연결시킨다
		else {
			Node *head = n;				// 해쉬테이블에 해당하는 노드의 첫 노드
			Node *before = NULL;		// n을 뒤따라가는 노드
			bool hasSamePrefix = false;
			while (head != NULL) {		// 노드를 순회한다
				// 이때, prefix의 워드와 key가 일치한다면
				if (strcmp(head->data->pword1.c_str(), key1) == 0 && strcmp(head->data->pword2.c_str(), key2) == 0) {
					// tokenizing된 suffix가 있다면 추가, 없으면 그냥 빠져나감
					if (suffix != NULL) {
						Prefix *now = head->data;		// 현재 prefix를 가리킴
						bool hasSameSuffix = false;
						// suffix가 없었다면 생성
						if (now->suf == NULL) {
							Suffix *s = MakeSuffix(suffix);
							now->suf = s;
							now->sumFreq++;
						}
						// suffix가 있다면 연결
						else {
							Suffix *beforeSuf = NULL;
							Suffix *s = now->suf;
							while (s != NULL) {
								// 이때, suffix가 동일한게 있다면 freq 높여준다
								if (strcmp(s->sword.c_str(), suffix) == 0) {
									s->freq++;
									now->sumFreq++;
									hasSameSuffix = true;
									break;
								}
								beforeSuf = s;
								s = s->next;
							}
							// suffix가 동일한게 없다면 뒤에 연결
							if (!hasSameSuffix) {
								Suffix *newSuffix = MakeSuffix(suffix);
								now->sumFreq++;
								beforeSuf->next = newSuffix;
							}
						}
					}
					hasSamePrefix = true;
					break;
				}
				before = head;
				head = head->next;
			}
			// prefix가 동일한게 없다면 뒤에 연결
			if (!hasSamePrefix) {
				// 여기서도 suffix가 존재한다면 추가해줘야지
				if (suffix != NULL) {
					Suffix *s = MakeSuffix(suffix);
					p->suf = s;
					p->sumFreq++;
				}
				Node *&newNode = MakeNode(p);
				before->next = newNode;
			}
		}
		token = strtok(NULL, " ");
	}
	return true;
}
Prefix* MakePrefix(char *key1, char *key2)
{
	Prefix *p = new Prefix;
	p->pword1 = key1;
	p->pword2 = key2;
	p->sumFreq = 0;
	p->suf = NULL;
	return p;
}
Suffix* MakeSuffix(char *suffix)
{
	Suffix *s = new Suffix;
	s->sword = suffix;
	s->freq = 1;
	s->next = NULL;
	return s;
}
Node*& MakeNode(Prefix *p)
{
	Node *newNode = new Node;
	newNode->data = p;
	newNode->next = NULL;
	return newNode;
}
void PrintHashTable()
{

	Node *node;
	for(int i = 0 ; i < NHASH ; i++) {
		node = htable[i];
		if (node == NULL)
			continue;
		Prefix *p = node->data;
		cout << "#" << i << ": " << "Prefix: " << p->pword1 << ", " << p->pword2 << "\t\t";
		cout << "Suffix: ";
		Suffix *s = p->suf;
		while (s != NULL) {
			cout << s->sword << "(" << s->freq << "), ";
			s = s->next;
		}
		cout << endl;
	}
}	 // DEBUG용 함수
void PrintFakeText()
{
	int randIndex = rand() % NHASH;
	cout << htable[randIndex]->data->pword1 << " ";
	cout << htable[randIndex]->data->pword2 << " ";
	MakeFakeText(htable[randIndex]->data, 0);
}
void MakeFakeText(Prefix *prefix, int count)
{
	if (prefix == NULL || count == 1000)
		return;
	Suffix* randSuffix;
	randSuffix = GetRandomSuffix(prefix);
	if (randSuffix == NULL)
		return;
	cout << randSuffix->sword << " ";		// prefix의 suffix중 하나를 랜덤 출력
	// 마지막 두 단어로 구성된 prefix 찾는다
	Prefix *nextPrefix = FindPrefix(prefix->pword2.c_str(), randSuffix->sword.c_str());
	return MakeFakeText(nextPrefix, count+1);
	
}
Suffix* GetRandomSuffix(Prefix *p)
{
	int i = 0;
	int randNum;
	int sequenceNum;
	vector<int> weightArray;		// 각 suffix의 누적빈도를 저장하는 배열
	Suffix *suf = p->suf;
	if (suf == NULL || p->sumFreq == 0)
		return NULL;
	while (suf != NULL) {
		if (i == 0) {
			// 첫 suffix의 freq는 그냥 추가한다
			weightArray.push_back(suf->freq);
			suf = suf->next; i++;
			continue;
		}
		// 현재 suffix의 freq와 이전의 값을 누적하여 추가한다
		weightArray.push_back(suf->freq + weightArray.at(i - 1));
		suf = suf->next; i++;
	}
	randNum = rand() % p->sumFreq;		// 랜덤한 인덱스 선택 (0 ~ sumFreq-1)
	for (int j = 0; j < weightArray.size(); j++) {
		// 처음으로 randNum이 누적freq보다 작거나 같게 되는 인덱스(j)가 선택됨
		if (randNum <= weightArray.at(j)) {
			sequenceNum = j;
			break;
		}
	}
	// sequenceNum 번째로 나오는 suffix를 찾는다
	suf = p->suf;
	while (sequenceNum > 0) {
		suf = suf->next;
		sequenceNum--;
	}
	return suf;
}
Prefix* FindPrefix(const char *key1, const char *key2)
{
	unsigned int index = Hash(key1, key2);
	Node *n = htable[index];
	while (n != NULL) {
		// 주어진 key와 같은 prefix 찾으면 반환
		if (strcmp(n->data->pword1.c_str(), key1) == 0 && strcmp(n->data->pword2.c_str(), key2) == 0) {
			return n->data;
		}
		n = n->next;
	}
	// 못 찾으면 NULL반환
	return NULL;
}
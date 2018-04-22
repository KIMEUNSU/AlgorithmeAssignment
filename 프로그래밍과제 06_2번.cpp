#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#define MAX 500
#define LEFT 1
#define RIGHT 2
using namespace std;

class Address;
class Node;

char *token;
char command[MAX];
vector<Address> address;
Node *head;

void ReadFile(FILE *fp);
void Print();
/* 이진 탐색 트리 */
void ReadFileByInsert(FILE *fp);
void ListInOrder(Node *x);
void PrintNodeData(Node *p);
void FindNodeByName(string s, Node *p);
void TraceNode(string s, Node *p);
void DeleteNode(string s);
Node* FindSuccessor(Node *p);
Node* FindMinimumNode(Node *p);
Node* FindMaximumNode(Node *p);
void SaveFile(FILE *fp, Node *x);
void GetFloordAndCeillingNodes(string s);
void FindFloorAndCeiling(Node *p, Node * &floor, Node * &ceil, string s);
string trim(string &s);
class Address {
public:
	// 이름, 회사, 주소, 우편번호, 전화번호, 이메일 주소
	string name, company, address, zipCode, phones, eMail;
	Address(string nam, string comp, string addr, string zip, string tel, string mail) {
		name = nam; company = comp; address = addr; zipCode = zip; phones = tel; eMail = mail;
	}
	Address() {}
};
class Node {
public:
	Address data;
	Node* left;
	Node* right;
	Node* parent;
	Node(string n, string c, string a, string z, string t, string m) {
		data.name = n; data.company = c; data.address = a; data.zipCode = z; data.phones = t; data.eMail = m;
	}
};
struct sort_by_name {
	inline bool operator() (const Address& a1, const Address& a2) {
		return (a1.name < a2.name);
	}
};
struct sort_by_address {
	inline bool operator() (const Address& a1, const Address& a2) {
		return (a1.address < a2.address);
	}
};
int main()
{
	FILE *fp;
	while (1) {
		cout << "$ ";
		gets_s(command, MAX);
		token = strtok(command, " ");
		if (strcmp(token, "read") == 0) {
			token = strtok(NULL, " ");
			fp = fopen(token, "r");
			if (fp == NULL) {
				cout << "Fail to open the file" << endl;
				break;
			}
			//ReadFile(fp);
			ReadFileByInsert(fp);
		}
		/*else if (strcmp(token, "sort") == 0) {
			token = strtok(NULL, " ");
			if (strcmp(token, "by") != 0)
				break;
			token = strtok(NULL, " ");
			if (strcmp(token, "name") == 0) {
				// sort by name
				sort(address.begin(), address.end(), sort_by_name());
			}
			else if (strcmp(token, "address") == 0) {
				// sort by address
				sort(address.begin(), address.end(), sort_by_address());
			}
		}*/
		/*else if (strcmp(token, "print") == 0) {
			Print();
		}*/
		else if (strcmp(token, "exit") == 0)
			break;
		// 이진 탐색트리 활용
		else if (strcmp(token, "list") == 0) {
			ListInOrder(head);
		}
		else if (strcmp(token, "find") == 0) {
			token = strtok(NULL, " ");
			if (token == NULL)
				break;
			FindNodeByName(token, head);
		}
		else if (strcmp(token, "trace") == 0) {
			token = strtok(NULL, " ");
			if (token == NULL)
				break;
			TraceNode(token, head);
		}
		else if (strcmp(token, "delete") == 0) {
			token = strtok(NULL, " ");
			if (token == NULL)
				break;
			DeleteNode(token);
		}
		else if (strcmp(token, "save") == 0) {
			token = strtok(NULL, " ");
			FILE *sfp = fopen(token, "w");
			SaveFile(sfp, head);
		}
		else
			continue;
	}
	return 0;
}
void ReadFile(FILE *fp)
{
	char buffer[MAX];
	char *token;
	int i = 0, j = 0;
	string data[6];
	while (!feof(fp)) {
		fgets(buffer, MAX, fp);
		token = strtok(buffer, "|");
		while (token != NULL) {
			data[i++] = token;
			token = strtok(NULL, "|");
		}
		Address p = Address(data[0], data[1], data[2], data[3], data[4], data[5]);
		address.push_back(p); i = 0;
	}
}
void Print()
{
	for (int i = 0; i < address.size(); i++) {
		cout << address.at(i).name << endl;
		cout << "\t" << "Company: " << address.at(i).company << endl;
		cout << "\t" << "Address: " << address.at(i).address << endl;
		cout << "\t" << "Zipcode: " << address.at(i).zipCode << endl;
		cout << "\t" << "Phones: " << address.at(i).phones << endl;
		cout << "\t" << "Email: " << address.at(i).eMail << endl;
	}
}
/* 이진 검색 트리 */
void ReadFileByInsert(FILE *fp)
{
	char buffer[MAX];
	char *token;
	string data[6];
	while (!feof(fp)) {
		int i = 0, child = 0;
		fgets(buffer, MAX, fp);
		token = strtok(buffer, "|");
		while (token != NULL) {
			data[i++] = token;
			token = strtok(NULL, "|");
		}
		// data 들의 whiteSpace를 제거한다
		for (int j = 0; j < 6; j++) {
			data[j] = trim(data[j]);
		}
		// head 없다면 만든다
		if (head == NULL) {
			Node *p = new Node(data[0], data[1], data[2], data[3], data[4], data[5]);
			p->parent = NULL; p->left = NULL; p->right = NULL;
			head = p;
		}
		//head 있다면 추가한다
		else if (head != NULL) {
			Node *y = NULL;				// 한 칸씩 뒤따라오는 포인터
			Node *x = head;
			// x가 끝에 도달할때까지 내려간다
			while (x != NULL ) {
				y = x;
				if (data[0] < x->data.name) {
					x = x->left;
					child = LEFT;
				}
				else {
					x = x->right;
					child = RIGHT;
				}
			}
			x = new Node(data[0], data[1], data[2], data[3], data[4], data[5]);
			x->parent = y; x->left = NULL; x->right = NULL; 
			if (child == LEFT) {
				y->left = x;
			}
			else if (child == RIGHT) {
				y->right = x;
			}
			x->parent = y;
		}
	}
}
void ListInOrder(Node *x)
{
	if (x != NULL) {
		ListInOrder(x->left);
		PrintNodeData(x);
		ListInOrder(x->right);
	}
}
void PrintNodeData(Node *p)
{
	cout << p->data.name << endl;
	cout << "\t" << "Company: " << p->data.company << endl;
	cout << "\t" << "Address: " << p->data.address << endl;
	cout << "\t" << "Zipcode: " << p->data.zipCode << endl;
	cout << "\t" << "Phones: " << p->data.phones << endl;
	cout << "\t" << "Email: " << p->data.eMail << endl;
}
void FindNodeByName(string s, Node *p)
{
	if (p == NULL) {
		cout << "'" << s << "'" << " : Not Founded" << endl;
		GetFloordAndCeillingNodes(s);
		return;
	}
	else if (s < p->data.name) {
		p = p->left;
	}
	else if (s > p->data.name) {
		p = p->right;
	}
	else if (s._Equal(p->data.name)) {
		PrintNodeData(p);
		return;
	}
	FindNodeByName(s, p);
}
string trim(string &s)
{
	if (s.length() == 0)
		return s;
	
	size_t beg = s.find_first_not_of(" ");
	size_t end = s.find_last_not_of(" ");
	if (beg == string::npos)
		return "";
	return string(s, beg, end - beg + 1);
}
void TraceNode(string s, Node *p)
{
	if (p == NULL) {
		cout << "Not Founded" << endl;
		return;
	}
	cout << p->data.name << endl;
	if (s < p->data.name) {
		p = p->left;
	}
	else if (s > p->data.name) {
		p = p->right;
	}
	else if (s.compare(p->data.name) == 0) {
		return;
	}
	TraceNode(s, p);
}
void DeleteNode(string s)
{
	Node *p = head;
	while (p != NULL) {
		if (s < p->data.name) {
			p = p->left;
		}
		else if (s > p->data.name) {
			p = p->right;
		}
		else if (s.compare(p->data.name) == 0) {
			Node *y;
			Node *x;
			if (p->left == NULL || p->right == NULL)
				y = p;
			else
				y = FindSuccessor(p);
			if (y->left != NULL)
				x = y->left;
			else
				x = y->right;
			if (x != NULL)
				x->parent = y->parent;
			if (y->parent == NULL) {
				head = x;
			}
			else if (y == y->parent->left)
				y->parent->left = x;
			else
				y->parent->right = x;

			if (y != p)
				p->data = y->data;
			return;
		}
	}
	cout << "Not Founded" << endl;
}
Node* FindSuccessor(Node *p) {
	if (p == NULL)
		return NULL;
	Node *right = p->right;
	if (right != NULL) {
		// 오른족 부트리가 존재할경우 오른쪽 부트리의 최소값이 Successor 가 된다.
		return FindMinimumNode(right);
	}
	Node *y = p->parent;
	while (y != NULL && p == y->right) {
		p = y;
		y = y->parent;
	}
	return y;
}
Node* FindMinimumNode(Node *p) {
	while (p->left != NULL) {
		p = p->left;
	}
	return p;
}
Node* FindMaximumNode(Node *p) {
	while (p->right != NULL) {
		p = p->right;
	}
	return p;
}
void SaveFile(FILE *fp, Node *x) 
{
	char c[] = " | ";
	char *cr = "\n";
	if (x != NULL) {
		SaveFile(fp, x->left);
		string s = x->data.name;
		fputs(x->data.name.c_str(), fp);
		fputs(c, fp);
		fputs(x->data.company.c_str(), fp);
		fputs(c, fp);
		fputs(x->data.address.c_str(), fp);
		fputs(c, fp);
		fputs(x->data.zipCode.c_str(), fp);
		fputs(c, fp);
		fputs(x->data.phones.c_str(), fp);
		fputs(c, fp);
		fputs(x->data.eMail.c_str(), fp);
		SaveFile(fp, x->right);
	}
}
void GetFloordAndCeillingNodes(string s) {
	Node *floor, *ceil;
	FindFloorAndCeiling(head, floor, ceil, s);
	if (floor == NULL) {
		cout << "Floor don't exist" << endl;
	}
	if (ceil == NULL) {
		cout << "Ceil don't exist" << endl;
	}
	cout << "Floor: " << floor->data.name << endl;
	cout << "Ceiling: " << ceil->data.name << endl;
}
void FindFloorAndCeiling(Node *p, Node * &floor, Node * &ceil, string s)
{
	// base case
	if (p == NULL)
		return;
	// if node with key's value is found, both floor and ceil is equal to current node
	if (p->data.name.compare(s) == 0) {
		floor = p;
		ceil = p;
	}
	// if given key is less than the root node, recuse for left subtree
	else if (s < p->data.name) {
		// update ceil to current node before recursing in left subtree
		ceil = p;
		FindFloorAndCeiling(p->left, floor, ceil, s);
	}
	// if given key is more than the root node, recuse for right subtree
	else {
		floor = p;
		FindFloorAndCeiling(p->right, floor, ceil, s);
	}
}
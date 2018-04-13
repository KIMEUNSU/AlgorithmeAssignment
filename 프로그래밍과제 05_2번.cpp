#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#define MAX 200
using namespace std;

class Address;

char *token;
char command[MAX];
vector<Address> address;

void ReadFile(FILE *fp);
void Print();
class Address {
public:
	// 이름, 회사, 주소, 우편번호, 전화번호, 이메일 주소
	string name, company, address, zipCode, phones, eMail;
	Address(string nam, string comp, string addr, string zip, string tel, string mail) {
		name = nam; company = comp; address = addr; zipCode = zip; phones = tel; eMail = mail;
	}
	Address() {}
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
		if (strcmp(token, "read")==0) {
			token = strtok(NULL, " ");
			fp = fopen(token, "r");
			if (fp == NULL) {
				cout << "Fail to open the file" << endl;
				break;
			}
			ReadFile(fp);
		}
		else if (strcmp(token, "sort") == 0) {
			token = strtok(NULL, " ");
			if (strcmp(token, "by") != 0)
				break;
			token = strtok(NULL, " ");
			if (strcmp(token, "name")==0) {
				// sort by name
				sort(address.begin(), address.end(), sort_by_name());
			}
			else if (strcmp(token, "address")==0) {
				// sort by address
				sort(address.begin(), address.end(), sort_by_address());
			}
		}
		else if (strcmp(token, "print") == 0) {
			Print();
		}
		else if (strcmp(token, "exit") == 0)
			break;
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
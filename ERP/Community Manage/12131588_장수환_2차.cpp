#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<fstream>
#include <sstream>
#include <iterator>
#include<list>
using namespace std;

class Member //ȸ�� Ŭ����
{
public:
	int id;
	string name;
	string phone;
	int reader = -1;
	Member() {

	}
	Member(int i, string n, string p) {
		id = i;
		name = n;
		phone = p;
	}

	void setReader(int r) {
		reader = r;
	}
};
int N, M;
Member arrayByID[5001]; //ID�� index�� ��� Member �迭
vector<list<int>> adjacencyList(5001); //���� ȸ������ ���Ƴ��� ��������Ʈ
vector<list<int>> reverse_adjacencyList(5001); //���������� ���� ȸ������ ��Ƴ��� ��������Ʈ
void init_loadData(){ //ó�� ȸ������ �Է¹޴� �Լ�
	cout << "�Է������� �̸��� �Է��ϼ��� : ";
	fstream inputFile("list_1000.txt", ios_base::in);
	string line;
	
	if (inputFile.is_open()) {
		inputFile >> N >> M;
		
		int id;
		string name, phone, temp;
		for (int i = 0; i < N; i++) {
			inputFile >> id >> name >> phone;
			arrayByID[id] = Member(id, name, phone); //id�� index ��� �ش� ĭ�� ��� ����
		}
		int A_id, B_id;
		for (int i = 0; i < M; i++) { //A�� B�� follow ���� ���� ��������Ʈ ����
			inputFile >> A_id >> B_id;
			adjacencyList[A_id].push_back(B_id);
			reverse_adjacencyList[B_id].push_back(A_id);
		}
	}
	else {
		cout << "fail to read file" << endl;
	}

	inputFile.close();

}
int visited[5001]; //��� �湮 ����
int C; //SCC ����
stack<int> st;
void dfs(int cur) {

	for (auto it = adjacencyList[cur].begin(); it != adjacencyList[cur].end(); it++) {

		int id = *it;
		if (!visited[id]) {
			visited[id] = 1;
			dfs(id);
		}

	}
	st.push(cur);
}
void reverseDFS(int cur, int reader) { //������ DFS & ������ ����

	for (auto it = reverse_adjacencyList[cur].begin(); it != reverse_adjacencyList[cur].end(); it++) {

		int id = *it;
		if (!visited[id]) {
			arrayByID[id].setReader(reader);
			visited[id] = 1;
			reverseDFS(id, reader);
		}

	}
}
void Kosaraju() {//������ dfs ���� �� stack�� ��� ���Ҹ� pop�ϸ鼭 ������ dfs �����ϸ鼭 readerã�� & SCC ���� ����

	C = 0;
	st = stack<int>();
	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			visited[i] = 1;
			dfs(i);
		}
	}
	memset(visited, 0, sizeof(visited));
	
	while (!st.empty()) {
		int cur = st.top();
		st.pop();
		if (!visited[cur]) {
			C++;
			visited[cur] = 1;
			arrayByID[cur].setReader(cur);
			reverseDFS(cur, cur);
		}
	}
	memset(visited, 0, sizeof(visited));
}
void accessLeaderInfo(int id) { //id�� ���� ����� ���� �׷��� ���� ���� ���
	int readerId;
	readerId = arrayByID[id].reader;
	cout << readerId << " " << arrayByID[readerId].name << " " << arrayByID[readerId].phone << endl;
}
void changeFollowing(int A_id, int B_id) { //following ����

	int findFlag = 0; //following ���� �÷���
	for (auto it = adjacencyList[A_id].begin(); it != adjacencyList[A_id].end(); it++) {

		int id = *it;
		if (id == B_id) { //���� following ����Ʈ�� B id�� �ִٸ�
			adjacencyList[A_id].erase(it); //following ����
			findFlag = 1;
			break;
		}
	}
	if (findFlag) { //�����⵵ Ȯ��
		for (auto it = reverse_adjacencyList[B_id].begin(); it != reverse_adjacencyList[B_id].end(); it++) {

			int id = *it;
			if (id == A_id) {
				reverse_adjacencyList[B_id].erase(it);
				break;
			}
		}
	}
	else {//following ���ϰ� ���� �� following����
		adjacencyList[A_id].push_back(B_id);
		reverse_adjacencyList[B_id].push_back(A_id);
	}
	Kosaraju(); //�׷����� ����Ǿ����Ƿ� �ٽ� kosaraju ����
	cout << arrayByID[A_id].reader << endl;
}
vector<string> readCommand() {

	string str;
	getline(cin, str);
	if (str.length() == 0)
		getline(cin, str);

	istringstream buf(str);
	istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end);
	return tokens;
}
//�� ������ ���� ��� ����
void execute(vector<string> command) {

	string symbol = command[0];
	if (symbol == "T") {
		accessLeaderInfo(stoi(command[1]));
	}
	else if (symbol == "A") {
		changeFollowing(stoi(command[1]), stoi(command[2]));
	}
	else if (symbol == "0") {

		cout << C << endl;
		exit(0);
	}
}
int main() {

	ios::sync_with_stdio(false);
	init_loadData();
	Kosaraju();
	vector<string> command;
	while (1) {
		command = readCommand();
		execute(command);
	}
}

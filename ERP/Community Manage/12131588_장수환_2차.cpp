#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<fstream>
#include <sstream>
#include <iterator>
#include<list>
using namespace std;

class Member //회원 클래스
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
Member arrayByID[5001]; //ID를 index를 삼는 Member 배열
vector<list<int>> adjacencyList(5001); //인접 회원들을 남아놓는 인접리스트
vector<list<int>> reverse_adjacencyList(5001); //역방향으로 인접 회원들을 담아놓는 인접리스트
void init_loadData(){ //처음 회원들을 입력받는 함수
	cout << "입력파일의 이름을 입력하세요 : ";
	fstream inputFile("list_1000.txt", ios_base::in);
	string line;
	
	if (inputFile.is_open()) {
		inputFile >> N >> M;
		
		int id;
		string name, phone, temp;
		for (int i = 0; i < N; i++) {
			inputFile >> id >> name >> phone;
			arrayByID[id] = Member(id, name, phone); //id를 index 삼아 해당 칸에 멤버 저장
		}
		int A_id, B_id;
		for (int i = 0; i < M; i++) { //A와 B의 follow 구현 위한 인접리스트 생성
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
int visited[5001]; //노드 방문 여부
int C; //SCC 갯수
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
void reverseDFS(int cur, int reader) { //역방향 DFS & 리더를 저장

	for (auto it = reverse_adjacencyList[cur].begin(); it != reverse_adjacencyList[cur].end(); it++) {

		int id = *it;
		if (!visited[id]) {
			arrayByID[id].setReader(reader);
			visited[id] = 1;
			reverseDFS(id, reader);
		}

	}
}
void Kosaraju() {//정방향 dfs 실행 후 stack에 담긴 원소를 pop하면서 역방향 dfs 실행하면서 reader찾기 & SCC 갯수 증가

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
void accessLeaderInfo(int id) { //id를 가진 멤버가 속한 그룹의 리더 정보 출력
	int readerId;
	readerId = arrayByID[id].reader;
	cout << readerId << " " << arrayByID[readerId].name << " " << arrayByID[readerId].phone << endl;
}
void changeFollowing(int A_id, int B_id) { //following 변경

	int findFlag = 0; //following 여부 플래그
	for (auto it = adjacencyList[A_id].begin(); it != adjacencyList[A_id].end(); it++) {

		int id = *it;
		if (id == B_id) { //만약 following 리스트에 B id가 있다면
			adjacencyList[A_id].erase(it); //following 해제
			findFlag = 1;
			break;
		}
	}
	if (findFlag) { //역방향도 확인
		for (auto it = reverse_adjacencyList[B_id].begin(); it != reverse_adjacencyList[B_id].end(); it++) {

			int id = *it;
			if (id == A_id) {
				reverse_adjacencyList[B_id].erase(it);
				break;
			}
		}
	}
	else {//following 안하고 있을 때 following해줌
		adjacencyList[A_id].push_back(B_id);
		reverse_adjacencyList[B_id].push_back(A_id);
	}
	Kosaraju(); //그래프가 변경되었으므로 다시 kosaraju 실행
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
//각 쿼리에 따라 모듈 실행
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

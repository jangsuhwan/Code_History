#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <queue>
using namespace std;

const int BLACK = 0;
const int RED = 1;
long areaValue[1001][1001];
long areaHost[1001][1001];
int updateFlag; //멤버의 현재금액이 변동된 경우를 확인하는 플래그

class Details //회원의 최근 변동 내역에 대한 클래스
{
public:
	int flag; //증감
	long change; //변동 금액
	Details()
	{
		flag = -1;
		change = -1;
	}
	Details(int f, long c)
	{
		flag = f;
		change = c;
	}
};

class Member //회원 클래스
{
public:
	long ID;
	int laterInserted;
	string name;
	string phone;
	int grade;
	long money;
	vector<Details> details;
	void setPrimaryInfo(long i, long m) {
		ID = i;
		money = m;
	}
};

class Node
{
public:
	int color = RED; //초기에 들어오는 모든 노드들의 색깔은 RED
	long height = 0;
	Member* member;
	Node* parent = NULL;
	Node* rc = NULL;
	Node* lc = NULL;
	~Node() {
		delete parent;
		delete rc;
		delete lc;
		delete(member);
	}
};
class RBTree
{
public:

	int insert(Node* root, Node* newNode);
	Node* search(Node* root, long ID, int h);
	int check(Node* newNode);
	int getSiblingColor(Node* newNode);
	void reColor(Node* newNode);
	void reConstruct(Node* newNode);
	void LL_Rotation(Node* parent);
	void RR_Rotation(Node* parent);
	void LR_Rotation(Node* cur);
	void RL_Rotation(Node* cur);
};

bool CompareData(const Member* A, const Member* B)
{
	return (A->money < B->money) ||
		((A->money == B->money) && (A->ID > B->ID));
}
void quickSort(vector<Member*>& array, int low, int high)
{
	int i = low;
	int j = high;

	Member* pivot = array[(i + j) / 2];
	Member* temp;

	while (i <= j)
	{
		while (CompareData(pivot, array[i]))
			i++;

		while (CompareData(array[j], pivot))
			j--;

		if (i <= j)
		{
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i++;
			j--;
		}
	}
	if (j > low)
		quickSort(array, low, j);
	if (i < high)
		quickSort(array, i, high);
}

vector<Member*> sortByMoneyAndID; //회원들을 돈과 ID순으로 정렬
RBTree* tree;
Node* root;

int RBTree::insert(Node* root, Node* newNode) { //회원을 RBTree에 넣는 함수

	int duplicateFlag = 1; //회원이 이미 있는지 확인하는 플래그

	if (root->member->ID > newNode->member->ID) { //새로 들어오는 회원 ID가 더 작을 경우 왼쪽으로 이동
		if (root->lc == NULL) { //왼쪽 자식이 없다면 왼쪽에 삽입
			root->lc = newNode;
			newNode->parent = root;
			return duplicateFlag = 1;
		}
		else {
			duplicateFlag = insert(root->lc, newNode);
		}
	}
	else if (root->member->ID < newNode->member->ID) {//새로 들어오는 회원 ID가 더 클 경우 오른쪽으로 이동
		if (root->rc == NULL) {//왼쪽 자식이 없다면 오른쪽에 삽입
			root->rc = newNode;
			newNode->parent = root;
			return duplicateFlag = 1;
		}
		else {
			duplicateFlag = insert(root->rc, newNode);
		}
	}
	else {
		return duplicateFlag = 0;
	}
	return duplicateFlag;
}

Node* RBTree::search(Node* root, long ID, int h) {//특정 회원을 ID를 기반으로 검색

	Node* findNode = new Node();
	findNode->height = -1;//findNode의 높이가 -1로 유지 되있다면 찾는 데 실패
	if (root->member->ID > ID) {//ID를 기준으로 왼쪽, 오른쪽 결정
		if (root->lc == NULL) {
			return findNode;
		}
		else {
			findNode = search(root->lc, ID, h += 1);
		}
	}
	else if (root->member->ID < ID) {
		if (root->rc == NULL) {
			return findNode;
		}
		else {
			findNode = search(root->rc, ID, h += 1);
		}
	}
	else {//찾는 ID와 현재 노드의 ID가 같다면 찾았으므로 해당 노드의 깊이 설정 후 반환
		  //cout << root->member->ID << endl;
		findNode = root;
		findNode->height = h;
		return findNode;
	}
	return findNode;
}

//check parent and child color
int RBTree::check(Node* cur) {

	if (cur->parent->color == RED && cur->color == RED)
		return 1;
	else
		return 0;
}

//조카의 색깔을 검사
int RBTree::getSiblingColor(Node* cur) {

	Node* parent = cur->parent;
	Node* ancester = parent->parent;

	if (ancester->rc == parent) {
		return ancester->lc == NULL ? BLACK : ancester->lc->color;
	}
	else {
		return ancester->rc == NULL ? BLACK : ancester->rc->color;
	}

}

//조카의 색깔이 빨간색이면 reColoring실행
void RBTree::reColor(Node* cur) {

	Node* parent = cur->parent;
	Node* ancester = parent->parent;

	ancester->color = ancester->parent == NULL ? BLACK : RED;
	ancester->lc->color = BLACK;
	ancester->rc->color = BLACK;
}

//왼쪽으로 linear하게 이룬 구조 일때
//부모와 조상의 색깔을 바꾸고 reconstruct
//노드 바꿔줄 때 각 노드의 parent 설정
void RBTree::LL_Rotation(Node* parent)
{
	Node* ancester = parent->parent;
	Node* temp = ancester->parent;
	ancester->lc = parent->rc;
	if (parent->rc != NULL)
		parent->rc->parent = ancester;
	parent->rc = ancester;
	ancester->parent = parent;
	parent->color = BLACK;
	ancester->color = RED;
	parent->parent = temp;
	if (temp != NULL) {
		if (temp->member->ID < parent->member->ID) {
			temp->rc = parent;
		}
		else
			temp->lc = parent;
	}
}
//오른쪽으로 linear하게 이룬 구조 일때
//부모와 조상의 색깔을 바꾸고 reconstruct
//노드 바꿔줄 때 각 노드의 parent 설정
void RBTree::RR_Rotation(Node* parent)
{
	Node* ancester = parent->parent;
	Node* temp = ancester->parent;
	ancester->rc = parent->lc;
	if (parent->lc != NULL)
		parent->lc->parent = ancester;
	parent->lc = ancester;
	ancester->parent = parent;
	parent->color = BLACK;
	ancester->color = RED;
	parent->parent = temp;

	if (temp != NULL) {
		if (temp->member->ID < parent->member->ID) {
			temp->rc = parent;
		}
		else
			temp->lc = parent;
	}
}
//구조가 왼쪽 오른쪽 구조일때 linear형태로 만든 후 방향에 따라 LL 또는 RR을 호출
//변형에 따라 parent 설정
void RBTree::LR_Rotation(Node* cur)
{
	Node* parent = cur->parent;
	Node* ancester = parent->parent;

	parent->rc = cur->lc;
	if (cur->lc != NULL)
		cur->lc->parent = parent;
	cur->lc = parent;
	parent->parent = cur;
	ancester->lc = cur;
	cur->parent = ancester;

	LL_Rotation(cur);
}
//LR과 마찬가지 메커니즘
void RBTree::RL_Rotation(Node* cur)
{
	Node* parent = cur->parent;
	Node* ancester = parent->parent;

	parent->lc = cur->rc;
	if (cur->rc != NULL)
		cur->rc->parent = parent;
	cur->rc = parent;
	parent->parent = cur;
	ancester->rc = cur;
	cur->parent = ancester;

	RR_Rotation(cur);
}
//조카의 색깔이 검은색일경우 reConstructing
void RBTree::reConstruct(Node* cur) {

	Node* parent = cur->parent;
	Node* ancester = parent->parent;
	//부모와 새로 삽입된 노드의 방향에 따라 각각 변형 방법 선택
	if (cur->member->ID < ancester->member->ID)
	{
		if (cur->member->ID < parent->member->ID)
		{
			tree->LL_Rotation(parent);
		}
		else
		{
			tree->LR_Rotation(cur);
		}
		return;
	}
	if (cur->member->ID > ancester->member->ID)
	{
		if (cur->member->ID > parent->member->ID)
		{
			tree->RR_Rotation(parent);
		}
		else
		{
			tree->RL_Rotation(cur);
		}
		return;
	}
}
Member* getMember(string line) {

	//입력받은 string을 공백 기준으로 tokenize 하여 vector화
	istringstream s(line);
	vector<string> tokString(istream_iterator<string>{s}, istream_iterator<string>());

	//멤버를 만듬 
	Member* member = new Member();
	member->ID = stol(tokString[0]);
	member->name = tokString[1];
	member->phone = tokString[2];
	int ax = stoi(tokString[3]);
	int ay = stoi(tokString[4]);
	member->grade = stoi(tokString[5]);
	member->money = stol(tokString[6]);

	//해당 좌표에 주인이 없다면 현재 멤버를 주인으로 만듬
	if (areaHost[ax][ay] == 0) {
		areaHost[ax][ay] = member->ID;
	}

	return member;
}

//현재금액에 따라 등급 반환
int getGrade(long money) {

	if (money < 30000) {
		return 0;
	}
	else if (money < 50000) {
		return 1;
	}
	else if (money < 100000) {
		return 2;
	}
	else {
		return 3;
	}
}

//새로운 회원을 삽입해주고 나서 RBTree규칙에 따라 fix
void fix_RBTree(Node* newNode) {

	while (newNode->parent != NULL) {
		if (tree->check(newNode)) {
			if (tree->getSiblingColor(newNode) == RED) {
				tree->reColor(newNode);
			}
			else {
				tree->reConstruct(newNode);
			}
		}
		//newNode가 root 될 때
		if (newNode->parent == NULL) {
			root = newNode;
			break;
		}
		//부모가 root일 때
		if (newNode->parent->parent == NULL) {
			root = newNode->parent;
		}
		newNode = newNode->parent;
	}
}
//초기에 5만명 회원 read 후 RBTree에 삽입
void readDataFromFile() {

	cout << "입력파일의 이름을 입력하세요 : ";
	ifstream ifs("list_50k.txt");

	if (!ifs)
	{
		printf("Erro opening file.");
		exit(-1);
	}

	string line;
	//line by line으로 삽입
	while (getline(ifs, line)) {

		Node* newNode = new Node();
		newNode->member = getMember(line);
		newNode->member->grade = getGrade(newNode->member->money);
		sortByMoneyAndID.push_back(newNode->member);

		//한번도 삽입이 안 이루어졌다면 해당 멤버를 루트로 설정 색깔은 BLACK
		if (root == NULL) {
			newNode->color = BLACK;
			root = newNode;
			continue;
		}
		tree->insert(root, newNode);
		fix_RBTree(newNode);
	}
	quickSort(sortByMoneyAndID, 0, sortByMoneyAndID.size() - 1);
	ifs.close();
}

//query를 공백기준으로 tokenize 후 벡터 화
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

//회원가입 메서드
void signUp(vector<string> command) {

	Member* member = new Member();
	member->ID = stol(command[1]);
	member->name = command[2];
	member->phone = command[3];
	member->grade = 0;
	member->money = 0;

	Node* newNode = new Node();
	newNode->member = member;

	//새로운 회원을 삽입 후 반환값에 따라 가입여부 판단
	//search 해서 삽입된 노드의 깊이를 알아낸다.
	int res = tree->insert(root, newNode);
	if (res == 0) {
		printf("%ld 0\n", tree->search(root, member->ID, 0)->height);
		delete(newNode);
	}
	else {
		fix_RBTree(newNode);
		printf("%ld 1\n", tree->search(root, member->ID, 0)->height);
		if (areaHost[stoi(command[4])][stoi(command[5])] == 0)
			areaHost[stoi(command[4])][stoi(command[5])] = member->ID;
		newNode->height = 0;
	}


}
//ID를 가진 회원의 정보 출력
void printInfoMember(long ID) {

	Node* findMember = tree->search(root, ID, 0);

	//높이가 -1이라면 해당 회원을 못 찾았으므로 not found 출력
	if (findMember->height == -1) {
		printf("Not found!\n");
	}
	else {
		Member* member = findMember->member;
		member->grade = getGrade(member->money);
		cout << member->name << " " << member->phone << " ";
		printf("%d %d %ld\n", member->grade, member->money, findMember->height);
	}
	findMember->height = 0;
}
//회원의 현재금액을 충전
void putCash(long ID, long addMoney) {

	//높이가 -1이라면 해당 회원을 못 찾았으므로 not found 출력
	Node* findMember = tree->search(root, ID, 0);
	if (findMember->height == -1) {
		printf("Not found!\n");
	}
	else {
		Member* member = findMember->member;
		member->money += addMoney;
		member->grade = getGrade(member->money);

		if (member->laterInserted) { //정렬 멤버 수 줄이기 위해 0원을 가진 멤버는 정렬하지 않는다.
			member->laterInserted = 0;
			sortByMoneyAndID.push_back(member);
		}

		//금액 충전 후 최근 금액 변동 내역에 추가
		Details detail(1, addMoney);
		(member->details).push_back(detail);

		printf("%d %d\n", findMember->height, member->grade);
		updateFlag = 1;
	}
	findMember->height = 0;
}

//상위 5명 출력
void printInfoTopFive() {

	if(updateFlag)
		quickSort(sortByMoneyAndID, 0, sortByMoneyAndID.size() - 1);

	//금액변동이 있을 때에만 멤버들 quicksort 초기에는 무조건 한번 해줌
	for (int i = 0; i < 5; i++) {
		printf("%ld %ld\n", sortByMoneyAndID[i]->ID, sortByMoneyAndID[i]->money);
	}
	updateFlag = 0;
}
//최근 금액 변동 내역 출력
void printRecentlyDetails(long ID, int L) {

	//높이가 -1이라면 해당 회원을 못 찾았으므로 not found 출력
	Node* findMember = tree->search(root, ID, 0);
	if (findMember->height == -1) {
		printf("Not found!\n");
	}
	else {
		vector<Details> details = findMember->member->details;

		//사이즈가 0이라면 이 회원의 변동 내역이 없으므로 0 출력
		if (details.size() == 0) {
			printf("0\n");
		}
		int cnt = 0;
		//L개만큼 변동 내역들을 출력
		for (int i = details.size() - 1; (i >= 0) && cnt < L; i--)
		{
			printf("%d %ld\n", details[i].flag, details[i].change);
			cnt++;
		}
	}
	findMember->height = 0;
}

//땅을 사는 메서드
void buyArea(vector<string> command) {

	Node* buyer = tree->search(root, stol(command[1]), 0);
	long buyerID = buyer->member->ID;
	int ax = stoi(command[2]);
	int ay = stoi(command[3]);
	long buyMoney = stol(command[4]);

	//땅값이 구매 가격보다 비싼경우나 구매자의 현재 금액이 구매 가격보다 낮은 경우
	if (areaValue[ax][ay] > buyMoney || buyer->member->money < buyMoney) {
		printf("0 %ld %ld\n", buyer->member->money, (areaHost[ax][ay] == 0 ? -1 : areaHost[ax][ay]));
	}
	else {
		//구매자가 땅을 살 수 있는 경우 
		long hostID = areaHost[ax][ay];
		if (hostID == 0);
		else {
			//땅 주인의 현재금액을 구매가격만큼 증가시키고 변동내역에 삽입
			Node* host = tree->search(root, hostID, 0);
			host->member->money += buyMoney;
			(host->member->details).push_back(Details(1, buyMoney));
			host->height = 0;
		}
		//구매자의 현재금액을 구매가격만큼 감소시키고 변동내역에 삽입
		areaHost[ax][ay] = buyerID;
		areaValue[ax][ay] = buyMoney;
		buyer->member->money -= buyMoney;
		(buyer->member->details).push_back(Details(0, buyMoney));

		printf("1 %ld %ld\n", buyer->member->money, areaHost[ax][ay]);
		updateFlag = 1;
		
	}
	buyer->height = 0;

}
//각 쿼리에 따라 모듈 실행
void execute(vector<string> command) {

	string symbol = command[0];
	if (symbol == "I") {
		signUp(command);
	}
	else if (symbol == "P") {
		printInfoMember(stol(command[1]));
	}
	else if (symbol == "A") {
		putCash(stol(command[1]), stol(command[2]));
	}
	else if (symbol == "F") {
		printInfoTopFive();
	}
	else if (symbol == "R") {
		printRecentlyDetails(stol(command[1]), stoi(command[2]));
	}
	else if (symbol == "B") {
		buyArea(command);
	}
	else if (symbol == "Q") {

		delete(tree);
		exit(0);
	}
}

int main() {

	readDataFromFile();
	vector<string> command;
	while (1) {
		command = readCommand();
		execute(command);
	}
}

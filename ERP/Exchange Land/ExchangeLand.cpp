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
int updateFlag; //����� ����ݾ��� ������ ��츦 Ȯ���ϴ� �÷���

class Details //ȸ���� �ֱ� ���� ������ ���� Ŭ����
{
public:
	int flag; //����
	long change; //���� �ݾ�
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

class Member //ȸ�� Ŭ����
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
	int color = RED; //�ʱ⿡ ������ ��� ������ ������ RED
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

vector<Member*> sortByMoneyAndID; //ȸ������ ���� ID������ ����
RBTree* tree;
Node* root;

int RBTree::insert(Node* root, Node* newNode) { //ȸ���� RBTree�� �ִ� �Լ�

	int duplicateFlag = 1; //ȸ���� �̹� �ִ��� Ȯ���ϴ� �÷���

	if (root->member->ID > newNode->member->ID) { //���� ������ ȸ�� ID�� �� ���� ��� �������� �̵�
		if (root->lc == NULL) { //���� �ڽ��� ���ٸ� ���ʿ� ����
			root->lc = newNode;
			newNode->parent = root;
			return duplicateFlag = 1;
		}
		else {
			duplicateFlag = insert(root->lc, newNode);
		}
	}
	else if (root->member->ID < newNode->member->ID) {//���� ������ ȸ�� ID�� �� Ŭ ��� ���������� �̵�
		if (root->rc == NULL) {//���� �ڽ��� ���ٸ� �����ʿ� ����
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

Node* RBTree::search(Node* root, long ID, int h) {//Ư�� ȸ���� ID�� ������� �˻�

	Node* findNode = new Node();
	findNode->height = -1;//findNode�� ���̰� -1�� ���� ���ִٸ� ã�� �� ����
	if (root->member->ID > ID) {//ID�� �������� ����, ������ ����
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
	else {//ã�� ID�� ���� ����� ID�� ���ٸ� ã�����Ƿ� �ش� ����� ���� ���� �� ��ȯ
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

//��ī�� ������ �˻�
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

//��ī�� ������ �������̸� reColoring����
void RBTree::reColor(Node* cur) {

	Node* parent = cur->parent;
	Node* ancester = parent->parent;

	ancester->color = ancester->parent == NULL ? BLACK : RED;
	ancester->lc->color = BLACK;
	ancester->rc->color = BLACK;
}

//�������� linear�ϰ� �̷� ���� �϶�
//�θ�� ������ ������ �ٲٰ� reconstruct
//��� �ٲ��� �� �� ����� parent ����
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
//���������� linear�ϰ� �̷� ���� �϶�
//�θ�� ������ ������ �ٲٰ� reconstruct
//��� �ٲ��� �� �� ����� parent ����
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
//������ ���� ������ �����϶� linear���·� ���� �� ���⿡ ���� LL �Ǵ� RR�� ȣ��
//������ ���� parent ����
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
//LR�� �������� ��Ŀ����
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
//��ī�� ������ �������ϰ�� reConstructing
void RBTree::reConstruct(Node* cur) {

	Node* parent = cur->parent;
	Node* ancester = parent->parent;
	//�θ�� ���� ���Ե� ����� ���⿡ ���� ���� ���� ��� ����
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

	//�Է¹��� string�� ���� �������� tokenize �Ͽ� vectorȭ
	istringstream s(line);
	vector<string> tokString(istream_iterator<string>{s}, istream_iterator<string>());

	//����� ���� 
	Member* member = new Member();
	member->ID = stol(tokString[0]);
	member->name = tokString[1];
	member->phone = tokString[2];
	int ax = stoi(tokString[3]);
	int ay = stoi(tokString[4]);
	member->grade = stoi(tokString[5]);
	member->money = stol(tokString[6]);

	//�ش� ��ǥ�� ������ ���ٸ� ���� ����� �������� ����
	if (areaHost[ax][ay] == 0) {
		areaHost[ax][ay] = member->ID;
	}

	return member;
}

//����ݾ׿� ���� ��� ��ȯ
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

//���ο� ȸ���� �������ְ� ���� RBTree��Ģ�� ���� fix
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
		//newNode�� root �� ��
		if (newNode->parent == NULL) {
			root = newNode;
			break;
		}
		//�θ� root�� ��
		if (newNode->parent->parent == NULL) {
			root = newNode->parent;
		}
		newNode = newNode->parent;
	}
}
//�ʱ⿡ 5���� ȸ�� read �� RBTree�� ����
void readDataFromFile() {

	cout << "�Է������� �̸��� �Է��ϼ��� : ";
	ifstream ifs("list_50k.txt");

	if (!ifs)
	{
		printf("Erro opening file.");
		exit(-1);
	}

	string line;
	//line by line���� ����
	while (getline(ifs, line)) {

		Node* newNode = new Node();
		newNode->member = getMember(line);
		newNode->member->grade = getGrade(newNode->member->money);
		sortByMoneyAndID.push_back(newNode->member);

		//�ѹ��� ������ �� �̷�����ٸ� �ش� ����� ��Ʈ�� ���� ������ BLACK
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

//query�� ����������� tokenize �� ���� ȭ
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

//ȸ������ �޼���
void signUp(vector<string> command) {

	Member* member = new Member();
	member->ID = stol(command[1]);
	member->name = command[2];
	member->phone = command[3];
	member->grade = 0;
	member->money = 0;

	Node* newNode = new Node();
	newNode->member = member;

	//���ο� ȸ���� ���� �� ��ȯ���� ���� ���Կ��� �Ǵ�
	//search �ؼ� ���Ե� ����� ���̸� �˾Ƴ���.
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
//ID�� ���� ȸ���� ���� ���
void printInfoMember(long ID) {

	Node* findMember = tree->search(root, ID, 0);

	//���̰� -1�̶�� �ش� ȸ���� �� ã�����Ƿ� not found ���
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
//ȸ���� ����ݾ��� ����
void putCash(long ID, long addMoney) {

	//���̰� -1�̶�� �ش� ȸ���� �� ã�����Ƿ� not found ���
	Node* findMember = tree->search(root, ID, 0);
	if (findMember->height == -1) {
		printf("Not found!\n");
	}
	else {
		Member* member = findMember->member;
		member->money += addMoney;
		member->grade = getGrade(member->money);

		if (member->laterInserted) { //���� ��� �� ���̱� ���� 0���� ���� ����� �������� �ʴ´�.
			member->laterInserted = 0;
			sortByMoneyAndID.push_back(member);
		}

		//�ݾ� ���� �� �ֱ� �ݾ� ���� ������ �߰�
		Details detail(1, addMoney);
		(member->details).push_back(detail);

		printf("%d %d\n", findMember->height, member->grade);
		updateFlag = 1;
	}
	findMember->height = 0;
}

//���� 5�� ���
void printInfoTopFive() {

	if(updateFlag)
		quickSort(sortByMoneyAndID, 0, sortByMoneyAndID.size() - 1);

	//�ݾ׺����� ���� ������ ����� quicksort �ʱ⿡�� ������ �ѹ� ����
	for (int i = 0; i < 5; i++) {
		printf("%ld %ld\n", sortByMoneyAndID[i]->ID, sortByMoneyAndID[i]->money);
	}
	updateFlag = 0;
}
//�ֱ� �ݾ� ���� ���� ���
void printRecentlyDetails(long ID, int L) {

	//���̰� -1�̶�� �ش� ȸ���� �� ã�����Ƿ� not found ���
	Node* findMember = tree->search(root, ID, 0);
	if (findMember->height == -1) {
		printf("Not found!\n");
	}
	else {
		vector<Details> details = findMember->member->details;

		//����� 0�̶�� �� ȸ���� ���� ������ �����Ƿ� 0 ���
		if (details.size() == 0) {
			printf("0\n");
		}
		int cnt = 0;
		//L����ŭ ���� �������� ���
		for (int i = details.size() - 1; (i >= 0) && cnt < L; i--)
		{
			printf("%d %ld\n", details[i].flag, details[i].change);
			cnt++;
		}
	}
	findMember->height = 0;
}

//���� ��� �޼���
void buyArea(vector<string> command) {

	Node* buyer = tree->search(root, stol(command[1]), 0);
	long buyerID = buyer->member->ID;
	int ax = stoi(command[2]);
	int ay = stoi(command[3]);
	long buyMoney = stol(command[4]);

	//������ ���� ���ݺ��� ��Ѱ�쳪 �������� ���� �ݾ��� ���� ���ݺ��� ���� ���
	if (areaValue[ax][ay] > buyMoney || buyer->member->money < buyMoney) {
		printf("0 %ld %ld\n", buyer->member->money, (areaHost[ax][ay] == 0 ? -1 : areaHost[ax][ay]));
	}
	else {
		//�����ڰ� ���� �� �� �ִ� ��� 
		long hostID = areaHost[ax][ay];
		if (hostID == 0);
		else {
			//�� ������ ����ݾ��� ���Ű��ݸ�ŭ ������Ű�� ���������� ����
			Node* host = tree->search(root, hostID, 0);
			host->member->money += buyMoney;
			(host->member->details).push_back(Details(1, buyMoney));
			host->height = 0;
		}
		//�������� ����ݾ��� ���Ű��ݸ�ŭ ���ҽ�Ű�� ���������� ����
		areaHost[ax][ay] = buyerID;
		areaValue[ax][ay] = buyMoney;
		buyer->member->money -= buyMoney;
		(buyer->member->details).push_back(Details(0, buyMoney));

		printf("1 %ld %ld\n", buyer->member->money, areaHost[ax][ay]);
		updateFlag = 1;
		
	}
	buyer->height = 0;

}
//�� ������ ���� ��� ����
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

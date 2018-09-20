#pragma once

typedef int LData;

typedef struct _node
{
	LData data;
	struct _node* next; // �ش� ����� ������ ����Ű�� ������
	struct _node* prev; // �ش� ����� ���� ����Ű�� ������
} Node;

typedef struct _list
{
	int numOfData; // �������� ��
	Node* head; // �� ���� ����Ű�� ������
	Node* tail; // �� �ڸ� ����Ű�� ������
} DoublyLinkedList; //������ũ�� ����Ʈ�� �����ϱ� ���� �Ӽ�

typedef DoublyLinkedList List;

void ListInit(List* list);

void Insert_Head(FILE* w, List* list, LData data);

void Find(FILE* w, List* list, LData data);

void Insert_Before(FILE* w, List* list, LData data1, LData data2);

void Insert_After(FILE* w, List* list, LData data1, LData data2);

void Replace(FILE* w, List* list, LData data1, LData data2);

void Erase(FILE* w, List* list, LData data);

void Next(FILE* w, List* list, LData data);

void Previous(FILE* w, List* list, LData data);

void Print(FILE* w, List* list);

void Exit();

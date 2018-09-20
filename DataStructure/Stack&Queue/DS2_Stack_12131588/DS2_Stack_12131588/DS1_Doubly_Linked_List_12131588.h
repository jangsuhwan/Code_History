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

void Insert_Head(List* list, LData data);

void Find(List* list, LData data);

void Insert_Before(List* list, LData data1, LData data2);

void Insert_After(List* list, LData data1, LData data2);

void Replace(List* list, LData data1, LData data2);

void Erase(List* list, LData data);

void Next(List* list, LData data);

void Previous(List* list, LData data);

void Print(List* list);

void Exit();

#pragma once

typedef int LData;

typedef struct _node
{
	LData data;
	struct _node* next; // 해당 노드의 다음을 가리키는 포인터
	struct _node* prev; // 해당 노드의 전을 가리키는 포인터
} Node;

typedef struct _list
{
	int numOfData; // 데이터의 수
	Node* head; // 맨 앞을 가리키는 포인터
	Node* tail; // 맨 뒤를 가리키는 포인터
} DoublyLinkedList; //더블리링크드 리스트를 구현하기 위한 속성

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

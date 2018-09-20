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

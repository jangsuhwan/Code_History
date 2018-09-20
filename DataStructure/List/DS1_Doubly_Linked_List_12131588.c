#include <stdio.h>
#include <stdlib.h>
#include "DS1_Doubly_Linked_List_12131588.h"

void ListInit(List* list) //리스트 속성 초기화
{
	list->head = NULL;
	list->tail = NULL;
	list->numOfData = 0;
}

void Insert_Head(FILE* w, List* list, LData data) //리스트 맨 앞에 삽입
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //새로운 노드를 할당해 매개변수 data를 넣는다.
	newNode->data = data;

	if (list->head == NULL)
	{
		list->head = newNode; //처음에는 newNode 하나만 있게되므로 head와 tail포인터를 newNode를 가리키게 한다.
		list->tail = newNode;
		newNode->next = NULL;
		newNode->prev = NULL;
	}
	else
	{
		newNode->next = list->head;
		list->head->prev = newNode;
		list->head = newNode;
		newNode->prev = NULL;
	}
	list->numOfData += 1;
	fprintf(w, "\n");
}

void Find(FILE* w, List* list, LData data) //data찾는 메서드
{
	Node* fNode = list->head; //head에서부터 tail까지 찾는다.

	while (fNode != NULL) //fNode가 NULL이라면 data가 존재하지 않으므로 -1출력
	{
		if (fNode->data == data)
		{
			fprintf(w, "%d\n", fNode->data);
			return;
		}
		fNode = fNode->next; //fNode를 한칸 이동
	}
	fprintf(w, "-1\n");
}

void Insert_Before(FILE* w, List* list, LData data1, LData data2) //data1 앞에 data2 삽입
{
	Node* fNode = list->head;
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data2;

	while (list->head != NULL)
	{
		if (fNode->data == data1)
		{
			newNode->next = fNode; //새로운노드 다음을 fNode 가리키고
			newNode->prev = fNode->prev; //새로운노드 전을 fNode 전 노드를 가리킨다.

			if (fNode == list->head) //만약 fNode가 헤드라면
				list->head = newNode; //새로운노드에 헤드로 가리킨다.

			else//아니라면
				fNode->prev->next = newNode;//fNode의 전노드의 다음을 새로운노드로 가리킨다.

			fNode->prev = newNode; //fNode의 전을 새로운 노드를 가리킨다.
			list->numOfData += 1;
			fprintf(w, "\n");
			return;
		}
		fNode = fNode->next;
	}
	fprintf(w, "-1\n");

}

void Insert_After(FILE* w, List* list, LData data1, LData data2) //data1 뒤에 data2삽입
{
	Node* fNode = list->head;
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data2;
	while (fNode != NULL)
	{
		if (fNode->data == data1)
		{ //fNode는 data1의 노드
			newNode->prev = fNode; //새로운 노드의 전을 fNode가리킨다.
			newNode->next = fNode->next; //새로운 노드의 다음을 fNode의 다음을 가리킨다.

			if (fNode == list->tail) //data1을 가지고 있는 노드가 tail이라면
				list->tail = newNode; // 새로운 노드에 tail 할당

			else
				fNode->next->prev = newNode;//아니라면 fNode의 다음노드의 전을 새로운노드 가리킴

			fNode->next = newNode; //fNode의 다음을 새로운 노드를 가리킴
			list->numOfData += 1;
			fprintf(w, "\n");
			return;
		}
		fNode = fNode->next;
	}
	fprintf(w, "-1\n");
}

void Replace(FILE* w, List* list, LData data1, LData data2)
{
	Node* fNode = list->head;
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data2;

	while (fNode != NULL)
	{
		if (fNode->data == data1)//data1의 노드를 찾앗으면 해당 노드의 데이터를 data2로 바꿈
		{
			fNode->data = data2;
			fprintf(w, "\n");
			return;
		}
		fNode = fNode->next;
	}
	fprintf(w, "-1\n");
}

void Erase(FILE* w, List* list, LData data)
{
	Node* fNode = list->head;
	while (fNode != NULL)
	{
		if (fNode->data == data)
		{
			if (list->numOfData == 1) //데이터의 수가 하나라면 해당 노드 삭제하고 head와 tail이 NULL을 가리키게 만듬
			{
				list->head = NULL;
				list->tail = NULL;
			}
			else if (fNode == list->head) //data의 노드가 헤드라면 헤드를 다음 노드로 할당
			{
				list->head = fNode->next;
				fNode->next->prev = NULL;
			}
			else if (fNode == list->tail) //data의 노드가 테일이라면 테일을 이전 노드로 할당
			{
				list->tail = fNode->prev;
				fNode->prev->next = NULL;
			}
			else//data의 노드가 중간에 있다면 그 노드의 앞뒤 노드를 연결시킨다.
			{
				fNode->next->prev = fNode->prev;
				fNode->prev->next = fNode->next;
			}
			list->numOfData -= 1;
			fNode = NULL; //data의 노드 메모리 해제
			free(fNode);
			fprintf(w, "\n");
			return;
		}
		fNode = fNode->next;
	}
	fprintf(w, "-1\n");
}
void Print(FILE* w, List* list)
{
	Node* cNode = list->head;
	while (cNode != NULL)
	{
		fprintf(w, "%d ", cNode->data);
		cNode = cNode->next;
	}
	fprintf(w, "\n");
}

void Next(FILE* w, List* list, LData data)
{
	Node* fNode = list->head;
	while (fNode->next != NULL) //다음 노드가 존재하지 않으면 -1 출력
	{
		if (fNode->data == data)
		{
			fprintf(w, "%d\n", fNode->next->data);
			return;
		}
		fNode = fNode->next;
	}
	fprintf(w, "-1\n");
}

void Previous(FILE* w, List* list, LData data)
{
	Node* fNode = list->head;
	while (fNode != NULL)//
	{
		if (fNode->prev !=NULL && fNode->data == data)//이전 노드가 존재하지 않으면 pass
		{
			fprintf(w, "%d\n", fNode->prev->data);
			return;
		}
		fNode = fNode->next;
	}
	fprintf(w, "-1\n");
}

void Exit()
{
	printf("프로그램 종료\n");
	exit(0);
}
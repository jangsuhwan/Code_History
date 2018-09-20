#include <stdio.h>
#include <stdlib.h>
#include "DS1_Doubly_Linked_List_12131588.h"

void ListInit(List* list) //����Ʈ �Ӽ� �ʱ�ȭ
{
	list->head = NULL;
	list->tail = NULL;
	list->numOfData = 0;
}

void Insert_Head(FILE* w, List* list, LData data) //����Ʈ �� �տ� ����
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //���ο� ��带 �Ҵ��� �Ű����� data�� �ִ´�.
	newNode->data = data;

	if (list->head == NULL)
	{
		list->head = newNode; //ó������ newNode �ϳ��� �ְԵǹǷ� head�� tail�����͸� newNode�� ����Ű�� �Ѵ�.
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

void Find(FILE* w, List* list, LData data) //dataã�� �޼���
{
	Node* fNode = list->head; //head�������� tail���� ã�´�.

	while (fNode != NULL) //fNode�� NULL�̶�� data�� �������� �����Ƿ� -1���
	{
		if (fNode->data == data)
		{
			fprintf(w, "%d\n", fNode->data);
			return;
		}
		fNode = fNode->next; //fNode�� ��ĭ �̵�
	}
	fprintf(w, "-1\n");
}

void Insert_Before(FILE* w, List* list, LData data1, LData data2) //data1 �տ� data2 ����
{
	Node* fNode = list->head;
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data2;

	while (list->head != NULL)
	{
		if (fNode->data == data1)
		{
			newNode->next = fNode; //���ο��� ������ fNode ����Ű��
			newNode->prev = fNode->prev; //���ο��� ���� fNode �� ��带 ����Ų��.

			if (fNode == list->head) //���� fNode�� �����
				list->head = newNode; //���ο��忡 ���� ����Ų��.

			else//�ƴ϶��
				fNode->prev->next = newNode;//fNode�� ������� ������ ���ο���� ����Ų��.

			fNode->prev = newNode; //fNode�� ���� ���ο� ��带 ����Ų��.
			list->numOfData += 1;
			fprintf(w, "\n");
			return;
		}
		fNode = fNode->next;
	}
	fprintf(w, "-1\n");

}

void Insert_After(FILE* w, List* list, LData data1, LData data2) //data1 �ڿ� data2����
{
	Node* fNode = list->head;
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data2;
	while (fNode != NULL)
	{
		if (fNode->data == data1)
		{ //fNode�� data1�� ���
			newNode->prev = fNode; //���ο� ����� ���� fNode����Ų��.
			newNode->next = fNode->next; //���ο� ����� ������ fNode�� ������ ����Ų��.

			if (fNode == list->tail) //data1�� ������ �ִ� ��尡 tail�̶��
				list->tail = newNode; // ���ο� ��忡 tail �Ҵ�

			else
				fNode->next->prev = newNode;//�ƴ϶�� fNode�� ��������� ���� ���ο��� ����Ŵ

			fNode->next = newNode; //fNode�� ������ ���ο� ��带 ����Ŵ
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
		if (fNode->data == data1)//data1�� ��带 ã������ �ش� ����� �����͸� data2�� �ٲ�
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
			if (list->numOfData == 1) //�������� ���� �ϳ���� �ش� ��� �����ϰ� head�� tail�� NULL�� ����Ű�� ����
			{
				list->head = NULL;
				list->tail = NULL;
			}
			else if (fNode == list->head) //data�� ��尡 ����� ��带 ���� ���� �Ҵ�
			{
				list->head = fNode->next;
				fNode->next->prev = NULL;
			}
			else if (fNode == list->tail) //data�� ��尡 �����̶�� ������ ���� ���� �Ҵ�
			{
				list->tail = fNode->prev;
				fNode->prev->next = NULL;
			}
			else//data�� ��尡 �߰��� �ִٸ� �� ����� �յ� ��带 �����Ų��.
			{
				fNode->next->prev = fNode->prev;
				fNode->prev->next = fNode->next;
			}
			list->numOfData -= 1;
			fNode = NULL; //data�� ��� �޸� ����
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
	while (fNode->next != NULL) //���� ��尡 �������� ������ -1 ���
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
		if (fNode->prev !=NULL && fNode->data == data)//���� ��尡 �������� ������ pass
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
	printf("���α׷� ����\n");
	exit(0);
}
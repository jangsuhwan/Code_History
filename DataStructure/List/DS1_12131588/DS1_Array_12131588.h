#pragma once

#define SIZE 100000 

typedef int AData;

typedef struct _array
{
	AData arr[SIZE]; //�����͸� ���� �� �ִ� 1000ũ���� �迭
	int numOfData;   //����Ʈ�� ����ִ� ������ ��
	int curPosition; //���� ����Ű�� �ִ� �ε���
} ArrayList;		//�迭�� �̿��ؼ� ����Ʈ�� ����

typedef ArrayList List;

void ListInit(List* list);												

void Insert_Head(FILE* w, List* list, AData data);							

void Find(FILE* w, List* list, AData data);

void Insert_Before(FILE* w, List* list, AData data1, AData data2);

void Insert_After(FILE* w, List* list, AData data1, AData data2);

void Replace(FILE* w, List* list, AData data1, AData data2);

void Erase(FILE* w, List* list, AData data);

void Next(FILE* w, List* list, AData data);

void Previous(FILE* w, List* list, AData data);

void Print(FILE* w, List* list);

void Exit();


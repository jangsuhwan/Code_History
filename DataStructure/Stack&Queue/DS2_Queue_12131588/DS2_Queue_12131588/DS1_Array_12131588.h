#pragma once

#define SIZE 100000

typedef int AData;

typedef struct _array
{
	AData arr[SIZE]; //�����͸� ���� �� �ִ� 100000ũ���� �迭
	int numOfData;   //����Ʈ�� ����ִ� ������ ��
	int curPosition; //���� ����Ű�� �ִ� �ε���
} ArrayList;		//�迭�� �̿��ؼ� ����Ʈ�� ����

typedef ArrayList List;

void ListInit(List* list);

void Insert_Head(List* list, AData data);

void Find(List* list, AData data);

void Insert_Before(List* list, AData data1, AData data2);

void Insert_After(List* list, AData data1, AData data2);

void Replace(List* list, AData data1, AData data2);

void Erase(List* list, AData data);

void Next(List* list, AData data);

void Previous(List* list, AData data);

void Print(List* list);

void Exit();



#pragma once

#define SIZE 100000

typedef int AData;

typedef struct _array
{
	AData arr[SIZE]; //데이터를 담을 수 있는 100000크기의 배열
	int numOfData;   //리스트에 들어있는 데이터 수
	int curPosition; //현재 가리키고 있는 인덱스
} ArrayList;		//배열을 이용해서 리스트를 구현

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



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DS1_Array_12131588.h"

void ListInit(List* list) //����Ʈ �Ӽ� �ʱ�ȭ
{
	list->curPosition = 0;
	list->numOfData = 0;    //�������� �� 0��
}

void Insert_Head(List* list, AData data) //�� �տ� ������ �����ϴ� �޼���
{
	if (list->numOfData == 0)
	{
		list->arr[0] = data;	//�� ���� 0��°�� ������ ����
		list->numOfData += 1;	//�������� �� ����
	}
	else
	{
		int data1 = list->arr[0];
		Insert_Before(list, data1, data);
	}

}

void Find(List* list, AData data) //������ ã�� �޼���
{
	int cur = list->curPosition;

	while (cur < list->numOfData) //�迭�� index�� ����Ű�� �ִ� �����Ͱ� �������� ���� �Ѿ������ ���� ����.
	{
		if (list->arr[cur] == data) //ã�� ������ ��ġ
		{
			printf("%d\n", list->arr[cur]); //�ش� ������ ������Ͽ� ���
			return;
		}
		(cur)++;
	}
	printf("-1\n");
}

void Insert_Before(List* list, AData data1, AData data2) // data1 �տ� data2 ���� �ϴ� �޼���
{
	int cur = list->curPosition;
	int arrTemp[SIZE];
	memcpy(arrTemp, list->arr, SIZE); //����Ʈ�� �ִ� �迭�� ���� ������ �迭 ����

	if ((list->numOfData) == SIZE) // ������ �� �ִ� �ִ� ���� Ȯ��
	{
		printf("-1\n");
		return;
	}

	while (cur < (list->numOfData))
	{
		if ((list->arr[cur]) == data1) //data1�� �ش��ϴ� curPosition set
		{

			for (int i = cur; i < list->numOfData; i++) //data1�� ����ִ� cur���� �տ� �ֱ� ���� ������ �迭�� cur���� ������ ����Ʈ �迭 ��ĭ �ڿ� �ٿ��ִ´�.
			{
				list->arr[i + 1] = arrTemp[i];
			}
			list->arr[cur] = data2; //���� data1�� �ִ� ���� data2 ����
			list->numOfData += 1;
			printf("\n");
			return;
		}
		cur++;
	}
	printf("-1\n");

}

void Insert_After(List* list, AData data1, AData data2) //data1 �ڿ� data2 ����
{
	int cur = list->curPosition;
	int arrTemp[SIZE];
	memcpy(arrTemp, list->arr, SIZE);
	if ((list->numOfData) == SIZE)
	{
		printf("-1\n");
		return;
	}
	while (cur < list->numOfData)
	{
		if ((list->arr[cur]) == data1)
		{
			if (cur == SIZE - 1)
				break;
			for (int i = cur + 1; i < list->numOfData; i++) //data1�� ����ִ� cur���� �ڿ� �ֱ� ���� ������ �迭�� cur+1���� ������ ����Ʈ �迭 ��ĭ �ڿ� �ٿ��ִ´�.
			{
				list->arr[i + 1] = arrTemp[i];
			}
			list->arr[cur + 1] = data2; //data1�� ����ִ� �� �ڿ� data2 ����
			list->numOfData += 1;
			return;
		}
		cur++;
	}
}

void Replace(List* list, AData data1, AData data2) // data1�� data2�� ��ü
{
	int cur = list->curPosition;

	while (cur < list->numOfData)
	{
		if (list->arr[cur] == data1)
		{
			list->arr[cur] = data2;
			printf("\n");
			return;
		}
		cur++;
	}

	printf("-1\n");
}

void Erase(List* list, AData data) //data����
{
	int cur = list->curPosition;

	while (cur < (list->numOfData))
	{
		if (list->arr[cur] == data)
		{
			for (int i = cur; i < (list->numOfData) - 1; i++) //����Ʈ�迭�� data�� ����ִ� cur���� �������� �����ǹ迭�� cur+1���� ������ ������ �ٿ��ִ´�.
			{
				list->arr[i] = list->arr[i + 1];
				list->numOfData -= 1;
				return;
			}
		}
		cur++;
	}
	printf("-1\n");
}
void Print(List* list) //������ ���
{
	int cur = list->curPosition;

	while (cur<(list->numOfData))
	{
		printf("%d ", list->arr[cur]);
		cur++;
	}
	printf("\n");
}

void Next(List* list, AData data) // data ���� data ���
{
	int cur = list->curPosition;
	while (cur < (list->numOfData))
	{
		if (list->arr[cur] == data)
		{
			if (cur == list->numOfData - 1) //�Ű������� ���� data�� ������ �����Ͷ�� Ż���ϰ� -1���
				break;
			printf("%d\n", list->arr[cur + 1]); //cur+1�� ������ ���
			return;
		}
		cur++;
	}
	printf("-1\n");
}

void Previous(List* list, AData data) // data ���� data ���
{
	int cur = list->curPosition;
	while (cur < (list->numOfData))
	{
		if (list->arr[cur] == data)
		{
			if (cur == 0) //�Ű������� ���� data�� ù��° �����Ͷ�� Ż���ϰ� -1 ���
				break;
			printf("%d\n", list->arr[cur - 1]); //cur-1�� ������ ���
			return;
		}
		cur++;
	}
	printf("-1\n");
}

void Exit() //���α׷� ����
{
	printf("���α׷� ����\n");
	exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "DS1_Doubly_Linked_List_12131588.h"

typedef int Data;

typedef struct _liststack
{
	List* plist;
} ListStack; //1�� ���� �� ������ ���� �迭����Ʈ ���

typedef ListStack Stack;

void StackInit(Stack* pstack)//���� �ʱ�ȭ �Լ�
{
	pstack->plist = (List*)malloc(sizeof(List)); //����Ʈ �Ҵ�
	ListInit(pstack->plist); //����Ʈ �ʱ�ȭ
}

void Empty(Stack* pstack) //������ ����ִ��� Ȯ�� �޼���
{
	if (pstack->plist->numOfData == 0) //���� 0���� ��������Ƿ� TRUE ��� 
	{
		printf("TRUE\n");
	}
	else //�ƴϸ� FALSE ���
		{
			printf("FALSE\n");
		}
	}

Data Top(Stack* pstack) //���� ���߿� �� ������ ��ȯ
{
	if (pstack->plist->numOfData == 0) //���� 0���� ��������Ƿ� -1 ��� 
	{
		return -1;
	}
	return pstack->plist->head->data;
}

Data Pop(Stack* pstack) //���� ���߿� ������ ���� �� ��ȯ
{
	if (pstack->plist->numOfData == 0) //���� 0���� ��������Ƿ� -1 ��� 
	{
		printf("-1\n");
		return -1;
	}
	Data data = pstack->plist->head->data;
	Erase(pstack->plist, data);
	return data;
}

void Push(Stack* pstack, Data pdata) //������ ���� �տ� ����
{
	Insert_Head(pstack->plist, pdata);
}

int Size(Stack* pstack) //������ ���� Ȯ�� �޼���
{
	return pstack->plist->numOfData;
}

void Reverse_Polish_Notation(Stack* pstack) 
{
	while (Size(pstack) != 0)//������ ������� ������ ����.
	{
		Pop(pstack);
	}
	getchar();
	char array[10000]; //array �迭�� ����� �� �޾ƿ���
	fgets(array, 10000, stdin);
	int i = 0;
	char c = array[0];  //�迭�� ����ִ� ù��° ����
	int num;   //���� ����
	char op = '0'; //������ ����
	
	while (1)
	{
		num = 0;
		c = array[i++]; //�迭�� ����ִ� �����͸� c�� ����
		if (c == '$')
			exit(0);
		if (isspace(c))
			continue;

		if (c == '-') //�������� ������ -���� �Ǻ�
		{
			if (!isspace(array[i])) //-���� �Ѱ��� �ƴ϶�� ����
			{
				int j = 1;
				int cur = i+1;
				while (isdigit(array[cur])) //���ڰ� ���ڸ��� ���� �˾Ƴ��� ����.
				{
					j *= 10;
					cur++;
				}
				cur = i;
				while (j != 0) //���� �ϳ��ϳ��� �ڸ����� ���ؼ� ����.
				{
					num += (array[cur] - '0') * j;
					j /= 10;
					cur++;
				}
				num = -num; //������ ����
				Push(pstack, num);
				i = cur;
				continue;
			}
		}
		if (isdigit(c)) //�� ���ڰ� ���ڸ� ���ÿ� �ִ´�.
		{
			int j = 1;
			int cur = i;
			while (isdigit(array[cur]))
			{
				j *= 10;
				cur++;
			}
			cur = i-1;
			while (j != 0)
			{
				num += (array[cur]-'0') * j;
				j /= 10;
				cur++;
			}
			
			Push(pstack, num);
			i = cur;
			continue;
		}
		
		op = c;
		//�����ڸ� ���ÿ��� �� ���� ���ڸ� ������ �����ڿ� ���� ����Ѵ�.
		int val1 = Pop(pstack); 
		int val2 = Pop(pstack);
		switch (op)
		{
			case '+':
				Push(pstack, val2 + val1);
				printf("%d\n", val2 + val1);
				break;
			case '-':
				Push(pstack, (val2 - val1));
				printf("%d\n", val2 - val1);
				break;
			case '*':
				Push(pstack, (val2 * val1));
				printf("%d\n", val2 * val1);
				break;
			case '/':
				Push(pstack, (val2 / val1));
				printf("%d\n", val2 / val1);
				break;
		}
		i++;
	}
	exit(0);
}
void freeList(Stack* pstack)
{
	free(pstack->plist);
}
int main(int argc, char** argv)
{
	Stack stack;
	StackInit(&stack);
	int methodNum = -1;
	while(1)
	{
		scanf_s("%d", &methodNum);
		Data pdata;
	switch (methodNum)
	{
		case 0:
			Reverse_Polish_Notation(&stack);
			break;
		case 1:
			Empty(&stack);
			break;
		case 2:
			printf("%d\n", Top(&stack));
			break;
		case 3:
			Pop(&stack);
			break;
		case 4:
			scanf_s("%d", &pdata);
			Push(&stack, pdata);
			break;
		case 5:
			printf("%d\n", Size(&stack));
			break;
		default:
			break;
	}
	}

	freeList(&stack);
	return 0;
}
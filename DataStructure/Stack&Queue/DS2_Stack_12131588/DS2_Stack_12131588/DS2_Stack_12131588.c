#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "DS1_Doubly_Linked_List_12131588.h"

typedef int Data;

typedef struct _liststack
{
	List* plist;
} ListStack; //1차 과제 때 구현해 놓은 배열리스트 사용

typedef ListStack Stack;

void StackInit(Stack* pstack)//스택 초기화 함수
{
	pstack->plist = (List*)malloc(sizeof(List)); //리스트 할당
	ListInit(pstack->plist); //리스트 초기화
}

void Empty(Stack* pstack) //스택이 비어있는지 확인 메서드
{
	if (pstack->plist->numOfData == 0) //갯수 0개면 비어있으므로 TRUE 출력 
	{
		printf("TRUE\n");
	}
	else //아니면 FALSE 출력
		{
			printf("FALSE\n");
		}
	}

Data Top(Stack* pstack) //가장 나중에 들어간 데이터 반환
{
	if (pstack->plist->numOfData == 0) //갯수 0개면 비어있으므로 -1 출력 
	{
		return -1;
	}
	return pstack->plist->head->data;
}

Data Pop(Stack* pstack) //가장 나중에 데이터 삭제 및 반환
{
	if (pstack->plist->numOfData == 0) //갯수 0개면 비어있으므로 -1 출력 
	{
		printf("-1\n");
		return -1;
	}
	Data data = pstack->plist->head->data;
	Erase(pstack->plist, data);
	return data;
}

void Push(Stack* pstack, Data pdata) //데이터 가장 앞에 삽입
{
	Insert_Head(pstack->plist, pdata);
}

int Size(Stack* pstack) //데이터 갯수 확인 메서드
{
	return pstack->plist->numOfData;
}

void Reverse_Polish_Notation(Stack* pstack) 
{
	while (Size(pstack) != 0)//스택이 비어있지 않으면 비운다.
	{
		Pop(pstack);
	}
	getchar();
	char array[10000]; //array 배열에 계산할 행 받아오기
	fgets(array, 10000, stdin);
	int i = 0;
	char c = array[0];  //배열에 들어있는 첫번째 문자
	int num;   //숫자 변수
	char op = '0'; //연산자 변수
	
	while (1)
	{
		num = 0;
		c = array[i++]; //배열에 들어있는 데이터를 c에 저장
		if (c == '$')
			exit(0);
		if (isspace(c))
			continue;

		if (c == '-') //음수인지 연산자 -인지 판변
		{
			if (!isspace(array[i])) //-문자 한개가 아니라면 음수
			{
				int j = 1;
				int cur = i+1;
				while (isdigit(array[cur])) //숫자가 몇자릿수 인지 알아내기 위함.
				{
					j *= 10;
					cur++;
				}
				cur = i;
				while (j != 0) //숫자 하나하나에 자릿수를 곱해서 합함.
				{
					num += (array[cur] - '0') * j;
					j /= 10;
					cur++;
				}
				num = -num; //음수로 만듬
				Push(pstack, num);
				i = cur;
				continue;
			}
		}
		if (isdigit(c)) //그 문자가 숫자면 스택에 넣는다.
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
		//연산자면 스택에서 두 개의 숫자를 꺼내서 연산자에 따라 계산한다.
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
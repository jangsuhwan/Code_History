#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DS1_Array_12131588.h"

void ListInit(List* list) //리스트 속성 초기화
{
	list->curPosition = 0;
	list->numOfData = 0;    //데이터의 수 0개
}

void Insert_Head(FILE* w, List* list, AData data) //맨 앞에 데이터 삽입하는 메서드
{
	if (list->numOfData == 0)
	{
		list->arr[0] = data;	//맨 앞인 0번째에 데이터 삽입
		list->numOfData += 1;	//데이터의 수 증가
		fprintf(w, "\n");		//출력파일에 빈칸 생성
	}
	else
	{
		int data1 = list->arr[0];
		Insert_Before(w, list, data1, data);
	}
	
}

void Find(FILE* w, List* list, AData data) //데이터 찾는 메서드
{
	int cur = list->curPosition;

	while (cur < list->numOfData) //배열에 index를 가리키고 있는 포인터가 데이터의 수가 넘어갈때까지 루프 돈다.
	{
		if (list->arr[cur] == data) //찾는 데이터 일치
		{
			fprintf(w, "%d\n", list->arr[cur]); //해당 데이터 출력파일에 출력
			return;
		}
		(cur)++;
	}
	fprintf(w, "-1\n");
}

void Insert_Before(FILE* w, List* list, AData data1, AData data2) // data1 앞에 data2 삽입 하는 메서드
{
	int cur = list->curPosition;
	int arrTemp[SIZE];
	memcpy(arrTemp, list->arr, SIZE); //리스트에 있는 배열과 같은 임의의 배열 생성

	if ((list->numOfData) == SIZE) // 삽입할 수 있는 최대 갯수 확인
	{
		fprintf(w, "-1\n");
		return;
	}
	
	while (cur < (list->numOfData)) 
	{
		if ((list->arr[cur]) == data1) //data1의 해당하는 curPosition set
		{
			
			for (int i = cur; i < list->numOfData; i++) //data1이 들어있는 cur보다 앞에 넣기 위해 임의의 배열에 cur부터 끝까지 리스트 배열 한칸 뒤에 붙여넣는다.
			{
				list->arr[i+1] = arrTemp[i];
			}
			list->arr[cur] = data2; //원래 data1에 있는 곳에 data2 삽입
			list->numOfData += 1;
			fprintf(w, "\n");
			return;
		}
		cur++;
	}
	fprintf(w, "-1\n");

}	

void Insert_After(FILE* w, List* list, AData data1, AData data2) //data1 뒤에 data2 삽입
{
	int cur = list->curPosition;
	int arrTemp[SIZE];
	memcpy(arrTemp, list->arr, SIZE);
	if ((list->numOfData) == SIZE)
	{
		fprintf(w, "-1\n");
		return;
	}
	while (cur < list->numOfData)
	{
		if ((list->arr[cur]) == data1)
		{
			if (cur == SIZE - 1)
				break;
			for (int i = cur+1; i < list->numOfData; i++) //data1이 들어있는 cur보다 뒤에 넣기 위해 임의의 배열에 cur+1부터 끝까지 리스트 배열 두칸 뒤에 붙여넣는다.
			{
				list->arr[i+1] = arrTemp[i];
			}
			list->arr[cur+1] = data2; //data1이 들어있는 곳 뒤에 data2 삽입
			list->numOfData += 1;
			fprintf(w, "\n");
			return;
		}
		cur++;
	}
	fprintf(w, "-1\n");
}

void Replace(FILE* w, List* list, AData data1, AData data2) // data1를 data2로 교체
{
	int cur = list->curPosition;

	while (cur < list->numOfData)
	{
		if (list->arr[cur] == data1) 
		{
			list->arr[cur] = data2;
			fprintf(w, "\n");
			return;
		}
		cur++;
	}
	
	fprintf(w, "-1\n");
}

void Erase(FILE* w, List* list, AData data) //data삭제
{
	int cur = list->curPosition;

	while (cur < (list->numOfData))
	{
		if (list->arr[cur] == data)
		{
			for (int i = cur; i < (list->numOfData)-1; i++) //리스트배열에 data가 들어있는 cur부터 끝까지를 임의의배열에 cur+1부터 끝까지 내용을 붙여넣는다.
			{
				list->arr[i] = list->arr[i + 1];
			}
			list->numOfData -= 1;
			fprintf(w, "\n");
			return;
		}
		cur++;
	}
	fprintf(w, "-1\n");
}
void Print(FILE* w, List* list) //데이터 출력
{
	int cur = list->curPosition;

	while (cur<(list->numOfData))
	{
		fprintf(w, "%d ", list->arr[cur]);
		cur++;
	}
	fprintf(w, "\n");
}

void Next(FILE* w, List* list, AData data) // data 다음 data 출력
{
	int cur = list->curPosition;
	while (cur < (list->numOfData))
	{
		if (list->arr[cur]==data)
		{
			if (cur == list->numOfData-1) //매개변수로 받은 data가 마지막 데이터라면 탈출하고 -1출력
				break;
			fprintf(w, "%d\n", list->arr[cur+1]); //cur+1의 데이터 출력
			return;
		}
		cur++;
	}
	fprintf(w, "-1\n");
}

void Previous(FILE* w, List* list, AData data) // data 이전 data 출력
{
	int cur = list->curPosition;
	while (cur < (list->numOfData))
	{
		if (list->arr[cur] == data)
		{
			if (cur == 0) //매개변수로 받은 data가 첫번째 데이터라면 탈출하고 -1 출력
				break;
			fprintf(w, "%d\n", list->arr[cur-1]); //cur-1의 데이터 출력
			return;
		}
		cur++;
	}
	fprintf(w, "-1\n");
}

void Exit() //프로그램 종료
{
	printf("프로그램 종료\n");
	exit(0);
}
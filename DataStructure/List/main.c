#include <stdio.h>
#include <stdlib.h>
#include "DS1_Array_12131588.h"

int main(int argc, char** argv)
{
	FILE* f;
	FILE* w;
	f = fopen(argv[1], "r");  
	w = fopen(argv[2], "w");

	if (f == NULL&& w== NULL)
	{
		printf("열기 실패");
		return 1;
	}

	List list;
	int num; //메서드 선택 변수
	int e1; //첫번째 데이터
	int e2; //두번째 데이터

	ListInit(&list); //리스트 초기화
	
	while (!feof(f))
	{
		//input.txt에서 한줄씩 확인해 num, e1, e2에 할당해 메서드 실행
		num = 0;
		e1 = 0;
		e2 = 0;
		fscanf(f, "%d", &num); //가장 앞에있는 숫자를 입력받는다 메서드 넘버
							   //num과 맞는 메서드 실행
		if (num == 9 || num == 0) //Print와 Exit메서드는 인자가 필요 없기 때문에 e1과 e2받지 않는다.
		{
			if (num == 9)
			{
				Print(w, &list);
			}
			else
			{
				fclose(f);
				fclose(w);
				Exit();
			}
		}
		else if (num == 3 || num == 4 || num == 5) //Insert와 Replace는 인자 두개 필요하기 때문에 입력받아온다.
		{
			fscanf(f, "%d", &e1);
			fscanf(f, "%d", &e2);
			switch (num)
			{
			case 3:
				Insert_Before(w, &list, e1, e2);
				break;
			case 4:
				Insert_After(w, &list, e1, e2);
				break;
			case 5:
				Replace(w, &list, e1, e2);
				break;
			}
		}
		else//그 외의 메서드는 한개의 인자만 필요하므로 e1을 받아와 메서드 실행
		{
			fscanf(f, "%d", &e1);
			switch (num)
			{
			case 1:
				Insert_Head(w, &list, e1);
				break;
			case 2:
				Find(w, &list, e1);
				break;
			case 6:
				Erase(w, &list, e1);
				break;
			case 7:
				Next(w, &list, e1);
				break;
			case 8:
				Previous(w, &list, e1);
				break;
			}
		}
	}
	fclose(f);
	fclose(w);
	return 0;
	
}

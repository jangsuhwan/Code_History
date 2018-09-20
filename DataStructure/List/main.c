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
		printf("���� ����");
		return 1;
	}

	List list;
	int num; //�޼��� ���� ����
	int e1; //ù��° ������
	int e2; //�ι�° ������

	ListInit(&list); //����Ʈ �ʱ�ȭ
	
	while (!feof(f))
	{
		//input.txt���� ���پ� Ȯ���� num, e1, e2�� �Ҵ��� �޼��� ����
		num = 0;
		e1 = 0;
		e2 = 0;
		fscanf(f, "%d", &num); //���� �տ��ִ� ���ڸ� �Է¹޴´� �޼��� �ѹ�
							   //num�� �´� �޼��� ����
		if (num == 9 || num == 0) //Print�� Exit�޼���� ���ڰ� �ʿ� ���� ������ e1�� e2���� �ʴ´�.
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
		else if (num == 3 || num == 4 || num == 5) //Insert�� Replace�� ���� �ΰ� �ʿ��ϱ� ������ �Է¹޾ƿ´�.
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
		else//�� ���� �޼���� �Ѱ��� ���ڸ� �ʿ��ϹǷ� e1�� �޾ƿ� �޼��� ����
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

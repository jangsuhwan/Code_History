#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

void FIFO(int(*)[2], int*, int);
void OPT(int(*)[2], int*, int);
void LRU(int(*)[2], int*, int);
void SCA(int(*)[2], int*, int);
int isPage(int(*)[2], int);
int findNextUse(int, int*, int);
int prevUsedPage(int(*)[2]);
int nextUsePage(int(*)[2]);
int findPage(int(*)[2], int);
int isFullPage(int(*)[2]);
int strToInt(char*);
int frame_size = 0;
int data_num = 0;

int main(int argc, char **argv) {

	FILE *fp = fopen(argv[2], "r");

	if (fp == NULL)
	{
		printf("fail Dataset.txt open");
		return 0;
	}

	int i = 0;
	char *pStr;
	char temp[200];


	while (!feof(fp))
	{
		pStr = fgets(temp, sizeof(temp), fp);
		data_num++;
	}
	int *data_set;
	frame_size = strToInt(argv[1]);
	int(*frame)[2];
	frame = malloc((frame_size * 1000) * sizeof(int));

	for (i = 0; i < frame_size; i++)
	{
		frame[i][0] = -1;
	}

	for (i = 0; i < frame_size; i++)
	{
		frame[i][1] = 0;
	}

	data_set = (int*)malloc(data_num * sizeof(int));
	fseek(fp, 0, SEEK_SET);

	for (i = 0; i < data_num; i++)
	{
		fscanf(fp, "%d", &data_set[i]);
	}

	printf("Select Page Replacement\n");
	printf("1. FIFO\n");
	printf("2. OPT\n");
	printf("3. LRU\n");
	printf("4. Second-Chance\n");
	int k;
	scanf("%d", &k);

	switch (k) {
	case 1: printf("FIFO\n"); FIFO(frame, data_set, data_num); break;
	case 2: printf("OPT\n"); OPT(frame, data_set, data_num); break;
	case 3: printf("LRU\n"); LRU(frame, data_set, data_num); break;
	case 4: printf("Second-Chance\n"); SCA(frame, data_set, data_num); break;
	default: printf("bye\n");  break;
	}

	free(frame);
	free(data_set);

	return 0;
}

int strToInt(char *str)
{
	int i = 0, num = 0, mul = 1;

	while (str[i] != '\0') i++;

	while (--i >= 0) {
		num += (str[i] - '0') * mul;
		mul *= 10;
	}
	return num;
}


void FIFO(int(*frame)[2], int *data_set, int data_num)
{
	int(*frame_temp)[2] = frame;
	int i = 0;
	int time = 0;
	int fault = 0;
	int counter = 0;
	while (counter < data_num)
	{
		if (isPage(frame_temp, *data_set))
		{
			if (isFullPage(frame_temp))
				i = prevUsedPage(frame_temp);

			frame_temp[i % frame_size][0] = *data_set;
			frame_temp[i % frame_size][1] = time;
			fault++;
			i++;
			printf("Number : %d\t", *data_set);
			for (int i = 0; i < frame_size; i++)
			{
				printf("%d\t", frame_temp[i][0]);
			}
			printf("\n");

		}
		else {
			printf("Number : %d\n", *data_set);
		}

		data_set++;
		time++;
		counter++;
	}

	printf("Page Fault : %d", fault);

}

void OPT(int(*frame)[2], int *data_set, int data_num)
{
	int(*frame_temp)[2] = frame;
	int i = 0;
	int fault = 0;
	int counter = 0;

	while (counter < data_num)
	{
		if (isPage(frame_temp, *data_set))
		{
			if (isFullPage(frame_temp))
				i = nextUsePage(frame_temp);

			frame_temp[i % frame_size][0] = *data_set;
			frame_temp[i % frame_size][1] = findNextUse(frame_temp[i % frame_size][0], data_set, counter);
			fault++;
			i++;
			printf("Number : %d\t", *data_set);
			for (int i = 0; i < frame_size; i++)
			{
				printf("%d\t", frame_temp[i][0]);
			}
			printf("\n");
		}
		else {
			int k = findPage(frame_temp, *data_set);
			frame_temp[k][1] = findNextUse(frame_temp[k][0], data_set, counter);
			i++;
			printf("Number : %d\n", *data_set);
		}
		data_set++;
		counter++;
	}

	printf("Page Fault : %d", fault);

}

void LRU(int(*frame)[2], int *data_set, int data_num)
{
	int(*frame_temp)[2] = frame;
	int i = 0;
	int time = 0;
	int fault = 0;
	int counter = 0;

	while (counter < data_num)
	{
		if (isPage(frame_temp, *data_set))
		{
			if (isFullPage(frame_temp))
				i = prevUsedPage(frame_temp);

			frame_temp[i % frame_size][0] = *data_set;
			frame_temp[i % frame_size][1] = time;
			fault++;
			i++;
			printf("Number : %d\t", *data_set);
			for (int i = 0; i < frame_size; i++)
			{
				printf("%d\t", frame_temp[i][0]);
			}
			printf("\n");
		}
		else
		{
			int k = findPage(frame_temp, *data_set);
			frame_temp[k][1] = time;
			i++;
			printf("Number : %d\n", *data_set);
		}
		data_set++;
		time++;
		counter++;
	}

	printf("Page Fault : %d", fault);

}
void SCA(int(*frame)[2], int *data_set, int data_num)
{
	int(*frame_temp)[2] = frame;
	int* ref_bit;
	ref_bit = (int*)malloc(frame_size * sizeof(int));
	for (int i = 0; i < frame_size; i++)
	{
		ref_bit[i] = 0;
	}
	int i = 0;
	int time = 0;
	int fault = 0;
	int counter = 0;

	while (counter < data_num)
	{
		if (isPage(frame_temp, *data_set))
		{
			if (!isFullPage(frame))
			{
				int k = findPage(frame_temp, -1);
				frame_temp[k % frame_size][0] = *data_set;
				frame_temp[k % frame_size][1] = time;
				ref_bit[k%frame_size] = 0;
				printf("Number : %d\t", *data_set);
				fault++;
				for (int i = 0; i < frame_size; i++)
				{
					printf("%d\t", frame_temp[i][0]);
				}
				printf("\n");
				i = k + 1;
			}
			else
			{
			A: if (ref_bit[i%frame_size] == 0)
			{
				frame_temp[i % frame_size][0] = *data_set;
				frame_temp[i % frame_size][1] = time;
				ref_bit[i%frame_size] = 0;
				fault++;
				printf("Number : %d\t", *data_set);
				for (int i = 0; i < frame_size; i++)
				{
					printf("%d\t", frame_temp[i][0]);
				}
				printf("\n");
				i += 1;
			}
			   else
			   {
				   ref_bit[i%frame_size] = 0;
				   i++;
				   goto A;
			   }
			}
		}
		else
		{
			int k = findPage(frame_temp, *data_set);
			ref_bit[k%frame_size] = 1;
			printf("Number : %d\t", *data_set);
			printf("\n");
		}
		data_set++;
		time++;
		counter++;
	}
	printf("Page Fault : %d", fault);
	free(ref_bit);
}

int isFullPage(int(*frame)[2])
{
	int full = 1;
	for (int i = 0; i < data_num; i++)
	{
		if (frame[i][0] == -1)
		{
			full = 0;
		}
	}
	return full;
}
int isPage(int(*frame)[2], int a)
{
	int isPage = 1;

	for (int i = 0; i < data_num; i++)
	{
		if (frame[i][0] == a)
		{
			isPage = 0;
		}
	}
	return isPage;
}
int findPage(int(*frame)[2], int a)
{
	for (int i = 0; i < frame_size; i++)
	{
		if (frame[i][0] == a)
			return i;
	}
}
int prevUsedPage(int(*frame)[2])
{
	int low = frame[0][1];
	for (int i = 1; i < frame_size; i++)
	{
		if (low > frame[i][1])
			low = frame[i][1];
	}
	for (int i = 0; i < frame_size; i++)
	{
		if (frame[i][1] == low)
		{
			return i;
		}
	}
}

int nextUsePage(int(*frame)[2])
{
	int max = frame[0][1];
	for (int i = 1; i < frame_size; i++)
	{
		if (max < frame[i][1])
			max = frame[i][1];
	}
	for (int i = 0; i < frame_size; i++)
	{
		if (frame[i][1] == max)
		{
			return i;
		}
	}
}

int findNextUse(int p, int *DataSet, int c)
{
	for (int j = c; j < data_num; j++)
	{
		++DataSet;
		if (p == *DataSet)
			return j;
	}
	return 1000;
}


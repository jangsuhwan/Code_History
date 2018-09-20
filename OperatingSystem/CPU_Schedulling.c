#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct process {
	int pid;
	int priority;
	int bursttime;
	int bursttmp;
	int arrivetime;
	int waitingtime;
}process;

void Input_Bursttime(FILE*, process*, int);
void Input_Priority(FILE*, process*, int);
void Sched_FCFS(process*[], int);
void Sched_SJF(process*[], int);
void Sched_RR(process*[], int);
void Sched_Priority(process*[], int);
void Sort(process*[], int, int);
void Execute(process*[], int);

int main()
{
	FILE *fp = fopen("C:\\text\\input.txt", "r");

	if (fp == NULL)
	{
		puts("fail file open");
		return -1;
	}

	char ch;
	int inputPNum = 0;
	int i = 0;

	while (1)
	{
		ch = fgetc(fp);
		if (isdigit(ch))
			break;
	}
	fseek(fp, -1, SEEK_CUR);
	fscanf(fp, "%d", &inputPNum);

	process *p[1000];
	for (i = 0; i<inputPNum; i++)
	{
		process* pr = (process*)malloc(sizeof(process) * 1);
		int id;
		fscanf(fp, "%d", &id);
		pr->pid = id;
		pr->arrivetime = 0;
		pr->waitingtime = 0;
		Input_Bursttime(fp, pr, i);
		pr->bursttmp = pr->bursttime;
		Input_Priority(fp, pr, i);
		p[i] = pr;
	}
	printf("Select Scheduling\n");
	printf("1. FCFS\n");
	printf("2. Non-preemtive SJF\n");
	printf("3. RR\n");
	printf("4. Priority\n");
	int k;
	scanf("%d", &k);
	switch (k) {
	case 1: printf("FCFS\n"); Sched_FCFS(p, inputPNum); break;
	case 2: printf(" Non-preemtive SJF\n"); Sched_SJF(p, inputPNum); break;
	case 3: printf("RR\n"); Sched_RR(p, inputPNum); break;
	case 4: printf("Priority\n"); Sched_Priority(p, inputPNum); break;
	}

	for (i = 0; i < inputPNum; i++)
	{
		free(p[i]);
	}

	fclose(fp);
	system("pause");
	return 0;
}

void Input_Priority(FILE* fp, process* pr, int i)
{
	while (1)
	{
		char ch;
		ch = fgetc(fp);
		if (!isspace(ch))
		{
			fseek(fp, -1, SEEK_CUR);
			fscanf(fp, "%d", &(pr->priority));
			break;
		}
	}
}

void Input_Bursttime(FILE* fp, process* pr, int i)
{
	while (1)
	{
		char ch;
		ch = fgetc(fp);
		if (!isspace(ch))
		{
			fseek(fp, -1, SEEK_CUR);
			fscanf(fp, "%d", &(pr->bursttime));
			break;
		}
	}
}

void Sched_FCFS(process* p[], int n)
{
	Execute(p, n);
}

void Sched_SJF(process* p[], int n)
{
	Sort(p, n, 1);
	Execute(p, n);
}

void Sort(process *p[], int n, int t)
{
	struct process *temp;
	int i = 0, j = 0;
	for (i = n; i > 1; i--)
	{
		for (j = 1; j < i; j++)
		{
			if (t == 1)
			{
				if (p[j - 1]->bursttime > p[j]->bursttime)
				{

					temp = p[j - 1];
					p[j - 1] = p[j];
					p[j] = temp;
				}
			}
			else
			{
				if (p[j - 1]->priority > p[j]->priority)
				{

					temp = p[j - 1];
					p[j - 1] = p[j];
					p[j] = temp;
				}
			}
		}
	}
}

void Sched_RR(process* p[], int n)
{
	int totalburst = 0;
	int count = 0;
	int i = 0;
	int totalwaiting = 0;

	while (1)
	{
		for (i = 0; i < n; i++)
		{
			int t_quantum = 10;
			if (p[i]->bursttmp == 0)
			{
				continue;
			}
			if (p[i]->bursttmp > t_quantum)
			{
				p[i]->bursttmp -= t_quantum;
			}
			else
			{
				t_quantum = p[i]->bursttmp;
				p[i]->bursttmp = 0;
				++count;
			}
			totalburst += t_quantum;
			p[i]->arrivetime = totalburst;
			if (count == n)
				break;
		}
		if (count == n)
			break;
	}
	for (i = 0; i < n; i++)
	{
		p[i]->waitingtime = p[i]->arrivetime - p[i]->bursttime;
		totalwaiting += p[i]->waitingtime;
		printf("Name : %d, Wait Time : %d, Burst Time : %d\n", p[i]->pid, p[i]->waitingtime, p[i]->bursttime);
	}
	printf("Total Burst Time : %d\n", totalburst);
	printf("Average Waiting time : %d", totalwaiting / n);
}

void Sched_Priority(process* p[], int n)
{
	Sort(p, n, 0);
	Execute(p, n);
}

void Execute(process* p[], int n)
{
	int arrtmp = 0;
	int totalwaiting = 0;
	int totalburst = 0;

	for (int i = 0; i < n; i++)
	{
		p[i]->waitingtime = arrtmp;
		totalburst += p[i]->bursttime;
		totalwaiting += p[i]->waitingtime;
		arrtmp = (p[i]->bursttime) + (p[i]->waitingtime);
		printf("Name : %d, Wait Time : %d, Burst Time : %d\n", p[i]->pid, p[i]->waitingtime, p[i]->bursttime);
	}

	printf("Total Burst Time : %d\n", totalburst);
	printf("Average Waiting time : %d", totalwaiting / n);
}
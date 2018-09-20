#include <stdio.h>
#include <stdlib.h>
#include "DS1_Array_12131588.h"

typedef struct _cQueue
{
	int front; //�� ���� ����Ű�� �ε���
	int rear;  //�� ���� ����Ű�� �ε���
	List* plist; //1������ �� ������ arraylist ���
} CQueue;

typedef CQueue Queue;

static int arrNode[10000][2]; //input.txt�� ���� ������ �Է¹޾Ƴ��� �迭
static int arrParent[10000]; //input.txt�� ���� �θ����͸� �޾Ƴ��� �迭

void QueueInit(Queue* pq) //����� Queue �ʱ�ȭ
{
	pq->front = 0;
	pq->rear = 0;
	pq->plist = (List*)malloc(sizeof(List));
	ListInit(pq->plist);
}
void Empty(Queue* pq) //����ִ��� Ȯ�� �޼���
{
	if (pq->plist->numOfData==0) //���� 0���� TRUE ���
	{
		printf("TRUE\n");
	}
	else//���� 0�� �ƴϸ� FALSE ���
	{
		printf("FALSE\n");
	}
}

AData Front(Queue* pq) //front�� ����Ű�� ������ ��ȯ
{
	if (pq->plist->numOfData==0) //�����Ͱ� �ƹ��͵� ������ -1 ��ȯ
		return -1;
	
	int cur = (pq->front+1)%SIZE; //�����͸� ��ĭ �ű�� ���� �迭�̹Ƿ� ũ��� ��ⷯ�ؼ� ��ġ�� ������ ����
	return (pq->plist->arr[cur]); 
}

AData Back(Queue* pq) //rear�� ����Ű��(�� ��) ������ ��ȯ
{
	if (pq->plist->numOfData == 0) //�����Ͱ� �ƹ��͵� ������ -1 ��ȯ
	{
		return -1;
	}
	int cur = pq->rear; 
	return (pq->plist->arr[cur]);
}

AData Pop(Queue* pq) //front�� ����Ű��(�� ��) ������ ����
{
	if (pq->plist->numOfData == 0) //�����Ͱ� �ƹ��͵� ������ -1 ��ȯ
	{
		printf("-1\n");
		return -1;
	}
	
	pq->front = (pq->front + 1) % SIZE; //�����͸� �� ĭ �ű��.

	AData data = pq->plist->arr[pq->front]; //��ȯ�� �� �� ������ �ӽ÷� �����ϰ� 
	pq->plist->arr[pq->front] = -1;			//����
	pq->plist->numOfData -= 1;              //���� �ϳ� ����
	return data;							//�ӽ� ������ ���� ������ ��ȯ
}

void Push(Queue* pq, AData data) //read�� ����Ű��(�� ��)�� ����
{
	if (pq->plist->numOfData == SIZE) //�� �������� �ƹ��͵� ���� �ʴ´�.
		return;

	pq->rear = (pq->rear+1) % SIZE;   //������ �� ĭ �ű��.
	pq->plist->arr[pq->rear] = data;  //rear�� ����Ű�� ������
	pq->plist->numOfData += 1; //���� �ϳ� ����
}

int Size(Queue* pq) //queue�� ����մ� ����
{
	return pq->plist->numOfData;
}

void Breath_First_Traversal(Queue* pq) //�ʺ� Ž�� �޼���
{
	int numOfNode = 0, root = 0, idx = 0; //�������� ������ ��Ʈ���, �迭�� ��ġ �ε���
	scanf_s("%d %d", &numOfNode, &root);

	for (int i = 0; i<numOfNode; i++)
	{
		scanf_s("%d %d %d", &arrParent[idx], &(arrNode[idx][0]), &(arrNode[idx][1])); //�Է����Ͽ� �࿡�� �θ���� �ڽĳ��� �� ���� �迭�� ���� ����
		idx++;
	}

	while (pq->plist->numOfData != 0) //������� ������ ����
	{
		Pop(pq);
	}

	if (numOfNode == 0)  //������ 0���� ����
		exit(0);
	else if (numOfNode ==1) //������ �Ѱ��� ��Ʈ �����͸� ��� �� ����
	{
		printf("%d", root);
		exit(0);
	}
	
	int parent = root; 
	int index;
	printf("%d ", root);

	while(1)
	{
		for (int i = 0; i < numOfNode; i++)
		{
			if (parent == arrParent[i]) //���� ť�� ���� �θ� �������� �ε����� ã�´�.
				index = i;
		}

		if (arrNode[index][0] != -1) //�Է¹��� 2���� �迭���� ã�� �ε��� �κп����� �ڽĵ��� �ִ´�. -1�̸� ���� �ʴ´�.
			Push(pq, arrNode[index][0]);
		if (arrNode[index][1] != -1)
			Push(pq, arrNode[index][1]);

		if (pq->plist->numOfData == 0) //ť�� �����Ͱ� ������ Ż��
			break;

		printf("%d ", Front(pq)); //ť�� ���� ������ �� ���� ���� �־��� ��� ���
		parent = Pop(pq); //�����鼭 ������ ã�� parent ����
	}
	exit(0);
}
void freeList(Queue* queue)
{
	free(queue->plist);
}

int main(int argc, char** argv)
{
	Queue queue;
	QueueInit(&queue);
	int methodNum = -1;
	while (1)
	{
		scanf_s("%d", &methodNum);
		int pdata;
		switch (methodNum)
		{
		case 0:
			Breath_First_Traversal(&queue);
			break;
		case 1:
			Empty(&queue);
			break;
		case 2:
			printf("%d\n", Front(&queue));
			break;
		case 3:
			printf("%d\n", Back(&queue));
			break;
		case 4:
			Pop(&queue);
			break;
		case 5:
			scanf_s("%d", &pdata);
			Push(&queue, pdata);
			break;
		case 6:
			printf("%d\n", Size(&queue));
			break;
		default:
			break;
		}
	}
	freeList(&queue);
	return 0;
}
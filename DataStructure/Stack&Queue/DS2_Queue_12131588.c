#include <stdio.h>
#include <stdlib.h>
#include "DS1_Array_12131588.h"

typedef struct _cQueue
{
	int front; //맨 앞을 가리키는 인덱스
	int rear;  //맨 뒤을 가리키는 인덱스
	List* plist; //1차과제 떄 구현한 arraylist 사용
} CQueue;

typedef CQueue Queue;

static int arrNode[10000][2]; //input.txt로 부터 데이터 입력받아놓을 배열
static int arrParent[10000]; //input.txt로 부터 부모데이터만 받아놓을 배열

void QueueInit(Queue* pq) //사용할 Queue 초기화
{
	pq->front = 0;
	pq->rear = 0;
	pq->plist = (List*)malloc(sizeof(List));
	ListInit(pq->plist);
}
void Empty(Queue* pq) //비어있는지 확인 메서드
{
	if (pq->plist->numOfData==0) //갯수 0개면 TRUE 출력
	{
		printf("TRUE\n");
	}
	else//갯수 0개 아니면 FALSE 출력
	{
		printf("FALSE\n");
	}
}

AData Front(Queue* pq) //front가 가리키는 데이터 반환
{
	if (pq->plist->numOfData==0) //데이터가 아무것도 없으면 -1 반환
		return -1;
	
	int cur = (pq->front+1)%SIZE; //포인터를 한칸 옮기고 원형 배열이므로 크기로 모듈러해서 위치를 적절히 조정
	return (pq->plist->arr[cur]); 
}

AData Back(Queue* pq) //rear가 가리키는(맨 뒤) 데이터 반환
{
	if (pq->plist->numOfData == 0) //데이터가 아무것도 없으면 -1 반환
	{
		return -1;
	}
	int cur = pq->rear; 
	return (pq->plist->arr[cur]);
}

AData Pop(Queue* pq) //front가 가리키는(맨 앞) 데이터 꺼냄
{
	if (pq->plist->numOfData == 0) //데이터가 아무것도 없으면 -1 반환
	{
		printf("-1\n");
		return -1;
	}
	
	pq->front = (pq->front + 1) % SIZE; //포인터를 한 칸 옮긴다.

	AData data = pq->plist->arr[pq->front]; //반환할 맨 앞 데이터 임시로 저장하고 
	pq->plist->arr[pq->front] = -1;			//제거
	pq->plist->numOfData -= 1;              //갯수 하나 줄임
	return data;							//임시 저장해 놓은 데이터 반환
}

void Push(Queue* pq, AData data) //read가 가리키는(맨 뒤)에 삽입
{
	if (pq->plist->numOfData == SIZE) //꽉 차있으면 아무것도 하지 않는다.
		return;

	pq->rear = (pq->rear+1) % SIZE;   //포인터 한 칸 옮긴다.
	pq->plist->arr[pq->rear] = data;  //rear가 가리키는 데이터
	pq->plist->numOfData += 1; //개수 하나 증가
}

int Size(Queue* pq) //queue에 들어잇는 갯수
{
	return pq->plist->numOfData;
}

void Breath_First_Traversal(Queue* pq) //너비 탐색 메서드
{
	int numOfNode = 0, root = 0, idx = 0; //데이터의 개수와 루트노드, 배열의 위치 인덱스
	scanf_s("%d %d", &numOfNode, &root);

	for (int i = 0; i<numOfNode; i++)
	{
		scanf_s("%d %d %d", &arrParent[idx], &(arrNode[idx][0]), &(arrNode[idx][1])); //입력파일에 행에서 부모노드와 자식노드들 두 개의 배열에 나눠 저장
		idx++;
	}

	while (pq->plist->numOfData != 0) //비어있지 않으면 비우기
	{
		Pop(pq);
	}

	if (numOfNode == 0)  //데이터 0개면 종료
		exit(0);
	else if (numOfNode ==1) //데이터 한개면 루트 데이터만 출력 후 종료
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
			if (parent == arrParent[i]) //먼저 큐에 넣을 부모 데이터의 인덱스를 찾는다.
				index = i;
		}

		if (arrNode[index][0] != -1) //입력받은 2차원 배열에서 찾은 인덱스 부분에서의 자식들을 넣는다. -1이면 넣지 않는다.
			Push(pq, arrNode[index][0]);
		if (arrNode[index][1] != -1)
			Push(pq, arrNode[index][1]);

		if (pq->plist->numOfData == 0) //큐의 데이터가 없으면 탈출
			break;

		printf("%d ", Front(pq)); //큐에 넣은 데이터 중 가장 먼저 넣어진 노드 출력
		parent = Pop(pq); //꺼내면서 다음에 찾을 parent 설정
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
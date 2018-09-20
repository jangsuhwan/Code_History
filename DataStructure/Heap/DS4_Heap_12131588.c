//12131588 장수환
//4차 과제 Heap 구현
#include <stdio.h>

#define SIZE 100002
void HeapSort(int* arr, int size);
typedef int PriorityComp(int d1, int d2); //Priority function pointer

typedef struct heap
{
	PriorityComp* comp;
	int numOfData;
	int arr[SIZE];
} Heap;

void Init(Heap* h, PriorityComp* comp)//heap initialize(total data num 0, set Priority function)
{
	h->numOfData = 0;
	h->comp = comp;
}

int IsEmpty(Heap* h) // confirm empty heap
{
	if (h->numOfData == 0)
		return 1;
	else
		return 0;
}

int GetPIdx(int idx) //get index of parent
{
	return idx / 2;
}

int GetLCIdx(int idx) //get index of left child
{
	return idx * 2;
}

int GetRCIdx(int idx) //get index of right child
{
	return idx * 2 + 1;
}

int GetHighPriChildIdx(Heap* h, int idx)//get index of high priority child index
{
	if (GetLCIdx(idx) > h->numOfData)//if no child return 0;
		return 0;
	else if (GetLCIdx(idx) == h->numOfData)// if only have left child, then index of left child return
		return GetLCIdx(idx);
	else
	{
		if (h->comp(h->arr[GetLCIdx(idx)], h->arr[GetRCIdx(idx)])<0) //using priority fuction, priority compare left child and right child, return high priority child index
			return GetRCIdx(idx);
		else
			return GetLCIdx(idx);
	}
}

void Insert(Heap* h, int data) //insert data in heap
{
	int idx = h->numOfData + 1; //start from last index

	while (idx != 1) //if index is 1, priority of data is the highest in heap
	{
		if (h->comp(data, h->arr[GetPIdx(idx)]) > 0) //if priority of data is higher than parent, exchange parent and data
		{
			h->arr[idx] = h->arr[GetPIdx(idx)];
			idx = GetPIdx(idx);
		}
		else
			break;
	}
	h->arr[idx] = data;
	h->numOfData += 1;
}

void Delete(Heap* h) //delete data in heap
{
	int rData = h->arr[1]; //highest priority is deleted
	int lastElem = h->arr[h->numOfData]; //last element replace index 1, and find its proper position

	int pIdx = 1;
	int cIdx;

	while (cIdx = GetHighPriChildIdx(h, pIdx)) //priority compare with childs, and if its priority is low, go down
	{
		if (h->comp(lastElem, h->arr[cIdx]) >= 0)
			break;
		h->arr[pIdx] = h->arr[cIdx];
		pIdx = cIdx;
	}
	h->arr[pIdx] = lastElem;
	h->numOfData -= 1;
}

int nPriorityComp(int d1, int d2) //compare priority
{
	return d2 - d1;
}
void Top(Heap* h) //get highest priority in heap
{
	printf("%d\n", h->arr[1]);
}
void PriQueue(Heap* h, PriorityComp pc) //Priority Queue initailize method
{
	Init(h, pc);
}

void Push(Heap* h, int data)//Priority Queue data insert method
{
	Insert(h, data);
}

void Pop(Heap* h) //Priority Queue data delete method
{
	Delete(h);
}
void Print(Heap* h)//print with BFS
{
	for (int i = 1; i <= h->numOfData; i++)
	{
		printf("%d ", h->arr[i]);
	}
	printf("\n");
}
void swap(int* data, int* data2)
{
	int temp = *data;
	*data = *data2;
	*data2 = temp;
}
void Heapification(int* arr, int size)//unsorted array transform to heap
{
	int start = size / 2; //leaf node는 heap이므로 그 다음 노드부터 조절
	int hPri = 0;

	for (int i = start; i >= 1; i--)
	{
		int cur = i;
		while (cur * 2 <= size)
		{
			if (cur * 2 + 1 <= size)
			{
				if (arr[cur * 2] < arr[cur * 2 + 1])
					hPri = cur * 2;
				else
					hPri = cur * 2 + 1;
			}
			else
				hPri = cur * 2;

			if (arr[hPri] < arr[cur])
				swap(&arr[hPri], &arr[cur]);
			cur = hPri;
		}

	}

	for (int i = 1; i <= start; i++)
	{
		int cur = i;
		while (cur * 2 <= size)
		{
			if (cur * 2 + 1 <= size)
			{
				if (arr[cur * 2] < arr[cur * 2 + 1])
					hPri = cur * 2;
				else
					hPri = cur * 2 + 1;
			}
			else
				hPri = cur * 2;

			if (arr[hPri] < arr[cur])
				swap(&arr[hPri], &arr[cur]);
			cur = hPri;
		}
	}
}

void HeapSort(int* arr, int capacity)//heap sort
{
	Heapification(arr, capacity);
	for (int i = 1; i <= capacity; i++)
		printf("%d ", arr[i]);
	printf("\n");

	int popData, pIdx = 1, cIdx = 1, size = capacity;
	while (capacity != 1)
	{
		popData = arr[1];//가장 높은 우선순위 데이터 pop
		arr[1] = arr[capacity];
		pIdx = 1;
		cIdx = 1;
		while (1)//root percolation down
		{
			if (2 * pIdx > capacity)
				break;

			if (2 * pIdx == capacity)// if only have left child, then index of left child
				cIdx = 2 * pIdx;

			else //else choice low priority
			{
				if (arr[2 * pIdx] < arr[2 * pIdx + 1])
					cIdx = 2 * pIdx;
				else
					cIdx = 2 * pIdx + 1;
			}

			if (arr[pIdx] > arr[cIdx])
				swap(&arr[pIdx], &arr[cIdx]);
			pIdx = cIdx;
		}
		arr[capacity] = popData;//pop한 데이터를 마지막 방에 채워줌
		capacity -= 1;
	}
	for (int i = 1; i <= size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


int main()
{
	Heap heap;
	PriQueue(&heap, nPriorityComp);
	int** arr = (int**)malloc(sizeof(int*));
	int method, data;
	int size = 0;
	while (1)
	{
		scanf_s("%d", &method);
		switch (method)
		{
		case 1:
			Top(&heap);
			break;
		case 2:
			Pop(&heap);
			break;
		case 3:
			scanf_s("%d", &data);
			Push(&heap, data);
			break;
		case 4:
			Print(&heap);
			break;
		case 5:
			scanf_s("%d", &size);
			arr[0] = (int*)malloc(sizeof(int*)*(size+1));
			for (int i = 1; i <= size; i++)
				scanf_s("%d", &arr[0][i]);
			HeapSort(arr[0], size);
			free(arr[0]);
			break;
		case 0:
			free(arr);
			return 0;
		}
	}
	
	return 0;
}
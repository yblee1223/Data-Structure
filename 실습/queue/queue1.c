#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef int size;
typedef int front;
typedef int rear;

typedef struct queue {
	size N;
	front f;
	rear r;
	int* arr;
}Queue;

// init func
void init_queue(Queue* q, int n);
void enqueue(Queue* q, int elem);
void dequeue(Queue* q);
void print(Queue* q);
int isEmpty(Queue* q);
int isFull(Queue* q);

void main()
{
	int q_n, n;
	char command;
	int elem;
	Queue Q;
	// input
	scanf("%d", &q_n);
	scanf("%d", &n);
	getchar();
	init_queue(&Q, q_n);

	// calc
	for (int i = 0; i < n; i++) {
		scanf("%c", &command);
		getchar();
		if (command == 'I') {
			scanf("%d", &elem);
			getchar();
			enqueue(&Q, elem);
		}
		else if (command == 'D')
			dequeue(&Q);
		else if (command == 'P')
			print(&Q);
	}
	return 0;
}

/*
예제
6
10
I 10
I 20
P
I 30
I 40
D
P
I 50
I 60
I 70

4
100
I 10
I 20
D
P
I 30
D
P
I 40
I 50
D
P
D
D
D
I 80
I 90
I 100
P


*/

/* --- func --- */
void init_queue(Queue* q, int n)
{
	//q->arr = (int*)calloc(n, sizeof(int));
	q->N = n;
	q->arr = (int*)calloc(q->N, sizeof(int));
	q->r = q->f = 0;
}

void enqueue(Queue* q, int elem)
{
	if (isFull(q)) {
		printf("overflow");
		print(q);
		exit(1);
	}
	// q->arr[(++q->r) % q->N] = elem;
	q->r = (q->r + 1) % q->N;
	q->arr[q->r] = elem;
	
}
void dequeue(Queue* q)
{
	if (isEmpty(q)) {
		printf("underflow");
		exit(1);
	}
	//q->arr[(++q->f) % q->N] = 0;
	q->f = (q->f + 1) % q->N;
	q->arr[q->f] = 0;
}
void print(Queue* q)
{
	for (int i = 0; i < q->N; i++) {
		printf(" %d", q->arr[i]);
	}
	printf("\n");
}
int isEmpty(Queue* q)
{
	return (q->f == q->r);
}

int isFull(Queue* q)
{
	return ((q->r + 1) % q->N == q->f);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct node {
	struct node* prev;
	struct node* next;
	int elem;
}Node;

typedef struct deque {
	Node *front;
	Node *rear;
	int N;
}Deque;

// init func
void init_deque(Deque* D);
Node* NewNode(int X);
void add_front(Deque* D, int X);
void add_rear(Deque* D, int X);
void delete_front(Deque* D);
void delete_rear(Deque* D);
void print(Deque* D);
int isEmpty(Deque* D);


void main()
{
	int n, x;
	
	Deque D;
	init_deque(&D);
	scanf("%d", &n);
	getchar();

	//calc
	for (int i = 0; i < n; i++) {
		char command[3];
		scanf("%s", command);
		if (!strcmp(command, "AF")) {
			scanf(" %d", &x);
			add_front(&D, x);
		}
		else if (!strcmp(command, "AR")) {
			scanf(" %d", &x);
			add_rear(&D, x);
		}
		else if (!strcmp(command, "DF")) {
			delete_front(&D);
		}
		else if (!strcmp(command, "DR")) {
			delete_rear(&D);
		}
		else if (!strcmp(command, "P")) {
			print(&D);
		}
		getchar();
	}
}
/*
예제
7
AF 10
AF 20
AR 30
P
DF
DR
P

15
AF 10
AF 20
AF 30
AR 40
AR 50
P
DF
DF
DR
P
DF
DR
DR

*/

/* --- func --- */
void init_deque(Deque* D)
{
	D->front = NULL;
	D->rear = NULL;
	D->N = 0;
}
Node* NewNode(int X)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->elem = X;
	p->next = NULL;
	p->prev = NULL;
}
void add_front(Deque* D, int X)
{
	Node* q = NewNode(X);
	q->next = D->front;
	q->prev = NULL;
	
	if (D->N == 0)
		D->rear = q;
	else
		D->front->prev = q;
	D->front = q;
	D->N++;
}
void add_rear(Deque* D, int X)
{
	Node* q = NewNode(X);
	q->next = NULL;
	q->prev = D->rear;
	
	if (D->N == 0)
		D->front = q;
	else
		D->rear->next = q;
	D->rear = q;
	D->N++;
}
void delete_front(Deque* D)
{
	if (D->N == 0) {
		printf("underflow\n");
		exit(1);
	}
	Node* q = D->front;
	D->N--;
	if (D->N == 0)
		D->rear = NULL;
	else
		D->front->next->prev = NULL;
	D->front = q->next;
	free(q);
	
}
void delete_rear(Deque* D)
{
	if (D->N == 0) {
		printf("underflow\n");
		exit(1);
	}
	Node* q = D->rear;
	D->N--;
	if (D->N == 0)
		D->front = NULL;
	else
		D->rear->prev->next = NULL;
	D->rear = q->prev;
	free(q);
}
void print(Deque* D)
{
	Node* p = D->front;
	while (p != NULL) {
		printf(" %d", p->elem);
		p = p->next;
	}
	printf("\n");
}
int isEmpty(Deque* D)
{
	return (D->N == 0);
}

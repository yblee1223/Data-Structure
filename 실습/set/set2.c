#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct node {
	struct node* next;
	int elem;
}Node;
typedef struct list {
	Node* head;
	int count;
}List;

void init(List* lst);
Node* GenNode(int e);
Node* appendTerm(Node* p, int e);
void Union(List* A, List* B, List* C);
void intersect(List* A, List* B, List* C);
void removeFirst(List* lst);
void addLast(List* lst, int e);
int isEmpty(List* lst);
void print(List* lst);

void main()
{
	List A, B;
	List U, I; // union, intersect
	Node* p = (Node*)malloc(sizeof(Node));

	// init
	init(&A);
	init(&B);
	init(&U);
	init(&I);
	int N = 0, n = 0;

	// input A
	scanf("%d", &N);
	A.count = N;
	p = A.head;
	if (A.count != 0) {
		for (int i = 0; i < A.count; i++) {
			scanf("%d", &n);
			p = appendTerm(p, n);
		}
	}


	// input B
	scanf("%d", &N);
	B.count = N;
	p = B.head;
	if (B.count != 0) {
		for (int i = 0; i < B.count; i++) {
			scanf("%d", &n);
			p = appendTerm(p, n);
		}
	}

	// culc
	Union(&A, &B, &U);
	intersect(&A, &B, &I);

	// output
	print(&U);
	print(&I);


	// free
	free(p);
	
}
/*
예제
6
3 7 45 88 99 101
4
7 10 15 45

0
3
9 20 77

0
0
*/

/*--- func ---*/
void init(List* lst)
{
	lst->head = GenNode(0);
	lst->count = 0;
}

Node* appendTerm(Node* p, int e)
{
	Node* q = GenNode(e);
	q->next = NULL;
	p->next = q;
	return q;
}

Node* GenNode(int e)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->elem = e;
	p->next = NULL;
	return p;
}

void Union(List* A, List* B, List* C)
{
	int a, b;
	Node* p, * q;
	p = A->head;
	q = B->head;
	if (p->next == NULL && q->next == NULL)
		addLast(C, 0);
	while (p->next != NULL && q->next != NULL) {
		a = p->next->elem;
		b = q->next->elem;
		if (a < b) {
			addLast(C, a);
			p = p->next;
			//removeFirst(A);
		}
		else if (a > b) {
			addLast(C, b);
			q = q->next;
			//removeFirst(B);
		}
		else {
			addLast(C, a);
			p = p->next;
			q = q->next;
			//removeFirst(A);
			//removeFirst(B);
		}
	}
	while (p->next != NULL) {
		a = p->next->elem;
		addLast(C, a);
		p = p->next;
		//removeFirst(A);
	}
	while (q->next != NULL) {
		b = q->next->elem;
		addLast(C, b);
		q = q->next;
		//removeFirst(B);
	}
	
}

void intersect(List* A, List* B, List *C) {
	int a, b;
	Node* p, * q;
	p = A->head;
	q = B->head;
	if (p->next == NULL || q->next == NULL)
		addLast(C, 0);
	while (p->next != NULL && q->next != NULL) {
		a = p->next->elem;
		b = q->next->elem;
		if (a < b)
			p = p->next;
		//removeFirst(A);
		else if (a > b)
			q = q->next;
			//removeFirst(B);
		else { // a == b
			addLast(C, a);
			p = p->next;
			q = q->next;
			//removeFirst(A);
			//removeFirst(B);
		}
	}
	while (p->next != NULL)
		p = p->next;
		//removeFirst(A);
	while (q->next != NULL)
		q = q->next;
		//removeFirst(B);
	
}
void removeFirst(List* lst)
{
	Node* p;
	p = lst->head;
	p->next = p->next->next;
	lst->count--;
}
void addLast(List* lst, int e)
{
	Node* p;
	p = lst->head;
	for (int i = 0; i < lst->count; i++) {
		p = p->next;
	}
	p = appendTerm(p, e);
	lst->count++;
}
int isEmpty(List* lst)
{
	if (lst->count == 0)
		return 1;
	else
		return 0;
}
void print(List* lst)
{
	Node* p;
	p = lst->head->next;
	for (int i = 0; i < lst->count; i++) {
		printf(" %d", p->elem);
		p = p->next;
	}
	printf("\n");
}

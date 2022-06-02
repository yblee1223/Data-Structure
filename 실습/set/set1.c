#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct node {
	struct node* next;
	int elem;
}Node;


int member(Node* A, int e);
int subset(Node* A, Node* B);
Node* GenNode();


void main()
{
	Node A, B;
	Node* p = (Node*)malloc(sizeof(Node));
	int A_count = 0, B_count = 0;
	int N = 0, n = 0;

	// input A
	scanf("%d", &N);
	A_count = N;
	p = &A;
	// init
	p->elem = 0;
	p->next = NULL;

	if (A_count != 0) {
		for (int i = 0; i < A_count; i++) {
			scanf("%d", &n);
			p->elem = n;
			if (i == A_count - 1) {
				p->next = NULL;
				continue;
			}
				
			p->next = GenNode();
			p = p->next;
		}
	}
	

	// input B
	scanf("%d", &N);
	B_count = N;
	p = &B;
	// init
	p->elem = 0;
	p->next = NULL;
	if (B_count != 0) {
		for (int i = 0; i < B_count; i++) {
			scanf("%d", &n);
			p->elem = n;
			if (i == B_count - 1) {
				p->next = NULL;
				continue;
			}
			p->next = GenNode();
			p = p->next;
		}
	}
	

	// output
	printf("%d", subset(&A, &B));

	// free
	//free(p);
}
/*
예제
3
4 6 13
6
1 3 4 6 8 13

0
3
9 20 77

3
7 10 53
4
7 10 15 45

0
0

4
7 10 15 45
3
7 10 53
1
1
0
*/
/*--- func ---*/

Node* GenNode() // 동적할당 필수!!
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->next = NULL;
	return p;
}
int subset(Node* A, Node* B)
{
	Node* p = (Node*)malloc(sizeof(Node));
	
	if (A == NULL) {
		return 0;
	}
	p = A;
	while (1) {
		if (member(B, p->elem)) {
			if (p->next == NULL)
				return 0;
			else
				p = p->next;
		}
		else
			return p->elem;
	}
}
int member(Node* A, int e) {
	Node* p = (Node*)malloc(sizeof(Node));
	int a;

	if (A == NULL)
		return 0;
	p = A;
	while (1) {
		a = p->elem;
		if (a < e) {
			if (p->next == NULL) {
				return 0;
			}
			else
				p = p->next;
		}
		else if (a > e)
			return 0;
		else // a == e
			return 1;
	}
}

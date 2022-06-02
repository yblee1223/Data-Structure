#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
// stack LIFO
// Singly linkedList
typedef struct node {
	int value;
	struct node* link;
}Node;
typedef struct stack {
	Node* head;
}Stack;

// func init
void stack_init(Stack* sp);
Node* NewNode(int elem);
void push(Stack* sp, int elem); // addLast
int pop(Stack* sp); // removeFirst
void print(Stack* sp);

// calc
void encode(char* str);
void convert(char* infix, char* postfix); // infix to postfix
int prec(char op); // operator priorty
int evaluate(char* postfix); // arithmethic operation postfix
int isOperand(char s);
int perc(char op);


void main()
{
	int N;
	scanf("%d", &N);
	getchar();

	for (int i = 0; i < N; i++) {
		char postfix[101] = ""; // 후위 수식
		gets(postfix);
		// output
		printf("%d\n", evaluate(postfix));
	}
}

/*
예제
4
53*2+63+2*+
234*+
72/3-42*+21*-
923*1+2*+
*/
/* --- func --- */

// calc func

int evaluate(char* postfix)
{
	Stack S;
	stack_init(&S);
	char s;
	int a, b; // pop 연산
	int len = strlen(postfix);
	for (int i = 0; i < len; i++) {
		s = postfix[i];
		if (isOperand(s)) { // 피연산자
			push(&S, s - '0');
		}
		else { // 연산자
			b = pop(&S);
			a = pop(&S);
			if (s == '*')
				push(&S, a * b);
			else if (s == '/')
				push(&S, a / b);
			else if (s == '+')
				push(&S, a + b);
			else if (s == '-')
				push(&S, a - b);
		}
	}
	return pop(&S);
}

int isOperand(char s) // 비연산자 찾기
{
	if (('0' <= s && s <= '9')) {
		return 1;
	}
	return 0;
}


// stack func
void stack_init(Stack* sp)
{
	sp->head = NULL;
}
Node* NewNode(int elem)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->value = elem;
	p->link = NULL;
	return p;
}
void push(Stack* sp, int elem)
{
	Node* p = sp->head;
	Node* q = NewNode(elem);
	q->link = p;
	sp->head = q;
}
int pop(Stack* sp)
{
	int elem = sp->head->value;
	Node* p = sp->head;
	sp->head = p->link;
	free(p);
	return elem;
}
void print(Stack* sp)
{
	Node* p = sp->head;
	while (p != NULL) {
		printf("%d ", p->value);
		p = p->link;
	}
}

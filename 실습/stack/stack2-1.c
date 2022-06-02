#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
// stack LIFO
// Singly linkedList
typedef struct node {
	char value;
	struct node* link;
}Node;
typedef struct stack{
	Node* head;
}Stack;

// func init
void stack_init(Stack* sp);
Node* NewNode(char elem);
void push(Stack* sp, char elem); // addLast
char pop(Stack* sp); // removeFirst
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
	char infix[101] = ""; // 중위 수식
	
	
	int N;
	scanf("%d", &N);
	getchar();

	for (int i = 0; i < N; i++) {
		gets(infix);
		encode(infix);
		char postfix[101] = ""; // 후위 수식
		//printf("%s\n", infix);
		convert(infix, postfix);
		printf("%s\n", postfix);
	}
	
}

/*
예제
1
A*B+C+(D+E)*F
1
A&&B||C||!(E>F)

5
A*B+C+(D+E)*F
A+B*C
A/B-C+D*E-F*G
A+(B*C+D)*E
A&&B||C||!(E>F)
*/
/* --- func --- */

// calc func
void encode(char* str)
{
	char* p, * q;
	if (*str == '+')
		*str = 'p';
	if (*str == '-')
		*str = 'n';
	for (p = str + 1; *p; p++)
	{
		if (*p == '|' || *p == '&')
		{
			for (q = p + 1; *q; q++)
			{
				*(q - 1) = *q;
			}
			*(q - 1) = 0;
		}
	}
	for (p = str + 1; *p; p++)
	{
		if ((*(p - 1) < 'A' || *(p - 1) > 'Z') && *(p - 1) != ')')
		{
			if (*p == '+')
				*p = 'p';
			if (*p == '-')
				*p = 'n';
		}
	}
}

void convert(char* infix, char* postfix)
{
	Stack S;
	stack_init(&S);
	char s = NULL; // infix value;
	int len = strlen(infix);
	int j = 0; // postfix index
	char t; // pop(&S)

	for (int i = 0; i < len; i++) {
		s = infix[i];
		if (isOperand(s)) { // operand
			postfix[j] = s; j++;
		}
		else if (s == '(') {
			push(&S, s);
		}
		else if (s == ')') {
			while (S.head->value != '(') {
				t = pop(&S);
				if (t == '|' || t == '&') {
					postfix[j] = t; j++;
					postfix[j] = t; j++;
				}
				else if (t == 'p') {
					postfix[j] = '+'; j++;
				}
				else if (t == 'n') {
					postfix[j] = '-'; j++;
				}
				else {
					postfix[j] = t; j++;
				}
			}
			pop(&S);
		}
		else { // operator
			while (S.head != NULL && prec(s) <= prec(S.head->value)) {
				t = pop(&S);
				if (t == '|' || t == '&') {
					postfix[j] = t; j++;
					postfix[j] = t; j++;
				}
				else if (t == 'p') {
					postfix[j] = '+'; j++;
				}
				else if (t == 'n') {
					postfix[j] = '-'; j++;
				}
				else {
					postfix[j] = t; j++;
				}
			}
			push(&S, s);
		}
	}
	while (S.head != NULL) {
		t = pop(&S);
		if (t == '|' || t == '&') {
			postfix[j] = t; j++;
			postfix[j] = t; j++;
		}
		else if (t == 'p') {
			postfix[j] = '+'; j++;
		}
		else if (t == 'n') {
			postfix[j] = '-'; j++;
		}
		else {
			postfix[j] = t; j++;
		}
	}
}
int isOperand(char s) // 비연산자 찾기
{
	if (('A' <= s && s <= 'Z')) {
		return 1;
	}
	return 0;
}

int prec(char op)
{
	switch(op) {
		case '|': return 1;
		case '&': return 2;
		case '<': case '>': return 3;
		case '+': case '-': return 4;
		case '*': case '/': return 5;
		case '!': case 'p': case 'n': return 6;
	}
	return 0;
}

// stack func
void stack_init(Stack* sp)
{
	sp->head = NULL;
}
Node* NewNode(char elem)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->value = elem;
	p->link = NULL;
	return p;
}
void push(Stack* sp, char elem)
{
	Node* p = sp->head;
	Node* q = NewNode(elem);
	q->link = p;
	sp->head = q;
}
char pop(Stack* sp)
{
	char elem = sp->head->value;
	Node* p = sp->head;
	sp->head = p->link;
	free(p);
	return elem;
}
void print(Stack* sp)
{
	Node* p = sp->head;
	while (p != NULL) {
		printf("%c ", p->value);
		p = p->link;
	}
}

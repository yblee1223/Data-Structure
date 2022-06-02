#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct ArrayStack {
	int top;
	int capacity;
	char* arr;
}Stack;

// stack
Stack* createStack(int capacity);
void push(Stack* stack, char data); // addFirst
char pop(Stack* stack); // removeLast
char peek(Stack* stack);
void duplicate(Stack* stack);
void upRotate(Stack* stack, int rotate_num);
void downRotate(Stack* stack, int rotate_num);
void print(Stack* stack);

void main()
{
	// variable
	Stack* stack;
	int N, calc_count;
	char elem;
	int r; // rotate
	char command[10];

	// input
	scanf("%d\n", &N);
	stack = createStack(N);
	scanf("%d\n", &calc_count);

	for (int i = 0; i < calc_count; i++) {
		scanf("%s", command);
		if (strcmp(command, "PUSH") == 0) {
			scanf(" %c", &elem);
			push(stack, elem);
		}
		else if (strcmp(command, "POP") == 0) {
			r = pop(stack);
		}
		else if (strcmp(command, "PEEK") == 0) {
			r = peek(stack);
		}
		else if (strcmp(command, "DUP") == 0) {
			duplicate(stack);
		}
		else if (strcmp(command, "UpR") == 0) {
			scanf(" %d", &r);
			upRotate(stack, r);
		}
		else if (strcmp(command, "DownR") == 0) {
			scanf(" %d", &r);
			downRotate(stack, r);
		}
		else if (strcmp(command, "PRINT") == 0) {
			print(stack);
		}
		getchar();
	}
}
/*
예제
4
10
POP
PUSH s
PUSH t
PUSH a
PUSH r
PRINT
UpR 3
PRINT
PUSH s
PEEK

5
8
PUSH a
PUSH b
PUSH c
PUSH d
PUSH e
PRINT
DownR 5
PRINT



4
6
PUSH d
PUSH c
DUP
PUSH a
PRINT
PUSH s

검증
UpR
DownR
Error detection
Peek
*/

/* --- func --- */
Stack* createStack(int capacity)
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));

	stack->capacity = capacity;
	stack->top = -1;
	stack->arr = (char*)malloc(sizeof(char) * stack->capacity);

	return stack;
}
void push(Stack* stack, char data)
{
	if (isFull(stack)) {
		printf("Stack FULL\n");
	}
	else {
		stack->arr[++stack->top] = data;
	}
}
char pop(Stack* stack)
{
	if (isEmpty(stack)) {
		printf("Stack Empty\n");
		return;
	}
	else {
		return stack->arr[stack->top--];
	}
}
char peek(Stack* stack)
{
	if (isEmpty(stack)) {
		printf("Stack Empty\n");
		return;
	}
	else {
		printf("%c\n", stack->arr[stack->top]);
		return stack->arr[stack->top];
	}
}
void print(Stack* stack) {
	if (!isEmpty(stack)) {
		for (int i = stack->top; i >= 0; i--) {
			printf("%c", stack->arr[i]);
		}
		printf("\n");
	}
}
void duplicate(Stack* stack)
{
	char data;
	data = pop(stack);
	push(stack, data);
	push(stack, data);
}
void upRotate(Stack* stack, int rotate_num)
{
	if (rotate_num > stack->top + 1 || rotate_num == 0) {
		return;
	}
	char tmp;
	tmp = stack->arr[stack->top];
	for (int i = stack->top; i > stack->top - rotate_num + 1; i--) {
		stack->arr[i] = stack->arr[i - 1];
	}
	stack->arr[stack->top - rotate_num + 1] = tmp;
}
void downRotate(Stack* stack, int rotate_num)
{
	if (rotate_num > stack->top + 1 || rotate_num == 0) {
		return;
	}
	char tmp;
	tmp = stack->arr[stack->top - rotate_num + 1];
	for (int i = stack->top - rotate_num + 1; i <= stack->top; i++) {
		stack->arr[i] = stack->arr[i + 1];
	}
	stack->arr[stack->top] = tmp;
}

// Error
int isFull(Stack* stack)
{
	return (stack->top == stack->capacity - 1);
}
int isEmpty(Stack* stack)
{
	return (stack->top == -1);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct ArrayStack {
	int top;
	int capacity;
	char* arr;
}Stack;

// barket_cecker
void isBalanced(char* str);
int isCounterpart(char s, char t);
// stack
Stack* createStack(int capacity);
void push(Stack* stack, char data); // addFirst
char pop(Stack* stack); // removeLast
char peek(Stack* stack);
void duplicate(Stack* stack);
void upRotate(Stack* stack, int rotate_num);
void downRotate(Stack* stack, int rotate_num);
void print(Stack* stack);

int main()
{
	// variable
	char elem;
	char str[1000];
	
	// input
	gets(str);
	// calc
	isBalanced(str);
	return 0;
}
/*
예제
(3+40*(2+(30-7)*2133)

3*{4+(2-792)/1} + [3*{4-2* (100 -7)}]

301*{4+(2101-7)/1} + 9*{4-2* (10108-7)}}

(3*{4001+(2-7)/1} + [3*{4-2* (1-7)}])
*/

/* --- func --- */

void isBalanced(char* str)
{
	int str_N = strlen(str);
	Stack* stack;

	stack = createStack(1000);
	char data1, data2 = 0;
	int N = 0;
	int flag = 1;

	// calc
	for (int i = 0; i < str_N; i++) {
		data1 = str[i];
		if (data1 == '[' || data1 == '(' || data1 == '{') {
			push(stack, data1);
			N++;
		}
		else if (data1 == '}' || data1 == ')' || data1 == ']') {
			N++;
			if (!isEmpty(stack) == 0) {
				flag = 0;
				continue;
			}
			data2 = pop(stack);
			if (isCounterpart(data2, data1)) {
				continue;
			}
			flag = 0;
		}
	}
	if (isEmpty(stack) && flag == 1) {
		printf("OK_%d\n", N);
	}
	else printf("Wrong_%d\n", N);
}

int isCounterpart(char s, char t)
{
	if (s == '{' && t == '}') return 1;
	else if (s == '(' && t == ')') return 1;
	else if (s == '[' && t == ']') return 1;
	else return 0;
}
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
/*
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
*/
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
	int elem;
	elem = pop(stack);
	push(stack, elem);
	push(stack, elem);
}
void upRotate(Stack* stack, int rotate_num)
{
	if (rotate_num > stack->capacity || rotate_num == 0) {
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
	if (rotate_num > stack->capacity || rotate_num == 0) {
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

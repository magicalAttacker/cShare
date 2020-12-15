#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int DataType;
typedef struct {
	DataType data[MAXSIZE];
	int front;
	int rear;
}SeqQueue;
SeqQueue Q;
isInit = 1;

void InitQueue(SeqQueue *Q) {
	Q->front = Q->rear = 0;
	printf("初始化\n");
}

int EmptyQueue(SeqQueue *Q) {
	if (Q->front == Q->rear) 
		return 1;
	else 
		return 0;
}

int InQueue(SeqQueue *Q, DataType x) {
	if ((Q->rear + 1) % MAXSIZE == Q->front) {
		printf("队满，不能入队元素！");
		return 0;
	}
	else {
		Q->rear = (Q->rear + 1) % MAXSIZE;
		Q->data[Q->rear] = x;
		return 1;
	}
}

int DeQueue(SeqQueue *Q, DataType *x) {
	if (EmptyQueue(Q)) {
		printf("队空，不能出队元素！");
		return 0;
	}
	else {
		Q->front = (Q->front + 1) % MAXSIZE;
		*x=Q->data[Q->front];
		return 1;
	}
}

int GetFront(SeqQueue *Q, DataType *x) {
	if (EmptyQueue(Q)) {
		printf("队空，无队头元素！");
		return 0;
	}
	else {
		*x = Q->data[(Q->front + 1) % MAXSIZE];
		return 1;
	}
}

void ShowQueue(SeqQueue *Q) {
	int p = Q->front;
	if (p == Q->rear)
		printf("队列为空，无元素！\n");
	else {
		printf("从队头起队列中的各元素为：");
		while (p != Q->rear) {
			printf("%5d", Q->data[p + 1]);
			p++;
		}
	}
}

void MenuLayout() {
	printf("\n1. 入队操作");
	printf("\n2. 出队操作");
	printf("\n3. 求队头元素");
	printf("\n4. 显示队中所有元素");
	printf("\n0. 返回\n");
}

void Menu() {
	int i, n, flag, selector, isContinue;
	DataType x;
	if (isInit) {
		InitQueue(&Q);
		isInit = 0;
	}
	MenuLayout();
	printf("请输入选项：\n");
	scanf("%d", &selector);
	switch (selector) {
	case 1:
		printf("请输入要入队的元素个数：");
		scanf("%d", &n);
		printf("请输入%d个入队的整数: ", n);
		for (i = 0; i < n; i++) {
			scanf("%d", &x);
			flag = InQueue(&Q, x);
		}
		if (flag == 1) 
			printf("入队操作成功！");
		else
			printf("入队操作失败！");
		break;
	case 2: 
		printf("请输入要出队的元素个数：");
		scanf("%d", &n);
		printf("出队的元素顺序依次为：");
		for (i = 0; i < n; i++) {
			flag = DeQueue(&Q, &x);
			printf("%5d", x);
		}
		if (flag == 1) 
			printf("\n出队操作成功！");
		else 
			printf("\n出队操作失败！");
		break;
	case 3: 
		if (flag = GetFront(&Q, &x)) 
			printf("当前的队头元素值为：%d", x);
		break;
	case 4:
		ShowQueue(&Q);
		break;
	case 0:
		exit(0);
	default:
		printf("输入有误！");
	}
	printf("\n是否继续？\n0.退出 1.继续\n");
	scanf("%d", &isContinue);
	if (isContinue) 
		Menu();
}

int main() {
	Menu();
	return 0;
}

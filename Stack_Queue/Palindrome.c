/*
	设计一个算法，判断用户输入的字符串
	是否是回文字符串，用户输入的字符串
	同时存储于链栈和链队列中。 所涉及的
	链栈结点和链队列结点定义如下：
*/
#include <stdio.h>
#include <stdlib.h>

typedef char DataType;
/* 链栈的结点定义 */
typedef struct SNode
{
	DataType data;
	struct SNode* next;
}SNode, * LinkStack;
/* 链队列的结点定义 */
typedef struct QNode
{
	DataType data;
	struct QNode* next;
}LQNode, * PQNode;
/* 链队列的定义 */
typedef struct
{
	PQNode front, rear;		// 链队列的队头和队尾指针
}LinkQueue;

int InitLinkStack(LinkStack* L);   //初始化链栈
int LinkStackEmpty(LinkStack L);   //判链栈是否为空
int Push(LinkStack L, DataType e);   //入栈
int Pop(LinkStack L, DataType* e);   //出栈
int Destroy(LinkStack L);         //销毁链栈
int InitLinkQueue(LinkQueue* Q);      //链队列的入队
int LinkQueueEmpty(LinkQueue Q);      //判断队空
int EnLinkQueue(LinkQueue* Q, DataType e); //入队
int DeLinkQueue(LinkQueue* Q, DataType* e); //出队
int DestroyLinkQueue(LinkQueue* Q);    //销毁链队列
int JudgePalindrome(LinkStack st, LinkQueue qu); //判断是否为回文

int main()
{
	LinkStack s;
	LinkQueue q;
	char ch;
	int rst;
	InitLinkStack(&s);
	InitLinkQueue(&q);
	printf("请输入一段字符串：\n");
	while ((ch = getchar()) != '\n')
	{
		Push(s, ch);
		EnLinkQueue(&q, ch);
	}
	rst = JudgePalindrome(s, q);
	if (rst == 0)
	{
		printf("不是回文字符串\n");
	}
	else
	{
		printf("是回文字符串\n");
	}
	Destroy(s);
	DestroyLinkQueue(&q);
	return 0;
}

int InitLinkStack(LinkStack* L)			//初始化链栈
{
	*L = (LinkStack)malloc(sizeof(SNode));
	if (*L == NULL) {
		printf("初始化链栈失败！\n");
		return 0;
	}
	(*L)->next = NULL;
	return 1;
}

int LinkStackEmpty(LinkStack L) {		//判断是否链栈为空
	if (L->next == NULL)
		return 1;
	else
		return 0;
}

int Push(LinkStack L, DataType e)  //入栈
{
	SNode* p;
	p = (LinkStack)malloc(sizeof(SNode));		//生成一个新的结点
	if (!p)
	{
		printf("入栈操作出错！\n");
		return 0;
	}
	p->data = e;								//在栈顶位置插入新的结点
	p->next = L->next;
	L->next = p;
	return 1;
}

int Pop(LinkStack L, DataType* e)   //出栈
{
	SNode* p;
	if (!L->next)
	{
		printf("链栈为空，无法完成出栈操作\n");
		return 0;
	}
	p = L->next;
	L->next = p->next;
	*e = p->data;
	free(p);						//删除结点所占用的内存空间
	return 1;
}

int Destroy(LinkStack L)         //销毁链栈
{
	SNode* p;
	while (L)
	{
		p = L;
		L = L->next;
		free(p);
	}
	return 1;
}

int InitLinkQueue(LinkQueue* Q)      //链队列的初始化
{
	Q->front = Q->rear = (PQNode)malloc(sizeof(LQNode));		//生成一个头结点，并且使队头指针和队尾指针都指向该节点
	if (!Q->front)
	{
		printf("初始化队列失败！\n");
		return 0;
	}
	Q->front->next = NULL;
	return 1;
}

int LinkQueueEmpty(LinkQueue Q)      //判断队空
{
	if (Q.front == Q.rear)		return 1;
	else return 0;
}

int EnLinkQueue(LinkQueue* Q, DataType e)		//入队
{
	PQNode p;
	p = (PQNode)malloc(sizeof(LQNode));
	if (!p)
	{
		printf("入队操作失败！\n");
		return 0;
	}
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return 1;
}

int DeLinkQueue(LinkQueue* Q, DataType* e) //出队
{
	PQNode p;
	if (Q->rear == Q->front)
	{
		printf("链队列已经为空，无法完成出队操作！\n");
		return 0;
	}
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	free(p);
	if (Q->rear == p)						//如果删除的结点是最后一个结点就要移动尾指针
		Q->rear = Q->front;
	return 1;
}

int DestroyLinkQueue(LinkQueue* Q)    //销毁链队列
{
	while (Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return 1;
}


int JudgePalindrome(LinkStack st, LinkQueue qu) //判断是否为回文
{
	int flag = 1, m, n;
	while (!LinkStackEmpty(st) && !LinkQueueEmpty(qu))
	{
		Pop(st, &m);
		DeLinkQueue(&qu, &n);
		if (m != n)
			flag = 0;
	}
	if (flag == 1) return 1;
	else return 0;
}
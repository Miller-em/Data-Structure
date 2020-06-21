/*
	���һ���㷨���ж��û�������ַ���
	�Ƿ��ǻ����ַ������û�������ַ���
	ͬʱ�洢����ջ���������С� ���漰��
	��ջ���������н�㶨�����£�
*/
#include <stdio.h>
#include <stdlib.h>

typedef char DataType;
/* ��ջ�Ľ�㶨�� */
typedef struct SNode
{
	DataType data;
	struct SNode* next;
}SNode, * LinkStack;
/* �����еĽ�㶨�� */
typedef struct QNode
{
	DataType data;
	struct QNode* next;
}LQNode, * PQNode;
/* �����еĶ��� */
typedef struct
{
	PQNode front, rear;		// �����еĶ�ͷ�Ͷ�βָ��
}LinkQueue;

int InitLinkStack(LinkStack* L);   //��ʼ����ջ
int LinkStackEmpty(LinkStack L);   //����ջ�Ƿ�Ϊ��
int Push(LinkStack L, DataType e);   //��ջ
int Pop(LinkStack L, DataType* e);   //��ջ
int Destroy(LinkStack L);         //������ջ
int InitLinkQueue(LinkQueue* Q);      //�����е����
int LinkQueueEmpty(LinkQueue Q);      //�ж϶ӿ�
int EnLinkQueue(LinkQueue* Q, DataType e); //���
int DeLinkQueue(LinkQueue* Q, DataType* e); //����
int DestroyLinkQueue(LinkQueue* Q);    //����������
int JudgePalindrome(LinkStack st, LinkQueue qu); //�ж��Ƿ�Ϊ����

int main()
{
	LinkStack s;
	LinkQueue q;
	char ch;
	int rst;
	InitLinkStack(&s);
	InitLinkQueue(&q);
	printf("������һ���ַ�����\n");
	while ((ch = getchar()) != '\n')
	{
		Push(s, ch);
		EnLinkQueue(&q, ch);
	}
	rst = JudgePalindrome(s, q);
	if (rst == 0)
	{
		printf("���ǻ����ַ���\n");
	}
	else
	{
		printf("�ǻ����ַ���\n");
	}
	Destroy(s);
	DestroyLinkQueue(&q);
	return 0;
}

int InitLinkStack(LinkStack* L)			//��ʼ����ջ
{
	*L = (LinkStack)malloc(sizeof(SNode));
	if (*L == NULL) {
		printf("��ʼ����ջʧ�ܣ�\n");
		return 0;
	}
	(*L)->next = NULL;
	return 1;
}

int LinkStackEmpty(LinkStack L) {		//�ж��Ƿ���ջΪ��
	if (L->next == NULL)
		return 1;
	else
		return 0;
}

int Push(LinkStack L, DataType e)  //��ջ
{
	SNode* p;
	p = (LinkStack)malloc(sizeof(SNode));		//����һ���µĽ��
	if (!p)
	{
		printf("��ջ��������\n");
		return 0;
	}
	p->data = e;								//��ջ��λ�ò����µĽ��
	p->next = L->next;
	L->next = p;
	return 1;
}

int Pop(LinkStack L, DataType* e)   //��ջ
{
	SNode* p;
	if (!L->next)
	{
		printf("��ջΪ�գ��޷���ɳ�ջ����\n");
		return 0;
	}
	p = L->next;
	L->next = p->next;
	*e = p->data;
	free(p);						//ɾ�������ռ�õ��ڴ�ռ�
	return 1;
}

int Destroy(LinkStack L)         //������ջ
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

int InitLinkQueue(LinkQueue* Q)      //�����еĳ�ʼ��
{
	Q->front = Q->rear = (PQNode)malloc(sizeof(LQNode));		//����һ��ͷ��㣬����ʹ��ͷָ��Ͷ�βָ�붼ָ��ýڵ�
	if (!Q->front)
	{
		printf("��ʼ������ʧ�ܣ�\n");
		return 0;
	}
	Q->front->next = NULL;
	return 1;
}

int LinkQueueEmpty(LinkQueue Q)      //�ж϶ӿ�
{
	if (Q.front == Q.rear)		return 1;
	else return 0;
}

int EnLinkQueue(LinkQueue* Q, DataType e)		//���
{
	PQNode p;
	p = (PQNode)malloc(sizeof(LQNode));
	if (!p)
	{
		printf("��Ӳ���ʧ�ܣ�\n");
		return 0;
	}
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return 1;
}

int DeLinkQueue(LinkQueue* Q, DataType* e) //����
{
	PQNode p;
	if (Q->rear == Q->front)
	{
		printf("�������Ѿ�Ϊ�գ��޷���ɳ��Ӳ�����\n");
		return 0;
	}
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	free(p);
	if (Q->rear == p)						//���ɾ���Ľ�������һ������Ҫ�ƶ�βָ��
		Q->rear = Q->front;
	return 1;
}

int DestroyLinkQueue(LinkQueue* Q)    //����������
{
	while (Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return 1;
}


int JudgePalindrome(LinkStack st, LinkQueue qu) //�ж��Ƿ�Ϊ����
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
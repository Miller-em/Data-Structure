/*
	ʵ�ֶ����������Ļ���������
	���룬ɾ�������ң�������
*/
#include <stdio.h>
#include <stdlib.h>


typedef int ElementType;
typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal(BinTree BT);             //�������
void InorderTraversal(BinTree BT);              //�������

BinTree Insert(BinTree BST, ElementType X);     //�������
BinTree Delete(BinTree BST, ElementType X);     //ɾ������
Position Find(BinTree BST, ElementType X);      //����
Position FindMin(BinTree BST);                  //������Сֵ
Position FindMax(BinTree BST);                  //�������ֵ

int main()
{
    BinTree BST = NULL, MinB = NULL, MaxB = NULL, Temp = NULL;
    ElementType X;
    int N, i;

    printf("����������������Ľڵ������"); scanf_s("%d", &N);
    printf("����������������Ľڵ����ݣ�");
    for (i = 0; i < N; i++) {
        scanf_s("%d", &X);
        BST = Insert(BST, X);
    }
    printf("���������"); PreorderTraversal(BST); printf("\n");
    MinB = FindMin(BST);
    MaxB = FindMax(BST);
    printf("��������Ҫ���ҵ�����");
    scanf_s("%d", &X);
    Temp = Find(BST, X);
    if (Temp == NULL) printf("%d δ���ҵ�\n", X);
    else {
        printf("%d �ѱ��ҵ�\n", Temp->Data);
        if (Temp == MinB) printf("%d ����С�Ĺؼ���\n", Temp->Data);
        if (Temp == MaxB) printf("%d �����Ĺؼ���\n", Temp->Data);
    }
    printf("������Ҫɾ������ֵ��");
    scanf_s("%d", &X);
    BST = Delete(BST, X);
    printf("�������:"); InorderTraversal(BST); printf("\n");
    return 0;
}

void PreorderTraversal(BinTree BT)            //�������
{
    if (BT != NULL) {
        printf("%d ", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}

void InorderTraversal(BinTree BT)             //�������
{
    if (BT != NULL) {
        InorderTraversal(BT->Left);
        printf("%d ", BT->Data);
        InorderTraversal(BT->Right);
    }
}

BinTree Insert(BinTree BST, ElementType X)     //�������
{
    if (BST == NULL){                           //����ǿգ�������һ���µĽ��
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = NULL;
        BST->Right = NULL;
    }
    else {
        if (BST->Data < X)  BST->Right = Insert(BST->Right, X);    //���X���ڸ��ڵ��ֵ,������������
        else BST->Left = Insert(BST->Left, X);                      //���XС�ڸ��ڵ��ֵ,������������
        //�����Ⱦ�ʲô������
    }
    return BST;
}

BinTree Delete(BinTree BST, ElementType X)     //ɾ������
{
    Position temp;
    if (!BST) printf("Ҫɾ���Ľ��δ�ҵ���\n");   //�����Ϊ�գ�˵��û��
    else {
        if (X < BST->Data) BST->Left = Delete(BST->Left, X);
        else if (X > BST->Data) BST->Right = Delete(BST->Right, X);
        else {
            //��ǰBST����Ҫɾ���Ľ��
            if (BST->Right && BST->Left) {      //���Һ��Ӷ���Ϊ��
                temp = FindMin(BST->Right);
                BST->Data = temp->Data;
                BST->Right = Delete(BST->Right, temp->Data);
            }
            else {                              //ֻ��һ������
                temp = BST;
                if (!BST->Left) BST = BST->Right;
                else if (!BST->Right) BST = BST->Left;
                free(temp);
            }
        }
    }
    return BST;
}

Position Find(BinTree BST, ElementType X)      //����
{
    while (BST != NULL) {
        if (X < BST->Data) BST = BST->Left;         //�������ֵС�ڽ�㣬��������������
        else if (X > BST->Data) BST = BST->Right;   //�������ֵ���ڽ�㣬��������������
        else return BST;                            //��ȵĻ�˵���ҵ�����������ֵ
    }
    return BST;
}

Position FindMin(BinTree BST)                  //������Сֵ
{
    if (!BST) return NULL;
    else if (!BST->Left) return BST;
    else return FindMin(BST->Left);
}

Position FindMax(BinTree BST)                  //�������ֵ
{
    if (!BST) return NULL;
    else if (!BST->Right) return BST;
    else return FindMax(BST->Right);
}





/*
	实现二叉搜索树的基本操作：
	插入，删除，查找，遍历等
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

void PreorderTraversal(BinTree BT);             //先序遍历
void InorderTraversal(BinTree BT);              //中序遍历

BinTree Insert(BinTree BST, ElementType X);     //插入操作
BinTree Delete(BinTree BST, ElementType X);     //删除操作
Position Find(BinTree BST, ElementType X);      //查找
Position FindMin(BinTree BST);                  //查找最小值
Position FindMax(BinTree BST);                  //查找最大值

int main()
{
    BinTree BST = NULL, MinB = NULL, MaxB = NULL, Temp = NULL;
    ElementType X;
    int N, i;

    printf("请输入二叉搜索树的节点个数："); scanf_s("%d", &N);
    printf("请输入二叉搜索树的节点数据：");
    for (i = 0; i < N; i++) {
        scanf_s("%d", &X);
        BST = Insert(BST, X);
    }
    printf("先序遍历："); PreorderTraversal(BST); printf("\n");
    MinB = FindMin(BST);
    MaxB = FindMax(BST);
    printf("请输入需要查找的数：");
    scanf_s("%d", &X);
    Temp = Find(BST, X);
    if (Temp == NULL) printf("%d 未被找到\n", X);
    else {
        printf("%d 已被找到\n", Temp->Data);
        if (Temp == MinB) printf("%d 是最小的关键字\n", Temp->Data);
        if (Temp == MaxB) printf("%d 是最大的关键字\n", Temp->Data);
    }
    printf("请输入要删除结点的值：");
    scanf_s("%d", &X);
    BST = Delete(BST, X);
    printf("中序遍历:"); InorderTraversal(BST); printf("\n");
    return 0;
}

void PreorderTraversal(BinTree BT)            //先序遍历
{
    if (BT != NULL) {
        printf("%d ", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}

void InorderTraversal(BinTree BT)             //中序遍历
{
    if (BT != NULL) {
        InorderTraversal(BT->Left);
        printf("%d ", BT->Data);
        InorderTraversal(BT->Right);
    }
}

BinTree Insert(BinTree BST, ElementType X)     //插入操作
{
    if (BST == NULL){                           //如果是空，就生成一个新的结点
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = NULL;
        BST->Right = NULL;
    }
    else {
        if (BST->Data < X)  BST->Right = Insert(BST->Right, X);    //如果X大于根节点的值,在右子树插入
        else BST->Left = Insert(BST->Left, X);                      //如果X小于根节点的值,在左子树插入
        //如果相等就什么都不做
    }
    return BST;
}

BinTree Delete(BinTree BST, ElementType X)     //删除操作
{
    Position temp;
    if (!BST) printf("要删除的结点未找到！\n");   //如果树为空，说明没有
    else {
        if (X < BST->Data) BST->Left = Delete(BST->Left, X);
        else if (X > BST->Data) BST->Right = Delete(BST->Right, X);
        else {
            //当前BST就是要删除的结点
            if (BST->Right && BST->Left) {      //左右孩子都不为空
                temp = FindMin(BST->Right);
                BST->Data = temp->Data;
                BST->Right = Delete(BST->Right, temp->Data);
            }
            else {                              //只有一个孩子
                temp = BST;
                if (!BST->Left) BST = BST->Right;
                else if (!BST->Right) BST = BST->Left;
                free(temp);
            }
        }
    }
    return BST;
}

Position Find(BinTree BST, ElementType X)      //查找
{
    while (BST != NULL) {
        if (X < BST->Data) BST = BST->Left;         //如果插入值小于结点，就在左子树查找
        else if (X > BST->Data) BST = BST->Right;   //如果插入值大于结点，就在右子树查找
        else return BST;                            //相等的话说明找到，返回它的值
    }
    return BST;
}

Position FindMin(BinTree BST)                  //查找最小值
{
    if (!BST) return NULL;
    else if (!BST->Left) return BST;
    else return FindMin(BST->Left);
}

Position FindMax(BinTree BST)                  //查找最大值
{
    if (!BST) return NULL;
    else if (!BST->Right) return BST;
    else return FindMax(BST->Right);
}





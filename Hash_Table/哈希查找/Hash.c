#include<stdio.h>
#define HASHSIZE 13/*哈希表大小*/
#define DELFLAG -1	/*删除标志*/

typedef struct {	/*关键字*/
	int key;
}DataType;
typedef struct {
	DataType data;	/*数据域*/
	int times;	/*比较次数*/
}HashTable[HASHSIZE];

void CreateHash(HashTable ht, DataType items[], int n); //创建哈希表
int HashFunc(int key);//构造哈希函数 
int Collision(int d);//线性探测法处理冲突
int HashSearch(HashTable ht, DataType x);//哈希查找
int HashInsert(HashTable ht, DataType x);//插入
int HashDelete(HashTable ht, DataType x);//删除
void DisplayHash(HashTable ht);//哈希表的显示
//21 25 31 84 27 66 -1
void main()
{
	int addr, i;
	DataType x;
	DataType  items[6];
	HashTable ht;
	printf("输出6个存入哈希表中的数");
	for (i = 0; i < 6; i++)
	{
		scanf("%d", &items[i]);
	}
	CreateHash(ht, items, 6);
	printf("输入需要查找的数");
	scanf("%d", &x);
	addr = HashSearch(ht, x);
	DisplayHash(ht);
	if (addr >= 0)
	{
		printf("\n查找%d比较次数:", x.key);
		printf("%d\n", ht[addr].times);
	}
	else
		printf("\n查找%d失败\n:", x.key);
}
int HashFunc(int key)
{
	return key % HASHSIZE;
}
int Collision(int d)
{
	return (d + 1) % HASHSIZE;
}
void CreateHash(HashTable ht, DataType items[], int n)
{
	/* 利用所给关键字序列items创建哈希表，n为关键字个数 */
	int i;
	for (i = 0; i < HASHSIZE; i++)
	{
		ht[i].data.key = NULL;
		ht[i].times = 0;
	}
	for (i = 0; i < n; i++)
		HashInsert(ht, items[i]);

}
int HashSearch(HashTable ht, DataType x)
{
	int addr; int times = 1;
	addr = HashFunc(x.key);	/*获得哈希地址*/
	while (ht[addr].data.key != NULL && ht[addr].data.key != x.key)
	{
		addr = Collision(addr);	/*没找到，处理冲突*/
		times++;
	}
	if (ht[addr].data.key == x.key)
	{
		ht[addr].times = times;
		return addr; /*查找成功*/
	}
	else	return -addr; 		/*查找失败*/
}
int HashInsert(HashTable ht, DataType x)
{
	int addr;
	addr = HashSearch(ht, x);/*在哈希表中查找*/
	if (addr > 0) return 0;	/*找到，则不必插入*/
	ht[-addr].data = x;	/*没找到，则插入*/
	ht[-addr].times = 1;
	return 1;
}
int HashDelete(HashTable ht, DataType x)
{
	int addr;
	addr = HashSearch(ht, x);	/*查找数据元素*/
	if (addr >= 0) { 		/*找到，则打上删除标记*/
		ht[addr].data.key = DELFLAG;
		return 1;
	}
	return 0;
}
void DisplayHash(HashTable ht)
{
	int i;
	printf("\n哈希表\n哈希表地址:\t");
	for (i = 0; i < HASHSIZE; i++)
		printf("%d\t", i);
	printf("\n关键字:   \t");
	for (i = 0; i < HASHSIZE; i++)
		if (ht[i].data.key != NULL)
			printf("%d\t", ht[i].data.key);

		else
			printf("\t");
	printf("\n");
}
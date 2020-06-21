#include<stdio.h>
#define HASHSIZE 13/*��ϣ���С*/
#define DELFLAG -1	/*ɾ����־*/

typedef struct {	/*�ؼ���*/
	int key;
}DataType;
typedef struct {
	DataType data;	/*������*/
	int times;	/*�Ƚϴ���*/
}HashTable[HASHSIZE];

void CreateHash(HashTable ht, DataType items[], int n); //������ϣ��
int HashFunc(int key);//�����ϣ���� 
int Collision(int d);//����̽�ⷨ�����ͻ
int HashSearch(HashTable ht, DataType x);//��ϣ����
int HashInsert(HashTable ht, DataType x);//����
int HashDelete(HashTable ht, DataType x);//ɾ��
void DisplayHash(HashTable ht);//��ϣ�����ʾ
//21 25 31 84 27 66 -1
void main()
{
	int addr, i;
	DataType x;
	DataType  items[6];
	HashTable ht;
	printf("���6�������ϣ���е���");
	for (i = 0; i < 6; i++)
	{
		scanf("%d", &items[i]);
	}
	CreateHash(ht, items, 6);
	printf("������Ҫ���ҵ���");
	scanf("%d", &x);
	addr = HashSearch(ht, x);
	DisplayHash(ht);
	if (addr >= 0)
	{
		printf("\n����%d�Ƚϴ���:", x.key);
		printf("%d\n", ht[addr].times);
	}
	else
		printf("\n����%dʧ��\n:", x.key);
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
	/* ���������ؼ�������items������ϣ��nΪ�ؼ��ָ��� */
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
	addr = HashFunc(x.key);	/*��ù�ϣ��ַ*/
	while (ht[addr].data.key != NULL && ht[addr].data.key != x.key)
	{
		addr = Collision(addr);	/*û�ҵ��������ͻ*/
		times++;
	}
	if (ht[addr].data.key == x.key)
	{
		ht[addr].times = times;
		return addr; /*���ҳɹ�*/
	}
	else	return -addr; 		/*����ʧ��*/
}
int HashInsert(HashTable ht, DataType x)
{
	int addr;
	addr = HashSearch(ht, x);/*�ڹ�ϣ���в���*/
	if (addr > 0) return 0;	/*�ҵ����򲻱ز���*/
	ht[-addr].data = x;	/*û�ҵ��������*/
	ht[-addr].times = 1;
	return 1;
}
int HashDelete(HashTable ht, DataType x)
{
	int addr;
	addr = HashSearch(ht, x);	/*��������Ԫ��*/
	if (addr >= 0) { 		/*�ҵ��������ɾ�����*/
		ht[addr].data.key = DELFLAG;
		return 1;
	}
	return 0;
}
void DisplayHash(HashTable ht)
{
	int i;
	printf("\n��ϣ��\n��ϣ���ַ:\t");
	for (i = 0; i < HASHSIZE; i++)
		printf("%d\t", i);
	printf("\n�ؼ���:   \t");
	for (i = 0; i < HASHSIZE; i++)
		if (ht[i].data.key != NULL)
			printf("%d\t", ht[i].data.key);

		else
			printf("\t");
	printf("\n");
}
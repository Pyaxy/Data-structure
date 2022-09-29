//#include<stdio.h>
//#include<stdlib.h>
//
//
//#define ERROR 0
//#define OK 1
//
//typedef struct seqList
//{
//	int n;			// 顺序表长度
//	int maxLength;	// 最大长度
//	int* element;	// 指向顺序表存储空间的首地址
//}seqList;
//
//
//int Init(seqList* L, int mSize)	// 初始化
//{
//	L->maxLength = mSize;
//	L->n = 0;
//	L->element = (int*)malloc(sizeof(int) * mSize);	// 动态生成一维数组空间
//	if (!L->element)
//		return ERROR;
//	return OK;
//}
//
//int Find(seqList* L, int i, int* x)	// 查找
//{
//	if (i<0 || i>L->n - 1)			// 判断下标越界
//	{
//		return ERROR;
//	}
//	*x = L->element[i];				// x返回查找的值
//	return OK;
//}
//
//int Insert(seqList* L, int i, int x)	// 插入
//{
//	int j;
//	if (i<-1 || i>L->n - 1)			// 判断是否为有效索引
//	{
//		return ERROR;
//	}
//	if (L->n == L->maxLength)		// 判断是否存满
//	{
//		return ERROR;
//	}
//	for ( j = L->n-1; j > i; j--)	// 按顺序向后移
//	{
//		L->element[j + 1] = L->element[j];
//	}
//	L->element[i + 1] = x;
//	L->n += 1;
//	return OK;
//}
//
//int Delete(seqList* L, int i)		// 元素的删除
//{
//	if (i<0 || i>L->n - 1)					// 判断是否为有效索引
//	{
//		return ERROR;
//	}
//	if (!L->n)								// 判断是否为空
//		return ERROR;
//	for (int j = i + 1; j < L->n; j++)
//	{
//		L->element[j - 1] = L->element[j];	// 从前往后逐个前移元素
//	}
//	L->n--;
//	return OK;
//}
//
//int Output(seqList* L)		// 链表的输出
//{
//	int i;
//	if (L->n == 0)				// 判断是否为空
//		return ERROR;
//	for ( i = 0; i < L->n; i++)
//	{
//		printf("%d ", L->element[i]);	// 从前往后逐个输出元素
//	}
//	printf("\n");
//	return OK;
//}
//
//void Destory(seqList* L)	// 链表的撤销
//{
//	L->n = 0;
//	L->maxLength = 0;
//	free(L->element);
//}
//
//// 测试用主函数
//void main()
//{
//	int i;
//	seqList list;
//	Init(&list, 10);
//	for (i = 0; i < 10; i++)
//		Insert(&list, i - 1, i);
//	Output(&list);
//	Delete(&list, 0);
//	Output(&list);
//	Destory(&list);
//}
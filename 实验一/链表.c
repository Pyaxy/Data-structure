//#include<stdio.h>
//#include<stdlib.h>
//
//#define ERROR 0;
//#define OK 1;
//
//typedef struct node
//{
//	int element;		// 数据域
//	struct node* link;	// 指针域
//}Node;
//
//typedef struct hearderList
//{
//	Node* head;			// 头指针
//	int n;				// 元素个数
//}hearderList;
//
//int Init(hearderList* L)	// 初始化
//{
//	L->head = (Node*)malloc(sizeof(Node));	// 生成表头结点
//	if (!L->head)
//		return ERROR;
//	L->head->link= NULL;
//	L->n = 0;
//	return OK;
//}
//
//int Find(hearderList L, int i, int* x)	//查找
//{
//	Node* p;
//	int j;
//	if (i<0||i>L.n-1)					// 是否为合法位置
//	{
//		return ERROR;
//	}
//	p = L.head;
//	for ( j = 0; j < i; j++)			//定位查找的元素
//	{
//		p = p->link;
//	}
//	*x = p->element;					// 赋值
//	return OK;
//}
//
//int Insert(hearderList* L, int i, int x)	// 插入
//{
//	Node* p, * q;
//	int j;
//	if (i<-1 || i>L->n - 1)					//判断合法位置
//		return ERROR;
//	p = L->head;
//	for ( j = 0; j <= i; j++)
//	{
//		p = p->link;
//	}
//	q = (Node*)malloc(sizeof(Node));		//申请空间
//	q->element = x;
//	q->link = p->link;
//	p->link = q;
//	L->n++;
//	return OK;
//}
//
//int Delete(hearderList* L, int i)	// 删除
//{
//	int j;
//	Node* p, * q;
//	if (!L->n)					// 判断为空
//		return ERROR;
//	if (i<0||i>L->n-1)			// 判断合法
//	{
//		return ERROR;
//	}
//	q = L->head;
//	for ( j = 0; j < i-1; j++)	// 定位删除的前一位
//	{
//		q = q->link;
//	}
//	p = q->link;
//	q->link = p->link;
//	free(p);
//	L->n--;
//	return OK;
//}
//
//int Output(hearderList* L)	// 输出链表
//{
//	Node* p;
//	if (!L->n)				// 判断为空
//		return ERROR;
//	p = L->head->link;
//	while (p)
//	{
//		printf("%d ", p->element);
//		p = p->link;
//	}
//	return OK;
//}
//
//void Destory(hearderList* L)	// 撤销链表
//{
//	Node* p;
//	while (L->head)				// 循环撤销链表
//	{
//		p = L->head->link;		// 保存后继结点地址
//		free(L->head);
//		L->head = p;
//	}
//}
//
//int Revert(hearderList* L)	// 逆置
//{
//	if (!L->n)				// 判断为空
//		return ERROR;
//	Node* pre, *cur, *temp;	// 设置三个记录点
//	pre= L->head->link;		// 初始化三个记录点
//	cur = pre->link;
//	temp = cur->link;
//	pre->link = NULL;
//	while (temp)			// 当遍历一遍后完成逆置
//	{
//		cur->link = pre;	// 逆置前两个记录点
//		pre = cur;			// 继续后移
//		cur = temp;
//		temp = temp->link;
//	}
//	cur->link = pre;
//	L->head->link = cur;	// 重置头节点
//	return OK;
//}
//
//int Sort(hearderList* L)	// 排序链表，此处采用冒泡排序
//{
//	if (!L->n)				// 判断为空
//		return ERROR;
//	int temp;				// 交换用的temp
//	int judgeEnd = 1;		// 判断是否完成排序
//	
//	while (judgeEnd)		// 如果在一次遍历中没有发生交换，则judgeEnd=0，结束遍历，完成排序
//	{
//		Node* p = L->head->link;
//		Node* q = p->link;
//		judgeEnd = 0;		// 开始遍历时设为0
//		while (q)
//		{
//			if (p->element > q->element)	// 冒泡排序
//			{
//				temp = p->element;
//				p->element = q->element;
//				q->element = temp;
//				judgeEnd = 1;	// 如果在一次遍历中发生了交换，说明没有完成排序，judgeEnd=1继续遍历
//			}
//			p = p->link;
//			q = q->link;
//		}
//	}
//	return OK;
//}
//
//// 测试用主函数
//void main()
//{
//	int i;
//	int x;
//	hearderList list;
//	Init(&list);
//	for ( i = 0; i < 9; i++)
//	{
//		Insert(&list, i-1, i);
//	}
//	printf("the linklist is:");
//	Output(&list);
//	printf("\nthe revert linklist is:");
//	Revert(&list);
//	Output(&list);
//	printf("\nthe sorted linklist is:");
//	Sort(&list);
//	Output(&list);
//	Delete(&list, 0);
//	printf("\nthe linklist is:");
//	Output(&list);
//	Find(list, 1, &x);
//	printf("\nthe value is:");
//	printf("%d", x);
//	Destory(&list);
//}
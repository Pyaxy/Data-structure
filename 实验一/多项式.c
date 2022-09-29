#include<stdio.h>
#include<stdlib.h>

typedef struct pNode							// 多项式项
{
	int coef;									// 系数
	int exp;									// 指数
	struct pNode* link;
}PNode;

typedef struct polynominal						// 多项式
{
	PNode* head;								// 指向第一项
}Polynominal;

void Create(Polynominal* p)
{
	PNode* pn, * pre, * q;	
	p->head = (PNode*)malloc(sizeof(PNode));	// 初始化表头
	p->head->exp = -1;
	p->head->link = p->head;
	while(1)	// 创建链表
	{
		pn = (PNode*)malloc(sizeof(PNode));		// 申请空间
		printf("coef:\n");
		scanf_s("%d", &pn->coef);				// 输入系数
		printf("exp:\n");
		scanf_s("%d", &pn->exp);				// 输入指数
		if (pn->exp < 0)						// 当指数为0时停止输入
			break;
		pre = p->head;
		q = p->head->link;
		while (q&&q->exp>pn->exp)				// 按照降幂排列
		{
			pre = q;
			q = q->link;
		}
		pn->link = q;							// 插入结点
		pre->link = pn;
	}
}

void Output(Polynominal* p)							// 输出多项式
{
	PNode* temp = p->head->link;
	while (temp->exp>=0)
	{
		printf("%dx^%d", temp->coef, temp->exp);	// 循环输出
		printf("+");
		temp = temp->link;
	}
	// 控制格式
	printf("\b ");
	printf("\n");
}

void Add(Polynominal* px, Polynominal* qx)			// 多项式相加
{
	PNode* q, * q1 = qx->head, * p, * p1, * temp;	// q1指向表头结点
	p = px->head->link;								// p指向多项式px的第一个结点
	q = q1->link;									// q1是q的前驱
	while (p->exp>=0)
	{
		while (p->exp < q->exp)						// 跳过q->exp大的项
		{
			q1 = q;
			q = q->link;
		}
		if (p->exp==q->exp)							// 当指数相等时，系数相加
		{
			q->coef = q->coef + p->coef;
			if (q->coef == 0)						// 若相加后系数为0
			{
				q1->link = q->link;					// 删除q
				free(p);							// 释放空间
				q = q1->link;						// 重置指针
				p = p->link;
			}
			else									// 若相加后不为0
			{
				q1 = q;								// q1后移
				q = q->link;
				p = p->link;
			}
		}
		else // p->epx > q->exp 的情况
		{
			temp = (PNode*)malloc(sizeof(PNode));	// 生成新结点
			temp->coef = p->coef;
			temp->exp = p->exp;
			temp->link = q1->link;
			q1->link = temp;
			q1 = q1->link;
			p = p->link;
		}
	}
}

Polynominal* Time(Polynominal* px, Polynominal* qx)		// 多项式乘法
{
	PNode* p = px->head->link, * q = qx->head->link;	// 初始化参数指向两个多项式
	PNode* pn, * pre, * cur;
	Polynominal* result = (Polynominal*)malloc(sizeof(Polynominal));	// 新建一个多项式链表来储存结果
	result->head= (PNode*)malloc(sizeof(PNode));		// 初始化新链表
	result->head->exp = -1;
	result->head->link = result->head;
	while (p->exp>=0)							// 遍历第一个多项式
	{
		while (q->exp>=0)						// 遍历第二个多项式
		{
			pn = (PNode*)malloc(sizeof(PNode));	// 申请新的结点
			pn->coef = p->coef * q->coef;		// 新结点的系数为遍历中的两个多项式的项的系数之和
			pn->exp = p->exp + q->exp;			// 同理计算指数
			// 按降幂插入链表
			pre = result->head;
			cur = result->head->link;
			while (cur && cur->exp > pn->exp)
			{
				pre = cur;
				cur = cur->link;
			}
			pn->link = cur;
			pre->link = pn;
			// 继续遍历
			q = q->link;
		}
		q = qx->head->link;
		p = p->link;

	}
	return result;	// 返回结果
}

void main()
{
	Polynominal pn_1;
	Polynominal pn_2;
	Create(&pn_1);
	Output(&pn_1);
	Create(&pn_2);
	Output(&pn_2);
	printf("The time result is:");
	Output(Time(&pn_1, &pn_2));
}
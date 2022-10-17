#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;		// 设定元素为char类型
typedef struct bnode		// 结点结构体定义
{
	ElemType element;		// 结点数据
	struct bnode* lChild;	// 左孩子
	struct bnode* rChild;	// 右孩子
}BTNode;

typedef struct binarytree	// 二叉树定义
{
	BTNode* root;			// 根结点
}BinaryTree;
typedef struct priorityQueue
{
	BTNode *elements;		// 优先权队列数据
	int n;					// 当前长度
	int maxSize;			// 最大长度
}PriorityQueue;

/////////////////////////////////////////////////////////////////////////////


void Create(BinaryTree* bt)	// 创建二叉树
{
	bt->root = NULL;		// 设为空
}

BTNode* NewNode(ElemType x, BTNode* ln, BTNode* rn)	// 新建结点
{
	BTNode* p = (BTNode*)malloc(sizeof(BTNode));	// 申请内存空间
	p->element = x;									// 设置结点元素
	p->lChild = ln;									// 设置结点左孩子
	p->rChild = rn;									// 设置结点右孩子
	return p;
}

int Root(BinaryTree* bt, ElemType* x)				// 获得二叉树根节点的数值
{
	if (bt->root)									// 如果根节点存在
	{
		x = &bt->root->element;						// 赋值
		return 1;									// 成功
	}
	else
	{
		return 0;									// 失败
	}
}

// 创建树
void MakeTree(BinaryTree* bt, ElemType e, BinaryTree* left, BinaryTree* right)
{
	
	if (left ==NULL && right == NULL)
	{
		BTNode* p = (BTNode*)malloc(sizeof(BTNode));
		p->element = e;
		p->lChild = NULL;
		p->rChild = NULL;
		bt->root = p;
		return;
	}
	bt->root = NewNode(e, left->root, right->root);
}
void Clear(BTNode* t)								// 递归清除结点
{
	if (!t)
		return;
	Clear(t->lChild);
	Clear(t->rChild);
	free(t);
}

void TreeClear(BinaryTree* bt)						// 删除树
{
	Clear(bt->root);
}
/////////////////////////////////////////////////////////////////////////////
BTNode* PreCreateBT(BTNode* t)						// 先序创建二叉树
{
	ElemType ch;
	scanf_s("%d", &ch);
	if (ch == -1)									// 输入 # 表示子树为空
		t = NULL;
	else
	{
		t = (BTNode*)malloc(sizeof(BTNode));
		t->element = ch;
		t->lChild = PreCreateBT(t->lChild);			// 递归
		t->rChild = PreCreateBT(t->rChild);			// 递归
	}
	return t;
}
void PreMakeTree(BinaryTree* bt)
{
	bt->root = PreCreateBT(bt->root);
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
void PreOrder(BTNode *t)							// 先序遍历
{
	if (!t)											// 如果为空直接返回
		return;
	printf("%d ", t->element);				// 先序遍历先访问根节点的值
	PreOrder(t->lChild);							// 递归
	PreOrder(t->rChild);							// 递归
}
void PreOrderTree(BinaryTree* bt)
{
	PreOrder(bt->root);
	printf("\n");
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
void MidOrder(BTNode* t)							// 中序遍历
{
	if (!t)											// 如果为空直接返回
		return;
	MidOrder(t->lChild);
	printf("%d ", t->element);				// 中间访问根节点
	MidOrder(t->rChild);
}
void MidOrderTree(BinaryTree* t)
{
	MidOrder(t->root);
	printf("\n");
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
void LastOrder(BTNode* t)							// 后序遍历
{
	if (!t)											// 如果为空直接返回
		return;
	LastOrder(t->lChild);
	LastOrder(t->rChild);
	printf("%d ", t->element);				// 最后访问根节点
}
void LastOrderTree(BinaryTree* bt)
{
	LastOrder(bt->root);
	printf("\n");
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
int Size(BTNode* t)									// 求二叉树结点个数
{
	if (!t)
		return 0;
	return Size(t->lChild) + Size(t->rChild) + 1;	// 递归
}
int TreeSize(BinaryTree* bt)
{
	return Size(bt->root);
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
int lSize(BTNode* t)								// 求叶子结点数量
{
	if (t->lChild==NULL && t->rChild==NULL)			// 判断是否为叶子结点
		return 1;
	return lSize(t->lChild) + lSize(t->rChild);		// 递归
}
int LeafSize(BinaryTree* bt)
{
	return lSize(bt->root);
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
int GetHeight(BTNode* t)							// 求二叉树的高度
{
	int len1, len2;
	if (!t)
		return 0;
	len1 = GetHeight(t->lChild);					// 遍历二叉树获得最高的高度
	len2 = GetHeight(t->rChild);
	return len1 > len2 ? len1 + 1 : len2 + 1;
}
int TreeHeight(BinaryTree* bt)
{
	return GetHeight(bt->root);
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
void Exchange(BTNode* t)							// 交换所有子树
{
	if (!t)
		return;
	Exchange(t->lChild);							// 先从深处交换
	Exchange(t->rChild);
	if (t->lChild || t->rChild)						// 交换结点
	{
		BTNode *temp;
		temp = t->lChild;
		t->lChild = t->rChild;
		t->rChild = temp;
	}
}
void ExchangeTree(BinaryTree* bt)
{
	Exchange(bt->root);
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// 向下调整
void AdjustDown(BTNode heap[], int current, int border)
{
	int p = current;
	int minChild;
	BTNode temp;
	while (2 *p+1<=border)							// 若p不是叶结点，则执行调整
	{
		if ((2 * p + 2 <= border) && (heap[2 * p + 1].element > heap[2 * p + 2].element))
		{
			minChild = 2 * p + 2;					// 右孩子存在，且较小，则minChild指向p的右孩子
		}
		else
		{
			minChild = 2 * p + 1;					// 右孩子不存在，或较大，则minChild指向p的左孩子
		}
		if (heap[p].element <= heap[minChild].element)
		{
			break;
		}
		else										// p与最小孩子交换
		{
			temp = heap[p];
			heap[p] = heap[minChild];
			heap[minChild] = temp;
			p = minChild;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// 向上调整
void AdjustUp(BTNode heap[], int current)
{
	int p = current;
	BTNode temp;
	while (p>0)
	{
		if (heap[p].element < heap[(p - 1) >> 1].element)	// 若p指向的元素小于其双亲结点，则与双亲结点交换
		{
			temp = heap[p];
			heap[p] = heap[(p - 1) >> 1];
			heap[(p - 1) >> 1] = temp;
			p = (p - 1) >> 1;						// 若p指向的元素不小于其双亲结点，则调整完毕
		}
		else
		{
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// 创建一个空的优先权队列
void CreatePQ(PriorityQueue* PQ, int mSize)
{
	PQ->maxSize = mSize;
	PQ->n = 0;
	PQ->elements = (BTNode*)malloc(mSize * sizeof(BTNode));
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// 判断优先权队列是否为空
int IsEmpty(PriorityQueue* PQ)
{
	if (PQ->n == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// 判断优先权队列是否为满
int IsFull(PriorityQueue* PQ)
{
	if (PQ->n == PQ->maxSize)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// 在优先权队列中添加一个新元素x
void Append(PriorityQueue* PQ, BTNode x)
{
	if(IsFull(PQ)) return;
	PQ->elements[PQ->n] = x;
	PQ->n++;
	AdjustUp(PQ->elements, PQ->n - 1);
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// 取出优先级最高的元素并返回，并且在优先权列表中删除该元素
BTNode Serve(PriorityQueue* PQ)
{
	if (IsEmpty(PQ)) return;
	BTNode x = PQ->elements[0];
	PQ->n--;
	PQ->elements[0] = PQ->elements[PQ->n];
	AdjustDown(PQ->elements, 0, PQ->n - 1);
	return x;
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// 构建哈夫曼树
BinaryTree CreateHFMTree(int w[], int m)
{
	PriorityQueue PQ;							// 定义优先权队列
	BinaryTree x, y, z;							// x, y, z为二叉树变量
	CreatePQ(&PQ, m);							// 初始化优先权队列
	for (int i = 0; i < m; i++)
	{
		MakeTree(&x, w[i], NULL, NULL);			// 创建仅包含根节点的二叉树
		Append(&PQ, *x.root);					// 将根节点添加到优先权队列中
	}
	while (PQ.n > 1)
	{
		MakeTree(&x, 0, NULL, NULL);			// 初始化x, y
		MakeTree(&y, 0, NULL, NULL);
		*x.root = Serve(&PQ);					// 从PQ中取出优先权最大的结点
		*y.root = Serve(&PQ);					// 从PQ中取出剩下的权重中优先权最大的结点

		// 合并二叉树x, y 并保证左子树小于右子树
		if (x.root->element < y.root->element)
		{
			MakeTree(&z, x.root->element + y.root->element, &x, &y);
		}
		else
		{
			MakeTree(&z, x.root->element + y.root->element, &y, &x);
		}
		Append(&PQ, *z.root);					// 将合成的新二叉树插入优先权队列
		z.root = NULL;
		x.root = NULL;
		y.root = NULL;
	}
	MakeTree(&x, 0, NULL, NULL);
	*x.root = Serve(&PQ);						// 取出最后的二叉树
	return x;
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// 打印编码的权值
void printCode(BinaryTree* bt)
{
	char ch;
	BTNode *p = bt->root;
	while (ch = getchar())								// 获得编码
	{
		if (ch == '0')									// 如果为0则走左子树
		{
			p = p->lChild;
			if (p->lChild == NULL && p->rChild == NULL)	// 当为叶节点时打印出权值
			{
				printf("%d ", p->element);
				p = bt->root;
			}
		}
		else											// 当为1则走右子树
		{
			p = p->rChild;
			if (p->lChild == NULL && p->rChild == NULL)
			{
				printf("%d ", p->element);
				p = bt->root;
			}
		}
	}
}

void main()
{
	BinaryTree c;
	printf("先序创建二叉树：");
	PreMakeTree(&c);
	printf("先序遍历");
	PreOrderTree(&c);
	printf("中序遍历");
	MidOrderTree(&c);
	printf("后序遍历");
	LastOrderTree(&c);
	printf("结点个数：%d\n", TreeSize(&c));
	printf("叶节点个数：%d\n", LeafSize(&c));
	printf("树的高度：%d\n", TreeHeight(&c));
	ExchangeTree(&c);
	printf("交换二叉树：");
	PreOrderTree(&c);
	int a[4] = { 6,4,2,3 };		// 权值组合
	c = CreateHFMTree(a, 4);
	printf("请输入编码：");
	printCode(&c);
}
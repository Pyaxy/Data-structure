#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;		// 设定元素为char类型
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
	if (bt->root || left == right)
	{
		return;
	}
	bt->root = NewNode(e, left->root, right->root);
	left->root = right->root = NULL;
}

/////////////////////////////////////////////////////////////////////////////
BTNode* PreCreateBT(BTNode* t)						// 先序创建二叉树
{
	ElemType ch;
	ch = getchar();
	if (ch == '#')									// 输入 # 表示子树为空
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
	printf("%c ", t->element);				// 先序遍历先访问根节点的值
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
	printf("%c ", t->element);				// 中间访问根节点
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
	printf("%c ", t->element);				// 最后访问根节点
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
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 构造结点的结构体
typedef struct BiTNode {
    int data;               // 数据域
	struct BiTNode* lChild; // 左孩子指针
	struct BiTNode* rChild; // 右孩子指针
}BiNode;

// 初始化树的函数 1 2 3 4 5 6 7
void CreateBiTree(BiNode* T) {
	T->data = 1; // 第一层

	T->lChild = malloc(sizeof(BiNode));
	T->lChild->data = 2;
	T->rChild = malloc(sizeof(BiNode));
	T->rChild->data = 3; // 第二层

	T->lChild->lChild = malloc(sizeof(BiNode));
	T->lChild->lChild->data = 4;
	T->lChild->lChild->lChild = NULL;
	T->lChild->lChild->rChild = NULL;
	T->lChild->rChild = malloc(sizeof(BiNode));
	T->lChild->rChild->data = 5;
	//T->lChild->rChild->lChild = NULL;
	T->lChild->rChild->rChild = NULL; // 第三层左子树

	T->lChild->rChild->lChild = malloc(sizeof(BiNode));
	T->lChild->rChild->lChild->data = 6;
	T->lChild->rChild->lChild->lChild = NULL;
	T->lChild->rChild->lChild->rChild = NULL;
	
	T->rChild->lChild = NULL;
	//T->rChild->lChild = malloc(sizeof(BiNode));
	//T->rChild->lChild->data = 6;
	//T->rChild->lChild->lChild = NULL;
	//T->rChild->lChild->rChild = NULL;
	T->rChild->rChild = NULL;
	//T->rChild->rChild = malloc(sizeof(BiNode));
	//T->rChild->rChild->data = 7;
	//T->rChild->rChild->lChild = NULL;
	//T->rChild->rChild->rChild = NULL; // 第三层右子树
}

#if 0 // 递归算法
// 先序遍历的递归算法 根左右
void PerOrderTravserse(BiNode* T) {
	if (T)
	{
		printf("%d ", T->data);       // 打印结点数据
		PerOrderTravserse(T->lChild); // 遍历左孩子
		PerOrderTravserse(T->rChild); // 遍历右孩子
	}
}

// 中序遍历的递归算法 左根右
void InOrderTravserse(BiNode* T) {
	if (T)
	{
		InOrderTravserse(T->lChild);  // 遍历左孩子
		printf("%d ", T->data);       // 打印结点数据
		InOrderTravserse(T->rChild);  // 遍历右孩子
	}
}

// 后序遍历的递归算法 左右根
void PostOrderTraverse(BiNode* T) {
	if (T) {
		PostOrderTraverse(T->lChild); // 遍历左孩子
		PostOrderTraverse(T->rChild); // 遍历右孩子
		printf("%d ", T->data);       // 打印结点数据
	}
}

// 计算二叉树的深度
int Depth(BiNode* T) {
	if (!T)
		return 0;
	else
	{
		int m = Depth(T->lChild);
		int n = Depth(T->rChild);
		if (m > n)
			return m + 1;
		else
			return n + 1;
	}
}

#endif

#if 1 // 迭代算法
// 先序遍历的迭代算法 根左右
void PerOrderTravserse(BiNode* root) {
	BiNode* stack[1000];  // 生成顺序栈
	BiNode** top = stack; // 栈顶指针指向数组

	*top = root;
	top++; // 根节点入栈
	while (stack != top) { // 栈非空
		BiNode* node = *(top - 1);
		top--; // 取出栈顶元素
		printf("%d ", node->data); // 打印结点值
		if (node->rChild)          // 右孩子入栈
		{
			*top = node->rChild;
			top++;
		}
		if (node->lChild)          // 左孩子入栈
		{
			*top = node->lChild;
			top++;
		}
	}
}

// 中序遍历的迭代算法 左根右
void InOrderTravserse(BiNode* root) {
	BiNode* stack[1000];  // 生成顺序栈
	BiNode** top = stack; // 栈顶指针指向数组

	*top = root;
	top++; // 根结点入栈
	while (stack!=top) // 栈非空
	{
		BiNode* node = *(top - 1);
		if (node->lChild) // 左孩子入栈
		{
			*top = node->lChild;
			top++;
		}
		else
		{
			top--; // 取出栈顶元素
			printf("%d ", node->data); // 打印结点值
			
			if (node->rChild)          // 右孩子入栈
			{
				*top = node->rChild;
				top++;
			}
		}
	}
}

// 后序遍历的迭代算法 左右根
void PostOrderTraverse(BiNode* root) {
	BiNode* stack[1000];  // 生成顺序栈
	BiNode** top = stack; // 栈顶指针指向数组
	BiNode* t = root;     // 指向根节点
	BiNode* last = t;     // 指向t结点

	while (stack != top || t) {
		while (t)
		{
			*top = t;
			top++; // 结点入栈
			t = t->lChild; // 寻找到最左孩子
		}
		t = *(top - 1);
		top--; // 结点出栈
		if (!t->rChild || t->rChild == last) {
			printf("%d ", t->data);
			last = t;  // 记录当前访问过的节点
			t = NULL;
		}
		else {
			*top = t;
			top++;           // 否则将当前节点重新入栈
			t = t->rChild;   // 转而前往其右子树
		}
	}
}

// 层序遍历的迭代算法
void LevelOrder(BiNode* T) {
	BiNode* queue[1000];    // 创建队列
	BiNode** front = queue; // 创建对头指针
	BiNode** rear = front;  // 创建队尾指针

	*rear = T;              
	rear++;                // 根节点入队
	while (front!=rear) {  // 队列非空
		BiNode* node = *front;
		front++;
		printf("%d ", node->data); // 打印非空结点值
		if (node->lChild) // 若存在左孩子则左孩子入队
		{
			*rear = node->lChild;
			rear++;
		}
		if (node->rChild)// 若存在右孩子则右孩子入队
		{
			*rear = node->rChild;
			rear++;
		}
	}
}

// 计算二叉树的深度
int Depth(BiNode* T) {
	BiNode* queue[1000];    // 创建队列
	BiNode** front = queue; // 创建对头指针
	BiNode** rear = front;  // 创建队尾指针

	int length = 0;
	bool index = true;
	*rear = T;
	rear++;                  // 根节点入队
	while (front != rear) {  // 队列非空
		BiNode* node = *front;
		front++;
		if (node->lChild) // 若存在左孩子则左孩子入队
		{
			*rear = node->lChild;
			rear++;
			if (index)
			{
				length++; // 存在左孩子长度加1
				index = false;
			}
		}
		if (node->rChild) // 若存在右孩子则右孩子入队
		{
			*rear = node->rChild;
			rear++;
			if (index)
			{
				length++;
				index = false; // 防止重复计算同一层左右孩子高度
			}
		}
		index = true;
	}
	return length + 1;
}

// 求满二叉树（输入：完全二叉树的层序遍历 1，2，3，4，5 输出：二叉树）

#endif

int main() {
	BiNode* tree = malloc(sizeof(BiNode));
	CreateBiTree(tree);

	printf("先序遍历二叉树为: ");
	PerOrderTravserse(tree);
	printf("\n");

	printf("中序遍历二叉树为: ");
	InOrderTravserse(tree);
	printf("\n");

	printf("后序遍历二叉树为: ");
	PostOrderTraverse(tree);
	printf("\n");

	printf("层序遍历二叉树为: ");
	LevelOrder(tree);
	printf("\n");

	printf("二叉树高度为: %d\n", Depth(tree));

	return 0;
}

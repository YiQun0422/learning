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
	T->data = 1;
	T->lChild = malloc(sizeof(BiNode));
	T->rChild = malloc(sizeof(BiNode));
	T->lChild->data = 2;
	T->lChild->lChild = malloc(sizeof(BiNode));
	T->lChild->rChild = malloc(sizeof(BiNode));
	T->lChild->rChild->data = 5;
	T->lChild->rChild->lChild = NULL;
	T->lChild->rChild->rChild = NULL;
	T->rChild->data = 3;
	T->rChild->lChild = malloc(sizeof(BiNode));
	T->rChild->lChild->data = 6;
	T->rChild->lChild->lChild = NULL;
	T->rChild->lChild->rChild = NULL;
	T->rChild->rChild = malloc(sizeof(BiNode));
	T->rChild->rChild->data = 7;
	T->rChild->rChild->lChild = NULL;
	T->rChild->rChild->rChild = NULL;
	T->lChild->lChild->data = 4;
	T->lChild->lChild->lChild = NULL;
	T->lChild->lChild->rChild = NULL;
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

	*top = root; // push(root) 根节点入栈?
	top++;
	while (stack != top) { // 若栈非空?
		BiNode* node = *(top - 1); // 取出栈顶元素
		top--;
		if(node!=NULL)
			printf("%d ", node->data); // 打印结点值
		else
			continue;
		*top = node->rChild; // 右孩子入栈
		top++;
		*top = node->lChild; // 左孩子入栈
		top++;
	}
}

// 中序遍历的迭代算法 左根右
void InOrderTravserse(BiNode* T) {
	BiNode* stack[1000];
	BiNode** top = stack;
	BiNode* p = T;

	while (stack != top||p) {
		if (p)
		{
			*top = p;
			top++;
			p = p->lChild;
		}
		else {
			BiNode* q = *(top - 1);
			top--;
 			printf("%d ", q->data);
			p = q->rChild;
		}
	}
}

// 后序遍历的迭代算法 左右根
void PostOrderTraverse(BiNode* T) {
	BiNode* stack[1000];
	BiNode** top = stack;
	BiNode* t = T;
	BiNode* last = t;

	while (stack != top||t) {
		while (t)
		{
			*top = t;
			top++; 
			t = t->lChild;
		}
		t = *(top - 1);
		top--;
		if (!t->rChild || t->rChild == last) {
			printf("%d ", t->data);
			last = t;
			t = NULL;
		}
		else {
			*top = t;
			top++;
			t = t->rChild;

		}
	}
}

// 层序遍历的迭代算法
void LevelOrder(BiNode* T) {
	BiNode* queue[1000];    // 创建队列
	BiNode** front = queue; // 创建对头指针
	BiNode** rear = front;  // 创建队尾指针
	BiNode* t = T;          // 使t指向T

	*rear = t;              
	rear++;                // 根节点入队
	while (front!=rear||t) {        // 队列非空
		BiNode* node = *front;
		front++;
		printf("%d ", node->data);
		

		if (node->lChild)
			*rear = node->lChild;
			rear++;
		if (node->rChild)
			*rear = node->rChild;
			rear++;
}
}

// 计算二叉树的深度
int Depth(BiNode* T) {
	return 3;
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

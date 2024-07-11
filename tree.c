#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 1.实现 四种遍历方式 求二叉树高度 迭代
// 2.求满二叉树（输入：完全二叉树的层序遍历 1，2，3，4，5 输出：二叉树）一个
#define MAXSIZE 1000

//构造结点的结构体
typedef struct BiTNode {
    int data;//数据域
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

#if 1 // 递归算法
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

//后序遍历
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

#if 0 // 迭代算法
void InOrderTravserse(BiNode* T) {

}

// 中序遍历的递归算法 左根右
void InOrderTravserse(BiNode* T) {

}

// 后序遍历的递归算法 左右根
void InOrderTravserse(BiNode* T) {

}

// 计算二叉树的深度
int Depth(BiNode* T) {

}


#endif

void a() {
	int stack[1000];
	int* top = stack;

	int value = 1;

}

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

	printf("二叉树高度为: %d\n", Depth(tree));

	return 0;
}
